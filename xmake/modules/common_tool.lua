
function get_build_dir()
    if import then
        return path.absolute(import("core.project.config").buildir())
    else
        return "$(buildir)"
    end
end

function get_thirdparty_path(module)
    return path.join(os.projectdir(), "3rdparty", module)
end

function get_config_path(module)
    return path.join(get_build_dir(), "config", module)
end

function get_auto_gendir(targetName)
    import("core.project.config")
    import("core.project.project")
    local target = project.target(targetName)
    return path.join(config.buildir(), ".gens", string.format("%s_%s_%s", target:plat(), config.mode(), target:arch()), targetName)
end

function get_default_templates()
    -- module: {0} = module name
    -- type: {0} = type name, {1} = module name
    local codegen_dir = "../.."
    local root_dir = "../../../../.."

    return {
        module = {
            ["module_header.scriban"] =  "{0}.gen.h",
            ["module_cpp.scriban"] =  "{0}.gen.cpp",
        },
        type = {
            ["type_header.scriban"] =  "type/{0}.gen.h",
            ["type_cpp.scriban"] =  "type/{0}.gen.cpp",
        },
        js_type = {
            ["js_type_cpp.scriban"] =  codegen_dir.."/YrScripting/codegen/{1}/{0}.js_binding.cpp",
        },
        js_module = {
            ["ts_module_index.scriban"] = root_dir.."/src/scripts/typescript/gen/{0}.d.ts",
            ["js_module_setup.scriban"] = root_dir.."/src/scripts/javascript/gen/{0}.js",
        },
        depends = {
            ["include/common.scriban"] = "not use to generate!",
            ["include/meta.scriban"] = "not use to generate!",
        }
    }
end

function get_templates(overrides, additions)
    local templates = get_default_templates()
    if overrides then
        table.join2(templates, overrides)
    end

    if additions then
        for key, val in pairs(additions) do
            templates[key] = table.join(templates[key] or {}, val)
        end
    end

    return templates
end
