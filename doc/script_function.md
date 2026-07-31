# ScriptFunction 指南（ScriptFunction Guide）

本文档面向 mod 作者（TS/JS 脚本使用者），介绍 ScriptFunction 这一将 C++ 可调用对象暴露给脚本层，并通过注册表统一管理的机制。本文档所有事实表述均可溯源到 `src/` 下的源码引用。

## 概述（Overview）

### 1.1 ScriptFunction 是什么

ScriptFunction 是注册在 `ScriptFunctionRegister` 中的可调用对象（callable object），通过 **category + name** 组合唯一标识。脚本侧可以用 category 和 name 精确地注册、查找并调用某个可调用对象，而无需持有其指针本身。

- 可调用对象：`ScriptFunction<TFunc>` 继承自 `std::function<TFunc>`，因此本质上是一个带签名类型的可调用包装（`src/core/tool/script_function.h:21-26`）。
- 唯一标识：每个已注册的 ScriptFunction 以 `(category, name)` 为键存放在全局注册表 `GScriptFunctions` 中（`src/core/tool/script_function.cpp:6`、`:18-29`）。
- 使用场景：C++ 侧定义签名并绑定回调，脚本侧按 category/name 引用，两者通过注册表解耦。

> **English:** A ScriptFunction is a callable object registered in the ScriptFunctionRegister, uniquely identified by a category plus a name pair. The ScriptFunction<TFunc> type inherits from std::function<TFunc>, so it is essentially a typed callable wrapper, and the global registry stores each entry keyed by (category, name).

### 1.2 C++ 核心类型

ScriptFunction 机制由三个核心 C++ 类型构成（均定义于 `src/core/tool/script_function.h`）：

| 类型 | 说明 | 定义位置 |
| --- | --- | --- |
| `ScriptFunctionBase` | 基类，仅含 `name` / `category` 两个 `StringName` 属性 | `src/core/tool/script_function.h:11-19` |
| `ScriptFunction<TFunc>` | 模板，同时继承 `ScriptFunctionBase` 与 `std::function<TFunc>` | `src/core/tool/script_function.h:21-26` |
| `ScriptFunctionRegister` | 静态注册表，提供 RegisterFunction / RegisterLoader / GetFunction / GetId / GetFunctionById / GetFunctionAs | `src/core/tool/script_function.h:28-65` |

- `ScriptFunctionBase`：唯一的职责是携带 `name` 与 `category` 两个 `StringName` 属性，作为所有 ScriptFunction 的共同基类。
- `ScriptFunction<TFunc>`：模板类型，`TFunc` 是回调的函数签名；它同时是一个 `ScriptFunctionBase`（携带名字信息）和一个 `std::function<TFunc>`（可被直接调用）。
- `ScriptFunctionRegister`：静态注册表，负责注册、查找与解析：
  - `RegisterFunction(category, name, func)` / `RegisterLoader(category, loader)`：两种注册入口；
  - `GetFunction(category, name)` / `GetFunctionById(funcId)`：两种查找方式（按名 / 按 FuncId）；
  - `GetId(category, name)`：由 category + name 派生稳定标识；
  - `GetFunctionAs<TScriptFunction>(category, name)`：按名查找并做类型转换的模板方法。

> **English:** Three core C++ types make up this mechanism, all defined in src/core/tool/script_function.h. ScriptFunctionBase carries only the name and category StringName properties. ScriptFunction<TFunc> inherits both ScriptFunctionBase and std::function<TFunc>. ScriptFunctionRegister is the static registry exposing RegisterFunction, RegisterLoader, GetFunction, GetId, GetFunctionById and GetFunctionAs.

### 1.3 注册方式与文件地图

注册表提供两种注册方式：

1. **立即注册 `RegisterFunction(category, name, func)`**：调用时直接把 `func` 写入注册表，并同步写入 FuncId 映射（`src/core/tool/script_function.cpp:18-29`）。适合在脚本加载期确定注册的回调。
2. **惰性注册 `RegisterLoader(category, loader)`**：仅登记 loader（加载器），不立即注册具体函数；当按名查找未命中时，会按顺序调用该 category 下的 loader 补注册，再重新查找（`src/core/tool/script_function.cpp:31-38`、`:40-75`）。适合数量大、按需创建的回调集合。

文件地图：

| 层面 | 文件 | 职责 |
| --- | --- | --- |
| core 定义 | `src/core/tool/script_function.h` / `script_function.cpp` | 类型定义与注册表实现 |
| scripting 绑定 | `src/scripting/javascript/script_function_binding.cpp`、`script_function_wrappers.h` | 将各签名绑定到 JS 环境并生成具名 wrapper 类 |
| scripts typings | `src/scripts/javascript/typings/yr/scriptable.d.ts` | 脚本侧的 `ScriptFunction<TFunc>` 泛型环境声明与 `RegisterScriptFunction` 助手声明 |

> **English:** Two registration methods exist. RegisterFunction(category, name, func) registers the callable immediately, while RegisterLoader(category, loader) registers a lazy loader that only fires when a by-name lookup misses. File map: core definitions live in src/core/tool/script_function.h and .cpp; scripting bindings and named wrapper classes live in src/scripting/javascript/script_function_binding.cpp and script_function_wrappers.h; script-side typings live in src/scripts/javascript/typings/yr/scriptable.d.ts.

