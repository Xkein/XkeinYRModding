tracy_dir = get_thirdparty_path("tracy")

target("tracy")
    set_kind("shared")
    set_languages("cxx20")
    add_headerfiles(tracy_dir.."/public/tracy/Tracy.hpp")
    add_files(tracy_dir.."/public/TracyClient.cpp")

    if has_config("enable_tracy") then
        add_defines("TRACY_ENABLE", {public = true})
    end
    add_defines("TRACY_EXPORTS", {public = false})
    add_defines("TRACY_IMPORTS", "TRACY_DELAYED_INIT", "TRACY_MANUAL_LIFETIME", "TRACY_ON_DEMAND", {public = true})
    -- add_syslinks("ws2_32", "user32")
    add_includedirs(tracy_dir.."/public", {public = true})
    add_filegroups("tracy", {rootdir = tracy_dir})
