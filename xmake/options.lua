
option("skip_codegen")
    set_default(false)
    set_description("skip codegen")
    
option("make_artifacts")
    set_default(false)
    set_description("make artifacts")

option("enable_tracy")
    set_default(false)
    set_description("enable Tracy profiling")
    
option("enable_hook_try_except")
    set_default(true)
    set_description("enable __try __except for hook, which may cause performance loss")

option("bundle_mcp")
    set_default(false)
    set_description("bundle xkein_yr_mcp tool into artifacts")

