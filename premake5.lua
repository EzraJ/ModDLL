function os.winSdkVersion()
    local reg_arch = iif( os.is64bit(), "\\Wow6432Node\\", "\\" )
    local sdk_version = os.getWindowsRegistry( "HKLM:SOFTWARE" .. reg_arch .."Microsoft\\Microsoft SDKs\\Windows\\v10.0\\ProductVersion" )
    if sdk_version ~= nil then return sdk_version end
end

workspace "ModDLL"
    configurations {"Debug", "Release"}
    filter {"system:windows", "action:vs*"}
    systemversion(os.winSdkVersion() .. ".0")
project "ModDLL"
    kind "SharedLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    libdirs {"liblua53.a", "src/Lua535"}
    libdirs {"lua53.dll", "src/Lua535"}
    includedirs {"src/", "src/Lua535/include"}
    files {"src/**.h", "src/**.cpp", "src/**.c"}
    defines {"MODDLL_EXPORTS"}
    

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"