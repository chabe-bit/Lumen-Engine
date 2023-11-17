workspace "Lumen"

    architecture "x64" 

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Lumen/vendor/GLFW/include"
IncludeDir["Glad"] = "Lumen/vendor/Glad/include"

include "Lumen/vendor/GLFW"
include "Lumen/vendor/Glad"


project "Lumen"
    location "Lumen"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "lmpch.h"
    pchsource "Lumen/src/lmpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
        
    }

    externalincludedirs
    {
        "C:/Users/amyke/Desktop/glfw-3.3.8.bin.WIN64/include",
    }

    syslibdirs 
    { 
        "C:/Users/amyke/Desktop/glfw-3.3.8.bin.WIN64/lib-vc2022",
        

    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib",
        "glfw3dll.lib",
        "glfw3.lib"
        
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LM_PLATFORM_WINDOWS",
            "LM_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "LM_DEBUG"
        staticruntime "off"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "LM_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "LM_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Lumen/vendor/spdlog/include",
        "Lumen/src"
    }

    links 
    {
        "Lumen"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LM_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "LM_DEBUG"
        staticruntime "off"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "LM_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "LM_DIST"
        optimize "On"

