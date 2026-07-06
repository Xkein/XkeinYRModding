// ==========================================================================
// delegate_test.cpp — Comprehensive compile-time and runtime tests for
//                     the delegate system (delegate.h)
//
// Standalone: g++ -std=c++20 -Isrc -I3rdparty/entt/src src/core/tool/delegate_test.cpp
// No external test framework required — uses assert() and static_assert.
// ==========================================================================

#include "core/tool/delegate.h"
#include <cassert>
#include <cstdio>
#include <type_traits>
#include <unordered_set>
#include <functional>

// ==========================================================================
// Helper types and globals
// ==========================================================================

static int g_TestCounter = 0;
static void ResetCounter() { g_TestCounter = 0; }
static void IncCounter() { ++g_TestCounter; }
static void IncBy(int x) { g_TestCounter += x; }

struct FTestListener {
    void OnEvent() { ++g_TestCounter; }
    void OnEventInt(int x) { g_TestCounter += x; }
};

static int Square(int x) { return x * x; }

// ==========================================================================
// Compile-time checks
// ==========================================================================

// -- TDelegate is instantiable -------------------------------------------
static_assert(std::is_default_constructible_v<TDelegate<void()>>,
    "TDelegate<void()> must be default-constructible");
static_assert(std::is_default_constructible_v<TDelegate<int(int)>>,
    "TDelegate<int(int)> must be default-constructible");
static_assert(std::is_copy_constructible_v<TDelegate<void()>>,
    "TDelegate must be copy-constructible");
static_assert(std::is_move_constructible_v<TDelegate<void()>>,
    "TDelegate must be move-constructible");
static_assert(std::is_copy_assignable_v<TDelegate<void()>>,
    "TDelegate must be copy-assignable");
static_assert(std::is_move_assignable_v<TDelegate<void()>>,
    "TDelegate must be move-assignable");

// -- TMulticastDelegate is instantiable ----------------------------------
static_assert(std::is_default_constructible_v<TMulticastDelegate<void()>>,
    "TMulticastDelegate<void()> must be default-constructible");
static_assert(std::is_default_constructible_v<TMulticastDelegate<void(), FThreadSafeDelegateMode>>,
    "TMulticastDelegate<void(), FThreadSafeDelegateMode> must be default-constructible");

// -- Registration wrappers are instantiable ------------------------------
static_assert(std::is_default_constructible_v<TMulticastDelegateRegistration<void()>>,
    "TMulticastDelegateRegistration<void()> must be default-constructible");
static_assert(std::is_default_constructible_v<TDelegateRegistration<void()>>,
    "TDelegateRegistration<void()> must be default-constructible");

// ==========================================================================
// FDelegateHandle tests
// ==========================================================================

static void Test_FDelegateHandle()
{
    puts("  FDelegateHandle...");

    // Default-constructed handle is NOT valid
    {
        FDelegateHandle h;
        assert(!h.IsValid() && "Default handle should be invalid");
    }

    // GenerateNew() returns valid handle
    {
        auto h = FDelegateHandle::GenerateNew();
        assert(h.IsValid() && "GenerateNew() should return valid handle");
    }

    // Reset() makes handle invalid
    {
        auto h = FDelegateHandle::GenerateNew();
        assert(h.IsValid());
        h.Reset();
        assert(!h.IsValid() && "Reset() should make handle invalid");
    }

    // Two sequentially generated handles are NOT equal
    {
        auto h1 = FDelegateHandle::GenerateNew();
        auto h2 = FDelegateHandle::GenerateNew();
        assert(h1 != h2 && "Sequential handles must not be equal");
    }

    // operator== works (handle compared by Id)
    {
        auto h1 = FDelegateHandle::GenerateNew();
        auto h2 = h1;
        assert(h1 == h2 && "Same handle value should be equal");
    }

    // std::hash<FDelegateHandle> works
    {
        std::hash<FDelegateHandle> hasher;
        auto h1 = FDelegateHandle::GenerateNew();
        auto h2 = FDelegateHandle::GenerateNew();
        auto hash1 = hasher(h1);
        auto hash2 = hasher(h2);
        // Two different handles produce (likely) different hash values
        // The hash is just the Id cast to size_t, so this is deterministic
        assert(hash1 != hash2 && "Hash of different handles should differ");
        assert(hasher(h1) == hasher(h1) && "Hash must be deterministic");
    }

    // FDelegateHandle works with unordered_set (via std::hash)
    {
        std::unordered_set<FDelegateHandle> set;
        auto h1 = FDelegateHandle::GenerateNew();
        auto h2 = FDelegateHandle::GenerateNew();
        set.insert(h1);
        set.insert(h2);
        assert(set.size() == 2);
        set.insert(h1);
        assert(set.size() == 2); // duplicate not added
    }
}

