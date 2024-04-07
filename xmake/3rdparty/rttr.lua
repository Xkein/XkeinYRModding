
local rttr_dir = get_thirdparty_path("rttr")
local rttr_source_dir = rttr_dir.."/src"
local rttr_gen_dir = get_config_path("rttr")

-- package("rttr_package")
--     add_deps("cmake")
--     set_sourcedir(rttr_dir)
--     on_load(function (package)
--         local configs = {
--             -- "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"),
--             -- "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"),
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
--         import("common")
--         import("package.tools.cmake").install(package, configs, {
--             buildir = get_thirdparty_path("rttr"),
--         })
--     end)
-- package_end()

-- add_requires("rttr_package")

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
    add_includedirs(rttr_gen_dir, {public = true})

    on_load(function (target)
        import("common_tool")
        -- i have no idea about this but write it by hand...
        local content = "#ifndef RTTR_VERSION_H_\n#define RTTR_VERSION_H_\n#define RTTR_VERSION_MAJOR 0\n#define RTTR_VERSION_MINOR 9\n#define RTTR_VERSION_PATCH 7\n#define RTTR_VERSION       907\n#define RTTR_VERSION_STR   \"0.9.7\"\n#endif // RTTR_VERSION_H_"

        local rttr_gen_dir = common_tool.get_config_path("rttr")
        local file_path = rttr_gen_dir.."/rttr/detail/base/version.h"
        if not os.exists(file_path) then
            io.writefile(file_path, content)
        end
    end)

