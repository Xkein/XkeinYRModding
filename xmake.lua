add_rules("mode.debug", "mode.release")

set_allowedplats("windows")
set_allowedarchs("x86")

add_moduledirs("xmake/modules")
includes("xmake/modules/common_tool.lua")

includes("xmake/options.lua")
includes("xmake/3rdparty.lua")
includes("xmake/rules.lua")

add_rules("CoreRule")
target("Core")
    set_kind("static")
    set_languages("cxxlatest")
    add_deps("entt", "json")
    add_packages("boost", "utfcpp", "efsw", "spdlog", "cereal", { public = true })
    add_headerfiles("src/core/**.h", "src/core/**.hpp")
    add_files("src/core/**.cpp")
    add_headerfiles("src/runtime/**.h")
    add_files("src/runtime/**.cpp")
    add_includedirs("src", { public = true })
    add_filegroups("Core", {rootdir = "src"})
    add_cxxflags("/bigobj", "/utf-8", {public = true})

target("YrExtCore")
    set_kind("shared")
    set_languages("cxxlatest")
    add_rules("codegen-cpp")
    add_deps("Core", "YRpp")
    add_packages("asmjit", "zydis", { public = true })
    -- export symbols
    add_files("src/core/**.cpp", "src/runtime/**.cpp")
    add_headerfiles("src/yr/**.h")
    add_files("src/yr/**.cpp")
    add_filegroups("YrExtCore", {rootdir = "src"})
    add_syslinks("DbgHelp")

target("XkeinExt")
    set_kind("shared")
    set_languages("cxxlatest")
    add_rules("codegen-cpp")

    add_deps("YrExtCore", "JoltPhysics", "wwise", "puerts", "gainput")
    add_packages("cppzmq", "stb", "msgpack-cxx")

    add_headerfiles("src/audio/**.h", "src/physics/**.h", "src/render/**.h", "src/scripting/**.h", "src/input/**.h")
    add_files("src/audio/**.cpp", "src/physics/**.cpp", "src/render/**.cpp", "src/scripting/**.cpp", "src/input/**.cpp")

    add_headerfiles("src/xkein/**.h")
    add_files("src/xkein/**.cpp")
    -- editor
    add_deps("imgui", "ImguiNodeEditor")
    add_headerfiles("src/ui/**.h")
    add_files("src/ui/**.cpp")
    add_syslinks("d3d11", "user32", "Comctl32")
    -- wwise generated content
    add_includedirs("content/yr_wwise_template/GeneratedSoundBanks", { public = true })

    add_filegroups("XkeinExt", {rootdir = "src"})
    
target("XkeinEditor")
    set_kind("shared")
    set_languages("cxxlatest")
    add_rules("codegen-cpp")
    add_deps("YrExtCore", "XkeinExt")
    add_headerfiles("src/editor/**.h")
    add_files("src/editor/**.cpp")
    add_filegroups("XkeinEditor", {rootdir = "src"})

target("Scripts")
    set_kind("phony")
    add_extrafiles("src/scripts/**.js")
    -- add_extrafiles("3rdparty/puerts/unreal/Puerts/Content/JavaScript/**.js")
    add_extrafiles("src/scripts/**.ts")
    add_filegroups("Scripts", {rootdir = "src/scripts"})
    add_filegroups("puerts", {rootdir = "3rdparty/puerts/unreal/Puerts/Content"})
    on_build(function (target)
        local auto_gendir = target:autogendir({root = true})
        local gendir = path.absolute(auto_gendir)
        import("core.project.depend")
        depend.on_changed(function ()
            -- print("compiling typescript...")
            -- os.execv("tsc.cmd", {
            --     "-p", path.absolute("src/scripts/typescript/tsconfig.json"),
            -- })
        end, {dependfile = gendir.."/compile.d", files = target:get("extrafiles")})
    end)
target_end()

target("make_artifacts")
    set_kind("phony")
    add_deps("Scripts", "XkeinExt", "XkeinEditor")
    after_build(function (target)
        if not has_config("make_artifacts") then
            return
        end
        import("core.project.config")
        local build_dir = path.join(config.buildir(), config.plat(), config.arch(), config.mode())
        print("making artifacts...")
        local output_dir = path.join(config.buildir(), "artifacts", config.mode())
        local copy_pairs = {
            [build_dir.."/YrExtCore.dll"] = output_dir.."/YrExtCore.dll",
            [build_dir.."/imgui.dll"] = output_dir.."/plugins/imgui.dll",
            [build_dir.."/ImguiNodeEditor.dll"] = output_dir.."/plugins/ImguiNodeEditor.dll",
            [build_dir.."/JoltPhysics.dll"] = output_dir.."/plugins/JoltPhysics.dll",
            [build_dir.."/gainput.dll"] = output_dir.."/plugins/gainput.dll",
            [build_dir.."/XkeinEditor.dll"] = output_dir.."/plugins/XkeinEditor.dll",
            [build_dir.."/XkeinExt.dll"] = output_dir.."/plugins/XkeinExt.dll",
            [os.getenv("NODEJS_PATH").."/lib/Win32/libnode.dll"] = output_dir.."/plugins/libnode.dll",
        }

        local function get_copy_files(dir, pattern, out_dir)
            local files = os.files(path.join(dir, pattern))
            for _, file in ipairs(files) do
                local rel = path.relative(path.relative(file), dir)
                copy_pairs[path.join(dir, rel)] = path.join(out_dir, rel)
            end
        end
        -- copy javascript
        get_copy_files("src/scripts/javascript/", "**", output_dir.."/assets/JavaScript/")
        -- copy wwise sound banks
        get_copy_files("content/yr_wwise_template/GeneratedSoundBanks/Windows/", "**.bnk", output_dir.."/assets/wwise/")
        -- copy raw assets
        get_copy_files("assets/", "**", output_dir.."/assets/")

        local depend_files = {}
        for src, dst in pairs(copy_pairs) do
            table.insert(depend_files, path.absolute(src))
        end

        import("core.project.depend")
        depend.on_changed(function ()
            for src, dst in pairs(copy_pairs) do
                print(string.format("copy %s -> %s", src, dst))
                os.cp(src, dst)
            end
        end, {dependfile = output_dir.."/../files.d", files = depend_files})
    end)
