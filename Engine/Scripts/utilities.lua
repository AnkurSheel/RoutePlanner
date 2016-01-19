local utils = require('utils')

return {
	run = function(enginePath, outputDirectory)
		project "Utilities"
		kind "SharedLib"
		location = outputDirectory
		inputPath = enginePath.."/Source/Utilities"
		utils.addfiles(inputPath)
		includedirs
		{
			enginePath.."/Source/Utilities/Includes",
			enginePath.."/Source/Base/Includes",
			enginePath.."/extern/Include/VisualLeakDetector",
			enginePath.."/extern/Include/zlib",
			enginePath.."/extern/Include/TinyXml"
		}
		libdirs
		{
			enginePath.."/extern/Lib/Zlib",
			enginePath.."/extern/Lib/VisualLeakDetector/Win32"
		}
		if _ACTION == "vs2010" then
			libdirs 
			{
				enginePath.."/extern/Lib/TinyXml/VS2010"
			}
		end
		pchsource (enginePath.."/Source/Utilities/src/stdafx.cpp")
		defines {"UTILITIES_EXPORTS"}
		links { "zlibwapi" , "Winmm"}
		configuration ("Debug")
			links { "Base_d", "tinyxml2d" }
		configuration ("Release")
			links { "Base", "tinyxml2" }
	end
}
