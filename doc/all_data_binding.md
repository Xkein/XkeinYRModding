# JS 数据绑定体系说明

文件位置：[src/scripting/javascript/all_data_binding.h](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/all_data_binding.h)
> 脚本作者视角的使用指南见 [ScriptFunction 指南](script_function.md)

## 一句话总结

**puerts（JS 绑定）的集中类型预注册表 + 配套实现文件群**。所有要在 JS 中暴露的类型（普通 C++ 类、容器、委托、`ScriptFunction<FUNC>` 等）必须先在 `all_data_binding.h` 登记，再在对应的 `.cpp` / `.h` 实现文件里完成 `DefineClass` 注册，puerts 才能在生成的绑定代码里解析它们的 `ScriptTypeName` / `Converter`。

`all_data_binding.h` 被 `#ifndef __HEADER_TOOL__` 包裹 —— 内容只参与 JS 绑定的编译，**不参与 CppHeaderTool 反射代码生成**。

## 整体架构：声明与实现分离

JS 绑定采用"**声明在头文件，实现在 cpp**"的两段式：

| 阶段 | 文件 | 职责 |
| --- | --- | --- |
| **声明** | `all_data_binding.h` | 通过 `Using*` 宏向 puerts 注册类型的 `ScriptTypeName` / `Converter`，使类型"可被识别"。 |
| **实现** | `delegate_binding.cpp` | 对 `FDelegateHandle`、`TDelegate<FUNC>`、`TMulticastDelegate<FUNC>` 及 `*Registration` 做 `DefineClass` + 方法/属性绑定 + `Register()`。 |
| | `script_function_binding.cpp` | 对 `ScriptFunction<FUNC>` 做 `DefineClass` + `Extends<ScriptFunctionBase>` + 构造函数绑定。 |
| | `script_function_wrappers.h` | 为每个 `FUNC` 生成一个具名派生结构体（`CLASS(BindJs)`），供反射系统引用；末尾用 `UsingCppType` 注册这些派生类。 |
| | `yr_containers.cpp` | 对 YR 容器（`VectorClass` / `DynamicVectorClass` / `TypeList` / `IndexClass`）及 STL 容器（`std::vector` / `std::map` / `std::set`）做 `DefineClass` 注册。 |
| | `yr_structs.cpp` | 对 YR 值类型结构体（`Vector2D` / `Vector3D` / `ColorStruct` / `Quaternion` / `DirStruct` / `RectangleStruct` / `Matrix3D` / `CDTimerClass`）做 `DefineClass` 注册。 |

**核心原则**：声明侧（`all_data_binding.h`）和实现侧（各 `.cpp`）的 FUNC 签名列表必须 **1:1 对应**，否则 puerts 编译期找不到类型或链接期找不到 `DefineClass` 实例化。

所有实现文件的入口函数均命名为 `__JsRegister_*()`，通过 `GLOBAL_INVOKE_ON_CTOR(...)` 在全局构造期自动执行，无需手动调用。

## 什么时候需要往里面加东西

满足以下任一条件就要加：

1. **新增 `CLASS()` 宏暴露给 JS 的类型**，且其方法/属性签名里引用了尚未登记的类型（参数、返回值、成员类型）→ 把被引用的类型登记到 `all_data_binding.h`。
2. **新增要暴露给 JS 的 `TDelegate<FUNC>` / `TMulticastDelegate<FUNC>`** → 需要同时修改 **3 个文件**：
   - `all_data_binding.h`：加 `UsingTDelegate(FUNC)` / `UsingTMulticastDelegate(FUNC)`；
   - `delegate_binding.cpp`：在 `__JsRegister_Delegates()` 里加 `RegisterTDelegate<FUNC>()` / `RegisterTMulticastDelegate<FUNC>()`；
   - `script_function_wrappers.h` + `script_function_binding.cpp` + `all_data_binding.h`：如果该委托签名需要支持 `BindScriptFunction` / `AddScriptFunction`，还需加 `UsingScriptFunction(FUNC)`（声明）+ `RegisterScriptFunction<FUNC>()`（实现）+ 对应 wrapper 结构体。
   - **两侧（声明 vs 实现）必须 1:1 对应**，否则 puerts 编译期找不到类型。
