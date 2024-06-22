# XkeinYRModing(WIP)

![https://www.gnu.org/graphics/gplv3-or-later.png](https://www.gnu.org/graphics/gplv3-or-later.png)

English Version click [here](#project-structure) or drag page down

## 项目结构介绍

## 主要模块

### CppHeaderTool

代码生成工具，风格仿UE（不依赖于C++的特性的meta注解）

使用CppAst.NET（基于clang）分析代码，调用scriban脚本生成代码

具体用途如下图：

![https://github.com/Xkein/Images/blob/master/XkeinYRModding/header_tool.png?raw=true](https://github.com/Xkein/Images/blob/master/XkeinYRModding/header_tool.png?raw=true)

### **YrExtCore**

开发框架的核心库，主要负责：

- 只在这个模块注入Hook
- 分发调用Hook事件
- 管理其他扩展DLL

除了其基本职能外，还提供了一些方便的工具：

- 适配于游戏的entt反射和ecs系统
- 适配于游戏的文件系统
- 提供一定的崩溃恢复机制，打印异常时的栈输出
- 利用meta注解自动生成附加到游戏对象上的组件实例化代码，INI配置读取代码
- 集成spdlog日志

### **YrExtUI**

基本UI框架，集成了方便调试开发的ImGui

### **YrScripting**

脚本模块，主要负责：

- 读取，执行，热重载JavaScript
- 自动生成游戏对象的js wrap代码

js代码热重载：

![https://github.com/Xkein/Images/blob/master/XkeinYRModding/yr_js_reload.gif?raw=true](https://github.com/Xkein/Images/blob/master/XkeinYRModding/yr_js_reload.gif?raw=true)

### 构建环境

- xmake — 构建系统
- dotnet 8 — 用于构建代码生成工具
- VS2022 — 提供基本sdk

### 第三方库

- [YRpp](https://github.com/Phobos-developers/YRpp)（根据此项目进行了定制修改）— 提供游戏的基本接口声明
- [CppAst.Net](https://github.com/xoofx/CppAst.NET) （根据此项目进行了定制修改）— C++ AST分析工具
- [scriban](https://github.com/scriban/scriban) — 文本渲染引擎和脚本语言
- [entt](https://github.com/skypjack/entt) — 提供ecs，反射框架
- [puerts](https://github.com/Tencent/puerts) — 游戏Typescript编程解决方案
- [imgui](https://github.com/thedmd/imgui) — 立即UI框架
- [imgui-node-editor](https://github.com/thedmd/imgui-node-editor) — 可视化节点编辑器UI
- v8 — javascript引擎
- [nlohmann json](https://github.com/nlohmann/json) — json库
- stb — 图像读取库
- spdlog — 日志库

## 编译

1. 准备构建环境

在编译前，你需要安装[xmake](https://xmake.io/), dotnet, VS2022

注：由于msvc编译器在C++20下存在[bug](https://stackoverflow.com/questions/76796033/ambiguous-call-to-operator-new-when-upgrading-to-c-20)，需要使用msvc 14.39编译避免编译错误

1. 准备第三方库
- [v8-backend](https://github.com/puerts/backend-v8/releases): 下载好之后，设置环境变量V8_PATH路径为v8 backend的路径
1. 配置

命令行输入

```powershell
xmake f -a x86 -m debug --skip_codegen=n --make_artifacts=y
```

第一次运行时可能会出现第三方库的安装请求, 输入y安装即可

1. 编译

命令行输入

```powershell
xmake build -v
```

1. 复制成品

前往`build\artifacts\debug` 复制成品到游戏目录

## 待办许愿池

- [ ]  适用于游戏的cegui
- [ ]  C#支持，考虑兼容dp，并且提供更高性能的语言交互（类似mono embed）
- [ ]  扩展模块管理工具
- [ ]  Profiler工具
- [ ]  MOD开发者便捷调试工具（如查看当前单位状态）

## 声明

本项目与Electronic Arts Inc没有直接关系。Command & Conquer, Command & Conquer Red Alert 2, Command & Conquer Yuri's Revenge是Electronic Arts Inc的注册商标。保留所有权利。

## 赞助

[Alipay](https://github.com/Xkein/Images/blob/master/SupportMe/alipay.jpg?raw=true)

[WeChat](https://github.com/Xkein/Images/blob/master/SupportMe/wechat.png?raw=true)

[Patreon](https://www.patreon.com/Xkein)

## Project Structure

## Main Module

### CppHeaderTool

Code generating tool has similar style with UE’s UnrealHeaderTool(independent on c++ attribute)

Use CppAst.Net(base on clang) to analyze code and generate code from scriban template

for example：

![https://github.com/Xkein/Images/blob/master/XkeinYRModding/header_tool.png?raw=true](https://github.com/Xkein/Images/blob/master/XkeinYRModding/header_tool.png?raw=true)

### **YrExtCore**

The core library of develop framework, mainly do:

- Inject hooks in this module only
- Dispatch hook events
- Manage extension dlls

Also some convenient tools are provided:

- Entt Reflection and ECS system ready for YR
- Filesystem ready for YR
- Exception recovery mechanic and exception stack printing
- Auto generating component instantiation code base on meta notation; such as ini reading, component instantiate on TechnoClass
- Spdlog logger integrated

### **YrExtUI**

Basic UI framework, integrating Imgui that convenient for debug developing

### **YrScripting**

Script module, mainly do：

- load, execute, hot reload the JavaScript code
- Auto generating Js wrap code for game classes

js code hot reload：

![https://github.com/Xkein/Images/blob/master/XkeinYRModding/yr_js_reload.gif?raw=true](https://github.com/Xkein/Images/blob/master/XkeinYRModding/yr_js_reload.gif?raw=true)

### Build Environment

- xmake — build system
- dotnet 8 — use to build the code generating tool
- VS2022 — provide basic SDKs

### Third Party

- [YRpp](https://github.com/Phobos-developers/YRpp)（Modified by this project）— Provide game basic interface declaration
- [CppAst.Net](https://github.com/xoofx/CppAst.NET) （Modified by this project）— C++ AST analyze tool
- [scriban](https://github.com/scriban/scriban) — Text rendering engine and script language
- [entt](https://github.com/skypjack/entt) — ECS, Reflection framework
- [puerts](https://github.com/Tencent/puerts) — Game Typescript programming resolution
- [imgui](https://github.com/thedmd/imgui) — Immediate UI framework
- [imgui-node-editor](https://github.com/thedmd/imgui-node-editor) — Visual node editor UI
- v8 — javascript engine
- [nlohmann json](https://github.com/nlohmann/json) — json library
- stb — image library
- spdlog — logger library

## Compile

1. Preparing build environment

Before compiling, you must install [xmake](https://xmake.io/), dotnet, VS2022

Note: Due to [bug](https://stackoverflow.com/questions/76796033/ambiguous-call-to-operator-new-when-upgrading-to-c-20) in the MSVC compiler under C++20, it is necessary to use MSVC 14.39 to avoid compilation errors

1. Preparing third party
- [v8-backend](https://github.com/puerts/backend-v8/releases): After download, set the environment variable `V8_PATH` to v8 backend path
1. Configure

```powershell
xmake f -a x86 -m debug --skip_codegen=n --make_artifacts=y
```

There may be some third party installation requests during the first configure. Please enter `y` to accept.

1. Compile

```powershell
xmake build -v
```

1. Copy artifacts

Goto`build\artifacts\debug` and copy files to  game directory

## Todo List Wishing Pool

- [ ]  cegui ready for YR
- [ ]  C# support, dp compatible, providing faster performance (like mono embed)
- [ ]  Extension module manager tool
- [ ]  Profiler tool
- [ ]  Modder debugging dev tool (such as inspect select object)

## Legal

This project has no direct affiliation with Electronic Arts Inc. Command & Conquer, Command & Conquer Red Alert 2, Command & Conquer Yuri's Revenge are registered trademarks of Electronic Arts Inc. All Rights Reserved.

## Support Me

[Patreon](https://www.patreon.com/Xkein)

[Alipay](https://github.com/Xkein/Images/blob/master/SupportMe/alipay.jpg?raw=true)

[WeChat](https://github.com/Xkein/Images/blob/master/SupportMe/wechat.png?raw=true)