### 1.4 术语表

| 术语 | 含义 |
| --- | --- |
| ScriptFunction | 注册在 `ScriptFunctionRegister` 中的可调用对象本体，即继承 `ScriptFunctionBase` 与 `std::function<TFunc>` 的 `ScriptFunction<TFunc>` 实例 |
| wrapper | `script_function_wrappers.h` 中为每个已绑定签名生成的具名派生类（如 `ScriptFunction_void_GameplayAbility__`），脚本侧通常用具名类而非裸泛型 |
| FuncId | 由 category + name 派生的稳定标识，`FuncId = (uint64(category.GetId()) << 32) | name.GetId()`（`src/core/tool/script_function.cpp:13-16`），用于跨层引用注册表条目 |

> **English:** Glossary. ScriptFunction is the registered callable object itself, a ScriptFunction<TFunc> instance inheriting ScriptFunctionBase and std::function<TFunc>. A wrapper is a named derived class generated for each bound signature in script_function_wrappers.h. FuncId is the stable identifier derived from category plus name via (uint64(category.GetId()) << 32) | name.GetId(), used to reference registry entries across layers.

## 与委托的关系（Relationship with Delegates）

委托（delegate）是调用 ScriptFunction 的常用入口：`TDelegate`（单播）与 `TMulticastDelegate`（多播）都支持把回调绑定为某个已注册的 ScriptFunction，但绑定**只保存 FuncId、不缓存指针**，并在调用时经注册表重新解析。本节描述这两类绑定 API、FuncId 间接层、复制/移动语义，以及热重载下的绑定有效性。

### 2.1 绑定 API 总览

两类委托都提供两个 ScriptFunction 绑定重载，且**都只存 FuncId、不缓存指针**：

| 委托类型 | 按名绑定 | 按指针绑定 | 定义位置 |
| --- | --- | --- | --- |
| `TDelegate`（单播） | `BindScriptFunction(category, funcName)` | `BindScriptFunction(sf)` | `src/core/tool/delegate.h:140-151`、`:153-162` |
| `TMulticastDelegate`（多播） | `AddScriptFunction(category, funcName)` | `AddScriptFunction(sf)` | `src/core/tool/delegate.h:497-510`、`:512-523` |

- 按名绑定 `BindScriptFunction(category, funcName)`：先用 `ScriptFunctionRegister::GetFunctionAs<...>` 校验函数已注册，命中后仅保存 `GetId(category, funcName)` 派生出的 FuncId（`src/core/tool/delegate.h:141-151`）；若未注册则不绑定、保持原状态。
- 按指针绑定 `BindScriptFunction(sf)`：传入已创建的 ScriptFunction 指针，同样只保存 `GetId(sf->category, sf->name)`（`src/core/tool/delegate.h:154-162`）。
- `TMulticastDelegate::AddScriptFunction` 两个重载语义相同，区别是返回 `FDelegateHandle` 以便后续 `Remove(handle)`，并把监听记入 `m_scriptFunctionListeners` 向量（`src/core/tool/delegate.h:497-523`）。
- `ExecuteIfBound` 仅存在于 **void 返回类型**的 `TDelegate`：其模板参数用 `std::enable_if_t<std::is_void_v<R>>` 约束，绑定时才执行并返回 true（`src/core/tool/delegate.h:226-235`）；非 void 委托只能直接 `Execute`。

> **English:** Both delegate families expose two ScriptFunction binding overloads. TDelegate has BindScriptFunction(category, funcName) and BindScriptFunction(sf), while TMulticastDelegate has AddScriptFunction(category, funcName) and AddScriptFunction(sf) returning an FDelegateHandle. All four overloads store only a FuncId, never a cached pointer. ExecuteIfBound exists only on void-returning TDelegate, constrained by std::enable_if_t<std::is_void_v<R>> (delegate.h:226-235).

### 2.2 FuncId 间接层

委托绑定 ScriptFunction 的核心设计是**间接引用**：绑定对象里只有 FuncId 这个 `uint64_t`，没有任何函数指针或 `ScriptFunctionBase*` 缓存。

- `TDelegate` 用 `FScriptFunctionBinding{ uint64_t FuncId }` 存储（`src/core/tool/delegate.h:87-101`）；`TMulticastDelegate` 用 `FScriptFunctionListener{ FDelegateHandle Handle; uint64_t FuncId }` 存储（`src/core/tool/delegate.h:341-346`）。
- 调用时经 `ScriptFunctionRegister::GetFunctionById(funcId)` 解析回真实指针：`TDelegate::Execute`（`src/core/tool/delegate.h:195-216`）、`TMulticastDelegate::Broadcast`（`src/core/tool/delegate.h:608-615`）。
- 解析失败（函数未注册或已注销）不会崩溃：`TDelegate::Execute` 记录警告日志「ScriptFunction (FuncId=...) not found」，void 返回类型直接返回、非 void 返回 `Ret{}`（`src/core/tool/delegate.h:200-206`）；`TMulticastDelegate::Broadcast` 静默跳过该监听（`src/core/tool/delegate.h:613`）。

