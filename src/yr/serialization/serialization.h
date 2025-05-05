#pragma once
#include "runtime/logger/logger.h"
#include "core/reflection/reflection.h"
#include "yr/serialization/serializer.h"
#include "yr/debug_util.h"
#include "runtime/platform/platform.h"
#include "yr/serialization/snapshot.h"
#include <string>
#include <entt/meta/factory.hpp>
#include <entt/entity/registry.hpp>
#include <functional>

namespace detail
{
    template<typename Type>
    concept has_save_prologue = requires(Type const& data) {
        data.SavePrologue();
    };
    template<typename Type>
    concept has_save_epilogue = requires(Type const& data) {
        data.SaveEpilogue();
    };
    template<typename Type>
    concept has_save_deferred = requires(Type const& data) {
        data.SaveDeferred();
    };
    template<typename Type>
    concept has_load_prologue = requires(Type& data) {
        data.LoadPrologue();
    };
    template<typename Type>
    concept has_load_epilogue = requires(Type& data) {
        data.LoadEpilogue();
    };
    template<typename Type>
    concept has_load_deferred = requires(Type& data) {
        data.LoadDeferred();
    };
}

struct SerializeContext
{
    std::string savegameName;
    std::string archivePath;
    SERIALIZATION_INPUT_ARCHIVE* inputArchive;
    SERIALIZATION_OUTPUT_ARCHIVE* outputArchive;
    ENTITY_SNAPSHOT* snapshot;
    ENTITY_SNAPSHOT_LOADER* snapshotLoader;
    uint counter;
};

class Serialization
{
public:
    YREXTCORE_API static SerializeContext* GetCurrentContext();
    YREXTCORE_API static bool IsSerializing();
    YREXTCORE_API static std::string GetArchivePath(const char* savegameName, const char* extension = nullptr);

    /// @brief Serialize data when saving/loading a game.
    template<typename Type>
    static void Serialize(Type&& data);
    
    template<typename Type>
    static void Save(SERIALIZATION_OUTPUT_ARCHIVE& ar, const Type& data);
    template<typename Type>
    static void Load(SERIALIZATION_INPUT_ARCHIVE& ar, Type& data);
    
    template<typename Archive, typename Type>
    static void CallPrologue(Archive& ar, Type&& data) {
        if constexpr(std::is_same_v<Archive, SERIALIZATION_INPUT_ARCHIVE>) {
            if constexpr (detail::has_load_prologue<std::remove_reference_t<Type>>)
                data.LoadPrologue();
        }
        else if constexpr(std::is_same_v<Archive, SERIALIZATION_OUTPUT_ARCHIVE>) {
            if constexpr (detail::has_save_prologue<std::remove_reference_t<Type>>)
                data.SavePrologue();
        }
    }
    template<typename Archive, typename Type>
    static void CallEpilogue(Archive& ar, Type&& data) {
        if constexpr(std::is_same_v<Archive, SERIALIZATION_INPUT_ARCHIVE>) {
            if constexpr (detail::has_load_epilogue<std::remove_reference_t<Type>>)
                data.LoadEpilogue();
        }
        else if constexpr(std::is_same_v<Archive, SERIALIZATION_OUTPUT_ARCHIVE>) {
            if constexpr (detail::has_save_epilogue<std::remove_reference_t<Type>>)
                data.SaveEpilogue();
        }
    }
    
    template<typename Type>
    static void Save(SERIALIZATION_OUTPUT_ARCHIVE& ar, const cereal::NameValuePair<Type>& data)
    {
        ar.setNextName(data.name);
        Serialization::Save(ar, data.value);
    }
    template<typename Type>
    static void Load(SERIALIZATION_INPUT_ARCHIVE& ar, cereal::NameValuePair<Type> data)
    {
        ar.setNextName(data.name);
        Serialization::Load(ar, data.value);
    }
    
    static void Save(SERIALIZATION_OUTPUT_ARCHIVE& ar, const std::string_view& data)
    {
        Serialization::Save(ar, std::string(data));
    }
    static void Load(SERIALIZATION_INPUT_ARCHIVE& ar, std::string_view& data)
    {
        std::string tmp;
        Serialization::Load(ar, tmp);
        data = get_pool_string_view(tmp);
    }

    /// @brief Register type into serialization sequence with save/load function
    template<typename Type, void (*SaveToArchive)(SERIALIZATION_OUTPUT_ARCHIVE&, Type&) = nullptr, void (*LoadFromArchive)(SERIALIZATION_INPUT_ARCHIVE&, Type&) = nullptr>
    static void RegisterSerialization()
    {
        using namespace entt::literals;
        entt::meta_factory<Type> factory{};
        if (SaveToArchive) {
            factory.func<reinterpret_cast<void (*)(SERIALIZATION_OUTPUT_ARCHIVE*, Type&)>(SaveToArchive)>("__SaveToArchive"_hs);
        }
        if (LoadFromArchive) {
            factory.func<reinterpret_cast<void (*)(SERIALIZATION_INPUT_ARCHIVE*, Type&)>(LoadFromArchive)>("__LoadFromArchive"_hs);
        }
        RegisterSnapshotInternal(entt::resolve<Type>(), [](ENTITY_SNAPSHOT& snapshot) {
            snapshot.get<Type>(gArchive);
        }, [](ENTITY_SNAPSHOT_LOADER& snapshot) {
            snapshot.get<Type>(gArchive);
        });
    }

