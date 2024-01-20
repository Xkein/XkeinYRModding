
target("codegen-policy")
    add_deps("build-header-tool")
    set_kind("headeronly")
    before_build(function(target)
        -- import("meta_codegen")
        -- meta_codegen()
    end)

rule("codegen-cpp")
    on_load(function (target, opt)
        target:add("deps", "codegen-policy")

        local gendir = path.join(target:autogendir({root = true}), target:plat(), "codegen")
        local sourcefile = path.join(gendir, target:name(), "/generated.cpp")
        -- import("core.base.task")
        -- task.run("dotnet-compile-job", {

        -- })
        -- target:add("files", sourcefile, { unity_ignored = true })
        -- target:add("includedirs", gendir, {public = true})
    end)