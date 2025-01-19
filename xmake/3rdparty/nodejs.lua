
nodejs_dir = os.getenv("NODEJS_PATH")
if nodejs_dir == nil then
    error("could not get nodejs path from env!")
end

if not os.exists(nodejs_dir) then
    error("nodejs directory not exists")
end

target("nodejs")
    set_kind("headeronly")
    add_includedirs(nodejs_dir.."/include",
                    nodejs_dir.."/deps/v8/include",
                    nodejs_dir.."/deps/uv/include", {public = true})
    add_headerfiles(nodejs_dir.."/include/**.h",
                    nodejs_dir.."/deps/v8/include/**.h",
                    nodejs_dir.."/deps/uv/include/**.h")
    add_syslinks("DbgHelp", "Winmm", "Advapi32", {public=true})
    add_links(nodejs_dir.."/lib/Win32/libnode.lib", {public=true})
    add_filegroups("nodejs", {rootdir = nodejs_dir})
