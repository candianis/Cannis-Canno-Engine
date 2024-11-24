workspace "CannisCanno"

	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Engine/vendor/GLFW"
include "Engine/vendor/Glad"
include "Engine/vendor/Imgui"

project "CannisCanno"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .."/%{prj.name}")
	objdir ("bin-int/" .. outputdir .."/%{prj.name}")

	pchheader "ccpch.h"
	pchsource "Engine/src/ccpch.cpp"

	files {
		"Engine/src/**.h",
		"Engine/src/**.hpp",
		"Engine/src/**.cpp",
		"Engine/vendor/GLM/glm/**.hpp",
		"Engine/vendor/GLM/glm/**.inl",
	}

	includedirs {
		"Engine/src;",
		"Engine/vendor/spdlog/include;",
		"Engine/vendor/GLFW/include;",
		"Engine/vendor/Glad/include;",
		"Engine/vendor/Imgui;",
		"Engine/vendor/GLM;",
		"Engine/vendor/Assimp/include;",
		"Engine/vendor/stb_image/include;"
	}

	links {
		"GLFW",
		"Glad",
		"Imgui",
		"opengl32.lib",
		"dwmapi.lib",
		"Engine/vendor/Assimp/bin/assimp-vc143-mtd.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"CC_PLATFORM_WINDOWS",
			"CC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "CC_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "CC_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "CC_DIST"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .."/%{prj.name}")
	objdir ("bin-int/" .. outputdir .."/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/GLM/glm"
	}

	includedirs {
		"Engine/vendor/spdlog/include;",
		"Engine/src;",
		"Engine/vendor/GLM;",
		"Engine/vendor/Glad/include;",		
		"Engine/vendor/Assimp/include;",
		"Engine/vendor/stb_image/include;"
	}

	links {
		"CannisCanno"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"CC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CC_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "CC_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "CC_DIST"
		optimize "on"