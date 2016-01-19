require('premake_options')
local utils = require('utils')

pathPrefix = "../Tests"
if _OPTIONS["path_prefix"] then
	pathPrefix = _OPTIONS["path_prefix"]
end

projectName = "Dummy"
if _OPTIONS["project_name"] then
	projectName = _OPTIONS["project_name"]
end

testType = "all"
if _OPTIONS["tests"] then
	testType = _OPTIONS["tests"]
end

solution (projectName)
	outputDirectory = pathPrefix.."/Projects"
	location (outputDirectory)
	language "C++"
	objdir (pathPrefix.."/../Obj/")
	configurations {"Release", "Debug"}
	pchheader "stdafx.h"
	
	configuration { "Debug" } -- Will select Win32 | Debug in our case
		defines { "_DEBUG", "SPASSERT_DEBUG_MODE" }
		flags { "Symbols" } -- Debug symbols
		targetsuffix '_d' 
		targetdir (pathPrefix.."/../Debug")
		libdirs {pathPrefix.."/../Debug"}
		
	configuration { "Release*" } -- Selects both Release
		defines { "NDEBUG" }
		flags { "Optimize" } -- Optimization switches on
		targetdir (pathPrefix.."/../bin")
		libdirs {pathPrefix.."/../bin"}
	--configuration { "Native" } -- On Win32
		--defines{ "WIN32" } -- Define WIN32

	vpaths 
	{
		["Interfaces"] = {pathPrefix.."/**.hxx"},
		["Headers"] = {pathPrefix.."/**.h"},
		["Sources"] = {pathPrefix.."/**.c", pathPrefix.."/**.cpp"}
	}

	project (projectName)
		kind "ConsoleApp"
		location = outputDirectory
		inputPath = pathPrefix.."/src"
		utils.addfiles(inputPath) 
		includedirs
		{
			"../extern/Include/VisualLeakDetector",
			"../extern/Include"
		}
		libdirs 
		{
			"../extern/Lib/VisualLeakDetector/Win32",
			--"../extern/Lib/gTest",
			"../extern/Lib/gMock"
		}
		pchsource (inputPath.."/stdafx.cpp")
		configuration ("Debug")
			debugdir (pathPrefix.."/../Debug")
			--links { "gtestd" }
			links { "gmockd" }
		configuration ("Release")
			debugdir (pathPrefix.."/../bin")
			--links { "gtest"}
			links { "gmock" }
		
		if testType == "base" then
			configuration ("Debug")
				links { "Base_D" }
			configuration ("Release")
				links { "Base" }
			configuration {}
				includedirs
				{
					"../Source/Base/Includes",
				}
			require('base').run("..", outputDirectory)
		end

		if testType == "utilities" then
			configuration {}
			links { "Utilities" }
			includedirs
			{
				"../Source/Utilities/Includes",
				"../Source/Base/Includes",
			}
			require('utilities').run("..", outputDirectory)
		end
		
		if testType == "ai" then
			configuration ("Debug")
				links { "Base_D", "AI_D" }
			configuration ("Release")
				links { "Base", "AI" }
			configuration {}
			
			includedirs
			{
				"../Source/AI/Includes",
				"../Source/Base/Includes",
			}
			require('ai').run("..", outputDirectory)
		end
	
		if testType == "graphics" then
			configuration {}
			links { "Graphics" }
			includedirs
			{
				"../Source/GraphicsEngine/Includes",
			}
			require('graphics').run("..", outputDirectory)
		end
		
		if testType == "physics" then
			configuration {}
			links { "Physics" }
			includedirs
			{
				"../Source/Physics/Includes",
			}
			require('physics').run("..", outputDirectory)
		end
		
		if testType == "sound" then
			configuration {}
			links { "Sound" }
			includedirs
			{
				"../Source/Sound/Includes",
			}
			require('sound').run("..", outputDirectory)
		end
		
		if testType == "gamebase" then
			configuration {}
			links { "Gamebase" }
			includedirs
			{
				"../Source/Gamebase/Includes",
			}
			require('gamebase').run("..", outputDirectory)
		end
		
