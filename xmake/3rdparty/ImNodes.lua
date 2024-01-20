ImNodes_includes_dir = get_thirdparty_path("ImNodes")

target("ImNodes")
    set_kind("static")
    add_deps("imgui", {public = true})
    add_headerfiles(
        ImNodes_includes_dir.."/imnodes.h",
        ImNodes_includes_dir.."/imnodes_internal.h"
    )
    add_files(ImNodes_includes_dir.."/imnodes.cpp")
    add_defines("IMGUI_DEFINE_MATH_OPERATORS", {public = false})
    add_includedirs(ImNodes_includes_dir, {public = true})
    add_filegroups("ImNodes", {rootdir = ImNodes_includes_dir})