// ==========================================================================
// TDelegate tests
// ==========================================================================

static void Test_TDelegate_CompileTime()
{
    puts("  TDelegate compile-time...");

    // These are implicit compile-time checks — if they compile, we pass.
    // BindStatic<&FreeFunc>() compiles
    {
        TDelegate<void()> del;
        del.BindStatic<&IncCounter>();
        // (no runtime assertion needed here — compile-time proof only)
    }

    // BindStatic with return value compiles
    {
        TDelegate<int(int)> del;
        del.BindStatic<&Square>();
    }

    // BindRaw<&Class::Method>(obj) compiles
    {
        FTestListener listener;
        TDelegate<void()> del;
        del.BindRaw<&FTestListener::OnEvent>(&listener);
    }

    // BindLambda compiles
    {
        TDelegate<void()> del;
        del.BindLambda([]() {});
    }

    puts("    OK (all compilations succeeded)");
}

static void Test_TDelegate_Runtime()
{
    puts("  TDelegate runtime...");

    // BindStatic a free function, Execute, verify result
    {
        ResetCounter();
        TDelegate<void()> del;
        del.BindStatic<&IncCounter>();
        del.Execute();
        assert(g_TestCounter == 1 && "BindStatic + Execute should call IncCounter");
    }

    // TDelegate with return value: BindStatic + Execute
    {
        TDelegate<int(int)> del;
        del.BindStatic<&Square>();
        assert(del.Execute(5) == 25 && "Square(5) should be 25");
        assert(del.Execute(0) == 0);
        assert(del.Execute(-3) == 9);
    }

    // Capturing lambda, Execute — test the capture value changes
    {
        TDelegate<void()> del;
        int capture = 0;
        del.BindLambda([&capture]() { capture = 42; });
        del.Execute();
        assert(capture == 42 && "Lambda capture should be modified by Execute");
    }

    // Capturing lambda with return value
    {
        TDelegate<int(int)> del;
        int factor = 3;
        del.BindLambda([factor](int x) { return x * factor; });
        assert(del.Execute(7) == 21 && "Lambda with capture and return value");
    }

    // ExecuteIfBound on bound delegate returns true and calls function (void-return)
    {
        ResetCounter();
        TDelegate<void()> del;
        del.BindStatic<&IncCounter>();
        bool result = del.ExecuteIfBound();
        assert(result == true && "ExecuteIfBound on bound delegate should return true");
        assert(g_TestCounter == 1 && "ExecuteIfBound should call the function");
    }

    // ExecuteIfBound on unbound delegate returns false
    {
        TDelegate<void()> del;
        bool result = del.ExecuteIfBound();
        assert(result == false && "ExecuteIfBound on unbound delegate should return false");
    }

    // IsBound returns false initially, true after Bind
    {
        TDelegate<void()> del;
        assert(!del.IsBound() && "Default TDelegate should not be bound");
        del.BindStatic<&IncCounter>();
        assert(del.IsBound() && "TDelegate should be bound after BindStatic");
    }

    // Unbind resets to unbound state
    {
        TDelegate<void()> del;
        del.BindStatic<&IncCounter>();
        assert(del.IsBound());
        del.Unbind();
        assert(!del.IsBound() && "After Unbind, TDelegate should not be bound");
    }

    // Copy construct from bound delegate — original and copy both work
    {
        ResetCounter();
        TDelegate<void()> original;
        original.BindStatic<&IncCounter>();
        TDelegate<void()> copy(original);

        // Original still works
        assert(original.IsBound());
        original.Execute();
        assert(g_TestCounter == 1);

        // Copy also works
        ResetCounter();
        assert(copy.IsBound());
        copy.Execute();
        assert(g_TestCounter == 1);

        // Original still independent
        ResetCounter();
        original.Execute();
        assert(g_TestCounter == 1);
    }

    // Copy assignment works
    {
        ResetCounter();
        TDelegate<void()> a;
        a.BindStatic<&IncCounter>();

        TDelegate<void()> b;
        b = a;
        assert(b.IsBound());
        b.Execute();
        assert(g_TestCounter == 1);
    }

    // Move construct from bound delegate — new has function, old is unbound
    {
        ResetCounter();
        TDelegate<void()> original;
        original.BindStatic<&IncCounter>();

        TDelegate<void()> moved(std::move(original));
        assert(moved.IsBound() && "Moved-to delegate should be bound");
        assert(!original.IsBound() && "Moved-from delegate should be unbound");

        moved.Execute();
        assert(g_TestCounter == 1);
    }

    // Move assignment works
    {
        ResetCounter();
        TDelegate<void()> a;
        a.BindStatic<&IncCounter>();

        TDelegate<void()> b;
        b = std::move(a);
        assert(b.IsBound());
        assert(!a.IsBound());
        b.Execute();
        assert(g_TestCounter == 1);
    }

    // Self-assignment is safe (copy)
    {
        TDelegate<void()> del;
        del.BindStatic<&IncCounter>();
        // Deliberately self-assign via a trick to avoid compiler warning
        auto& del_ref = del;
        del = del_ref;
        assert(del.IsBound());
    }

    // Self-assignment is safe (move)
    {
        TDelegate<void()> del;
        del.BindStatic<&IncCounter>();
        auto& del_ref = del;
        del = std::move(del_ref);
        // After self-move, the object should still be in a valid (but unspecified) state.
        // The variant should still be non-monostate because we moved from ourselves.
        // Just verify it doesn't crash:
        [[maybe_unused]] auto _ = del.IsBound();
    }
}