> **English:** The design is indirect: bindings hold only the uint64_t FuncId, never a raw pointer. TDelegate stores it in FScriptFunctionBinding (delegate.h:87-101); TMulticastDelegate in FScriptFunctionListener (delegate.h:341-346). At call time both resolve through ScriptFunctionRegister::GetFunctionById — TDelegate::Execute at delegate.h:195-216, TMulticastDelegate::Broadcast at delegate.h:608-615. A missing function never crashes: TDelegate logs a warning and returns Ret{} (delegate.h:200-206), while TMulticastDelegate silently skips the listener.

### 2.3 复制与移动的监听语义

复制/移动的监听语义**仅适用于 `TMulticastDelegate`**，`TDelegate` 的行为完全不同：

| 操作 | `TMulticastDelegate` 的监听 | `TDelegate` 的监听 |
| --- | --- | --- |
| 复制构造 / 复制赋值 | **全部丢弃**（entt 连接、lambda、ScriptFunction 均不复制） | 默认深拷贝（不丢弃） |
| 移动构造 / 移动赋值 | **保留 lambda 与 ScriptFunction 监听、仅丢弃 entt 连接** | 默认移动（不丢弃） |

- `TMulticastDelegate` 复制构造：只深拷贝 `m_signal`，`m_connections`、`m_lambdaListeners`、`m_scriptFunctionListeners` 全部保持为空（注释明确 "intentionally empty"，`src/core/tool/delegate.h:379-385`）；复制赋值同样 `clear()` 这三者（`src/core/tool/delegate.h:397-409`）。
- `TMulticastDelegate` 移动构造/移动赋值：`m_signal` 移动、`m_connections` 置空（旧连接指向被移动者的 signal，已失效）、`m_lambdaListeners` 与 `m_scriptFunctionListeners` 用 `std::move` 整体搬移、监听全部保留（`src/core/tool/delegate.h:388-394`、`:412-424`）。
- 对照：`TDelegate` 的复制构造/赋值、移动构造/赋值全部是 `= default`，即默认的深拷贝/移动，**不丢弃任何监听**（`src/core/tool/delegate.h:104-108`）。

> **English:** Copy/move semantics differ between the two types, and the "drops listeners" behavior applies only to TMulticastDelegate. Its copy constructor and copy assignment drop every listener — entt connections, lambdas, and ScriptFunction listeners are all intentionally emptied (delegate.h:379-385, 397-409). Its move constructor and move assignment keep the lambda and ScriptFunction listeners, discarding only the entt connections, which reference the source's signal (delegate.h:388-394, 412-424). In contrast, TDelegate's copy and move operations are all = default, i.e. plain deep copies that drop nothing (delegate.h:104-108).

### 2.4 热重载下的绑定（机制推导）

热重载场景下委托绑定是否仍然有效，可以由 FuncId 的派生机制推导：

- FuncId 由 category/name 的**内容哈希**派生：`StringName` 在构造时用 `std::hash<std::string>{}(*NameStr)` 缓存 `Id`（`src/core/string/string_name.h:28-30`），`GetId()` 直接返回该缓存值（`src/core/string/string_name.h:78-80`）；`FuncId = (uint64(category.GetId()) << 32) | name.GetId()`（`src/core/tool/script_function.cpp:13-16`）。
- 因此，只要热重载后以**相同的 category/name** 重新注册函数，委托持有的 FuncId 依然能通过 `GetFunctionById` 解析到新实例，**绑定仍然有效**。
- 注意：**此结论由 FuncId 内容哈希机制推导，非实测**；反向推论同样成立——若重载后 category 或 name 字符串发生变化，FuncId 也随之改变，旧绑定将无法解析。

> **English:** Whether a binding survives hot reload follows from how FuncId is derived. StringName caches Id as std::hash<std::string>{}(content) at construction (string_name.h:28-30), GetId() returns that cached value (string_name.h:78-80), and FuncId combines both parts as (uint64(category.GetId()) << 32) | name.GetId() (script_function.cpp:13-16). So as long as the function is re-registered under the same category and name after reload, the FuncId held by the delegate still resolves and the binding stays valid. This conclusion is derived from the FuncId content-hash mechanism, not from direct testing.

## 存档问题（Savegame / Archive）

存档/读档是脚本回调在持久化场景下的核心考验：游戏存档（AutoSavegame 反射标签与 cereal 序列化，见 `doc/meta.md:201-248`、`:347-371`）会把委托的绑定状态写盘、再在下次运行读回。委托的 cereal 序列化对不同类型的绑定采取截然不同的策略——**只有 `BindScriptFunction` / `AddScriptFunction` 绑定的回调能被保存与恢复**，其余绑定（entt 静态绑定、std::function lambda）要么被跳过、要么被静默丢弃。本节对照序列化三态、FuncId 稳定性、注册时机、读档惰性恢复与 GC 危险模型，全部事实可溯源到 `src/core/tool/delegate.h`、`src/core/string/string_name.h` 与 `src/core/tool/script_function.cpp`；`doc/gas.md` §16（第 1678-1762 行）已从「用法」角度给出结论（两种绑定方式对比、注册时机），本节从「机制」角度解释其所以然（FuncId 内容哈希、惰性解析、GC 危险模型），两处可互相参照。

### 3.1 序列化行为对照

两类委托的序列化行为按绑定方式分列如下：

