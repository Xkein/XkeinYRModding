
includes("rules/codegen.lua")

rule("CoreRule")
    after_load(function (target)
        if target:kind() == "phony" or (target:name() ~= "Core" and target:dep("Core") == nil) then
            return
        end
        
        if is_mode("debug") then
            target:add("defines", "IS_EDITOR")
            target:add("defines", "DEBUG")
        else
            target:add("defines", "RELEASE")
        end

        if target:name() == "YrExtCore" then
            -- target:add("defines", "ENTT_API=ENTT_EXPORT", {private=true})
            target:add("defines", "CORE_IMPL", {private=true})
            target:add("defines", "CORE_API=__declspec(dllexport)", {private=true})
        else
            -- target:add("defines", "ENTT_API=ENTT_IMPORT", {private=true})
            target:add("defines", "CORE_API=__declspec(dllimport)", {private=true})
            if target:name() ~= "Core" and target:name() ~= "YRpp" then
                target:add("links", "YrExtCore.lib", {private=true})
            end
        end

        local api = string.upper(target:name())
        target:add("defines", api.."_IMPL")
        if target:name() ~= "Core" then
            target:add("defines", api.."_API=__declspec(dllimport)", {interface=true})
        end
        target:add("defines", api.."_API=__declspec(dllexport)", {private=true})
    end)
rule_end()
