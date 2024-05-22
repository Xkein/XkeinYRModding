
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

function get_default_templates()
    return {
        module = {
            ["module_header.scriban"] =  "{0}.gen.h",
            ["module_cpp.scriban"] =  "{0}.gen.cpp",
        },
        type = {
            ["type_header.scriban"] =  "type/{0}.gen.h",
            ["type_cpp.scriban"] =  "type/{0}.gen.cpp",
            ["js_type_cpp.scriban"] =  "../YrScripting/{1}/type/{0}.gen.cpp",
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
        for key, templates in pairs(additions) do
            templates[key] = table.join(templates[key] or {}, templates)
        end
    end

    return templates
end
