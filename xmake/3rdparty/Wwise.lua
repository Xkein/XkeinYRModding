
wwise_sdk_path = os.getenv("WWISESDK")
if wwise_sdk_path == nil then
    error("could not get wwise path from env!")
end

wwise_includes_dir = wwise_sdk_path.."/include"
if is_mode("debug") then
    wwise_lib_dir = wwise_sdk_path.."/Win32_vc170/Debug(StaticCRT)/lib"
else
    wwise_lib_dir = wwise_sdk_path.."/Win32_vc170/Release(StaticCRT)/lib"
end

if not os.exists(wwise_includes_dir) or not os.exists(wwise_lib_dir) then
    error("wwise include or library directory not exists")
end

target("Wwise")
    set_kind("static")
    set_languages("cxx20")
    add_rules("codegen-cpp", {
        parser_includes = {
            "AK/SoundEngine/Common/AkSoundEngine.h",
    }})
    add_headerfiles(wwise_includes_dir.."/**.h")
    add_includedirs(wwise_includes_dir, {public = true})
    add_files(wwise_sdk_path.."/samples/SoundEngine/Common/**.cpp", wwise_sdk_path.."/samples/SoundEngine/Win32/**.cpp")
    add_headerfiles(wwise_sdk_path.."/samples/SoundEngine/Common/**.h", wwise_sdk_path.."/samples/SoundEngine/Win32/**.h")
    add_includedirs(
        wwise_sdk_path.."/samples/SoundEngine/Common",
        wwise_sdk_path.."/samples/SoundEngine/Win32",
        {public = true})
    add_defines("UNICODE", {public = true})
    add_linkdirs(wwise_lib_dir, {public = true})
    add_syslinks("DbgHelp", "Winmm", "Dsound", "ws2_32", "Msacm32", {public=true})
    if is_mode("debug") then
        add_links("CommunicationCentral.lib")
    else
        add_defines("AK_OPTIMIZED", {public = true})
    end
    add_links("Ak3DAudioBedMixerFX.lib",
              "AkAudioInputSource.lib",
              "AkCompressorFX.lib",
              "AkDelayFX.lib",
              "AkExpanderFX.lib",
              "AkFlangerFX.lib",
              "AkGainFX.lib",
              "AkGuitarDistortionFX.lib",
              "AkHarmonizerFX.lib",
              "AkMatrixReverbFX.lib",
              "AkMeterFX.lib",
              "AkParametricEQFX.lib",
              "AkPeakLimiterFX.lib",
              "AkPitchShifterFX.lib",
              "AkRecorderFX.lib",
              "AkRoomVerbFX.lib",
              "AkSilenceSource.lib",
              "AkSineSource.lib",
              "AkStereoDelayFX.lib",
              "AkSynthOneSource.lib",
              "AkTimeStretchFX.lib",
              "AkToneSource.lib",
              "AkTremoloFX.lib",
              "AkMemoryMgr.lib",
              "AkMusicEngine.lib",
              "AkSoundEngine.lib",
              "AkSpatialAudio.lib",
              "AkStreamMgr.lib",
              "AkVorbisDecoder.lib",
              "AkOpusDecoder.lib",
        {public=true})
    add_filegroups("Wwise", {rootdir = wwise_includes_dir})
