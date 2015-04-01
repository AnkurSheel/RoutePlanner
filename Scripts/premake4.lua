package.path = "../Engine/Scripts/?.lua;" .. package.path
require('premake_options')
local utils = require('utils')

pathPrefix = "../"
if _OPTIONS["path_prefix"] then
	pathPrefix = _OPTIONS["path_prefix"]
end

if _OPTIONS["no_engine_project"] ~= nil then
	utils.CreateProjectForGithub(pathPrefix)
end

projectName = "Dummy"
if _OPTIONS["project_name"] then
	projectName = _OPTIONS["project_name"]
end
solution (projectName)
	outputDirectory = pathPrefix.."/Projects"
	location (outputDirectory)
	language "C++"
	objdir (pathPrefix.."/Obj/")
	--configurations {"Release", "Debug", "ReleaseCandidate"}
	configurations {"Release", "Debug"}
	pchheader "stdafx.h"
	
	configuration { "Debug" } -- Will select Win32 | Debug in our case
		defines { "_DEBUG", "SPASSERT_DEBUG_MODE" }
		flags { "Symbols" } -- Debug symbols
		targetsuffix '_d' 
		targetdir (pathPrefix.."/Debug")
		libdirs {pathPrefix.."/Debug"}
		
	configuration { "Release*" } -- Selects both Release
		defines { "NDEBUG" }
		flags { "Optimize", "Symbols" } -- Optimization switches on
		targetdir (pathPrefix.."/bin")
		libdirs {pathPrefix.."/bin"}
		
	-- configuration { "ReleaseCandidate" } -- All ReleaseCandidates needs a special define
		-- defines { "RELEASE_CANDIDATE" }

	configuration { "Native" } -- On Win32
		defines{ "WIN32" } -- Define WIN32

	-- fileSet = 
    -- {
	-- "*.cpp",
	-- "*.hpp",
	-- "*.h",
		-- "*.hxx"
    -- }

	vpaths 
	{
		["Interfaces"] = {pathPrefix.."/**.hxx"},
		["Headers"] = {pathPrefix.."/**.h"},
		["Sources"] = {pathPrefix.."/**.c", pathPrefix.."/**.cpp"}
	}

	project (projectName)
		kind "ConsoleApp"
		location = outputDirectory
		inputPath = pathPrefix.."/Source/"..projectName.."/"
		utils.addfiles(inputPath)
		files
		{ 
			pathPrefix.."/Debug/**.ini", 
			pathPrefix.."/bin/**.ini", 
		}
		vpaths 
		{
			["DebugConfig"] = {pathPrefix.."/Debug/**.ini"},
			["RelaseConfig"] = {pathPrefix.."/bin/**.ini"},
		}

		includedirs
		{
			pathPrefix.."/Source/"..projectName.."/Includes",
			pathPrefix.."/Engine/Source/Base/Includes",
			pathPrefix.."/Engine/Source/Utilities/Includes",
			pathPrefix.."/Engine/Source/AI/Includes",
			inputPath.."src",
			pathPrefix.."/Engine/extern/Include/VisualLeakDetector"
		}
		libdirs 
		{
			pathPrefix.."/Engine/extern/Lib/VisualLeakDetector/Win32"
		}
		pchsource (inputPath.."src/stdafx.cpp")
		configuration ("Debug")
			debugdir (pathPrefix.."/Debug")
			links { "AI_d", "Base_d", "Utilities_d" }
		configuration ("Release")
			debugdir (pathPrefix.."/bin")
			links { "AI", "Base", "Utilities" }
		files
		{ 
			pathPrefix.."/Debug/**.ini", 
			pathPrefix.."/bin/**.ini", 
		}
		vpaths 
		{
			["DebugConfig"] = {pathPrefix.."/Debug/**.ini"},
			["RelaseConfig"] = {pathPrefix.."/bin/**.ini"},
		}

		flags{"WinMain"}
		configuration ("Debug")
			debugdir (pathPrefix.."/Debug")
			links { "AI_d", "Base_d", "Utilities_d" }
		configuration ("Release")
			debugdir (pathPrefix.."/bin")
			links { "AI", "Base", "Utilities" }
			


	if _OPTIONS["no_engine_project"] == nil then
		require('ai').run(pathPrefix.."/Engine", outputDirectory)
		require('base').run(pathPrefix.."/Engine", outputDirectory)
		require('utilities').run(pathPrefix.."/Engine", outputDirectory)
	end
	