| 绑定方式 | 存档行为 | 读档行为 | 源码位置 |
| --- | --- | --- | --- |
| `BindStdFunction` / `BindLambda`（std::function） | **不序列化**：`TDelegate` 记录警告并写 `"Unsupported"` 标记 | 变 unbound（monostate） | `src/core/tool/delegate.h:263-267`、`:294-297` |
| entt 静态绑定（`BindStatic` / `BindRaw`） | **不序列化**：与 std::function 同一分支，同样警告 + `"Unsupported"` | 变 unbound（monostate） | `src/core/tool/delegate.h:261-267` |
| `TMulticastDelegate` 的 lambda / entt 监听 | **不序列化**：**静默丢弃**、无警告（save 只遍历 `m_scriptFunctionListeners`，其余容器根本不写盘） | 读档后不再存在 | `src/core/tool/delegate.h:634-641` |
| `BindScriptFunction`（单播） | 保存 FuncId | 按 FuncId 重建绑定 | `src/core/tool/delegate.h:268-272`、`:279-298` |
| `AddScriptFunction`（多播） | 保存 FuncId 列表 | 按 FuncId 重建监听 | `src/core/tool/delegate.h:637-640`、`:643-653` |

序列化三态（`TDelegate::save` 按 variant 索引区分，`src/core/tool/delegate.h:254-277`）：

- `""`（未绑定，monostate，`:259`）
- `"Unsupported"`（不可序列化绑定：entt / std_function，存档时警告 + 写标记，`:263-267`）
- `"ScriptFunction"` + `FuncId`（可序列化的 ScriptFunction 绑定，`:269-271`）

读档分支：仅当 `Type == "ScriptFunction"` 时才重建 `FScriptFunctionBinding{FuncId}`；`""` / `"Unsupported"` / 未知类型一律落回 monostate（unbound），`src/core/tool/delegate.h:288-297`。

> 对照已有文档：`doc/gas.md:1010`（ASC multicast 存档说明：`AddScriptFunction` 存 FuncId、`AddStdFunction` 静默丢弃、仅单播记录警告）、`doc/gas.md:1678-1762`（§16 委托存档，两种绑定方式对比与注册时机）。

> **English:** This section compares serialization behavior across binding kinds. Only ScriptFunction bindings are persisted: TDelegate::save writes the FuncId and TMulticastDelegate::save writes the FuncId list. Non-serializable bindings (entt static bindings and std::function lambdas) are dropped: TDelegate logs a warning and writes the "Unsupported" marker so the load becomes unbound (monostate), while TMulticastDelegate silently discards them without any warning, since its save only iterates m_scriptFunctionListeners. The serialization has three states: "" for unbound, "Unsupported" for non-serializable bindings, and "ScriptFunction" plus FuncId for registered ScriptFunction bindings. See also doc/gas.md:1010 and doc/gas.md §16.

### 3.2 FuncId 稳定性

FuncId 能否跨会话恢复，取决于它的派生方式是否确定：

- `StringName` 在构造时用 `std::hash<std::string>{}(*NameStr)` 计算并缓存内容哈希到成员 `Id`（`src/core/string/string_name.h:28-30`），`GetId()` 直接返回该缓存值（`:78-80`）。因此**相同字符串构造的 `StringName` 恒有相同的 `Id`**，且是内容哈希（不是地址或序号）。
- `FuncId = (uint64(category.GetId()) << 32) | name.GetId()`（`src/core/tool/script_function.cpp:13-16`），把 category / name 两部分的 32 位内容哈希拼成一个 64 位标识。

推论：

- **同构建跨会话稳定**：同一二进制（同一编译器 + 同一标准库实现）下，存档写入的 FuncId 在下次运行读档时仍能经 `GetFunctionById` 解析，绑定可恢复。
- **跨编译器 / 标准库版本不保证**：`std::hash<std::string>` 的实现由标准库决定（MSVC STL、libstdc++、libc++ 各不相同），更换工具链或升级标准库后，同一字符串可能产生不同的 FuncId，旧存档中的 FuncId 可能无法在注册表中命中。

> **English:** FuncId stability rests on the content hash. StringName caches Id as std::hash<std::string>{}(content) at construction (string_name.h:28-30) and GetId() returns that cached value (string_name.h:78-80); FuncId combines both parts as (uint64(category.GetId()) << 32) | name.GetId() (script_function.cpp:13-16). Within the same build the FuncId is stable across sessions, so saved bindings can be restored after a reload. Across different compilers or standard-library versions stability is not guaranteed, because std::hash<std::string> is implementation-defined.

### 3.3 注册时机

脚本函数必须"在该在的时候已经在注册表里"，否则存档链路会在三个时间点出问题：

1. **绑定前**：`BindScriptFunction(category, funcName)` 先用 `ScriptFunctionRegister::GetFunctionAs<...>` 校验函数已注册，**未命中则不绑定、保持原状态**（`src/core/tool/delegate.h:141-151`）。函数未注册时，绑定这一步就静默失败了。
2. **存档前**：函数需已注册——`save` 只把 `FScriptFunctionBinding` 里已存的 FuncId 写盘，**不做任何校验**（`src/core/tool/delegate.h:268-272`）；若绑定建立时函数未注册，这里没有有效 FuncId 可写（见上一条）。
3. **读档后调用前**：函数必须已注册进注册表的 FuncId 映射 `GFuncIdMap`——`GetFunctionById` 只查该 map（`src/core/tool/script_function.cpp:77-85`），**没有 loader 回退**；**注意**：loader 仅在按名解析（如重新执行 `BindScriptFunction`）时经 `GetFunction` 触发（`src/core/tool/script_function.cpp:40-75`），**不会**自动恢复读档还原出的 FuncId 绑定——读档后不能只依赖 loader，需在启动期（如脚本加载阶段）统一注册，见 `doc/gas.md:1744`。

