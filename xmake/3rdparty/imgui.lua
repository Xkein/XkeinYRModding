imgui_includes_dir = get_thirdparty_path("imgui")

target("imgui")
    set_kind("static")
    add_headerfiles(imgui_includes_dir.."/*.h")
    add_files(imgui_includes_dir.."/*.cpp")

    add_headerfiles(
        imgui_includes_dir.."/backends/imgui_impl_dx11.h",
        imgui_includes_dir.."/backends/imgui_impl_win32.h"
    )
    add_files(
        imgui_includes_dir.."/backends/imgui_impl_dx11.cpp",
        imgui_includes_dir.."/backends/imgui_impl_win32.cpp"
    )

    add_defines("ImTextureID=ImU64", {public = true})

    add_includedirs(imgui_includes_dir, {public = true})
    add_filegroups("imgui", {rootdir = imgui_includes_dir})
