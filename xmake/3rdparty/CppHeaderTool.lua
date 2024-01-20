
header_tool_project_dir = get_thirdparty_path("CppHeaderTool")

task("dotnet-compile-job")
    on_run(function ()
        print("compiling CppHeaderTool projects...")
        os.execv("dotnet", {
            "publish", os.projectdir().."/3rdparty/CppHeaderTool",
            "--output", os.projectdir().."/build/tools",
        })
    end)

target("build-header-tool")
    set_kind("phony")
    before_build(function (target) 
        import("core.base.task")
        task.run("dotnet-compile-job")
    end)

task("run-header-tool")
    on_run(function (info)
        print("running header tool with info: " .. info)
        
    end)
