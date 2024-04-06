
target("codegen-policy")
    set_kind("static")
    add_deps("cpp-header-tool")
    set_policy("build.across_targets_in_parallel", false)
    before_build(function(target)
    end)

rule("codegen-cpp")
    on_load(function (target, opt)
        target:add("deps", "codegen-policy")
    end)
    after_load(function(target)
        local gendir = path.absolute(path.join(target:autogendir({root = true}), target:plat(), "codegen"))

        local header_list = {}
        for _, headerfile in ipairs(target:headerfiles()) do
            table.insert(header_list, path.absolute(headerfile))
        end
        -- run codegen task
        import("core.project.depend")
        depend.on_changed(function ()
            local target_name = target:name()
            local target_dir = target:targetdir()
            print(string.format("generating code for target: %s, gendir: %s", target_name, gendir))
            -- collect include dirs
            local include_list = {}
            for _, includeDir in ipairs(target:get("includedirs")) do
                table.insert(include_list, path.absolute(includeDir))
            end
            -- collect system include dirs
            local sysinclude_list = {}
            for _, dep in pairs(target:deps()) do
                for _, includeDir in ipairs(dep:get("includedirs")) do
                    table.insert(sysinclude_list, path.absolute(includeDir))
                end
            end
            for _, sysincludeDir in ipairs(target:get("sysincludedirs")) do
                table.insert(sysinclude_list, path.absolute(sysincludeDir))
            end
            -- collect defines
            local defines = {
                "__HEADER_TOOL__",
                "NDEBUG",
                "_CRT_USE_BUILTIN_OFFSETOF",
            }
            for _, dep in pairs(target:deps()) do
                for _, define in ipairs(dep:get("defines", {public = true})) do
                    table.insert(defines, define)
                end
            end
            -- collect compiler arguments
            local arguments = {
                "-std=c++2c",
                "--verbose",
            }
            
            local runInfo = {
                template = path.join(os.projectdir(), "src/template"),
                module = target_name,
                header_list = header_list,
                include_list = include_list,
                sysinclude_list = sysinclude_list,
                defines = defines,
                arguments = arguments,
                outDir = gendir,
                targetCpu = "X86",
                isWindowsMsvc = true,
                isParseSystemIncludes = false,
            }

            import("core.base.task")
            local iDontKnowWtfError = false
            if iDontKnowWtfError then
                for _, headerfile in ipairs(header_list) do
                    runInfo.header_list = { headerfile }
                    task.run("run-header-tool", {}, runInfo)
                end
            else
                task.run("run-header-tool", {}, runInfo)
            end
        end, {dependfile = gendir.."/codegen.d", files = header_list})
        
        local genCppFiles = os.files(gendir.."/**.cpp")
        for _, file in ipairs(genCppFiles) do
            target:add("files", file)
        end
        target:add("includedirs", gendir)
    end)