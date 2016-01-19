local utils = require('utils')

return {
	run = function(enginePath, outputDirectory)
		project "AI"
		kind "SharedLib"
		location = outputDirectory
		inputPath = enginePath.."/Source/AI/"
		utils.addfiles(inputPath)
		includedirs
		{
			enginePath.."/Source/AI/Includes",
			enginePath.."/Source/Base/Includes",
			enginePath.."/Source/Utilities/Includes/",
			enginePath.."/extern/Include/VisualLeakDetector"
		}
		libdirs 
		{
			enginePath.."/extern/Lib/VisualLeakDetector/Win32"
		}
		pchsource (enginePath.."/Source/AI/src/stdafx.cpp")
		defines {"AI_EXPORTS"}
		configuration ("Debug")
			links { "Base_d", "Utilities_D"}
		configuration ("Release")
			links { "Base", "Utilities" }
	end
}

