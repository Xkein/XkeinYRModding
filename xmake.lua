add_rules("mode.debug", "mode.release")

set_allowedplats("windows")
set_allowedarchs("x86")

add_moduledirs("xmake/modules")
includes("xmake/modules/common_tool.lua")

includes("xmake/options.lua")
includes("xmake/3rdparty.lua")
includes("xmake/rules.lua")

add_rules("CoreRule")
rule("CoreRule")
    after_load(function (target)
        if target:kind() == "phony" or (target:name() ~= "Core" and target:dep("Core") == nil) then
            return
        end
        local api = string.upper(target:name())
        target:add("defines", api.."_IMPL")
        target:add("defines", api.."_API=__declspec(dllimport)", {interface=true})
        target:add("defines", api.."_API=__declspec(dllexport)", {private=true})
    end)


target("Core")
    set_kind("static")
    set_languages("cxxlatest")
    add_deps("rttr", "spdlog", "json")
    add_headerfiles("src/core/**.h")
    add_headerfiles("src/core/**.hpp")
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
    add_deps("Core", { public = false })
    add_deps("YRpp")
    add_headerfiles("src/yr/**.h")
    add_headerfiles("src/yr/**.hpp")
    add_files("src/yr/**.cpp")
    add_includedirs("src", "src/yr")
    add_filegroups("YrExtCore", {rootdir = "src"})

target("YrScripting")
    set_kind("shared")
    set_languages("cxxlatest")
    add_rules("codegen-cpp")
    add_deps("Core", "YrExtCore", "entt", "imgui", { public = false })
    -- add_packages("rttr", {public = false})
    add_headerfiles("src/scripting/**.h")
    add_headerfiles("src/scripting/**.hpp")
    add_files("src/scripting/**.cpp")
    add_includedirs("src", "src/scripting", {public = false})
    add_filegroups("Engine", {rootdir = "src"})
