
option("download_v8")
    set_default(false)
    set_description("use depot tool to clone v8 and build")
option_end()

if(has_config("download_v8")) then
    error("TODO: support download v8")
    v8_dir = nil
else
    v8_dir = os.getenv("V8_PATH")
    if v8_dir == nil then
        error("could not get v8 path from env!")
    end
end

v8_includes_dir = v8_dir.."/Inc"
v8_lib_dir = v8_dir.."/Lib/Win32"

if not os.exists(v8_includes_dir) or not os.exists(v8_includes_dir) then
    error("v8 include or library directory not exists")
end

target("v8")
    set_kind("headeronly")
    add_headerfiles(v8_includes_dir.."/**.h")
    add_includedirs(v8_includes_dir, {public = true})
    add_syslinks("DbgHelp", "Winmm", "Advapi32", {public=true})
    add_links(v8_lib_dir.."/wee8.lib", {public=true})
    add_filegroups("v8", {rootdir = v8_includes_dir})
