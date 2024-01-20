spdlog_dir = get_thirdparty_path("spdlog")
spdlog_includes_dir = spdlog_dir.."/include"

target("spdlog")
    set_kind("headeronly")
    add_headerfiles(spdlog_includes_dir.."/**.h")
    add_headerfiles(spdlog_includes_dir.."/**.hpp")
    add_includedirs(spdlog_includes_dir, {public = true})
    add_filegroups("spdlog", {rootdir = spdlog_includes_dir.."/spdlog"})
