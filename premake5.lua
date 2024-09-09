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
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .."/%{prj.name}")
	objdir ("bin-int/" .. outputdir .."/%{prj.name}")

	pchheader "ccpch.h"
	pchsource "Engine/src/ccpch.cpp"

	files {
		"Engine/src/**.h",
		"Engine/src/**.cpp",
	}

	includedirs {
		"Engine/src;",
		"Engine/vendor/spdlog/include;",
		"Engine/vendor/GLFW/include;",
		"Engine/vendor/Glad/include;",
		"Engine/vendor/Imgui"
	}

	links {
		"GLFW",
		"Glad",
		"Imgui",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"CC_PLATFORM_WINDOWS",
			"CC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CC_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "CC_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "CC_DIST"
		buildoptions "/MD"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	
	language "C++"

	targetdir ("bin/" .. outputdir .."/%{prj.name}")
	objdir ("bin-int/" .. outputdir .."/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Engine/vendor/spdlog/include;",
		"Engine/src;"

	}

	links {
		"CannisCanno"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"CC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CC_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CC_DIST"
		optimize "On"