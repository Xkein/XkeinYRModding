ImNodes_includes_dir = get_thirdparty_path("imgui-node-editor")

target("ImguiNodeEditor")
    set_kind("static")
    add_deps("imgui", {public = true})
    add_headerfiles(ImNodes_includes_dir.."/*.h")
    add_files(ImNodes_includes_dir.."/*.cpp")
    add_includedirs(ImNodes_includes_dir, {public = true})
    add_filegroups("ImNodes", {rootdir = ImNodes_includes_dir})
