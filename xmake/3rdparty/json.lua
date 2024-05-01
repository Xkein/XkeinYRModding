json_dir = get_thirdparty_path("json")
json_includes_dir = json_dir.."/include"

target("json")
    set_kind("headeronly")
    add_headerfiles(json_includes_dir.."/**.h")
    add_headerfiles(json_includes_dir.."/**.hpp")
    add_includedirs(json_includes_dir, {public = true})
    add_filegroups("nlohmann", {rootdir = json_includes_dir.."/nlohmann"})