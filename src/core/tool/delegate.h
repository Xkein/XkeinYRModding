#pragma once

#include "core/reflection/reflection.h"
#include "runtime/platform/platform.h"
#include <entt/signal/sigh.hpp>
#include <functional>
#include <variant>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <vector>
#include <utility>
#include <type_traits>

/**
 * FDelegateHandle — Opaque handle for delegate registration.
 * Uses static atomic counter for globally unique IDs.
 * Id = 0 represents an invalid/unset handle.
 */
struct FDelegateHandle
{
    uint64 Id = 0;

    bool   IsValid() const { return Id != 0; }
    void   Reset() { Id = 0; }
    bool   operator==(const FDelegateHandle& Other) const { return Id == Other.Id; }
    bool   operator!=(const FDelegateHandle& Other) const { return Id != Other.Id; }
    bool   operator<(const FDelegateHandle& Other) const { return Id < Other.Id; }

    static FDelegateHandle GenerateNew()
    {
        static std::atomic<uint64> Counter{1};
        return FDelegateHandle{Counter++};
    }
};

namespace std {
    template<>
    struct hash<FDelegateHandle> {
        size_t operator()(const FDelegateHandle& handle) const noexcept {
            return static_cast<size_t>(handle.Id);
        }
    };
}

// ─── Policy tag structs ────────────────────────────────────────────────────

struct FNotThreadSafeDelegateMode {};
struct FThreadSafeDelegateMode {};

// ─── TDelegate — single-cast delegate ──────────────────────────────────────

template<typename TFunc>
class TDelegate;

/**
 * TDelegate<Ret(Args...)>
 *
 * Single-cast delegate supporting three binding modes:
 *   BindStatic<&Func>(args...)       → entt::delegate (zero-overhead, compile-time)
 *   BindRaw<&Method>(obj)            → entt::delegate (zero-overhead, compile-time)
 *   BindLambda(func)                 → std::function  (capturing lambdas)
 */
template<typename Ret, typename... Args>
class TDelegate<Ret(Args...)>
{
    using entt_delegate_t = entt::delegate<Ret(Args...)>;
    using std_function_t  = std::function<Ret(Args...)>;
    using storage_t       = std::variant<std::monostate, entt_delegate_t, std_function_t>;

    storage_t m_storage;

public:
    TDelegate() = default;
    TDelegate(const TDelegate&) = default;
    TDelegate(TDelegate&&) noexcept = default;
    TDelegate& operator=(const TDelegate&) = default;
    TDelegate& operator=(TDelegate&&) noexcept = default;

    /** Bind a free function or unbound member at compile time (entt::delegate). */
    template<auto Candidate, typename... BindArgs>
    void BindStatic(BindArgs&&... args)
    {
        entt_delegate_t del;
        del.template connect<Candidate>(std::forward<BindArgs>(args)...);
        m_storage = std::move(del);
    }

    /** Bind a member function with object pointer at compile time (entt::delegate). */
    template<auto Method, typename Type>
    void BindRaw(Type* obj)
    {
        entt_delegate_t del;
        del.template connect<Method>(obj);
        m_storage = std::move(del);
    }

    /** Bind a capturing lambda (std::function). */
    template<typename Func>
    void BindLambda(Func&& func)
    {
        m_storage = std_function_t(std::forward<Func>(func));
    }

    /** Invoke the delegate. Asserts if unbound (matching entt::delegate behavior). */
    Ret Execute(Args... args) const
    {
        ENTT_ASSERT(IsBound(), "Uninitialized TDelegate");

        if (auto* enttDel = std::get_if<entt_delegate_t>(&m_storage))
        {
            if constexpr (std::is_void_v<Ret>)
            {
                (*enttDel)(std::forward<Args>(args)...);
                return;
            }
            else
            {
                return (*enttDel)(std::forward<Args>(args)...);
            }
        }

        if (auto* func = std::get_if<std_function_t>(&m_storage))
        {
            if constexpr (std::is_void_v<Ret>)
            {
                (*func)(std::forward<Args>(args)...);
                return;
            }
            else
            {
                return (*func)(std::forward<Args>(args)...);
            }
        }

        // Unreachable (we asserted IsBound above)
        if constexpr (!std::is_void_v<Ret>)
        {
            return Ret{};
        }
    }