> **English:** Registration timing matters at three points. Before binding, BindScriptFunction validates via GetFunctionAs and refuses to bind an unregistered function (delegate.h:141-151). Before saving, the function must be registered, because save only writes the already-stored FuncId without any validation (delegate.h:268-272). After loading and before calling, the function must be registered in the GFuncIdMap, because GetFunctionById only queries that map with no loader fallback (script_function.cpp:77-85); the loader path fires only during by-name resolution such as a fresh BindScriptFunction (script_function.cpp:40-75) and never auto-restores FuncId bindings restored from a savegame, so you cannot rely on loaders alone after loading.

### 3.4 读档恢复（惰性解析）

读档恢复是**惰性**的——只重建 FuncId 数值，不解析任何指针：

- `TDelegate::load` 读到 `"ScriptFunction"` 后仅存 `FScriptFunctionBinding{FuncId}`（`src/core/tool/delegate.h:290-293`）；`TMulticastDelegate::load` 同理，仅 push `FScriptFunctionListener{handle, funcId}`（`:648-651`）。全程不查询、不解引用注册表。
- 解析推迟到**调用时**：`Execute` 里才经 `GetFunctionById` 查表并解引用（`src/core/tool/delegate.h:195-216`，查表与守卫 `:198-206`，实际调用 `:209` / `:214`）。
- 若读档后函数未注册（未进入 `GFuncIdMap`）：`Execute` 记录警告 `"ScriptFunction (FuncId=...) not found"` 并返回默认值——void 直接返回、非 void 返回 `Ret{}`（`src/core/tool/delegate.h:200-206`），**不崩溃**；`Broadcast` 对该监听静默跳过（`src/core/tool/delegate.h:613`）。

> **English:** Restoring a delegate from a savegame is lazy. Load only rebuilds the FuncId value — TDelegate::load stores FScriptFunctionBinding{FuncId} and TMulticastDelegate::load pushes FScriptFunctionListener{handle, funcId} — without resolving any pointer. Resolution is deferred to call time inside Execute, which resolves through GetFunctionById (delegate.h:195-216). If the function is not registered after loading, Execute logs a "ScriptFunction (FuncId=...) not found" warning and returns a default value: void returns immediately, non-void returns Ret{} (delegate.h:200-206). It never crashes, and Broadcast silently skips such listeners (delegate.h:613).

### 3.5 GC 与调用时 UAF

理解存档场景下的悬垂风险，必须先区分"序列化期"与"调用期"：

- **存档序列化仅读写 FuncId 数值，不触碰注册表指针，不存在存档期悬垂风险**：`TDelegate::save` 只写 `FuncId`（`src/core/tool/delegate.h:268-272`）、`TMulticastDelegate::save` 只收集 FuncId 列表（`:637-640`），序列化全程不查询、不解引用任何 ScriptFunction 指针，自然没有悬垂的机会。
- 悬垂 use-after-free **只可能发生在调用时**：`Execute` 解引用 `GetFunctionById` 返回的指针后调用 `(*sf)(...)`（`src/core/tool/delegate.h:195-216`，解析与守卫 `:198-206`，调用 `:209` / `:214`）；`Broadcast` 同理（`:611-614`）。典型场景：注册表条目指向的对象已被 GC 释放、而注册表未同步清理，调用时拿到悬垂指针再 `(*sf)(...)` 即构成 UAF。
- `IsBound` 只做 map 查找 / 容器判空、**不解引用**：`FScriptFunctionBinding::IsBound` 仅 `GetFunctionById(FuncId) != nullptr`（`src/core/tool/delegate.h:93-96`）、`TDelegate::IsBound` 仅 `m_storage.index() != 0`（`:238-241`）、`TMulticastDelegate::IsBound` 仅检查三个容器是否为空（`:621-627`）。它们都不会调用函数指针，**不得把 IsBound 列为 UAF 发生点**。

> **English:** The GC hazard model. Serialization only reads and writes the FuncId numeric value and never touches registry pointers, so there is no dangling-pointer risk during save or load. A use-after-free can only occur at call time: Execute resolves and dereferences the pointer returned by GetFunctionById and then invokes (*sf)(...) (delegate.h:195-216, resolution and guard at 198-206, invocation at 209/214), and Broadcast does the same (delegate.h:611-614). IsBound performs only a map lookup or a container emptiness check and never dereferences (delegate.h:93-96, 238-241, 621-627), so it is not a UAF site.

### 3.6 热重载与存档

与 §2.4 呼应：热重载后以**相同的 category/name** 重新注册函数 → `StringName` 内容哈希不变 → FuncId 不变 → 读档还原出的 FuncId 绑定仍能经 `GetFunctionById` 解析到新实例，**旧存档的绑定依然有效**。

