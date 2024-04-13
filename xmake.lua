add_rules("mode.debug", "mode.release")

set_allowedplats("windows")
set_allowedarchs("x86")

add_moduledirs("xmake/modules")
includes("xmake/modules/common_tool.lua")

includes("xmake/options.lua")
includes("xmake/3rdparty.lua")
includes("xmake/rules.lua")

target("YrScripting")
    set_kind("shared")
    set_languages("cxxlatest")
    add_rules("codegen-cpp")
    add_deps("YRpp", {public = false})
    add_deps("entt", {public = false})
    add_deps("rttr", {public = false})
    add_deps("imgui", {public = false})
    add_deps("spdlog", {public = false})
    -- add_packages("rttr", {public = false})
    add_headerfiles("src/**.h")
    add_headerfiles("src/**.hpp")
    add_files("src/**.cpp")
    add_includedirs("src", {public = false})
    add_filegroups("Engine", {rootdir = "src"})
