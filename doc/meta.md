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
It is recommended to use YrExtension to manager your module initialization and cleaning for below reasons:
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
When the game reaching the hook address,  HookEvent is used to store the transient data.

> This keyword can **only be used in YrExtCore module**!

See the code below:
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
Component can be automatically attach to game entitys if the type is match the list of ComponentTarget.

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
When we want loading configs from ini, the tag `IniComponent` will generate the ini loding code and do loading job after loading of `ComponentTarget`.
```cpp
CLASS(IniComponent, ComponentTarget = [ThemeControl])
struct ThemeComponent final
{
    PROPERTY(IniField = "Theme.Enable")
    bool enable {false};
    PROPERTY(IniField = "Theme.SoundBank")
    std::string_view soundBankName;
    PROPERTY(IniField = "Theme.PlayEvent")
    WwiseStringID playEvent;
    
    std::shared_ptr<WwiseSoundBank> soundBank;
    AkPlayingID playingID;
};
```

### IniAutoLoad
Sometime we want to load a global section in ini and the tag `IniAutoLoad` combined with `IniComponent` can do this work.
```cpp
CLASS(IniComponent, IniAutoLoad)
struct Stratagem
{
    PROPERTY(IniField = "Sequence")
    std::string_view sequence;
    PROPERTY(IniField = "Shared")
    bool shared {false};
    PROPERTY(IniField = "SuperWeapon")
    SuperWeaponTypeClass* swType;
};
```


### BindJs
Tag `BindJs` indicated that this class or struct should be wrapped to javascript side.
> Only the fields tagged by `PROPERTY` and function tagged by `FUNCTION` will be wrapped.
```cpp
CLASS(BindJs)
class PhysicsCollisionAddAndPersistResult
{
public:
    PROPERTY()
    PhysicsComponent* com1;
    PROPERTY()
    PhysicsComponent* com2;
    PROPERTY()
    CoordStruct point;
    PROPERTY()
    Vector3D<float> normal;
};
```


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

## Function Meta Keywords
The keyword `FUNCTION` writing before an function is used to specify function meta:
```cpp
CLASS(/*...*/)
class AClass
{
public:
    FUNCTION()
    void func() {}
};
```


## Member Meta Keywords
The keyword `PROPERTY` writing before a class member is used to specify class member meta:
```cpp
CLASS(/*...*/)
struct PhysicsTypeComponent final
{
    // ...
    PROPERTY(IniField = "Physics.HalfExtent")
    Vector3D<float> halfExtent {0.5f, 0.5f, 0.5f};

    JPH::Ref<JPH::ShapeSettings> shapeSettings;
};
```
This keyword always combine with keyword `CLASS`

### IniField
By default, the member will be loaded by its member name.

To custom the ini key of the member, use tag `IniField`.
```cpp
CLASS(BindJs, IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass, TerrainTypeClass, AnimTypeClass])
struct PhysicsTypeComponent final
{
    // ...
    PROPERTY(IniField = "Physics.HalfExtent")
    Vector3D<float> halfExtent {0.5f, 0.5f, 0.5f};

    JPH::Ref<JPH::ShapeSettings> shapeSettings;
};
```


## Reflection