
option("clone_v8")
    set_default(false)
    set_description("use depot tool to clone v8 and build")
option_end()

if(has_config("clone_v8")) then
    v8_dir = get_thirdparty_path("v8")
else
    v8_dir = os.getenv("V8_PATH")
    if v8_dir == nil then
        print("could not get v8 path!")
    end
end

v8_includes_dir = v8_dir.."/include"

target("v8")
    set_kind("headeronly")
    add_headerfiles(v8_includes_dir.."/**.h")
    add_includedirs(v8_includes_dir, {public = true})
    add_syslinks("DbgHelp", "Winmm", "Advapi32", {public=true})
    add_links(v8_dir.."/out.gn/x86.release/obj/wee8.lib", {public=true})
    add_filegroups("v8", {rootdir = v8_includes_dir})
