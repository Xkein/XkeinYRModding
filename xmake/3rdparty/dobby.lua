dobby_dir = get_thirdparty_path("dobby")

package("dobby_local")
    add_deps("cmake")
    set_sourcedir(dobby_dir)
    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        table.insert(configs, "-DCMAKE_SYSTEM_PROCESSOR=x86")
        table.insert(configs, "-DCMAKE_SYSTEM_NAME=Windows")
        -- table.insert(configs, "-DDOBBY_GENERATE_SHARED=OFF")
        -- table.insert(configs, "-DPlugin.ImportTableReplace=ON")
        import("package.tools.cmake").install(package, configs)
        -- Dobby's CMakeLists.txt does not install headers, manually copy them
        local src_dir = path.join(os.projectdir(), "3rdparty", "dobby")
        local inc_dir = path.join(package:installdir(), "include")
        os.mkdir(inc_dir)
        os.cp(path.join(src_dir, "include", "dobby.h"), inc_dir)
    end)
    on_test(function (package)
        -- Verify dobby library is installed
        assert(os.isfile(path.join(package:installdir(), "lib", "dobby.lib")))
    end)
package_end()

add_requires("dobby_local")