    /// @brief Register data to deferred process
    template<typename Type>
    static void RegisterSaveDeferredProcess(Type& data)
    {
        static_assert(!std::is_pointer_v<Type>, "unexpected type!");
        RegisterDeferredProcessInternal(&data, [](entt::meta_any cur){ cur.cast<Type*>()->SaveDeferred(); });
    }
    /// @brief Register data to deferred process
    template<typename Type>
    static void RegisterLoadDeferredProcess(Type& data)
    {
        static_assert(!std::is_pointer_v<Type>, "unexpected type!");
        RegisterDeferredProcessInternal(&data, [](entt::meta_any cur){ cur.cast<Type*>()->LoadDeferred(); });
    }
private:
    YREXTCORE_API static void RegisterSnapshotInternal(entt::meta_type type, void(*snapshotSave)(ENTITY_SNAPSHOT&), void(*snapshotLoad)(ENTITY_SNAPSHOT_LOADER&));
    YREXTCORE_API static void RegisterDeferredProcessInternal(entt::meta_any data, void(*processFunc)(entt::meta_any));
    
    struct SerializationArchive
    {
        template <typename Type>
        inline void operator()(Type&& data)
        {
            Serialization::Serialize<Type>(std::forward<Type>(data));
        }
    };
    YREXTCORE_API static SerializationArchive gArchive;
};

template<typename Type>
void Serialization::Serialize(Type&& data)
{
    SerializeContext* context = GetCurrentContext();
    if (context->inputArchive) {
        if constexpr(std::is_const_v<std::remove_reference_t<Type>>) {
            gLogger->error("can not load {} at this time...", entt::type_id<Type>().name());
            LogErrorStackTrace();
        }
        else {
            Serialization::Load(*context->inputArchive, const_cast<std::remove_reference_t<Type>&>(data));
        }
    }
    else if (context->outputArchive) {
        Serialization::Save(*context->outputArchive, std::forward<Type>(data));
    }
    else {
        gLogger->error("can not serialize anything at this time...");
        LogErrorStackTrace();
    }
}

template<typename Type>
void Serialization::Save(SERIALIZATION_OUTPUT_ARCHIVE& ar, const Type& data)
{
    using namespace entt::literals;
    if constexpr(cereal::traits::detail::count_output_serializers<Type, SERIALIZATION_OUTPUT_ARCHIVE>::value > 0) {
        ar(data);
        if constexpr (detail::has_save_deferred<Type>) {
            Serialization::RegisterSaveDeferredProcess(data);
        }
    }
    else {
        entt::meta_type type = entt::resolve<Type>();
        if (type) {
            entt::meta_func func = type.func("__SaveToArchive"_hs);
            if (func)
            {
                func.invoke({}, &ar, entt::forward_as_meta(const_cast<Type&>(data)));
                
                if constexpr (detail::has_save_deferred<Type>) {
                    Serialization::RegisterSaveDeferredProcess(data);
                }
            }
            else {
                gLogger->error("could not save {}: it is not auto serialize!", entt::type_id<Type>().name());
                LogErrorStackTrace();
            }
        }
        else {
            gLogger->error("could not save {}: meta not register!", entt::type_id<Type>().name());
            LogErrorStackTrace();
        }
    }
}

template<typename Type>
void Serialization::Load(SERIALIZATION_INPUT_ARCHIVE& ar, Type& data)
{
    using namespace entt::literals;
    if constexpr(cereal::traits::detail::count_input_serializers<Type, SERIALIZATION_INPUT_ARCHIVE>::value > 0) {
        ar(data);
        if constexpr (detail::has_load_deferred<Type>) {
            Serialization::RegisterLoadDeferredProcess(data);
        }
    }
    else {
        entt::meta_type type = entt::resolve<Type>();
        if (type) {
            entt::meta_func func = type.func("__LoadFromArchive"_hs);
            if (func)
            {
                func.invoke({}, &ar, entt::forward_as_meta(data));

                if constexpr (detail::has_load_deferred<Type>) {
                    Serialization::RegisterLoadDeferredProcess(data);
                }
            }
            else {
                gLogger->error("could not load {}: it is not auto serialize!", entt::type_id<Type>().name());
                LogErrorStackTrace();
            }
        }
        else {
            gLogger->error("could not load {}: meta not register!", entt::type_id<Type>().name());
            LogErrorStackTrace();
        }
    }
}
