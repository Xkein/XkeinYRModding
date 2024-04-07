yrpp_includes_dir = get_thirdparty_path("YRpp")

target("YRpp")
    set_languages("cxx20")
    set_kind("static")
    add_rules("codegen-cpp", {
        parserfiles = {
            
        },
        templates = {
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
    })
    set_optimize("fastest")
    add_headerfiles(yrpp_includes_dir.."/**.h")
    add_headerfiles(yrpp_includes_dir.."/**.hpp")
    add_files(yrpp_includes_dir.."/StaticInits.cpp")
    add_includedirs(yrpp_includes_dir, {public = true})
    add_filegroups("YRpp", {rootdir = yrpp_includes_dir})
    add_defines("_CRT_SECURE_NO_WARNINGS", "NOMINMAX", "WIN32", "HAS_EXCEPTIONS=0", "SYR_VER=2", {public = true})
    add_cxxflags("/permissive-", {public = true})
