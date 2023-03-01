workspace "Positron Build"
    -- Location of generated premake files
    location "Generated"

    --language is only c++
    language "C++"

    --c++ 17
    cppdialect "C++17"

    -- We will compile for x86_64. You can change this to x86 for 32 bit builds.
	architecture "x86_64"

    configurations { "Debug", "Release" }

    -- We now only set settings for the Debug configuration
	filter { "configurations:Debug" }
		-- We want debug symbols in our debug config
		symbols "On"

	-- We now only set settings for Release
	filter { "configurations:Release" }
		-- Release should be optimized
		optimize "On"

    -- Reset the filter for other settings
	filter { }

    -- * %{prj.name} will be replaced by "ExampleLib" / "App" / "UnitTests"
	--  * %{cfg.longname} will be replaced by "Debug" or "Release" depending on the configuration
    -- The path is relative to *this* folder
	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")

-- This function includes GLFW's header files
function includeGLFW()
	includedirs "Libraries/GLFW/Include"
end

-- This function links statically against GLFW
function linkGLFW()
	libdirs "Libraries/GLFW/Lib"

	-- Our static lib should not link against GLFW
	filter "kind:not StaticLib"
		links "glfw3"
	filter {}
end

function includeVulkan()
    includedirs "Libraries/Vulkan/Include"
end

function linkVulkan()
	libdirs "Libraries/Vulkan/Lib"

	-- Our static lib should not link against GLFW
	filter "kind:not StaticLib"
		links "vulkan-1"
	filter {}
end

--positron static lib
project "Positron"
    -- kind is used to indicate the type of this project.
	kind "StaticLib"

    -- We specify where the source files are.
	-- It would be better to separate header files in a folder and sources
	-- in another, but for our simple project we will put everything in the same place.
	-- Note: ** means recurse in subdirectories, so it will get all the files in ExampleLib/
	files "Projects/Positron/**"

    -- include funcs
    includedirs { "Libraries/Vulkan/Include", "Libraries/GLFW/Include" }

function usePositron()
    -- The library's public headers
	includedirs "Projects/Positron/include"

    -- We link against a library that's in the same workspace, so we can just
	-- use the project name - premake is really smart and will handle everything for us.
	links "Positron"

    includedirs { "Libraries/Vulkan/Include", "Libraries/GLFW/Include" }

    linkVulkan()
    linkGLFW()
end

-- The windowed app
project "App"
    kind "ConsoleApp"
	files "Projects/App/**"
    
    -- We also need the headers
	includedirs "Projects/Positron/include"

    usePositron()