// ==========================================================================
// TMulticastDelegate (FNotThreadSafeDelegateMode) tests
// ==========================================================================

static void Test_TMulticastDelegate_NotThreadSafe()
{
    puts("  TMulticastDelegate<FNotThreadSafeDelegateMode>...");

    // Add 3 listeners, Broadcast — all 3 are called
    {
        ResetCounter();
        TMulticastDelegate<void()> multi;
        multi.Add<&IncCounter>();

        FTestListener l2;
        multi.Add<&FTestListener::OnEvent>(l2);

        FTestListener l3;
        multi.Add<&FTestListener::OnEvent>(l3);

        multi.Broadcast();
        assert(g_TestCounter == 3 && "Broadcast should call all 3 listeners");
    }

    // Remove a listener by handle — removed listener NOT called
    {
        ResetCounter();
        TMulticastDelegate<void()> multi;
        multi.Add<&IncCounter>();

        FTestListener l2;
        auto h2 = multi.Add<&FTestListener::OnEvent>(l2);

        FTestListener l3;
        multi.Add<&FTestListener::OnEvent>(l3);

        // Remove l2
        bool removed = multi.Remove(h2);
        assert(removed && "Remove should return true for existing handle");

        ResetCounter();
        multi.Broadcast();
        assert(g_TestCounter == 2 && "After removing l2, only 2 listeners should fire");
    }

    // Remove with invalid handle returns false
    {
        TMulticastDelegate<void()> multi;
        FDelegateHandle invalidHandle;
        bool removed = multi.Remove(invalidHandle);
        assert(!removed && "Remove with invalid handle should return false");
    }

    // Remove handles from AddRaw
    {
        ResetCounter();
        TMulticastDelegate<void()> multi;
        FTestListener listener;

        auto h1 = multi.AddRaw<&FTestListener::OnEvent>(&listener);
        multi.AddRaw<&FTestListener::OnEvent>(&listener);

        multi.Broadcast();
        assert(g_TestCounter == 2);

        ResetCounter();
        multi.Remove(h1);
        multi.Broadcast();
        assert(g_TestCounter == 1 && "After RemoveRaw handle, 1 listener should remain");
    }

    // RemoveAll(instance_ptr) — only that instance's listeners removed
    {
        ResetCounter();
        TMulticastDelegate<void()> multi;
        multi.Add<&IncCounter>();

        FTestListener l2;
        multi.Add<&FTestListener::OnEvent>(l2);
        multi.Add<&FTestListener::OnEvent>(l2); // l2 registered twice

        FTestListener l3;
        auto h3 = multi.Add<&FTestListener::OnEvent>(l3);

        // Remove all listeners bound to l2
        multi.RemoveAll(&l2);

        ResetCounter();
        multi.Broadcast();
        // Only IncCounter + l3 should fire
        assert(g_TestCounter == 2 && "RemoveAll(l2) should keep IncCounter and l3");
    }

    // RemoveAll with unrelated pointer does nothing
    {
        ResetCounter();
        TMulticastDelegate<void()> multi;
        multi.Add<&IncCounter>();

        FTestListener other;
        multi.RemoveAll(&other); // no-op, other was never added

        ResetCounter();
        multi.Broadcast();
        assert(g_TestCounter == 1 && "RemoveAll unrelated pointer should not affect existing listeners");
    }

    // Clear removes all listeners — IsBound returns false
    {
        ResetCounter();
        TMulticastDelegate<void()> multi;
        multi.Add<&IncCounter>();

        FTestListener l2;
        multi.Add<&FTestListener::OnEvent>(l2);

        int lambdaCount = 0;
        multi.AddLambda([&lambdaCount]() { ++lambdaCount; });

        assert(multi.IsBound());
        multi.Clear();
        assert(!multi.IsBound() && "After Clear, IsBound should return false");

        ResetCounter();
        lambdaCount = 0;
        multi.Broadcast();
        assert(g_TestCounter == 0 && "After Clear, Broadcast should not call any listener");
        assert(lambdaCount == 0 && "After Clear, lambda listeners should also be removed");
    }

    // AddLambda with capturing lambda — Broadcast calls the lambda
    {
        TMulticastDelegate<void()> multi;
        int callCount = 0;
        auto h = multi.AddLambda([&callCount]() { ++callCount; });
        assert(h.IsValid());

        multi.Broadcast();
        assert(callCount == 1 && "AddLambda lambda should be called by Broadcast");

        // Remove lambda by handle
        multi.Remove(h);
        multi.Broadcast();
        assert(callCount == 1 && "After Remove, lambda should not be called again");
    }

    // Mixed Add + AddLambda — both paths are called
    {
        ResetCounter();
        TMulticastDelegate<void()> multi;
        int lambdaCount = 0;

        multi.Add<&IncCounter>();
        multi.AddLambda([&lambdaCount]() { ++lambdaCount; });

        multi.Broadcast();
        assert(g_TestCounter == 1 && "Entt-bound listener should fire");
        assert(lambdaCount == 1 && "Lambda listener should fire");
    }

    // IsBound returns false initially, true after Add
    {
        TMulticastDelegate<void()> multi;
        assert(!multi.IsBound() && "Default TMulticastDelegate should not be bound");

        multi.Add<&IncCounter>();
        assert(multi.IsBound() && "After Add, TMulticastDelegate should be bound");

        multi.Clear();
        assert(!multi.IsBound() && "After Clear, IsBound should be false");
    }

    // IsBound with AddLambda
    {
        TMulticastDelegate<void()> multi;
        assert(!multi.IsBound());

        int x = 0;
        multi.AddLambda([&x]() { x = 1; });
        assert(multi.IsBound() && "AddLambda should make IsBound() return true");
    }

    // Copy construct: signal deep-copied; entt connections NOT preserved;
    // lambda listeners NOT preserved (may dangle on ref-capture).
    {
        ResetCounter();
        TMulticastDelegate<void()> src;
        src.Add<&IncCounter>();

        int srcLambdaCount = 0;
        src.AddLambda([&srcLambdaCount]() { ++srcLambdaCount; });

        TMulticastDelegate<void()> dest(src);

        // Source still works
        assert(src.IsBound());

        // Destination is NOT bound (connections and lambdas not copied)
        assert(!dest.IsBound() && "Copy should NOT preserve IsBound (lambdas not copied)");

        // Destination Broadcast: IncCounter (entt) should NOT fire
        // (entt connections not preserved on copy), and no lambdas either.
        ResetCounter();
        srcLambdaCount = 0;
        dest.Broadcast();
        // IncCounter is entt-bound, connections not preserved → 0
        // lambda listeners are NOT copied either → 0
        assert(g_TestCounter == 0 && "Entt connections are not preserved on copy");
        assert(srcLambdaCount == 0 && "Lambda listeners are NOT preserved on copy");

        // Source Broadcast still works fully
        ResetCounter();
        srcLambdaCount = 0;
        src.Broadcast();
        assert(g_TestCounter == 1 && "Source entt connections still intact");
        assert(srcLambdaCount == 1 && "Source lambda listeners still intact");
    }

    // Copy assignment
    {
        ResetCounter();
        TMulticastDelegate<void()> src;
        src.Add<&IncCounter>();

        TMulticastDelegate<void()> dest;
        dest = src;

        ResetCounter();
        dest.Broadcast();
        // Same semantics as copy construct: entt not preserved, lambdas not copied
        assert(g_TestCounter == 0);
    }

    // Move construct: moves signal and lambda listeners; source is unbound
    {
        ResetCounter();
        TMulticastDelegate<void()> src;
        src.Add<&IncCounter>();

        int srcLambda = 0;
        src.AddLambda([&srcLambda]() { ++srcLambda; });

        TMulticastDelegate<void()> dest(std::move(src));

        // Source should be unbound
        assert(!src.IsBound() && "Moved-from multicast delegate should not be bound");

        // Destination should be bound
        assert(dest.IsBound() && "Moved-to multicast delegate should be bound");

        // Destination Broadcast should fire both entt and lambda listeners
        ResetCounter();
        srcLambda = 0;
        dest.Broadcast();
        assert(g_TestCounter == 1 && "Moved-to delegate: entt listeners should fire");
        assert(srcLambda == 1 && "Moved-to delegate: lambda listeners should fire");

        // Source Broadcast does nothing
        ResetCounter();
        int dummy = 0;
        auto h_dummy = src.AddLambda([&dummy]() { dummy = 99; });
        src.Broadcast();
        // Actually after move, source signal is empty, so even adding a new lambda won't
        // trigger old IncCounter. The new lambda should fire though.
        assert(dummy == 99);
    }

    // Move assignment
    {
        ResetCounter();
        TMulticastDelegate<void()> src;
        src.Add<&IncCounter>();

        TMulticastDelegate<void()> dest;
        dest = std::move(src);

        assert(!src.IsBound());
        assert(dest.IsBound());

        ResetCounter();
        dest.Broadcast();
        assert(g_TestCounter == 1);
    }

    // Self-copy-assignment is safe
    {
        TMulticastDelegate<void()> multi;
        multi.Add<&IncCounter>();
        auto& ref = multi;
        multi = ref;
        assert(multi.IsBound());
    }

    // Self-move-assignment is safe
    {
        TMulticastDelegate<void()> multi;
        multi.Add<&IncCounter>();
        auto& ref = multi;
        multi = std::move(ref);
        // In a valid state, though unspecified after self-move
        [[maybe_unused]] auto _ = multi.IsBound();
    }

    // TMulticastDelegate with int argument (IncBy)
    {
        ResetCounter();
        TMulticastDelegate<void(int)> multi;
        multi.Add<&IncBy>();

        FTestListener listener;
        multi.Add<&FTestListener::OnEventInt>(listener);

        multi.Broadcast(5);
        assert(g_TestCounter == 10 && "IncBy(5) + OnEventInt(5) should sum to 10");

        multi.Clear();
        ResetCounter();
        multi.Broadcast(5);
        assert(g_TestCounter == 0 && "After Clear, Broadcast should be no-op");
    }
}

