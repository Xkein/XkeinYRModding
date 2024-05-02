stb_dir = get_thirdparty_path("stb")
stb_includes_dir = stb_dir

target("stb")
    set_kind("headeronly")
    add_headerfiles(stb_includes_dir.."/*.h")
    add_includedirs(stb_includes_dir, {public = true})
    add_filegroups("stb", {rootdir = stb_includes_dir})
