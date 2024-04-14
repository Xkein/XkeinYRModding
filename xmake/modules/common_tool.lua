
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
        class = {
            ["class_header.scriban"] =  "class/{0}.gen.h",
            ["class_cpp.scriban"] =  "class/{0}.gen.cpp",
        },
        enum = {
            ["enum_header.scriban"] =  "enum/{0}.gen.h",
            ["enum_cpp.scriban"] =  "enum/{0}.gen.cpp",
        },
        depend_only = {
            ["include/common.scriban"] = "not use to generate!",
        }
    }
end

function get_templates(overrides)
    local templates = get_default_templates()
    table.join2(templates, overrides)
    return templates
end