    /** Invoke only if bound. Available only for void return type. */
    template<typename R = Ret, std::enable_if_t<std::is_void_v<R>, int> = 0>
    bool ExecuteIfBound(Args... args)
    {
        if (!IsBound())
        {
            return false;
        }
        Execute(std::forward<Args>(args)...);
        return true;
    }

    /** True if a function or lambda is bound. */
    [[nodiscard]] bool IsBound() const
    {
        return m_storage.index() != 0;
    }

    /** Reset to unbound state. */
    void Unbind()
    {
        m_storage = std::monostate{};
    }
};

// ─── Registration wrappers (forward declarations) ──────────────────────────

template<typename TFunc, typename TPolicy = FNotThreadSafeDelegateMode>
class TMulticastDelegateRegistration;

template<typename TFunc>
class TDelegateRegistration;

// ─── TMulticastDelegate — multicast delegate ───────────────────────────────

template<typename TFunc, typename TPolicy = FNotThreadSafeDelegateMode>
class TMulticastDelegate;

/**
 * TMulticastDelegate<Ret(Args...), TPolicy>
 *
 * Multicast delegate backed by entt::sigh for compile-time-bound listeners,
 * with a side-channel vector for capturing lambdas.
 *
 * TPolicy controls thread safety:
 *   FNotThreadSafeDelegateMode (default) — zero-overhead, no locking
 *   FThreadSafeDelegateMode              — all operations guarded by std::mutex
 *
 * static_assert: Ret must be void (multicast delegates cannot return values).
 */
template<typename Ret, typename... Args, typename TPolicy>
class TMulticastDelegate<Ret(Args...), TPolicy>
{
    static_assert(std::is_void_v<Ret>, "TMulticastDelegate requires void return type");

    using signal_t = entt::sigh<Ret(Args...)>;
    using sink_t   = entt::sink<signal_t>;

    /** Per-connection bookkeeping. */
    struct FConnectionEntry
    {
        entt::connection connection;
        const void*      instance = nullptr; // nullptr for free functions
    };

    signal_t                                                    m_signal;
    std::unordered_map<FDelegateHandle, FConnectionEntry>       m_connections;
    std::vector<std::pair<FDelegateHandle, std::function<Ret(Args...)>>> m_lambdaListeners;
    std::atomic<uint64>                                         m_nextHandle{1};
    mutable std::mutex                                          m_mutex;

    /** Generate a unique handle from the instance-local counter. */
    FDelegateHandle GenerateNextHandle()
    {
        return FDelegateHandle{m_nextHandle++};
    }

    /** RAII lock — only acquires for FThreadSafeDelegateMode. */
    [[nodiscard]] auto GetScopedLock() const
    {
        if constexpr (std::is_same_v<TPolicy, FThreadSafeDelegateMode>)
        {
            return std::unique_lock<std::mutex>(m_mutex);
        }
        else
        {
            return std::unique_lock<std::mutex>(); // no-op for non-threadsafe
        }
    }

public:
    TMulticastDelegate() = default;

    /** Copy: deep-copy m_signal, do NOT copy connections (users must re-Add). */
    TMulticastDelegate(const TMulticastDelegate& other)
        : m_signal(other.m_signal)
        , m_connections()  // intentionally empty
        , m_lambdaListeners(other.m_lambdaListeners)
        , m_nextHandle{1}
    {}

    /** Move: move m_signal, discard stale connections, move lambda listeners. */
    TMulticastDelegate(TMulticastDelegate&& other) noexcept
        : m_signal(std::move(other.m_signal))
        , m_connections()   // connections refer to other's signal — invalid after move
        , m_lambdaListeners(std::move(other.m_lambdaListeners))
        , m_nextHandle{1}
    {}

