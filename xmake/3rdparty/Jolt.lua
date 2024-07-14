jolt_includes_dir = get_thirdparty_path("JoltPhysics")

target("JoltPhysics")
    set_languages("cxx17")
    set_kind("shared")
    add_headerfiles(jolt_includes_dir.."/Jolt/**.h")
    add_files(jolt_includes_dir.."/Jolt/**.cpp")
    add_defines("JPH_SHARED_LIBRARY", {public = true})
    add_defines("JPH_BUILD_SHARED_LIBRARY", {private=true})
    add_includedirs(jolt_includes_dir, {public = true})
    add_filegroups("JoltPhysics", {rootdir = jolt_includes_dir})
