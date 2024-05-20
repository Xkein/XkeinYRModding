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
    add_deps("entt", "spdlog", "json")
    add_headerfiles("src/core/**.h")
    add_files("src/core/**.cpp")
    add_includedirs("src", "src/core")
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
    add_headerfiles("src/yr/**.h")
    add_files("src/yr/**.cpp")
    add_includedirs("src", "src/yr")
    add_filegroups("YrExtCore", {rootdir = "src"})
    add_syslinks("DbgHelp")

target("YrExtUI")
    set_kind("shared")
    set_languages("cxxlatest")
    add_deps("YrExtCore", "imgui", "stb")
    add_syslinks("d3d11", "user32", "Comctl32")
    add_headerfiles("src/ui/**.h")
    add_files("src/ui/**.cpp")
    add_includedirs("src", "src/ui")
    add_filegroups("YrExtUI", {rootdir = "src"})

target("YrScripting")
    set_kind("shared")
    set_languages("cxxlatest")
    add_rules("codegen-cpp")
    add_deps("YrExtCore", "YrExtUI", "ImguiNodeEditor", "puerts")
    add_headerfiles("src/scripting/**.h")
    add_files("src/scripting/**.cpp")
    add_includedirs("src", "src/scripting", {public = false})
    add_filegroups("YrScripting", {rootdir = "src"})
    after_build(function (target)
        
    end)
