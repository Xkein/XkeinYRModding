# XkeinYrmodding

这是一个针对于红色警戒尤里的复仇的扩展Dll。

## 项目结构

- `doc/` - 包含说明文档
- `src/` - 包含项目代码
- `src/audio` - 音频模块
- `src/core` - 核心模块
- `src/editor` - 编辑器模块
- `src/physics` - 物理模块
- `src/runtime` - 另一个"核心"模块
- `src/scripts` - 提供一些基础脚本（js/ts）
- `src/scripting` - 脚本模块，提供脚本运行时
- `src/template` - 代码生成模板
- `src/ui` - UI
- `src/yr` - 连接项目和YR的模块，包含注入功能等，也就是和游戏交互的模块
- `src/xkein` - 提供真正的玩法功能等

## 项目特点

- 代码生成，本项目有类似有虚幻引擎的反射方案，具体观看`doc/meta.md`以及`src/template/`

## 约束

### 代码规范

- 不允许使用形如`(void)Data;`的代码
- 不允许删除和优化无关的代码和注释

### 帧同步（Deterministic Lockstep）

- 本项目是 Red Alert 2 YR Mod，使用**帧同步**，不需要状态同步。
2. INI 加载规则

### INI 读取规则

使用现有代码生成管线，禁止手写注册表：

- 通过 `PROPERTY()` / `CLASS()` 宏 + CppHeaderTool 自动生成加载代码。
- **正确做法**：`CLASS(IniComponent, IniAutoLoad)`。

枚举解析由反射自动处理：

- `ENUM()` 宏声明的枚举被 `parser.h` 中泛型 `Parser<T, is_enum_v<T>>` 自动解析。
- **禁止**手写枚举 Parser 特化。
- **例外**：复杂组合类型可以手写 Parser。

### 蓝图/脚本 兼容

这里类比虚幻的概念，但要做出项目自己的风格

1. BlueprintImplementableEvent和BlueprintCallable

BlueprintCallable，也就是专供蓝图的节点，直接给函数添加FUNCTION()，比如
```code
    FUNCTION()
    virtual void K2_EndAbility();
```

BlueprintImplementableEvent，也就是蓝图可以实现的事件，使用std::function<>（不要套using type）的成员处理，比如
```code
    PROPERTY()
    std::function<void()> OnK2_ActivateAbility;
```


## 第三方库

- Wwise — 音频引擎
- 其他可以在`3rdparty.lua`和`3rdparty/`中观察到

## 注意事项

- 有不清晰和模糊的地方，询问用户
- 不需要调用xmake检查编译报错，由用户来手动操作

# 做事方针

Behavioral guidelines to reduce common LLM coding mistakes. Merge with project-specific instructions as needed.

**Tradeoff:** These guidelines bias toward caution over speed. For trivial tasks, use judgment.

## 1. Think Before Coding

**Don't assume. Don't hide confusion. Surface tradeoffs.**

Before implementing:
- State your assumptions explicitly. If uncertain, ask.
- If multiple interpretations exist, present them - don't pick silently.
- If a simpler approach exists, say so. Push back when warranted.
- If something is unclear, stop. Name what's confusing. Ask.

## 2. Simplicity First

**Minimum code that solves the problem. Nothing speculative.**

- No features beyond what was asked.
- No abstractions for single-use code.
- No "flexibility" or "configurability" that wasn't requested.
- No error handling for impossible scenarios.
- If you write 200 lines and it could be 50, rewrite it.

Ask yourself: "Would a senior engineer say this is overcomplicated?" If yes, simplify.

## 3. Surgical Changes

**Touch only what you must. Clean up only your own mess.**

When editing existing code:
- Don't "improve" adjacent code, comments, or formatting.
- Don't refactor things that aren't broken.
- Match existing style, even if you'd do it differently.
- If you notice unrelated dead code, mention it - don't delete it.

When your changes create orphans:
- Remove imports/variables/functions that YOUR changes made unused.
- Don't remove pre-existing dead code unless asked.

The test: Every changed line should trace directly to the user's request.

## 4. Goal-Driven Execution

**Define success criteria. Loop until verified.**

Transform tasks into verifiable goals:
- "Add validation" → "Write tests for invalid inputs, then make them pass"
- "Fix the bug" → "Write a test that reproduces it, then make it pass"
- "Refactor X" → "Ensure tests pass before and after"

For multi-step tasks, state a brief plan:
```
1. [Step] → verify: [check]
2. [Step] → verify: [check]
3. [Step] → verify: [check]
```

Strong success criteria let you loop independently. Weak criteria ("make it work") require constant clarification.

---

**These guidelines are working if:** fewer unnecessary changes in diffs, fewer rewrites due to overcomplication, and clarifying questions come before implementation rather than after mistakes.
