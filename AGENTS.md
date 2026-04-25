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

## 第三方库

- Wwise — 音频引擎
- 其他可以在`3rdparty.lua`和`3rdparty/`中观察到

## 注意事项

- 不需要调用xmake检查编译报错，由用户来手动操作
