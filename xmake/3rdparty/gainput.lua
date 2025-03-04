gainput_dir = get_thirdparty_path("gainput")

target("gainput")
    set_kind("shared")
    set_languages("cxx20")
    add_rules("codegen-cpp", {
        parser_includes = {
            "gainput/gainput.h",
    }})
    add_headerfiles(gainput_dir.."/lib/include/**.h")
    add_headerfiles(gainput_dir.."/lib/source/**.h")
    add_files(gainput_dir.."/lib/source/**.cpp")
    -- add_defines("GAINPUT_LIB_DYNAMIC_USE", {public = true})
    add_defines("GAINPUT_LIB_DYNAMIC", {private = true})
    add_syslinks("ws2_32", "xinput9_1_0", "user32")
    add_includedirs(gainput_dir.."/lib/include", {public = true})
    add_filegroups("gainput", {rootdir = gainput_dir})
