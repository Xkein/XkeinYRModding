# `all_data_binding.h` 说明

文件位置：[src/scripting/javascript/all_data_binding.h](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/all_data_binding.h)

## 一句话总结

**puerts（JS 绑定）的集中类型预注册表**。所有要在 JS 中暴露的类型（普通 C++ 类、容器、委托、`ScriptFunction<FUNC>` 等）必须先在这里登记，puerts 才能在生成的绑定代码里解析它们的 `ScriptTypeName` / `Converter`。

整个文件被 `#ifndef __HEADER_TOOL__` 包裹 —— 内容只参与 JS 绑定的编译，**不参与 CppHeaderTool 反射代码生成**。

## 什么时候需要往里面加东西

满足以下任一条件就要加：

1. **新增 `CLASS()` 宏暴露给 JS 的类型**，且其方法/属性签名里引用了尚未登记的类型（参数、返回值、成员类型）→ 把被引用的类型登记进来。
2. **新增要暴露给 JS 的 `TDelegate<FUNC>` / `TMulticastDelegate<FUNC>`** →
   - 在本文件加 `UsingTDelegate(FUNC)` / `UsingTMulticastDelegate(FUNC)`；
   - 同时在 [delegate_binding.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/delegate_binding.cpp) 的 `__JsRegister_Delegates()` 里加对应的 `RegisterTDelegate<FUNC>()` / `RegisterTMulticastDelegate<FUNC>()`。
   - **两侧必须 1:1 对应**，否则 puerts 编译期找不到类型。
3. **新增 `TDelegateRegistration<FUNC>` / `TMulticastDelegateRegistration<FUNC>`** → 同上，配对加 `UsingT*Registration(FUNC)` 和 `RegisterT*Registration<FUNC>()`。
4. **新增 `ScriptFunction<FUNC>`**（即给委托 `BindScriptFunction` / `AddScriptFunction` 用的脚本函数包装）→ 加 `UsingScriptFunction(FUNC)`，并且其 `FUNC` 签名通常对应一个已登记的 `UsingTDelegate(FUNC)`。
5. **在暴露给 JS 的签名中用到 `std::vector<T>`** → 加 `UsingStdVector(T)`。
6. **在暴露给 JS 的签名中用到 `std::map<K, V>`** → 加 `UsingStdMap(K, V)`。
7. **在暴露给 JS 的签名中用到 `TDelegate<T>` / `TMulticastDelegate<T>` 作为参数/返回值/属性类型** → 必须在文件中先 `UsingTDelegate(T)` / `UsingTMulticastDelegate(T)`，否则绑定代码无法编译。

## 什么时候**不**需要往里面加东西

- 仅在 C++ 内部使用、不暴露给 JS 的类型 —— 不登记。
- 已经在 [yr_data_bindings.h](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/yr_data_bindings.h) 中登记过的 YR 原生类（`AbstractClass`、`TechnoClass` 等通过 `UsingYrClass` 登记的）—— 本文件已经 `#include` 它了，不重复。
- CppHeaderTool 反射阶段（`__HEADER_TOOL__` 下所有 `Using*` 宏都被定义为空）。

## 文件被谁使用（include 关系）