    /** Copy assignment (mutex is non-copyable, so we must provide one). */
    TMulticastDelegate& operator=(const TMulticastDelegate& other)
    {
        if (this != &other)
        {
            auto lock = GetScopedLock();
            m_signal = other.m_signal;
            m_connections.clear();          // connections not copied
            m_lambdaListeners = other.m_lambdaListeners;
            m_nextHandle = 1;
        }
        return *this;
    }

    /** Move assignment. */
    TMulticastDelegate& operator=(TMulticastDelegate&& other) noexcept
    {
        if (this != &other)
        {
            auto lock = GetScopedLock();
            m_signal = std::move(other.m_signal);
            m_connections.clear();          // stale connections discarded
            m_lambdaListeners = std::move(other.m_lambdaListeners);
            m_nextHandle = 1;
        }
        return *this;
    }

    // ── Add: entt-compile-time binding ──────────────────────────────────

    /** Bind a free function or unbound member — no instance. */
    template<auto Candidate>
    FDelegateHandle Add()
    {
        auto lock = GetScopedLock();
        sink_t sink{m_signal};
        auto conn        = sink.template connect<Candidate>();
        auto handle      = GenerateNextHandle();
        m_connections[handle] = {conn, nullptr};
        return handle;
    }

    /** Bind a member function with instance by reference. */
    template<auto Candidate, typename Type>
    FDelegateHandle Add(Type& value_or_instance)
    {
        auto lock = GetScopedLock();
        sink_t sink{m_signal};
        auto conn        = sink.template connect<Candidate>(value_or_instance);
        auto handle      = GenerateNextHandle();
        m_connections[handle] = {conn, reinterpret_cast<const void*>(&value_or_instance)};
        return handle;
    }

    /** Bind a member function with instance by pointer. */
    template<auto Candidate, typename Type>
    FDelegateHandle Add(Type* value_or_instance)
    {
        auto lock = GetScopedLock();
        sink_t sink{m_signal};
        auto conn        = sink.template connect<Candidate>(value_or_instance);
        auto handle      = GenerateNextHandle();
        m_connections[handle] = {conn, reinterpret_cast<const void*>(value_or_instance)};
        return handle;
    }

    // ── AddRaw: entt-compile-time member binding ────────────────────────

    /** Bind a member function with object pointer. */
    template<auto Method, typename Type>
    FDelegateHandle AddRaw(Type* obj)
    {
        auto lock = GetScopedLock();
        sink_t sink{m_signal};
        auto conn        = sink.template connect<Method>(obj);
        auto handle      = GenerateNextHandle();
        m_connections[handle] = {conn, reinterpret_cast<const void*>(obj)};
        return handle;
    }

    // ── AddLambda: runtime capturing-lambda binding ─────────────────────

    /** Bind a capturing lambda via std::function side-channel. */
    template<typename Func>
    FDelegateHandle AddLambda(Func&& func)
    {
        auto lock = GetScopedLock();
        auto handle = GenerateNextHandle();
        m_lambdaListeners.emplace_back(handle, std::function<Ret(Args...)>(std::forward<Func>(func)));
        return handle;
    }

    // ── Remove / RemoveAll / Clear ──────────────────────────────────────

    /** Remove a single listener by handle. Returns true if found and removed. */
    bool Remove(FDelegateHandle handle)
    {
        auto lock = GetScopedLock();

        auto connIt = m_connections.find(handle);
        if (connIt != m_connections.end())
        {
            connIt->second.connection.release();
            m_connections.erase(connIt);
            return true;
        }

        for (auto it = m_lambdaListeners.begin(); it != m_lambdaListeners.end(); ++it)
        {
            if (it->first == handle)
            {
                m_lambdaListeners.erase(it);
                return true;
            }
        }

        return false;
    }

    /** Remove all listeners bound to a specific object instance. */
    void RemoveAll(const void* instance_ptr)
    {
        auto lock = GetScopedLock();
        sink_t sink{m_signal};
        sink.disconnect(instance_ptr);

        for (auto it = m_connections.begin(); it != m_connections.end(); )
        {
            if (it->second.instance == instance_ptr)
            {
                it = m_connections.erase(it);
            }
            else
            {
                ++it;
            }
        }
        // Lambda listeners cannot be matched by instance — skip them.
    }