// ==========================================================================
// TMulticastDelegate (FThreadSafeDelegateMode) tests
// ==========================================================================

static void Test_TMulticastDelegate_ThreadSafe()
{
    puts("  TMulticastDelegate<FThreadSafeDelegateMode>...");

    // Basic: Add 2, Broadcast — both called
    {
        ResetCounter();
        TMulticastDelegate<void(), FThreadSafeDelegateMode> multi;
        multi.Add<&IncCounter>();

        FTestListener listener;
        multi.Add<&FTestListener::OnEvent>(listener);

        multi.Broadcast();
        assert(g_TestCounter == 2 && "Thread-safe Broadcast should call all listeners");
    }

    // Removal
    {
        ResetCounter();
        TMulticastDelegate<void(), FThreadSafeDelegateMode> multi;
        auto h1 = multi.Add<&IncCounter>();

        FTestListener listener;
        multi.Add<&FTestListener::OnEvent>(listener);

        multi.Remove(h1);
        ResetCounter();
        multi.Broadcast();
        assert(g_TestCounter == 1 && "After Remove, only 1 listener should fire");
    }

    // RemoveAll
    {
        ResetCounter();
        TMulticastDelegate<void(), FThreadSafeDelegateMode> multi;
        multi.Add<&IncCounter>();

        FTestListener listener;
        multi.Add<&FTestListener::OnEvent>(listener);
        multi.Add<&FTestListener::OnEvent>(listener); // twice

        multi.RemoveAll(&listener);
        ResetCounter();
        multi.Broadcast();
        assert(g_TestCounter == 1 && "After RemoveAll(&listener), only IncCounter remains");
    }

    // Clear
    {
        ResetCounter();
        TMulticastDelegate<void(), FThreadSafeDelegateMode> multi;
        multi.Add<&IncCounter>();

        FTestListener listener;
        multi.Add<&FTestListener::OnEvent>(listener);

        int lambdaCount = 0;
        multi.AddLambda([&lambdaCount]() { ++lambdaCount; });

        assert(multi.IsBound());
        multi.Clear();
        assert(!multi.IsBound());

        multi.Broadcast();
        assert(g_TestCounter == 0);
        assert(lambdaCount == 0);
    }

    // IsBound
    {
        TMulticastDelegate<void(), FThreadSafeDelegateMode> multi;
        assert(!multi.IsBound());

        multi.Add<&IncCounter>();
        assert(multi.IsBound());

        multi.Clear();
        assert(!multi.IsBound());
    }

    // AddLambda with capturing lambda
    {
        TMulticastDelegate<void(), FThreadSafeDelegateMode> multi;
        int capture = 0;
        auto h = multi.AddLambda([&capture]() { capture = 42; });
        assert(h.IsValid());
        assert(multi.IsBound());

        multi.Broadcast();
        assert(capture == 42);

        multi.Remove(h);
        multi.Broadcast();
        assert(capture == 42); // not called again
    }

    // Mixed Add + AddLambda
    {
        ResetCounter();
        TMulticastDelegate<void(), FThreadSafeDelegateMode> multi;
        int lambdaCount = 0;

        multi.Add<&IncCounter>();
        multi.AddLambda([&lambdaCount]() { ++lambdaCount; });

        multi.Broadcast();
        assert(g_TestCounter == 1);
        assert(lambdaCount == 1);
    }

    // TMulticastDelegate<void(int)> with thread-safe mode
    {
        ResetCounter();
        TMulticastDelegate<void(int), FThreadSafeDelegateMode> multi;
        multi.Add<&IncBy>();

        FTestListener listener;
        multi.Add<&FTestListener::OnEventInt>(listener);

        multi.Broadcast(3);
        assert(g_TestCounter == 6 && "IncBy(3) + OnEventInt(3) = 6");
    }

    // Copy and move with thread-safe mode
    {
        TMulticastDelegate<void(), FThreadSafeDelegateMode> src;
        int lambdaVal = 0;
        src.Add<&IncCounter>();
        src.AddLambda([&lambdaVal]() { lambdaVal = 1; });

        // Copy
        TMulticastDelegate<void(), FThreadSafeDelegateMode> dest(src);
        assert(dest.IsBound());

        ResetCounter();
        lambdaVal = 0;
        dest.Broadcast();
        assert(g_TestCounter == 0 && "Thread-safe copy: entt connections not preserved");
        assert(lambdaVal == 1 && "Thread-safe copy: lambdas preserved");

        // Move
        TMulticastDelegate<void(), FThreadSafeDelegateMode> moved(std::move(src));
        assert(moved.IsBound());
        assert(!src.IsBound());

        ResetCounter();
        lambdaVal = 0;
        moved.Broadcast();
        assert(g_TestCounter == 1 && "Thread-safe move: entt listeners moved");
        assert(lambdaVal == 1 && "Thread-safe move: lambdas moved");
    }
}

