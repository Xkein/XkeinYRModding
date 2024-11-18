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

### HookEvent

### IniComponent

### ComponentTarget

### BindJs

### IniAutoLoad

## Enum Meta Keywords


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
