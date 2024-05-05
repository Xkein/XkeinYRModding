entt_dir = get_thirdparty_path("entt")
entt_includes_dir = entt_dir.."/src"

target("entt")
    set_kind("headeronly")
    add_headerfiles(entt_includes_dir.."/**.h")
    add_headerfiles(entt_includes_dir.."/**.hpp")
    add_includedirs(entt_includes_dir, {public = true})
    add_extrafiles(entt_dir.."/natvis/entt/*.natvis")
    add_filegroups("entt", {rootdir = entt_includes_dir.."/entt"})