3. **新增 `TDelegateRegistration<FUNC>` / `TMulticastDelegateRegistration<FUNC>`** → 同上，配对加 `UsingT*Registration(FUNC)` 和 `RegisterT*Registration<FUNC>()`。
4. **新增 `ScriptFunction<FUNC>`**（即给委托 `BindScriptFunction` / `AddScriptFunction` 用的脚本函数包装）→ 需要同时修改 **3 个文件**：
   - `script_function_wrappers.h`：生成对应的具名 wrapper 结构体；
   - `all_data_binding.h`：加 `UsingScriptFunction(FUNC)`（展开为 `UsingCppType(ScriptFunction<FUNC>)`）；
   - `script_function_binding.cpp`：在 `__JsRegister_ScriptFunctions()` 里加 `RegisterScriptFunction<FUNC>()`。
   - 其 `FUNC` 签名通常对应一个已登记的 `UsingTDelegate(FUNC)` / `UsingTMulticastDelegate(FUNC)`。
5. **在暴露给 JS 的签名中用到 `std::vector<T>`** → `all_data_binding.h` 加 `UsingStdVector(T)`；若还需在 JS 中操作该 vector（`push_back` / `size` 等），还需在 `yr_containers.cpp` 的 `__JsRegister_YrContainers()` 里加 `RegisterStdVector<T>()`。
6. **在暴露给 JS 的签名中用到 `std::map<K, V>`** → `all_data_binding.h` 加 `UsingStdMap(K, V)`；若需 JS 操作，在 `yr_containers.cpp` 加 `RegisterStdMap<K, V>()`。
7. **在暴露给 JS 的签名中用到 `std::set<T>`** → `all_data_binding.h` 加 `UsingStdSet(T)`；若需 JS 操作，在 `yr_containers.cpp` 加 `RegisterStdSet<T>()`。
8. **在暴露给 JS 的签名中用到 `TDelegate<T>` / `TMulticastDelegate<T>` 作为参数/返回值/属性类型** → 必须在 `all_data_binding.h` 中先 `UsingTDelegate(T)` / `UsingTMulticastDelegate(T)`，否则绑定代码无法编译。
9. **新增 YR 容器实例**（如 `DynamicVectorClass<NewType*>`）→ 在 `yr_containers.cpp` 加 `REGISTER_DYNAMIC_VECTOR_CLASS(NewType*)` 等；若用到 `T**` 形态，还需加 `UsingPointer(NewType**)`。
10. **新增 YR 值类型结构体** → 在 `yr_structs.cpp` 的 `__JsRegister_YrStructs()` 里加 `DefineClass` + 方法/属性链式调用。值类型通常无需在 `all_data_binding.h` 登记（puerts 自动推导 Converter）。

## 什么时候**不**需要往里面加东西

- 仅在 C++ 内部使用、不暴露给 JS 的类型 —— 不登记。
- 已经在 [yr_data_bindings.h](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/yr_data_bindings.h) 中登记过的 YR 原生类（`AbstractClass`、`TechnoClass` 等通过 `UsingYrClass` 登记的）—— `all_data_binding.h` 已经 `#include` 它了，不重复。
- CppHeaderTool 反射阶段（`__HEADER_TOOL__` 下所有 `Using*` 宏都被定义为空）。
- YR 原生值类型结构体（`Vector2D` / `ColorStruct` 等）—— 仅需在 `yr_structs.cpp` 注册，无需在 `all_data_binding.h` 登记。

## 文件被谁使用（include 关系）