// ==========================================================================
// Registration wrapper tests
// ==========================================================================

static void Test_TMulticastDelegateRegistration()
{
    puts("  TMulticastDelegateRegistration...");

    // Add<&FreeFunc>() compiles ✓
    {
        TMulticastDelegate<void()> multi;
        TMulticastDelegateRegistration<void()> reg(multi);

        reg.Add<&IncCounter>();

        ResetCounter();
        multi.Broadcast();
        assert(g_TestCounter == 1 && "Registration::Add should delegate to underlying multicast");
    }

    // AddRaw compiles ✓
    {
        TMulticastDelegate<void()> multi;
        TMulticastDelegateRegistration<void()> reg(multi);

        FTestListener listener;
        reg.AddRaw<&FTestListener::OnEvent>(&listener);

        ResetCounter();
        multi.Broadcast();
        assert(g_TestCounter == 1);
    }

    // AddLambda compiles ✓
    {
        TMulticastDelegate<void()> multi;
        TMulticastDelegateRegistration<void()> reg(multi);

        int capture = 0;
        reg.AddLambda([&capture]() { capture = 7; });

        multi.Broadcast();
        assert(capture == 7);
    }

    // Remove, RemoveAll, Clear, IsBound all delegate correctly
    {
        TMulticastDelegate<void()> multi;
        TMulticastDelegateRegistration<void()> reg(multi);

        FTestListener listener;
        auto h = reg.Add<&IncCounter>();
        reg.AddRaw<&FTestListener::OnEvent>(&listener);

        assert(reg.IsBound());

        bool removed = reg.Remove(h);
        assert(removed);
        assert(reg.IsBound()); // listener still there

        reg.RemoveAll(&listener);
        assert(!reg.IsBound());

        // Re-add and Clear
        reg.Add<&IncCounter>();
        assert(reg.IsBound());
        reg.Clear();
        assert(!reg.IsBound());
    }

    // Broadcast is explicitly deleted — compile error if uncommented:
    //   reg.Broadcast();  // ERROR: use of deleted function
    //
    // The '= delete' on Broadcast prevents accidental invocation from
    // registration proxies that follow the C# event pattern (only expose
    // Add/Remove, never Broadcast/Invoke).
}

