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
            class = {
                ["yr/yr_class_header.scriban"] =  "class/{0}.gen.h",
                ["yr/yr_class_cpp.scriban"] =  "class/{0}.gen.cpp",
            },
            module = {
                ["module_header.scriban"] =  "{0}.gen.h",
                ["yr/yr_module_cpp.scriban"] =  "{0}.gen.cpp",
            },
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