| 消费者 | 作用 |
| --- | --- |
| [src/template/js_module_cpp.scriban](file:///d:/Dev/proj/YR/XkeinYRModding/src/template/js_module_cpp.scriban) | 代码生成模板：为每个 `CLASS()` 标注的类生成 `__JsRegister_<Class>()`。被引用的所有类型必须在此先登记。 |
| [src/scripting/javascript/yr_containers.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/yr_containers.cpp) | `#include "all_data_binding.h"` —— 依赖其中的 `UsingCppType`（元素类型）和 `UsingStdVector`/`UsingStdMap`/`UsingStdSet`（容器 Converter）。 |
| [src/scripting/javascript/script_function_binding.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/script_function_binding.cpp) | `#include "all_data_binding.h"` —— 依赖 `UsingScriptFunction(FUNC)` 声明。 |
| [src/scripting/javascript/js_events.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/js_events.cpp) | `JsGameEvents` / `JsEvents` 等事件类型的注册实现。 |
| [src/scripting/javascript/delegate_binding.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/delegate_binding.cpp) | `FDelegateHandle`、`TDelegate<FUNC>`、`TMulticastDelegate<FUNC>` 及对应 `*Registration` 的 `DefineClass` 模板显式实例化。 |
| [src/scripting/javascript/script_function_wrappers.h](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/script_function_wrappers.h) | 被 `all_data_binding.h` 在顶部 `#include`，确保 wrapper 派生类先于 `UsingScriptFunction` 的隐式实例化被定义。 |

注意：`yr_structs.cpp` **不依赖** `all_data_binding.h`，它仅 `#include "yr_data_bindings.h"` —— 因为注册的都是 YR 原生值类型，puerts 自动推导 Converter，无需预声明。

## 各文件详解

### all_data_binding.h —— 声明中心

按出现顺序，文件大致分成以下 6 块，每块都是"按模块分组的 `#include` + `Using*` 宏"：

1. **GAS 类型**：拉入所有 Gameplay Ability System 头文件，登记 GAS 相关的类与 `std::vector` 实例。
2. **JS 事件类型**：`JsEvents` 等全局单例事件类型，用 `UsingCppTypeWithRefCache` 登记。
3. **脚本 / 字符串 / 音频 / 物理 / 输入**：跨模块的基础设施类型，含少量仅为通过编译的 `MuteFunctionPtr`。
4. **YR 模块工具类**：`XkeinTools`、`IniReader`、网络封包、`YrInputBlocker` 等。
5. **YR Hook 事件系统**：`YrHookEventSystem`、`YrHookOverrideReturn<T>` 特化，以及覆盖 YR 各类构造/析构/加载/存档事件的 `Yr*Event`。
6. **委托 / ScriptFunction 集中区**：最需要人工维护的一块。`FDelegateHandle`、各 `UsingTDelegate`/`UsingTMulticastDelegate`/`UsingT*Registration`、`UsingScriptFunction`，均需与对应实现文件 1:1 对应（详见下文各实现文件章节）。

> **新增模块时的放置策略**：以上 6 块只是当前现状。后续新增模块的类型登记，**首选放在文件开头**（紧跟 `#include "scripting/javascript/script_function_wrappers.h"` 之后、GAS 块之前），按"include 头文件 + `Using*` 宏"的形式成组添加，并在此列表中补一条说明。若新类型属于上述已有模块的范畴，则归入对应块。

### delegate_binding.cpp —— 委托实现

**文件位置**：[src/scripting/javascript/delegate_binding.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/delegate_binding.cpp)

**职责**：通过 `PUERTS_NAMESPACE::DefineClass<T>()` + `.Method()` / `.Property()` / `.Register()` 链式 API，为每种委托类型构建实际的 JS 类结构（方法/属性表）。

**注册模板函数**：

| 模板函数 | 对应的 all_data_binding.h 宏 | 导出的方法 | 不导出的方法 |
| --- | --- | --- | --- |
| `RegisterFDelegateHandle()` | `UsingCppType(FDelegateHandle)` | `Id` 属性、`IsValid`、`Reset` | — |
| `RegisterTDelegate<Func>()` | `UsingTDelegate(FUNC)` | `BindStdFunction`、`BindScriptFunction`（两重载）、`IsBound`、`Unbind`、`Execute`、`ExecuteIfBound`（仅 void 返回） | — |
| `RegisterTMulticastDelegate<Func>()` | `UsingTMulticastDelegate(FUNC)` | `AddStdFunction`、`AddScriptFunction`（两重载）、`Remove`、`Clear`、`IsBound` | `Broadcast` |
| `RegisterTDelegateRegistration<Func>()` | `UsingTDelegateRegistration(FUNC)` | `BindStdFunction`、`BindScriptFunction`、`IsBound`、`Unbind` | `Execute`、`ExecuteIfBound` |
| `RegisterTMulticastDelegateRegistration<Func>()` | `UsingTMulticastDelegateRegistration(FUNC)` | `AddStdFunction`、`AddScriptFunction`、`Remove`、`Clear`、`IsBound` | `Broadcast` |

**`BindScriptFunction` / `AddScriptFunction` 的重载**：通过 `CombineOverloads` 提供两个重载 —— 一个接受 `(const StringName&, const StringName&)`，另一个接受 `ScriptFunction<Func>*`。后者依赖 `ScriptFunction<Func>` 已在 `all_data_binding.h` 中通过 `UsingScriptFunction(FUNC)` 登记。

**入口函数**：`__JsRegister_Delegates()`，通过 `GLOBAL_INVOKE_ON_CTOR` 自动调用。

**修改时机**：在 `all_data_binding.h` 加了 `UsingTDelegate(FUNC)` / `UsingTMulticastDelegate(FUNC)` / `UsingT*Registration(FUNC)` 后，必须在此文件的 `__JsRegister_Delegates()` 中加配对的 `RegisterT*<FUNC>()`。FUNC 签名必须完全一致（包括参数顺序、const、引用、指针）。

**注意**：本文件**不负责** `ScriptFunction` 本身的注册。`ScriptFunction<Func>` 仅作为参数类型（裸指针 `ScriptFunction<Func>*`）出现在委托方法重载里。

### script_function_binding.cpp —— ScriptFunction 实现

**文件位置**：[src/scripting/javascript/script_function_binding.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/script_function_binding.cpp)

**职责**：对 `ScriptFunction<FUNC>` 做 `DefineClass` + `Extends<ScriptFunctionBase>` + 绑定接受 `std::function<Func>` 的构造函数。

**核心模板**：

```cpp
template<typename Func>
void RegisterScriptFunction()
{
    using FuncType = ScriptFunction<Func>;
    auto builder = PUERTS_NAMESPACE::DefineClass<FuncType>();
    builder.Extends<ScriptFunctionBase>();
    builder.Constructor<std::function<Func>>();
    RegisterCheck(builder);
}
```

**入口函数**：`__JsRegister_ScriptFunctions()`，逐一为每种 FUNC 签名实例化 `RegisterScriptFunction<FUNC>()`，通过 `GLOBAL_INVOKE_ON_CTOR` 自动调用。

**修改时机**：在 `all_data_binding.h` 加了 `UsingScriptFunction(FUNC)` 后，必须在此文件的 `__JsRegister_ScriptFunctions()` 中加 `RegisterScriptFunction<FUNC>()`。FUNC 签名必须与声明完全一致。

**与声明侧的关系**：
- `all_data_binding.h` 的 `UsingScriptFunction(FUNC)` → 展开为 `UsingCppType(ScriptFunction<FUNC>)`，注册"类型可被 puerts 识别"。
- `script_function_binding.cpp` 的 `RegisterScriptFunction<FUNC>()` → 把 `ScriptFunction<FUNC>` 绑定为"可被脚本构造的 puerts 类"。
- 两者 FUNC 列表完全一致（当前 36 条）。

### script_function_wrappers.h —— 具名包装结构体

**文件位置**：[src/scripting/javascript/script_function_wrappers.h](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/script_function_wrappers.h)

**职责**：为每个 `FUNC` 签名生成一个**具名派生结构体**，继承自 `ScriptFunction<FUNC>`，带 `CLASS(BindJs)` 反射宏和 `FUNCTION()` 标注的构造函数。这解决了"模板实例 `ScriptFunction<FUNC>` 没有独立类型名、无法被反射系统单独引用"的问题。

**单个 wrapper 结构体的模式**：

```cpp
CLASS(BindJs)
struct ScriptFunction_void__ : public ScriptFunction<void()>
{
    FUNCTION()
    ScriptFunction_void__(std::function<void()> func) : ScriptFunction(std::move(func)) { }
};
```

**文件末尾**在 `#ifndef __HEADER_TOOL__` 块中用 `UsingCppType(...)` 逐一注册这些包装类型：

```cpp
#ifndef __HEADER_TOOL__
#include "scripting/javascript/cpp_binding.h"
UsingCppType(ScriptFunction_void__);
UsingCppType(ScriptFunction_void_bool_);
// ...
#endif
```

**与其它文件的关系**：
- 被 `all_data_binding.h` 在顶部 `#include`（第 7 行），确保派生类先于 `UsingScriptFunction` 的隐式实例化被定义。
- `all_data_binding.h` 通过 `UsingScriptFunction(FUNC)` 注册的是**裸模板实例** `ScriptFunction<FUNC>`；本文件通过 `UsingCppType(包装名)` 注册的是**派生包装类**。两者是并行的两套绑定对象。
- `script_function_binding.cpp` 注册的也是**裸模板实例** `ScriptFunction<FUNC>`。

**修改时机**：新增 `ScriptFunction<FUNC>` 时，必须在此文件中新增对应的 wrapper 结构体。结构体名遵循 `FormatIdentifier` 命名规则（见下文）。

#### wrapper 类型名命名规则 —— `FormatIdentifier`

wrapper 结构体名 = `ScriptFunction_` + `FormatIdentifier(FUNC签名)`

`FormatIdentifier` 定义在 [3rdparty/CppHeaderTool/src/CppHeaderTool/Types/HtType.cs](file:///d:/Dev/proj/YR/XkeinYRModding/3rdparty/CppHeaderTool/src/CppHeaderTool/Types/HtType.cs) 第 24–37 行：

```csharp
public static string FormatIdentifier(this string fullName, bool replaceArrayBrackets = true)
{
    string identifier = fullName
        .Replace('<', '_')
        .Replace('>', '_')
        .Replace(':', '_')
        .Replace(',', '_')
        .Replace('*', '_')
        .Replace('&', '_')
        .Replace(" ", "")
        .Replace("(", "_").Replace(")", "_")
        .Replace("[", "_").Replace("]", "_");
    return identifier;
}
```

**规则**：将函数签名中的每个特殊字符 `< > : , * & ( ) [ ]` 替换为 `_`，空格被移除，结果前加前缀 `ScriptFunction_`。

> **注意**：实际生成的名字中，`const` 与类型名之间会出现 `_`（如 `ScriptFunction_void_const_GameplayEventData__`），说明生成器在调用 `FormatIdentifier` 之前，会先将签名按 token 拆分并用 `_` 连接（等价于空格也变成 `_`），而非直接删除空格。最终效果：**空格与每个特殊字符都变成 `_`**。

**FUNC 签名 → wrapper 类型名 对照示例**：

| FUNC 签名 | wrapper 类型名 |
| --- | --- |
| `void()` | `ScriptFunction_void__` |
| `void(bool)` | `ScriptFunction_void_bool_` |
| `GameplayCueNotify_Static* ()` | `ScriptFunction_GameplayCueNotify_Static___` |
| `void(const GameplayEventData&)` | `ScriptFunction_void_const_GameplayEventData__` |
| `void(const GameplayAttribute&, float&)` | `ScriptFunction_void_const_GameplayAttribute__float__` |
| `void(const GameplayAttribute&, float, float)` | `ScriptFunction_void_const_GameplayAttribute__float_float_` |
| `void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle)` | `ScriptFunction_void_AbilitySystemComponent__const_GameplayEffectSpec__ActiveGameplayEffectHandle_` |
| `bool(GameplayAbilityActorInfo, GameplayAbilitySpecHandle, GameplayTagContainer*)` | `ScriptFunction_bool_GameplayAbilityActorInfo_GameplayAbilitySpecHandle_GameplayTagContainer___` |
| `float(const GameplayEffectSpec&)` | `ScriptFunction_float_const_GameplayEffectSpec__` |
| `void(FAggregator*)` | `ScriptFunction_void_FAggregator___` |

**手动推导方法**：取 `ScriptFunction_` + FUNC 签名字符串，将其中所有 `< > : , * & ( ) [ ]` 和空格替换为 `_`，即为 wrapper 类型名。

### yr_containers.cpp —— 容器实现

**文件位置**：[src/scripting/javascript/yr_containers.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/yr_containers.cpp)

**职责**：注册 YR 自定义容器和 STL 容器的 JS 类结构（方法/属性/继承/构造）。

**注册的容器类型**：

| 模板 | 注册函数 | 继承关系 |
| --- | --- | --- |
| `VectorClass<CLS>` | `RegisterVectorClass<CLS>()` | — |
| `DynamicVectorClass<CLS>` | `RegisterDynamicVectorClass<CLS>()` | `Extends<VectorClass<CLS>>` |
| `TypeList<CLS>` | `RegisterTypeClass<CLS>()` | `Extends<DynamicVectorClass<CLS>>` |
| `CounterClass` | 内联 `DefineClass` | `Extends<VectorClass<int>>` |
| `IndexClass<TKey, TValue>` | `RegisterIndexClass<TKey, TValue>()` | — |
| `std::vector<CLS>` | `RegisterStdVector<CLS>()` | — |
| `std::map<TKey, TValue>` | `RegisterStdMap<TKey, TValue>()` | — |
| `std::set<T>` | `RegisterStdSet<T>()` | — |

**批量调用宏**：

```cpp
#define REGISTER_DYNAMIC_VECTOR_CLASS(CLS) \
    RegisterVectorClass<CLS>(); \
    RegisterDynamicVectorClass<CLS>();

#define REGISTER_TYPE_LIST(CLS) \
    REGISTER_DYNAMIC_VECTOR_CLASS(CLS); \
    RegisterTypeClass<CLS>();
```

**`UsingPointer` 声明**：文件顶部包含大量 `UsingPointer(T**)` 和 `UsingPointer(T*const*)` 声明，用于注册指针的指针形态，使 YR 容器（如 `DynamicVectorClass<TechnoClass*>`）内部以 `TechnoClass**` 暴露给 JS 时可被转换。这些声明**不在 `all_data_binding.h` 中**，由本文件自行维护。

**与 `all_data_binding.h` 的关系**：
- 本文件 `#include "all_data_binding.h"`。
- STL 容器的**元素类型**必须先在 `all_data_binding.h` 中 `UsingCppType` 登记（如 `UsingCppType(AttributeSet)`）。
- STL 容器本身的 **Converter** 也由 `all_data_binding.h` 的 `UsingStdVector` / `UsingStdMap` / `UsingStdSet`（即 `UsingContainer`）提供。
- 本文件负责的只是"定义容器的 JS 类结构"，而非"类型可识别"。

**入口函数**：`__JsRegister_YrContainers()`，通过 `GLOBAL_INVOKE_ON_CTOR` 自动调用。

**修改时机**：
- 新增 `DynamicVectorClass<NewType*>` → 加 `REGISTER_DYNAMIC_VECTOR_CLASS(NewType*)`，必要时加 `UsingPointer(NewType**)`。
- 新增 `std::vector<NewType>` → 先在 `all_data_binding.h` 加 `UsingStdVector(NewType)` 和 `UsingCppType(NewType)`，再在此文件加 `RegisterStdVector<NewType>()`。

### yr_structs.cpp —— 结构体实现

**文件位置**：[src/scripting/javascript/yr_structs.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/yr_structs.cpp)

**职责**：注册 YR 原生值类型结构体的 JS 类结构。

**注册的类型**：`Vector2D<T>`（int/short）、`Vector3D<T>`（int/double/float）、`ColorStruct`、`Quaternion`、`DirStruct`、`RectangleStruct`、`Matrix3D`、`CDTimerClass`。

**注册模式**：使用 `PUERTS_NAMESPACE::DefineClass<T>()` + 链式 `.Constructor()` / `.Property()` / `.Method()` / `.Function()` / `.Register()`。对于有泛型参数的（`Vector2D<T>`），使用接收 `ClassDefineBuilder` 右值的模板函数：

```cpp
template<typename T, typename API, typename RegisterAPI>
void RegisterVector2D(PUERTS_NAMESPACE::ClassDefineBuilder<Vector2D<T>, API, RegisterAPI>&& builder)
{
    builder
        .Constructor<T, T>()
        .Property("X", MakeProperty(&Vector2D<T>::X))
        .Property("Y", MakeProperty(&Vector2D<T>::Y))
        .Method("Magnitude", MakeFunction(&Vector2D<T>::Magnitude))
        // ...
        .Register();
}
```

对于 MSVC 推导歧义的成员，使用 `MakeMethodCheck<&Class::Method>(builder, "name")` / `MakePropertyCheck<&Class::Member>(builder, "name")` 辅助宏。

**与 `all_data_binding.h` 的关系**：
- 本文件**不依赖** `all_data_binding.h`，仅 `#include "yr_data_bindings.h"`。
- 注册的都是 YR 原生值类型（POD），puerts 自动推导 Converter，无需 `UsingCppType` 预声明。

**入口函数**：`__JsRegister_YrStructs()`，通过 `GLOBAL_INVOKE_ON_CTOR` 自动调用。

**修改时机**：新增 YR 值类型结构体时，在此文件的 `__JsRegister_YrStructs()` 中加 `DefineClass` + 链式调用。无需修改 `all_data_binding.h`。

## 宏速查（来自 [cpp_binding.h](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/cpp_binding.h) / puerts）

| 宏 | 作用 | 展开为 |
| --- | --- | --- |
| `UsingCppType(CLS)` | 登记普通 C++ 类型，生成 `ScriptTypeName` / `CDataPointerConverter`。 | — |
| `UsingStdVector(CLS)` | 登记 `std::vector<CLS>`。 | `UsingContainer(std::vector<CLS>)` |
| `UsingStdMap(KEY, VALUE)` | 登记 `std::map<KEY, VALUE>`。 | `UsingContainer(typedef std::map<KEY,VALUE>)` |
| `UsingStdSet(CLS)` | 登记 `std::set<CLS>`。 | `UsingContainer(std::set<CLS>)` |
| `UsingContainer(CLS)` | 登记 `__DefObjectType` + `__DefCDataPointerConverter`。 | — |
| `UsingTDelegate(FUNC)` | 登记 `TDelegate<FUNC>`。 | `UsingContainer(TDelegate<FUNC>)` + `ScriptTypeName` 特化 |
| `UsingTMulticastDelegate(FUNC)` | 登记 `TMulticastDelegate<FUNC>`。 | `UsingContainer(TMulticastDelegate<FUNC>)` + `ScriptTypeName` 特化 |
| `UsingTDelegateRegistration(FUNC)` | 登记 `TDelegateRegistration<FUNC>`。 | `UsingContainer(...)` + `ScriptTypeName` 特化 |
| `UsingTMulticastDelegateRegistration(FUNC)` | 登记 `TMulticastDelegateRegistration<FUNC>`。 | `UsingContainer(...)` + `ScriptTypeName` 特化 |
| `UsingScriptFunction(FUNC)` | 登记 `ScriptFunction<FUNC>`。 | `UsingCppType(ScriptFunction<FUNC>)` |
| `UsingCppTypeWithRefCache(CLS)` | `UsingCppType(CLS)` + 带 ref cache 的 converter（适合值语义但 JS 端持引用的对象）。 | — |
| `UsingReferenceConverter(CLS)` | 额外登记 `CLS&` 的 converter。 | — |
| `UsingPointer(PTR)` | 登记 `T**` / `T*const*` 等指针的指针形态（与 `void*` 互转）。 | `__DefScriptTTypeName` + `__DefObjectType` + `Converter` 特化 |
| `MuteFunctionPtr(CLS)` | 仅给函数指针类型一个名字以通过编译，不真正生成绑定。 | `ScriptTypeName` + 空 `Converter` 特化 |

## 完整修改检查清单

新增一个需要 JS 绑定的类型时，按以下清单逐项检查：

### 通用（所有类型）

- [ ] 新类型已经 `#include` 对应头文件。
- [ ] 把声明放在 `all_data_binding.h` 的 `#ifndef __HEADER_TOOL__` 之内。
- [ ] 不重复登记（YR 原生类已在 [yr_data_bindings.h](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/yr_data_bindings.h) 处理）。
- [ ] 不要在 `all_data_binding.h` 里写 `CLASS()`、`PROPERTY()`、`FUNCTION()` 反射宏 —— 那是 CppHeaderTool 的事，本文件只服务 puerts。

### 委托（TDelegate / TMulticastDelegate / *Registration）

- [ ] `all_data_binding.h`：加了 `UsingTDelegate(FUNC)` / `UsingTMulticastDelegate(FUNC)` / `UsingT*Registration(FUNC)`。
- [ ] `delegate_binding.cpp`：在 `__JsRegister_Delegates()` 中加了配对的 `RegisterT*<FUNC>()`。
- [ ] FUNC 签名两侧完全一致（参数顺序、const、引用、指针）。
- [ ] 若委托需要支持 `BindScriptFunction` / `AddScriptFunction`，确认对应的 `ScriptFunction<FUNC>` 也已登记（见下）。

### ScriptFunction

- [ ] `script_function_wrappers.h`：新增了对应的具名 wrapper 结构体（名称遵循 `FormatIdentifier` 规则）。
- [ ] `all_data_binding.h`：加了 `UsingScriptFunction(FUNC)`。
- [ ] `script_function_binding.cpp`：在 `__JsRegister_ScriptFunctions()` 中加了 `RegisterScriptFunction<FUNC>()`。
- [ ] 三处 FUNC 签名完全一致。

### STL 容器（std::vector / std::map / std::set）

- [ ] `all_data_binding.h`：加了 `UsingStdVector(T)` / `UsingStdMap(K, V)` / `UsingStdSet(T)`。
- [ ] 元素类型 `T` / `K` / `V` 本身已 `UsingCppType` 登记。
- [ ] 若需在 JS 中操作该容器（`push_back` / `size` / `at` 等），在 `yr_containers.cpp` 加 `RegisterStdVector<T>()` / `RegisterStdMap<K, V>()` / `RegisterStdSet<T>()`。

### YR 容器（VectorClass / DynamicVectorClass / TypeList / IndexClass）

- [ ] `yr_containers.cpp`：加了 `REGISTER_DYNAMIC_VECTOR_CLASS(T)` / `REGISTER_TYPE_LIST(T)` / `RegisterIndexClass<K, V>()`。
- [ ] 若用到 `T**` 形态，加了 `UsingPointer(T**)`。
- [ ] 元素类型已在 `all_data_binding.h` 或 `yr_data_bindings.h` 登记。

### YR 值类型结构体

- [ ] `yr_structs.cpp`：在 `__JsRegister_YrStructs()` 中加了 `DefineClass` + 方法/属性链式调用。
- [ ] 无需修改 `all_data_binding.h`（值类型 puerts 自动推导 Converter）。
