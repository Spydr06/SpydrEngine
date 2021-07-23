workspace "SpydrEngine"
	architecture"x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Spydr/vendor/GLFW/include"
IncludeDir["Glad"] = "Spydr/vendor/Glad/include"
IncludeDir["ImGui"] = "Spydr/vendor/imgui"
IncludeDir["glm"] = "Spydr/vendor/glm"

include "Spydr/vendor/GLFW"
include "Spydr/vendor/Glad"
include "Spydr/vendor/imgui"

project "Spydr"
	location "Spydr"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	pchheader "sppch.h"
	pchsource "Spydr/src/sppch.cpp"

	filter "system:windows"
		systemversion "latest"

		defines {
			"SP_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "system:linux"
		defines {
			"SP_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "SP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SP_DIST"
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

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"Spydr/vendor/spdlog/include",
		"Spydr/src",
		"Spydr/vendor",
		"%{IncludeDir.glm}"
	}

	links {
		"Spydr",
		"ImGui",
		"Glad",
		"GLFW"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"SP_PLATFORM_WINDOWS"
		}
	
	filter "system:linux"
		defines {
			"SP_PLATFORM_LINUX"
		}
		linkoptions "-Wl,--no-as-needed -ldl -lpthread"

	filter "configurations:Debug"
		defines "SP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SP_DIST"
		runtime "Release"
		optimize "on"
