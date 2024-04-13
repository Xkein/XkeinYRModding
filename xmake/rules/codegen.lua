
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
        local extraconf = target:extraconf("rules", "codegen-cpp") or {}
        
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
            table.join2(defines, target:get("defines"))
            for _, dep in pairs(target:deps()) do
                table.join2(defines, dep:get("defines", {public = true}))
            end
            -- collect compiler arguments
            local arguments = {
                "-std=c++2c",
                "--verbose",
            }

            import("common_tool")
            local templates = extraconf.templates or common_tool.get_default_templates()
            local parser_includes = extraconf.parserincludes
            local input_text = nil
            for _, includefile in ipairs(parser_includes or {}) do
                local line = string.format("#include \"%s\"", includefile)
                input_text = input_text and input_text.."\n"..line or line
            end

            local runInfo = {
                templateDir = path.join(os.projectdir(), "src/template"),
                moduleTemplates = templates.module,
                classTemplates = templates.class,
                enumTemplates = templates.enum,
                module = target_name,
                input_text = input_text,
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
        local genHeaderFiles = os.files(gendir.."/**.h")
        for _, file in ipairs(genHeaderFiles) do
            target:add("headerfiles", file)
        end
        if #genCppFiles > 0 then
            target:add("filegroups", "codegen", {rootdir = gendir})
        end
        target:add("includedirs", gendir)
    end)