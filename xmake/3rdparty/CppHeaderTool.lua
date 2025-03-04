
task("dotnet-compile-job")
    on_run(function ()
        print("compiling CppHeaderTool projects...")
        import("core.project.config")
        os.execv("dotnet", {
            "build", os.projectdir().."/3rdparty/CppHeaderTool/src/CppHeaderTool/CppHeaderTool.csproj",
            "--output", path.join(config.buildir(), "tools"),
        })
    end)

target("cpp-header-tool")
    set_kind("phony")
    on_load(function (target)
        local header_tool_project_dir = os.projectdir().."/3rdparty/CppHeaderTool"
        local csproj = header_tool_project_dir.."/src/CppHeaderTool/CppHeaderTool.csproj"
        local files = { csproj }
        local csfiles = os.files(header_tool_project_dir.."/**.cs")
        for _, file in ipairs(csfiles) do
            if not string.find(file, "obj") then
                table.insert(files, file)
            end
        end
        table.sort(files)
        import("core.project.depend")
        depend.on_changed(function ()
            import("core.base.task")
            task.run("dotnet-compile-job")
        end, {dependfile = target:dependfile(csproj), files = files})
    end)

task("run-header-tool")
    on_run(function (info)
        print("running header tool with info:")
        print(info)
        
        import("core.base.json")
        local config_path = path.absolute(info.outDir.."/config.json")
        local json_data = {
            templateDir = info.templateDir,
            moduleTemplates = info.moduleTemplates,
            typeTemplates = info.typeTemplates,
            injectMetaTemplates = info.injectMetaTemplates,
            moduleName = info.module,
            inputText = info.input_text,
            preHeaderText = info.preHeaderText,
            postHeaderText = info.postHeaderText,
            headerFiles = info.header_list,
            includeDirs = info.include_list,
            systemIncludeDirs = info.sysinclude_list,
            defines = info.defines,
            arguments = info.arguments,
            targetAbi = info.targetAbi,
            targetSystem = info.targetSystem,
            targetVendor = info.targetVendor,
            targetCpuSub = info.targetCpuSub,
            targetCpu = info.targetCpu,
            isWindowsMsvc = info.isWindowsMsvc,
            isParseSystemIncludes = info.isParseSystemIncludes,
            parseTokenAttributes = false,
        }
        
        for _, t in ipairs({ json_data.headerFiles, json_data.includeDirs, json_data.systemIncludeDirs, json_data.defines, json_data.arguments }) do
            json.mark_as_array(t)
        end
        io.writefile(config_path, json.encode(json_data))
        
        import("core.project.config")
        -- print(argument_list)
        os.execv(path.join(config.buildir(), "tools/CppHeaderTool"), {
            "--config", config_path,
            "--out_dir", info.outDir,
            -- "--loop_generate", -- switch this to quickly test the scriban template
        })
    end)
