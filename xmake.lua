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
    add_packages("boost", "utfcpp", "efsw", "spdlog", { public = true })
    add_headerfiles("src/core/**.h", "src/core/**.hpp")
    add_files("src/core/**.cpp")
    add_headerfiles("src/runtime/**.h")
    add_files("src/runtime/**.cpp")
    add_includedirs("src", { public = true })
    add_filegroups("Core", {rootdir = "src"})

target("YrExtCore")
    set_kind("shared")
    set_languages("cxxlatest")
    add_rules("codegen-cpp", {
        templates = get_templates({
            module = {
                ["module_header.scriban"] =  "{0}.gen.h",
                ["yr/yr_module_cpp.scriban"] =  "{0}.gen.cpp",
            },
        })
    })
    add_deps("Core", "YRpp")
    -- export symbols
    add_files("src/core/**.cpp", "src/runtime/**.cpp")
    add_headerfiles("src/yr/**.h")
    add_files("src/yr/**.cpp")
    add_filegroups("YrExtCore", {rootdir = "src"})
    add_syslinks("DbgHelp")

target("YrExtUI")
    set_kind("shared")
    set_languages("cxxlatest")
    add_rules("codegen-cpp")
    add_deps("YrExtCore", "imgui")
    add_packages("stb")
    add_syslinks("d3d11", "user32", "Comctl32")
    add_headerfiles("src/ui/**.h")
    add_files("src/ui/**.cpp")
    add_filegroups("YrExtUI", {rootdir = "src"})

target("YrScripting")
    set_kind("shared")
    set_languages("cxxlatest")
    add_rules("codegen-cpp")
    add_deps("YrExtCore", "YrExtUI", "ImguiNodeEditor", "puerts")
    add_headerfiles("src/scripting/**.h")
    add_files("src/scripting/**.cpp")
    add_filegroups("YrScripting", {rootdir = "src"})
    add_cxxflags("/bigobj")

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

target("XkeinExt")
    set_kind("shared")
    set_languages("cxxlatest")
    add_rules("codegen-cpp")
    add_deps("YrExtCore")
    add_headerfiles("src/audio/**.h", "src/physics/**.h", "src/render/**.h")
    add_files("src/audio/**.cpp", "src/physics/**.cpp", "src/render/**.cpp")
    add_headerfiles("src/xkein/**.h")
    add_files("src/xkein/**.cpp")
    add_filegroups("XkeinExt", {rootdir = "src"})
    
target("XkeinEditor")
    set_kind("shared")
    set_languages("cxxlatest")
    add_rules("codegen-cpp")
    add_deps("YrExtCore", "YrExtUI")
    add_headerfiles("src/editor/**.h")
    add_files("src/editor/**.cpp")
    add_filegroups("XkeinEditor", {rootdir = "src"})

target("make_artifacts")
    set_kind("phony")
    add_deps("Scripts", "YrScripting")
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
            [build_dir.."/YrExtUI.dll"] = output_dir.."/plugins/YrExtUI.dll",
            [build_dir.."/YrScripting.dll"] = output_dir.."/plugins/YrScripting.dll",
            [build_dir.."/JoltPhysics.dll"] = output_dir.."/plugins/JoltPhysics.dll",
            [build_dir.."/XkeinEditor.dll"] = output_dir.."/plugins/XkeinEditor.dll",
            [build_dir.."/XkeinExt.dll"] = output_dir.."/plugins/XkeinExt.dll",
        }

        local function get_copy_files(dir, pattern, out_dir)
            local files = os.files(path.join(dir, pattern))
            for _, file in ipairs(files) do
                local rel = path.relative(path.relative(file), dir)
                copy_pairs[path.join(dir, rel)] = path.join(out_dir, rel)
            end
        end
        
        get_copy_files("src/scripts/javascript/", "**", output_dir.."/assets/JavaScript/")
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