    /** Remove every listener (entt + lambda). */
    void Clear()
    {
        auto lock = GetScopedLock();
        sink_t sink{m_signal};
        sink.disconnect();
        m_connections.clear();
        m_lambdaListeners.clear();
    }

    // ── Broadcast ───────────────────────────────────────────────────────

    /** Fire all listeners: entt signal first, then side-channel lambdas. */
    void Broadcast(Args... args)
    {
        auto lock = GetScopedLock();
        m_signal.publish(args...);
        for (auto& [_, func] : m_lambdaListeners)
        {
            func(args...);
        }
    }

    // ── Query ───────────────────────────────────────────────────────────

    /** True if any listener is registered. */
    [[nodiscard]] bool IsBound() const
    {
        auto lock = GetScopedLock();
        return !m_signal.empty() || !m_lambdaListeners.empty();
    }
};

// ─── TMulticastDelegateRegistration — C# event pattern, no Broadcast ──────

template<typename Ret, typename... Args, typename TPolicy>
class TMulticastDelegateRegistration<Ret(Args...), TPolicy>
{
    static_assert(std::is_void_v<Ret>, "TMulticastDelegateRegistration requires void return type");

    TMulticastDelegate<Ret(Args...), TPolicy>* m_delegate = nullptr;

public:
    TMulticastDelegateRegistration() = default;
    explicit TMulticastDelegateRegistration(TMulticastDelegate<Ret(Args...), TPolicy>& del)
        : m_delegate(&del) {}

    // Expose: Add, AddRaw, AddLambda, Remove, RemoveAll, Clear, IsBound
    template<auto Candidate>
    FDelegateHandle Add() { return m_delegate->template Add<Candidate>(); }

    template<auto Candidate, typename Type>
    FDelegateHandle Add(Type& v) { return m_delegate->template Add<Candidate>(v); }

    template<auto Candidate, typename Type>
    FDelegateHandle Add(Type* v) { return m_delegate->template Add<Candidate>(v); }

    template<auto Method, typename Type>
    FDelegateHandle AddRaw(Type* obj) { return m_delegate->template AddRaw<Method>(obj); }

    template<typename Func>
    FDelegateHandle AddLambda(Func&& f) { return m_delegate->AddLambda(std::forward<Func>(f)); }

    bool Remove(FDelegateHandle h) { return m_delegate->Remove(h); }

    void RemoveAll(const void* i) { return m_delegate->RemoveAll(i); }

    void Clear() { m_delegate->Clear(); }

    [[nodiscard]] bool IsBound() const { return m_delegate->IsBound(); }

    // Delete: Broadcast
    void Broadcast(Args... args) const = delete;
};

// ─── TDelegateRegistration — C# event pattern, no Execute ─────────────────

template<typename Ret, typename... Args>
class TDelegateRegistration<Ret(Args...)>
{
    TDelegate<Ret(Args...)>* m_delegate = nullptr;

public:
    TDelegateRegistration() = default;
    explicit TDelegateRegistration(TDelegate<Ret(Args...)>& del)
        : m_delegate(&del) {}

    // Expose: BindStatic, BindRaw, BindLambda, IsBound, Unbind
    template<auto Candidate, typename... BindArgs>
    void BindStatic(BindArgs&&... args) { m_delegate->template BindStatic<Candidate>(std::forward<BindArgs>(args)...); }

    template<auto Method, typename Type>
    void BindRaw(Type* obj) { m_delegate->template BindRaw<Method>(obj); }

    template<typename Func>
    void BindLambda(Func&& f) { m_delegate->BindLambda(std::forward<Func>(f)); }

    [[nodiscard]] bool IsBound() const { return m_delegate->IsBound(); }

    void Unbind() { m_delegate->Unbind(); }

    // Delete: Execute
    Ret Execute(Args... args) const = delete;
    bool ExecuteIfBound(Args... args) const = delete;
};