- **标注：此为推导属性，非实测**——由 FuncId 的内容哈希机制推得（`src/core/string/string_name.h:28-30` 构造时缓存哈希 + `src/core/tool/script_function.cpp:13-16` 组合公式）。
- 反向推论：若重载后 category 或 name 字符串发生变化 → FuncId 随之改变 → 旧存档中的 FuncId 无法在注册表命中 → 读档还原的绑定静默失效（调用时警告 + 默认值，见 §3.4）。

> **English:** Echoing §2.4: after a hot reload, re-registering the function under the same category and name keeps the FuncId unchanged, so bindings restored from old savegames still resolve to the new instance and remain valid. This is a derived property of the FuncId content-hash mechanism (string_name.h:28-30 and script_function.cpp:13-16), not a measured behavior. Conversely, if the category or name strings change, the FuncId changes too and old savegame bindings can no longer be resolved.

## TypeScript 使用规范（TypeScript Usage）

本节面向 TS/JS 脚本作者，说明如何用正确的方式在脚本层创建、注册 ScriptFunction，并把它绑定到委托上。核心结论两条：**用具名类而非泛型 `ScriptFunction<TXXX>`**、**用全局 `RegisterScriptFunction` 简化注册**；数量大、按需创建的签名则用 loader 模式。

### 4.1 用具名类而非泛型 ScriptFunction<TXXX>

ScriptFunction 的每个签名都必须在 C++ 侧**显式绑定**后才能在 JS 中构造：绑定模板定义于 `src/scripting/javascript/script_function_binding.cpp:6-14`（第 7 行 `void RegisterScriptFunction()`、第 9 行 `using FuncType = ScriptFunction<Func>;`），只为模板参数 `Func` 生成 JS 可构造类；其实例化集中在 `__JsRegister_ScriptFunctions`（`:16-67`），实测 **49** 个 `RegisterScriptFunction<...>` 实例化（`:18-66`）。脚本侧只有两类具名类可以直接 `new`：

| 类别 | 数量 | 定义位置 | 示例 |
| --- | --- | --- | --- |
| wrapper | 46 | `src/scripting/javascript/script_function_wrappers.h:29-349`（`CLASS(BindJs)` 具名派生类；`UsingCppType` 注册于 `:353-398`） | `ScriptFunction_void_GameplayAbility__` |
| creator | 3 | GAS 头文件（与 wrapper 同样合法）：`GameplayAbilityCreator` @ `src/xkein/GameplayAbilities/ability_system_globals.h:64`、`AttributeSetCreator` @ `:71`、`AbilityTaskCreator` @ `src/xkein/GameplayAbilities/ability_task/ability_task.h:146` | `GameplayAbilityCreator` |

- 生成 typings 给每个具名类带上**精确的回调签名类型检查**：如 `AbilityTaskCreator`（`src/scripts/javascript/typings/yr/gen/XkeinExt.d.ts:1593-1599`）、`GameplayAbilityCreator` / `AttributeSetCreator`（`:1623-1635`）、`ScriptFunction_void_AbilityTask__`（`:2257-2263`），回调参数类型由 TS 编译期检查。
- 泛型环境声明 `ScriptFunction<TFunc>` **无签名限制**：`src/scripts/javascript/typings/yr/scriptable.d.ts:11-14` 仅约束 `TFunc extends (...args:any[])=>any`，`constructor(func: TFunc | undefined)` 不检查回调签名是否与 C++ 已绑定的实例匹配。因此若用泛型写一个未绑定的签名，TS 编译期不报错，但**运行时构造会失败**。

> **English:** Every ScriptFunction signature must be explicitly bound on the C++ side before it can be constructed in JS. The binding template is defined at script_function_binding.cpp:6-14 and instantiated 49 times at :18-66, all inside __JsRegister_ScriptFunctions (:16-67). Script-side construction uses only the named classes: 46 wrappers in script_function_wrappers.h:29-349, registered via UsingCppType at :353-398, plus 3 creator classes defined in the GAS headers instead (GameplayAbilityCreator and AttributeSetCreator at ability_system_globals.h:64 and :71, AbilityTaskCreator at ability_task.h:146), which are equally valid. The generated typings (XkeinExt.d.ts:1593-1599, :1623-1635, :2257-2263) give each named class a precise callback signature checked at compile time, whereas the generic ScriptFunction<TFunc> declaration (scriptable.d.ts:11-14) has no signature restriction, so an unbound signature fails at runtime construction rather than at compile time.

### 4.2 用 RegisterScriptFunction 简化注册

注册表本身暴露的是 `ScriptFunctionRegister.RegisterFunction(category, name, func)`（`src/scripts/javascript/typings/yr/gen/YrExtCore.d.ts:33-44`），**不返回实例**。全局助手 `RegisterScriptFunction` 把它包成"一步注册 + 返回实例"：

- 实现：`src/scripts/javascript/utilities.js:33-36`——`global.RegisterScriptFunction = function (category, name, func) { YrExtCore.ScriptFunctionRegister.RegisterFunction(category, name, func); return func; }`
- TS 声明：`src/scripts/javascript/typings/yr/scriptable.d.ts:16`——`function RegisterScriptFunction<TScriptFunction extends ScriptFunction<any>>(category : string, name : string, func : TScriptFunction) : TScriptFunction;`（在 `declare global` 内，无需 import）

