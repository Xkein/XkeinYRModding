
function get_thirdparty_path(module)
    return "$(projectdir)/3rdparty/" .. module
end

function get_config_path(module)
    return "$(buildir)/config/"..module
end

function get_default_templates()
    return {
        module = {
            ["module_header.scriban"] =  "module/{0}.gen.h",
            ["module_cpp.scriban"] =  "module/{0}.gen.cpp",
        },
        class = {
            ["class_header.scriban"] =  "class/{0}.gen.h",
            ["class_cpp.scriban"] =  "class/{0}.gen.cpp",
        },
        enum = {
            ["enum_header.scriban"] =  "enum/{0}.gen.h",
            ["enum_cpp.scriban"] =  "enum/{0}.gen.cpp",
        },
    }
end
