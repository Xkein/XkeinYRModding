
target("codegen-policy")
    set_kind("phony")
    add_deps("cpp-header-tool")
    set_policy("build.across_targets_in_parallel", false)
    before_build(function(target)
    end)

target("_link_YrExtCore_First")
    set_kind("phony")
    add_deps("YrExtCore", {inherit = false})

rule("codegen-cpp")
    on_load(function (target, opt)
        target:add("deps", "codegen-policy", { public = false })
        if target:name() ~= "YrExtCore" and target:name() ~= "YRpp" then
            target:add("deps", "_link_YrExtCore_First", { public = false })
        end
        target:add("deps", "Core")
    end)
    after_load(function(target)
        local extraconf = target:extraconf("rules", "codegen-cpp") or {}
        import("common_tool")
        local auto_gendir = common_tool.get_auto_gendir(target:name())
        local gendir = path.absolute(path.join(auto_gendir, "codegen"))
        local header_list = {}
        for _, headerfile in ipairs(target:headerfiles()) do
            table.insert(header_list, path.absolute(headerfile))
        end

        local templates = extraconf.templates or common_tool.get_default_templates()
        local template_dir = path.join(os.projectdir(), "src/template")
        local depend_files = {}
        table.join2(depend_files, header_list)
        for _, template_type in pairs(templates) do
            for template, _ in pairs(template_type) do
                table.insert(depend_files, path.join(template_dir, template))
            end
        end
        -- table.insert(depend_files, path.join(common_tool.get_build_dir(), "tools/CppHeaderTool.dll"))
        table.sort(depend_files)
        -- run codegen task
        if has_config("skip_codegen") then
            print(string.format("======= %s codegen is skipped, remember before release!! =======", target:name()))
        else
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
                    for _, includeDir in ipairs(dep:get("includedirs", {interface = true})) do
                        table.insert(sysinclude_list, path.absolute(includeDir))
                    end
                end
                for _, sysincludeDir in ipairs(target:get("sysincludedirs")) do
                    table.insert(sysinclude_list, path.absolute(sysincludeDir))
                end
                -- collect package include dirs
                local function collect_package(target)
                    for package_name, package in pairs(target:orderpkgs()) do
                        table.insert(sysinclude_list, path.absolute(package:installdir() .. "/include"))
                    end
                end
                for _, dep in pairs(target:deps()) do
                    collect_package(dep)
                end
                collect_package(target)
                -- collect defines
                local defines = {
                    "__HEADER_TOOL__",
                    "NDEBUG",
                    "_CRT_USE_BUILTIN_OFFSETOF",
                }
                table.join2(defines, target:get("defines"))
                for _, dep in pairs(target:deps()) do
                    table.join2(defines, dep:get("defines", {interface = true}))
                end
                -- collect compiler arguments
                local arguments = {
                    "-std=c++2c",
                    "--verbose",
                }
    
                local parser_includes = extraconf.parser_includes or {}
                local input_text = nil
                for _, includefile in ipairs(parser_includes) do
                    local line = string.format("#include \"%s\"", includefile)
                    input_text = input_text and input_text.."\n"..line or line
                end
    
                local preHeaderText = extraconf.pre_header_text
                local postHeaderText = extraconf.post_header_text
    
                local mmoduleTemplates = table.join(templates.module, templates.js_module)
                local typeTemplates = table.join(templates.type, templates.js_type)
                local injectMetaTemplates = templates.inject_meta

                local runInfo = {
                    templateDir = template_dir,
                    moduleTemplates = mmoduleTemplates,
                    typeTemplates = typeTemplates,
                    injectMetaTemplates = injectMetaTemplates,
                    module = target_name,
                    input_text = input_text,
                    preHeaderText = preHeaderText,
                    postHeaderText = postHeaderText,
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
            end, {dependfile = gendir.."/codegen.d", files = depend_files})
        end
        
        local genCppFiles = os.files(gendir.."/**.cpp")
        for _, file in ipairs(genCppFiles) do
            target:add("files", file)
        end
        local genHeaderFiles = os.files(gendir.."/**.h")
        for _, file in ipairs(genHeaderFiles) do
            target:add("headerfiles", file)
        end
        if #genCppFiles > 0 or #genHeaderFiles > 0 then
            target:add("filegroups", "codegen", {rootdir = gendir})
        end
        target:add("includedirs", auto_gendir, { public = true })
    end)