两种写法对比：

```ts
// 简化写法：注册的同时拿到实例，可直接按指针绑定
const sf = RegisterScriptFunction(cat, name, new ScriptFunction_void_GameplayAbility__(fn));
ability.m_OnXxx.BindScriptFunction(sf);

// 不简化写法：RegisterFunction 不返回实例
ScriptFunctionRegister.RegisterFunction(cat, name, sf);
// 需要再查一次（ScriptFunctionRegister.GetFunction(cat, name)），
// 或改用按 category/name 绑定：ability.m_OnXxx.BindScriptFunction(cat, name)
```

> **English:** The registry API ScriptFunctionRegister.RegisterFunction(category, name, func) does not return the instance. The global helper RegisterScriptFunction wraps it as a one-step register-and-return: implemented at utilities.js:33-36 and declared in scriptable.d.ts:16 (inside declare global, so no import is needed). The simplified form binds the delegate by pointer using the returned instance; the unsimplified form must re-query the registry with ScriptFunctionRegister.GetFunction(cat, name), or fall back to by-name binding with BindScriptFunction(cat, name).

### 4.3 完整示例

一个完整的"注册 → 绑定委托 → 存档语义"示例：

```ts
// 1) 注册：构造具名类并注册，拿到实例
const onActivated = RegisterScriptFunction(cat, name, new ScriptFunction_void_GameplayAbility__(async (ability) => {
    // ... 回调体
}));

// 2) 绑定委托：按指针绑定，或按 category/name 绑定
ability.m_OnActivated.BindScriptFunction(onActivated);   // 按指针
ability.m_OnActivated.BindScriptFunction(cat, name);     // 按 category/name

// 3) 存档语义：只有 ScriptFunction 绑定可存档（存 FuncId，见 §3）
//    若改用 BindStdFunction / lambda 绑定，存档时被丢弃——单播警告 + "Unsupported" 标记，
//    多播静默丢弃（见 §3.1）；读档后需在启动期完成注册，见 §3.3
```

> **English:** A full example walks through the three steps: construct a named class and register it with RegisterScriptFunction to obtain the instance, bind it to a delegate either by pointer or by category/name, and keep the savegame semantics in mind. Only ScriptFunction bindings are serialized, since they store the FuncId (see §3). BindStdFunction or lambda bindings are dropped on save: a warning plus the "Unsupported" marker for TDelegate, silent discard for TMulticastDelegate (see §3.1). After loading, the function must be registered at startup for the restored FuncId binding to resolve (see §3.3).

### 4.4 loader 模式与 persistentObjs

当签名数量大、且函数按需创建时，用 `RegisterLoader` 注册惰性加载器（注册方式见 §1.3）。参照 `src/scripts/typescript/xkein/gas.ts:6-37`：

```ts
const persistentObjs: any[] = [];   // gas.ts:4  —— 防 GC：模块级数组保持引用

function abilityLoader(name: StringName) {
    const m = require(name.c_str());
    if (m && m.ability_creator) {
        let creator = new GameplayAbilityCreator(fn);   // 伪代码：fn 为回调占位符
        persistentObjs.push(creator);                   // gas.ts:10
        return creator;
    }
}
// attributeSetLoader / taskLoader 同理（gas.ts:15-31，push 分别在 :19 / :28）
// setupGas 中挂载 loader（gas.ts:33-37）：
ScriptFunctionRegister.RegisterLoader(category, abilityLoader);   // gas.ts:34
```

**`persistentObjs` 防 GC 惯例**：注册表只存裸指针（GC 危险模型见 §3.5）——JS 侧创建的 wrapper 对象被 GC 回收后，C++ 对象随之析构，注册表里的指针变成悬垂指针，**调用时**解引用构成 UAF；用模块级数组持有引用即可阻止 GC 回收。

> **English:** For many signatures created on demand, register a lazy loader with RegisterLoader (registration semantics in §1.3). Following gas.ts:6-37, each loader requires the module, constructs the matching creator class, pushes it into persistentObjs, and returns it, while setupGas wires the loaders via ScriptFunctionRegister.RegisterLoader (gas.ts:34). The persistentObjs module-level array (declared at gas.ts:4, pushed to at :10, :19 and :28) is the anti-GC convention: the registry stores raw pointers (see the GC hazard model in §3.5), so if the JS-created wrapper object is collected, the underlying C++ object is destroyed and the registry pointer dangles into a use-after-free at call time. Holding module-level references prevents collection.

### 4.5 选择指南

| 选择维度 | 用 ... | 当 ... |
| --- | --- | --- |
| 注册方式 | `RegisterFunction`（立即注册） | 数量少、启动期确定（脚本加载阶段一次性注册，见 §1.3） |
| | `RegisterLoader`（惰性加载） | 数量大、按需创建（每个 category 一个 loader，如 `gas.ts:33-37`） |
| 绑定方式 | `BindScriptFunction` | 回调需跨存档存活（存 FuncId，见 §3） |
| | `BindStdFunction`（lambda） | 临时回调、无需存档；注意存档时被丢弃（单播警告 / 多播静默，见 §3.1 与 `doc/gas.md` §16.5） |

