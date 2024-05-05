imgui_includes_dir = get_thirdparty_path("imgui")

target("imgui")
    set_kind("shared")
    add_headerfiles(imgui_includes_dir.."/*.h")
    add_files(imgui_includes_dir.."/*.cpp|imgui_demo.cpp")
    add_headerfiles(
        imgui_includes_dir.."/backends/imgui_impl_dx11.h",
        imgui_includes_dir.."/backends/imgui_impl_win32.h"
    )
    add_files(
        imgui_includes_dir.."/backends/imgui_impl_dx11.cpp",
        imgui_includes_dir.."/backends/imgui_impl_win32.cpp"
    )
    add_defines("IMGUI_API=__declspec(dllexport)", {private=true})
    add_defines("IMGUI_API=__declspec(dllimport)", {interface=true})
    add_defines("ImTextureID=void*", {public = true})
    add_includedirs(imgui_includes_dir, imgui_includes_dir.."/backends", {public = true})
    add_filegroups("imgui", {rootdir = imgui_includes_dir})
target_end()

ImNodes_includes_dir = get_thirdparty_path("imgui-node-editor")

target("ImguiNodeEditor")
    set_kind("shared")
    add_deps("imgui", {public = true})
    add_headerfiles(ImNodes_includes_dir.."/*.h")
    add_files(ImNodes_includes_dir.."/*.cpp")
    add_defines("IMGUI_NODE_EDITOR_API=__declspec(dllexport)", {private=true})
    add_defines("IMGUI_NODE_EDITOR_API=__declspec(dllimport)", {interface=true})
    add_defines("IMGUIEX_CANVAS_API=__declspec(dllexport)", {private=true})
    add_defines("IMGUIEX_CANVAS_API=__declspec(dllimport)", {interface=true})
    add_includedirs(ImNodes_includes_dir, {public = true})
    add_filegroups("ImNodes", {rootdir = ImNodes_includes_dir})
target_end()
    