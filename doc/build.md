# Build

## 编译

1. 准备构建环境

在编译前，你需要安装[xmake](https://xmake.io/), dotnet 8, VS2022

2. 准备第三方库
- [nodejs-backend](https://github.com/Xkein/backend-nodejs/releases/tag/NodeJS_22.14.0_ssl_114514): 下载nodejs_bin_22.14.0.zip
，然后需要设置环境变量NODEJS_PATH路径为nodejs backend的路径
- [Wwise SDK](https://www.audiokinetic.com/zh/wwise/overview): 版本Wwise2024.1

3. 配置

命令行输入

```powershell
xmake f -a x86 -m debug --skip_codegen=n --make_artifacts=y
```

第一次运行时可能会出现第三方库的安装请求, 输入y安装即可

- skip_codegen: 是否跳过代码生成
- make_artifacts: 编译完成时拷贝成品

4. 编译

命令行输入

```powershell
xmake build -v
```

5. 复制成品

前往`build\artifacts\debug` 复制成品到游戏目录

## Compile

1. Preparing build environment

Before compiling, you must install [xmake](https://xmake.io/), dotnet 8, VS2022

2. Preparing third party
- [nodejs-backend](https://github.com/Xkein/backend-nodejs/releases/tag/NodeJS_22.14.0_ssl_114514): Download nodejs_bin_22.14.0.zip. We need to set the environment variable `NODEJS_PATH` to nodejs backend path
- [Wwise SDK](https://www.audiokinetic.com/zh/wwise/overview): Version Wwise2024.1

3. Configure

```powershell
xmake f -a x86 -m debug --skip_codegen=n --make_artifacts=y
```

There may be some third party installation requests during the first configure. Please enter `y` to accept.

- skip_codegen: should skip code generation
- make_artifacts: copy files after compiled

4. Compile

```powershell
xmake build -v
```

5. Copy artifacts

Goto`build\artifacts\debug` and copy files to  game directory