static void Test_TDelegateRegistration()
{
    puts("  TDelegateRegistration...");

    // BindStatic<&FreeFunc>() compiles ✓
    {
        TDelegate<void()> del;
        TDelegateRegistration<void()> reg(del);

        reg.BindStatic<&IncCounter>();

        ResetCounter();
        del.Execute();
        assert(g_TestCounter == 1 && "Registration::BindStatic should delegate");
    }

    // BindRaw compiles ✓
    {
        TDelegate<void()> del;
        TDelegateRegistration<void()> reg(del);

        FTestListener listener;
        reg.BindRaw<&FTestListener::OnEvent>(&listener);

        ResetCounter();
        del.Execute();
        assert(g_TestCounter == 1);
    }

    // BindLambda compiles ✓
    {
        TDelegate<void()> del;
        TDelegateRegistration<void()> reg(del);

        int capture = 0;
        reg.BindLambda([&capture]() { capture = 3; });

        del.Execute();
        assert(capture == 3);
    }

    // IsBound and Unbind delegate correctly
    {
        TDelegate<void()> del;
        TDelegateRegistration<void()> reg(del);

        assert(!reg.IsBound());
        reg.BindStatic<&IncCounter>();
        assert(reg.IsBound());

        reg.Unbind();
        assert(!reg.IsBound());
    }

    // Execute is explicitly deleted — compile error if uncommented:
    //   reg.Execute();         // ERROR: use of deleted function
    //   reg.ExecuteIfBound();  // ERROR: use of deleted function
    //
    // This enforces the C# event pattern where registration proxies expose
    // only binding/unbinding, never invocation.
}

// ==========================================================================
// main
// ==========================================================================

int main()
{
    puts("============================================================");
    puts("  Delegate System Tests");
    puts("============================================================");

    // ── FDelegateHandle ────────────────────────────────────────────
    puts("[FDelegateHandle]");
    Test_FDelegateHandle();

    // ── TDelegate ──────────────────────────────────────────────────
    puts("[TDelegate]");
    Test_TDelegate_CompileTime();
    Test_TDelegate_Runtime();

    // ── TMulticastDelegate (FNotThreadSafeDelegateMode) ────────────
    puts("[TMulticastDelegate - FNotThreadSafeDelegateMode]");
    Test_TMulticastDelegate_NotThreadSafe();

    // ── TMulticastDelegate (FThreadSafeDelegateMode) ───────────────
    puts("[TMulticastDelegate - FThreadSafeDelegateMode]");
    Test_TMulticastDelegate_ThreadSafe();

    // ── Registration wrappers ──────────────────────────────────────
    puts("[TMulticastDelegateRegistration]");
    Test_TMulticastDelegateRegistration();

    puts("[TDelegateRegistration]");
    Test_TDelegateRegistration();

    puts("============================================================");
    puts("  All tests passed!");
    puts("============================================================");

    return 0;
}