| 消费者 | 作用 |
| --- | --- |
| [src/template/js_module_cpp.scriban](file:///d:/Dev/proj/YR/XkeinYRModding/src/template/js_module_cpp.scriban) | 代码生成模板：为每个 `CLASS()` 标注的类生成 `__JsRegister_<Class>()`。被引用的所有类型必须在此先登记。 |
| [src/scripting/javascript/yr_containers.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/yr_containers.cpp) | YR 容器（`VectorClass` / `DynamicVectorClass` / `IndexClass` / `HashTable` 等）的注册实现。 |
| [src/scripting/javascript/script_function_binding.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/script_function_binding.cpp) | `ScriptFunction<FUNC>` 各实例的 `DefineClass` 注册实现。 |
| [src/scripting/javascript/js_events.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/js_events.cpp) | `JsGameEvents` / `JsEvents` 等事件类型的注册实现。 |
| [src/scripting/javascript/delegate_binding.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/delegate_binding.cpp) | `FDelegateHandle`、`TDelegate<FUNC>`、`TMulticastDelegate<FUNC>` 及对应 `*Registration` 的 `DefineClass` 模板显式实例化。 |

## 文件里都有些什么

按出现顺序，文件由以下若干"按模块分组的 include + Using\* 宏"块组成：

### 1. GAS（Gameplay Ability System）类型 —— 第 4–150 行
- 通过 `#include "xkein/GameplayAbilities/..."` 拉入所有 GAS 头文件。
- `UsingCppType(...)`：`ActiveGameplayEffectHandle`、`AbilitySystemComponent`、`GameplayEffect`、`GameplayTag`、`GameplayAbilitySpec`、`GameplayCueNotify_*`、`AbilityTask_*` 等几十个类型。
- `UsingStdVector(...)`：`std::vector<AttributeSet>`、`std::vector<GameplayTag>`、`std::vector<GameplayEffect*>` 等用于 GAS API 中的 vector 形参/返回值。

### 2. JS 事件类型 —— 第 155–162 行
- `JsGameEvents` / `JsPhysicsEvents` / `JsEventOnCtor` / `JsEventOnDtor` / `JsEvents`。
- 用 `UsingCppTypeWithRefCache`（带引用缓存 converter，因为这些是值语义的全局单例引用）。
- `JsCppHelper` 同样用 ref cache。

### 3. 脚本 / 字符串 / 音频 / 物理 / 输入 —— 第 164–191 行
- `ScriptFunctionBase`、`ScriptFunctionRegister`、`StringName`；
- `WwiseSoundBankRef`、`AudioSystem`、`AudioComponent`；
- `PhysicsComponent`、`PhysicsTypeComponent`、碰撞结果类型；
- `Input`、`gainput::InputMap`、`gainput::InputManager` 等；
- `MuteFunctionPtr(std::remove_pointer_t<gainput::FilterFunc_T>)` —— 函数指针类型，仅为通过编译、不真正绑定。

### 4. YR 模块工具类 —— 第 193–220 行
- `XkeinTools`、`QueryVolume`、`QuerySphere`；
- `YrEntityAbstractComponent`；
- `IniReader`（+ `UsingReferenceConverter`，因为某 API 取 `IniReader&`）；
- `IniComponentLoader`、`YrHelper`、`Serialization`；
- 网络：`EventPack<unsigned char[99]>`、`VariantEventPack`、`NetPackDispatch`；
- `YrInputBlocker`。

### 5. YR Hook 事件系统 —— 第 218–401 行
- `YrHookEventSystem`、`YrHookContext`；
- `YrHookOverrideReturn<T>` 的若干显式特化（`void`、`Action`、`bool`、`int`、`DamageState`、`Vector3D<int>*`、`BulletClass*`、`FireError`、`long`）。
- 大量 `Yr*Event`（`YrAircraftCtorEvent`、`YrTechnoFireEvent`、`YrWarheadTypeLoadIniEvent` 等等，覆盖 YR 几乎所有可挂钩事件）。

### 6. 委托类型集中区 —— 第 403–494 行
**这是最容易遗漏、最需要人工维护的区域**：

- `UsingCppType(FDelegateHandle)` —— 委托句柄。
- `UsingTDelegate(FUNC)` —— 单播委托。每条都对应 `delegate_binding.cpp` 中 `RegisterTDelegate<FUNC>()` 的一次实例化。
- `UsingTDelegateRegistration(FUNC)` —— 带注册器的单播委托（不暴露 `Execute`）。
- `UsingTMulticastDelegate(FUNC)` —— 多播委托。每条对应 `RegisterTMulticastDelegate<FUNC>()`。
- `UsingTMulticastDelegateRegistration(FUNC)` —— 带注册器的多播委托。
- `UsingScriptFunction(FUNC)` —— `ScriptFunction<FUNC>`，用于 `BindScriptFunction(ScriptFunction<Func>*)` / `AddScriptFunction(ScriptFunction<Func>*)` 重载的参数类型解析。每个 `FUNC` 应该与上面某个 `UsingTDelegate` / `UsingTMulticastDelegate` 的签名匹配。

## 宏速查（来自 [cpp_binding.h](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/cpp_binding.h) / puerts）

| 宏 | 作用 |
| --- | --- |
| `UsingCppType(CLS)` | 登记普通 C++ 类型，生成 `ScriptTypeName` / `CDataPointerConverter`。 |
| `UsingStdVector(CLS)` | 登记 `std::vector<CLS>`（展开为 `UsingContainer(std::vector<CLS>)`）。 |
| `UsingStdMap(KEY, VALUE)` | 登记 `std::map<KEY, VALUE>`（展开为 `UsingContainer(std::map<KEY, VALUE>)`）。 |
| `UsingTDelegate(FUNC)` | 登记 `TDelegate<FUNC>`。**必须**与 `delegate_binding.cpp` 的 `RegisterTDelegate<FUNC>()` 一一对应。 |
| `UsingTMulticastDelegate(FUNC)` | 登记 `TMulticastDelegate<FUNC>`。**必须**与 `RegisterTMulticastDelegate<FUNC>()` 一一对应。 |
| `UsingTDelegateRegistration(FUNC)` | 登记 `TDelegateRegistration<FUNC>`。配对 `RegisterTDelegateRegistration<FUNC>()`。 |
| `UsingTMulticastDelegateRegistration(FUNC)` | 登记 `TMulticastDelegateRegistration<FUNC>`。配对 `RegisterTMulticastDelegateRegistration<FUNC>()`。 |
| `UsingScriptFunction(FUNC)` | 登记 `ScriptFunction<FUNC>`。通常 `FUNC` 来自已有的委托签名。 |
| `UsingCppTypeWithRefCache(CLS)` | `UsingCppType(CLS)` + 带 ref cache 的 converter（适合值语义但 JS 端持引用的对象）。 |
| `UsingReferenceConverter(CLS)` | 额外登记 `CLS&` 的 converter。 |
| `MuteFunctionPtr(CLS)` | 仅给函数指针类型一个名字以通过编译，不真正生成绑定。 |

## 检查清单（修改本文件前对照）

- [ ] 新类型已经 `#include` 对应头文件。
- [ ] 把声明放在 `#ifndef __HEADER_TOOL__` 之内。
- [ ] 若是委托 / `ScriptFunction`，已在 [delegate_binding.cpp](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/delegate_binding.cpp) 的 `__JsRegister_Delegates()` 加了配对的 `RegisterT*<FUNC>()`。
- [ ] 若是 `std::vector<T>`，确认 `T` 本身也已 `UsingCppType` 登记。
- [ ] 若是 `std::map<K, V>`，确认 `K` 和 `V` 本身也已 `UsingCppType` 登记。
- [ ] 不重复登记（YR 原生类已在 [yr_data_bindings.h](file:///d:/Dev/proj/YR/XkeinYRModding/src/scripting/javascript/yr_data_bindings.h) 处理）。
- [ ] 不要在这里写 `CLASS()`、`PROPERTY()`、`FUNCTION()` 反射宏 —— 那是 CppHeaderTool 的事，本文件只服务 puerts。
