# Meta

We have the [CppHeaderTool](../3rdparty/CppHeaderTool/) to scan header files and generate extra code before compile.

This allow us to get rid of these annoying writing jobs because they are generated: 
- Reflection: registering classes, members, enums, variables, methods
- Scripting Language Wrapper: JavaScript wrapper
- Serialization: save game, load game, ini loading
- Other things...

The scriban code templates can be found in `src/template`:
- js_module_cpp.scriban : register all generated class and enum wrapper code
- js_module_setup.scriban : JavaScript module setup code
- js_type_cpp.scriban : class or enum JavaScript wrapper
- ts_module_index.scriban : common module TypeScript index declarations
- other common code template...

If you want to specify the project templates, add extra config to rules `codegen-cpp` in your xmake files:
```lua
target("YrExtCore")
    -- ...
    add_rules("codegen-cpp", {
        -- copy default templates and override some keys
        templates = get_templates({
            module = {
                ["module_header.scriban"] =  "{0}.gen.h",
                ["yr/yr_module_cpp.scriban"] =  "{0}.gen.cpp",
            },
        })
    })
    -- ...
```

## Class Meta Keywords
The keyword `CLASS` writing before `struct` or `class` is used to specify class meta:
```cpp
CLASS(BindJs, IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass, TerrainTypeClass, AnimTypeClass])
struct PhysicsTypeComponent final
{
    // ...
};
```

### YrExtension
It is recommended to use YrExtension to manager your initialization and cleaning for below reasons:
- Clear execution order: all initialization and cleaning job are begin at one place
- Easy to reload: if your module is dynamic reloading supported, it is easy to do this.

You must implement interface `IYrExtension` and add rules `codegen-cpp`
```cpp
CLASS(YrExtension)
class YrXkeinModule final : public IYrExtension
{
private:
    virtual void Startup() override;
    virtual void Shutdown() override;
    virtual bool SupportsDynamicReloading() override
    {
        return false;
    }
};
```
```lua
target("XkeinEditor")
    -- ...
    add_rules("codegen-cpp")
    -- ...
```


### HookEvent
This keyword can **only be used in YrExtCore module**!

```cpp
// in header files
// declare a normal event
CLASS(HookEvent)
class YrTechnoLoadGameEndEvent
{
public:
    TechnoClass* pTechno;
    IStream* stream;
};

// declare a event that probably override a function return value and skip function execution
CLASS(HookEvent)
class YrTechnoFireEvent : public YrHookOverrideReturn<BulletClass*>
{
public:
    TechnoClass* pTechno;
    AbstractClass* pTarget;
    int nWeaponIndex;
};

// in cpp files
// broadcast hook event and initialize event data
BROADCAST_HOOK_EVENT(0x70C249, 0x5, YrTechnoLoadGameEndEvent)
{
    E->pTechno = reinterpret_cast<TechnoClass*>(gSavingObject);
    E->stream  = gSavingStream;
}
// where to jump if the return value is overrided
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrTechnoFireEvent, 0x6FDD50, 0x6FDE0B)
// broadcast hook event and initialize event data
BROADCAST_HOOK_EVENT(0x6FDD50, 0x6, YrTechnoFireEvent)
{
    E->pTechno      = R->ECX<TechnoClass*>();
    E->pTarget      = R->Stack<AbstractClass*>(0x4);
    E->nWeaponIndex = R->Stack<int>(0x8);
}

```

### ComponentTarget

```cpp
CLASS(ComponentTarget = [TechnoClass, BulletClass, TerrainClass, AnimClass])
class AudioComponent final
{
public:
    template<typename TargetType>
    static void OnEntityConstruct(entt::registry& reg, entt::entity entity, TargetType* pYrObject) {
        // ...
    }

    AudioComponent() = default;
    AudioComponent(AudioComponent&&) = default; // NOTICE: write this ctor to avoid double construction by entt
    ~AudioComponent();
    // ...
private:
    static void CreateAudioComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};
```

### IniComponent

```cpp
CLASS(IniComponent, ComponentTarget = [TechnoTypeClass])
struct HelldiverTypeComponent final
{
    PROPERTY(IniField = "Helldiver.Stratagems")
    std::vector<HelldiverStratagem*> stratagems;

};
```

### IniAutoLoad

### BindJs

## Enum Meta Keywords
The keyword `ENUM` writing before an enum is used to specify enum meta:
```cpp
ENUM()
enum class EPhysicShapeType : unsigned int {
    Auto,
    Sphere,
    Box,
    Capsule,
    Cylinder,
};
```


## Member Meta Keywords
The keyword `PROPERTY` writing before a class member is used to specify class member meta:
```cpp
CLASS(BindJs, IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass, TerrainTypeClass, AnimTypeClass])
struct PhysicsTypeComponent final
{
    PROPERTY(IniField = "Physics.Sensor")
    bool isSensor {false};
    PROPERTY(IniField = "Physics.Shape")
    EPhysicShapeType shapeType {EPhysicShapeType::Auto};
    PROPERTY(IniField = "Physics.Mass")
    float mass {0.0f};
    PROPERTY(IniField = "Physics.HalfExtent")
    Vector3D<float> halfExtent {0.5f, 0.5f, 0.5f};

    JPH::Ref<JPH::ShapeSettings> shapeSettings;
};
```
This keyword always combine with keyword `CLASS` or `ENUM`

### IniField

## Reflection
