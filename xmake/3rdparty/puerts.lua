puerts_dir = get_thirdparty_path("puerts")
puerts_unity_dir = puerts_dir.."/unity"
puerts_unreal_dir = puerts_dir.."/unreal"
puerts_3rd_dir = puerts_dir.."/unreal/Puerts/ThirdParty"
puerts_native_dir = puerts_dir.."/unity/native_src"
puerts_native_il2cpp_dir = puerts_dir.."/unity/native_src_il2cpp"
puerts_unreal_puerts_dir = puerts_unreal_dir.."/Puerts"

target("puerts")
    set_kind("static")
    set_languages("cxx17")
    add_deps("v8")
    add_includedirs(
        puerts_native_dir.."/Inc",
        puerts_unreal_puerts_dir.."/Source/JsEnv/Private",
        puerts_unreal_puerts_dir.."/Source/JsEnv/Public",
        puerts_3rd_dir.."/Include/websocketpp", 
        puerts_3rd_dir.."/Include/asio",
        {public = true})
    add_headerfiles(
        puerts_native_dir.."/Inc/*.h",
        puerts_unreal_puerts_dir.."/Source/JsEnv/Private/*.h",
        puerts_unreal_puerts_dir.."/Source/JsEnv/Public/*.h",
        puerts_unreal_puerts_dir.."/Source/JsEnv/Private/V8InspectorImpl.h",
        puerts_unreal_puerts_dir.."/Source/JsEnv/Private/PromiseRejectCallback.h"
    )
    add_files(
        puerts_unreal_puerts_dir.."/Source/JsEnv/Private/PesapiV8Impl.cpp",
        puerts_unreal_puerts_dir.."/Source/JsEnv/Private/CppObjectMapper.cpp",
        puerts_unreal_puerts_dir.."/Source/JsEnv/Private/DataTransfer.cpp",
        puerts_unreal_puerts_dir.."/Source/JsEnv/Private/JSClassRegister.cpp",
        puerts_native_dir.."/Src/BackendEnv.cpp",
        puerts_native_dir.."/Src/JSFunction.cpp",
        puerts_unreal_puerts_dir.."/Source/JsEnv/Private/V8InspectorImpl.cpp"
    )
    add_defines("MAPPER_ISOLATE_DATA_POS=2", {public = true})
    add_defines("puerts_API=__declspec(dllexport)", "BUILDING_V8_SHARED", {public = true}) -- static lib
    -- add_defines("puerts_API=__declspec(dllexport)", "BUILDING_V8_SHARED", {private=true})
    -- add_defines("puerts_API=__declspec(dllimport)", "USING_V8_SHARED", {interface=true})
    add_filegroups("puerts", {rootdir = puerts_dir})
target_end()