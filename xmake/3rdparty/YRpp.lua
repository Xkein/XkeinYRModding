yrpp_includes_dir = get_thirdparty_path("YRpp")

local function get_pre_header_text()
    return
        ""
end

target("YRpp")
    set_languages("cxx20")
    set_kind("static")
    add_rules("codegen-cpp", {
        parser_includes = {
            yrpp_includes_dir.."/StaticInits.cpp",
        },
        pre_header_text = get_pre_header_text(),
        templates = get_templates({
            type = {
                ["yr/yr_type_header.scriban"] =  "type/{0}.gen.h",
                ["yr/yr_type_cpp.scriban"] =  "type/{0}.gen.cpp",
            },
            module = {
                ["module_header.scriban"] =  "{0}.gen.h",
                ["yr/yr_module_cpp.scriban"] =  "{0}.gen.cpp",
            },
        }, {
            depends = {
                ["yr/yrpp.scriban"] = "not use to generate!",
            }
        })
    })
    set_optimize("fastest")
    add_headerfiles(yrpp_includes_dir.."/**.h")
    add_headerfiles(yrpp_includes_dir.."/**.hpp")
    add_files(yrpp_includes_dir.."/StaticInits.cpp")
    add_includedirs(yrpp_includes_dir, {public = true})
    add_filegroups("YRpp", {rootdir = yrpp_includes_dir})
    add_defines("_CRT_SECURE_NO_WARNINGS", "NOMINMAX", "WIN32", "HAS_EXCEPTIONS=0", "SYR_VER=2", {public = true})
    add_cxxflags("/permissive-", {public = true})