> **English:** Quick selection guide. Use RegisterFunction for few callbacks known at startup (registered once during script loading, see §1.3), and RegisterLoader for many callbacks created on demand, with one loader per category as in gas.ts:33-37. Use BindScriptFunction when the callback must survive savegames, since it persists the FuncId (see §3). Use BindStdFunction with a lambda for temporary callbacks that do not need archiving, remembering that they are dropped on save: a warning for TDelegate, silent discard for TMulticastDelegate, see §3.1 and doc/gas.md §16.5.

## 常见坑（Pitfalls）

本节汇总脚本作者在使用 ScriptFunction 时最容易踩到的五类坑，每条均标注现象、根因与对应机制的详细章节，可回溯定位。

### 5.1 陷阱清单

| # | 陷阱 | 现象 | 根因 | 详见 |
| --- | --- | --- | --- | --- |
| 1 | 用未绑定签名的泛型 `ScriptFunction<TXXX>` 构造 | 运行时构造失败（TS 编译期不报错） | 每个签名必须在 C++ 侧显式绑定后才生成 JS 可构造类；泛型声明无签名限制（`src/scripts/javascript/typings/yr/scriptable.d.ts:11-14`） | §4.1 |
| 2 | lambda 绑定参与存档 | 读档后回调丢失 | 只有 `BindScriptFunction` / `AddScriptFunction` 可序列化；`TDelegate` 警告 + `"Unsupported"` 标记、`TMulticastDelegate` 静默丢弃 | §3.1 |
| 3 | 注册后忘记保持 JS 引用 | 调用时 UAF | 注册表只存裸指针；wrapper 对象被 GC 回收后指针悬垂，`Execute` 解引用再调用即构成 UAF（`src/core/tool/delegate.h:195-216`） | §3.5、§4.4 |
| 4 | 改动 category / name 字符串 | 旧存档绑定失效 | FuncId 由字符串内容哈希派生（`src/core/tool/script_function.cpp:13-16`），字符串一变 FuncId 即变，旧 FuncId 无法在注册表命中 | §3.2、§3.6 |
| 5 | 读档前未注册函数 | 委托静默失效 | `GetFunctionById` 只查 `GFuncIdMap`、无 loader 回退（`src/core/tool/script_function.cpp:77-85`）；`Execute` 警告 + 返回默认值、`Broadcast` 静默跳过 | §3.3、§3.4 |

> **English:** This section lists the five pitfalls script authors hit most often, each traced back to its detailed section. (1) Constructing an unbound generic `ScriptFunction<TXXX>` fails at runtime, because every signature must be explicitly bound on the C++ side before a JS-constructible class is generated, and the generic declaration has no signature restriction (scriptable.d.ts:11-14), so TypeScript does not catch it at compile time (§4.1). (2) Lambda bindings are dropped on save, leaving the callback missing after loading: only `BindScriptFunction` and `AddScriptFunction` are serializable, with a warning plus the "Unsupported" marker for TDelegate and silent discard for TMulticastDelegate (§3.1). (3) Forgetting to keep a JS reference after registration causes a use-after-free at call time, because the registry stores raw pointers and the pointer dangles once the wrapper object is garbage-collected, so `Execute` dereferences a dangling pointer and invokes it (delegate.h:195-216) (§3.5, §4.4). (4) Changing the category or name strings changes the FuncId, since FuncId derives from the content hashes (script_function.cpp:13-16), so old savegame bindings can no longer be resolved (§3.2, §3.6). (5) Failing to register before loading leaves the delegate silently broken, because `GetFunctionById` only queries the GFuncIdMap with no loader fallback (script_function.cpp:77-85); `Execute` warns and returns a default value while `Broadcast` silently skips the listener (§3.3, §3.4).

## 相关文档（Related Docs）

与 ScriptFunction 机制相关的其他文档，按「从哪个视角看」给出索引，可与本文档 §3、§4 互相参照。

### 6.1 链接列表

| 文档 | 内容 | 与本文档的关系 |
| --- | --- | --- |
| `doc/gas.md` §16（委托存档） | 从用法视角给出两种绑定方式对比、注册时机与选择指南（第 1678-1762 行） | 本文档 §3 从机制角度解释其所以然（FuncId 内容哈希、惰性解析、GC 危险模型），两处可互相参照 |
| `doc/all_data_binding.md` | JS 绑定体系：puerts 集中类型预注册表，`ScriptFunction<FUNC>` 等绑定类型在此登记 | 说明 ScriptFunction 各签名为何必须显式绑定（对应 §4.1） |
| `doc/meta.md` | 反射 / Savegame 标签机制（AutoSavegame 反射标签与 cereal 序列化，第 201-248、347-371 行） | 存档链路（§3）依赖的底层机制 |

> **English:** Related documents, indexed by the perspective they take, cross-referencing §3 and §4 of this guide. doc/gas.md §16 covers delegate archiving from the usage perspective, comparing the two binding approaches and when to register (lines 1678-1762); this guide's §3 explains the mechanism behind it, and the two can be read together. doc/all_data_binding.md describes the JS binding system, the puerts centralized type pre-registry where bound types such as ScriptFunction<FUNC> are registered, which explains why every signature must be explicitly bound (§4.1). doc/meta.md documents the reflection and Savegame label mechanism, the AutoSavegame reflection labels and cereal serialization (lines 201-248 and 347-371) that the archiving chain in §3 relies on.
