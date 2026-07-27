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

## Meta Syntax
Each meta keyword accepts a comma-separated list of specifiers inside the parentheses. There are three specifier forms:

- **Tag**: a bare identifier, e.g. `CLASS(BindJs)`
- **Key-Value**: `Key = Value`, e.g. `CLASS(IniSection = "GAS")`
- **String List**: `Key = [Item1, Item2]`, e.g. `CLASS(ComponentTarget = [TechnoTypeClass, BulletTypeClass])`

Multiple specifiers can be combined: `CLASS(BindJs, IniComponent, ComponentTarget = [TechnoTypeClass])`.

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

### AutoSavegame
Tag `AutoSavegame` indicates that this class should be serialized when saving/loading the game.
The tool generates a `Serialize` function for the class. By default only members tagged with `PROPERTY(Savegame)` are serialized (see [Savegame](#savegame)).
```cpp
CLASS(BindJs, AutoSavegame)
class AudioComponent final
{
    // ...
    PROPERTY(Savegame)
    std::shared_ptr<WwiseSoundBank> soundBank;
    PROPERTY(Savegame)
    AkPlayingID playingID;
};
```

### Swizzleable
Tag `Swizzleable` is used together with `AutoSavegame`. In YR savegames, pointers are stored as raw addresses and need "swizzle" fix-up on load. When this tag is present, the generated serialize code calls `SwizzleManagerClass::Instance->Here_I_Am` to fix the object pointer.
```cpp
CLASS(BindJs, IniComponent, ComponentTarget = [TechnoTypeClass], AutoSavegame, Swizzleable)
struct PhysicsTypeComponent final
{
    // ...
};
```

### IniSection
When combined with `IniComponent`, the key-value `IniSection` specifies a global INI section name. The component will be loaded as a singleton from that section.
```cpp
CLASS(IniComponent, IniSection = "GAS")
struct AbilitySystemGlobals
{
    // loaded from [GAS] section
    PROPERTY()
    GameplayTag ActivateFailCanActivateAbilityTag;
};
```

### AllVisible
Tag `AllVisible` makes all members (including private and protected) visible to code generation, without needing to tag each one with `PROPERTY` or `FUNCTION`.

### AllPublicVisible
Tag `AllPublicVisible` makes all public members visible to code generation. Private and protected members still need explicit `PROPERTY`/`FUNCTION` tags.

### AllSavegame
Tag `AllSavegame` makes all members (including private and protected) serialized when the class has `AutoSavegame`. Without this, only members tagged with `Savegame` are serialized.

### AllPublicSavegame
Tag `AllPublicSavegame` makes all public members serialized when the class has `AutoSavegame`. Private and protected members still need explicit `Savegame` tags.


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

### BindJs
Tag `BindJs` on an enum indicates that the enum should be wrapped to javascript side.
```cpp
ENUM(BindJs)
enum EGameplayModOpType : int
{
    AddBase,
    MultiplyAdditive,
    // ...
};
```

## Enum Constant Meta Keywords
The keyword `META` writing after an enum constant is used to attach extra meta to that constant:
```cpp
ENUM(BindJs)
enum EGameplayModOpType : int
{
    AddBase             META(DisplayName = "Add (Base)"),
    MultiplyAdditive    META(DisplayName = "Multiply (Additive)"),
    Max                 META(Hidden, DisplayName = "Invalid"),
    Additive = 0        META(Hidden), // Backwards compat name
};
```

### DisplayName
Key-value `DisplayName` sets a human-friendly display name for the enum constant.

### Hidden
Tag `Hidden` hides the enum constant from display/UI.

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

`FUNCTION` can also be used on global (free) functions at module scope. For a global function to be wrapped to javascript, it must be tagged with `FUNCTION(BindJs)`:
```cpp
FUNCTION(BindJs)
void GlobalHelperFunction();
```

For class member functions, the `BindJs` tag on the class controls whether the function is wrapped; individual member functions only need `FUNCTION()`.


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

### Savegame
Tag `Savegame` on a property indicates that the field should be serialized in savegames. This is only effective when the enclosing class has `AutoSavegame`. Without `Savegame` (or `AllSavegame`/`AllPublicSavegame` on the class), the field is skipped during serialization.
```cpp
CLASS(AutoSavegame, Swizzleable)
class HelldiverStratagemInst
{
public:
    PROPERTY(Savegame)
    HelldiverStratagem* type;
    PROPERTY(Savegame)
    SuperClass* super;
};
```


## Visibility Rules
By default, only members explicitly tagged with `PROPERTY` or `FUNCTION` participate in code generation (reflection registration, JS binding, etc.). The class-level tags below can override this:

| Tag | Private / Protected | Public |
|-----|---------------------|--------|
| (none) | needs `PROPERTY` / `FUNCTION` | needs `PROPERTY` / `FUNCTION` |
| `AllPublicVisible` | needs `PROPERTY` / `FUNCTION` | auto-visible |
| `AllVisible` | auto-visible | auto-visible |

The same pattern applies to savegame serialization with `AllSavegame` / `AllPublicSavegame` (requires `AutoSavegame` on the class).

The `inject_meta.scriban` template can also inject `BindJs` / `AllPublicVisible` tags automatically for specific modules (e.g. `YRpp`, `Wwise`, `gainput`), so game types do not need manual tagging.


## Reflection
The reflection system is built on top of [entt::meta](https://github.com/skypjack/entt/wiki/Crash-Course:-runtime-reflection-system). The CppHeaderTool generates registration code that registers classes, enums, functions, and fields into the entt meta context.

### Generated Registration
For each tagged class, the tool generates a `__Gen_Type_<ClassName>__Register()` function that:
1. Creates an `entt::meta_factory` for the type
2. Registers base classes via `factory.base<BaseType>()`
3. Registers constructors, functions, and data members
4. Attaches extra metadata via `.custom<>()` (see [Metadata Structures](#metadata-structures))
5. Registers component targets, INI loaders, and serialization functions if applicable

These register functions are called from the module-level `Register()` / `Unregister()` functions, which are invoked during module startup/shutdown.

### Metadata Structures
The reflection system stores extra metadata alongside entt::meta. These structures are defined in `src/core/reflection/reflection.h`:

| Structure | Attached To | Purpose |
|-----------|-------------|---------|
| `ClassMeta` | class type | stores class name and reference conversion functions |
| `FieldMeta` | data member | stores field name |
| `FunctionMeta` | function | stores function name and parameter metadata |
| `ParameterMeta` | function parameter | stores parameter name |
| `EnumMeta` | enum type | stores enum name |
| `EnumConstantMeta` | enum constant | stores constant name |
| `ArrayMeta` | array type | stores element type and count |

### Runtime API
The `Reflection` class in `src/core/reflection/reflection.h` provides runtime helpers:

```cpp
// Get enum value from string
template<typename T>
static bool TryGetEnumValue(std::string_view str, T& value);

// Get enum value name from value
template<typename T>
static std::string_view GetEnumValueName(T value);

// Cast pointer between related types
static void* CastPtr(const entt::type_info& from, const entt::type_info& to, void* ptr);
```

### Reference Conversion
When a class derives from a base class, the tool generates reference conversion functions via `register_ref_convertion<Base, Derived>()`. This allows casting a base reference to a derived reference through the meta system, stored in `ClassMeta::refConv`.

### Generated Body
The `GENERATED_BODY(type_name)` macro declares the generated registration code as friends of the class, so private members can be accessed:
```cpp
class GameplayAbility
{
    GENERATED_BODY(GameplayAbility);
    // ...
};
```
This expands to friend declarations for `__Gen_Type_<type_name>`, `__JsRegister_<type_name>`, and `Serialize_<type_name>`.

### Meta Context
The entt meta context is managed via `sync_meta_ctx()`. Each module's `Register()` / `Unregister()` calls `sync_meta_ctx()` first to ensure the shared context is active.