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
IncludeDir["glm"] = "Lumen/vendor/glm"
IncludeDir["stb_image"] = "Lumen/vendor/stb_image"


include "Lumen/vendor/GLFW"
include "Lumen/vendor/Glad"


project "Lumen"
    location "Lumen"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "lmpch.h"
    pchsource "Lumen/src/lmpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"

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
        systemversion "latest"

        defines
        {
            "LM_PLATFORM_WINDOWS",
            "LM_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "LM_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LM_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LM_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Lumen/src",
        "%{IncludeDir.glm}",
    }

    links 
    {
        "Lumen"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "LM_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "LM_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LM_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LM_DIST"
        runtime "Release"
        optimize "on"

