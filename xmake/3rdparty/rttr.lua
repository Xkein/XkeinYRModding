
rttr_dir = get_thirdparty_path("rttr")
rttr_source_dir = rttr_dir.."/src"

-- package("rttr_package")
--     add_deps("cmake")
--     set_sourcedir("$(projectdir)/3rdparty/rttr")
--     on_install(function (package)
--         local configs = {
--             "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"),
--             "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"),
--             "-DUSE_PCH=OFF",
--             "-DBUILD_BENCHMARKS=OFF",
--             "-DCUSTOM_DOXYGEN_STYLE=OFF",
--             "-DBUILD_UNIT_TESTS=OFF",
--             "-DBUILD_STATIC=OFF",
--             "-DBUILD_WITH_STATIC_RUNTIME_LIBS=OFF",
--             "-DBUILD_DOCUMENTATION=OFF",
--             "-DBUILD_EXAMPLES=OFF",
--             "-DBUILD_INSTALLER=OFF",
--             "-DBUILD_PACKAGE=OFF",
--         }
--         if package:is_targetos("windows") then
--             table.insert(configs, '-DCMAKE_CXX_FLAGS="/EHsc /MP"')
--         end
--         import("package.tools.cmake").install(package, configs)
--     end)
-- package_end()

-- add_requires("rttr")

local rttr_gen_dir = get_gen_path("rttr")

target("rttr")
    set_kind("static")
    set_optimize("fastest")
    add_headerfiles(rttr_source_dir.."/rttr/**.h")
    add_headerfiles(rttr_source_dir.."/rttr/**.hpp")
    add_files(rttr_source_dir.."/rttr/**.cpp")
    add_includedirs(rttr_source_dir, {public = true})
    add_filegroups("rttr", {rootdir = rttr_dir})
    set_exceptions("cxx")
    -- add_packages("rttr_package", {public = false})

    set_configdir(rttr_gen_dir)
    set_configvar("LIBRARY_VERSION_MAJOR", 0)
    set_configvar("LIBRARY_VERSION_MINOR", 9)
    set_configvar("LIBRARY_VERSION_PATCH", 7)
    set_configvar("LIBRARY_VERSION_CALC", 907)
    set_configvar("LIBRARY_VERSION_STR", "0.9.7")
    add_configfiles(rttr_source_dir.."/rttr/detail/base/version.h.in", {
        prefixdir = "rttr/detail/base",
        pattern = "@([^\n]-)@",
    })
    add_includedirs(rttr_gen_dir, {public = false})

