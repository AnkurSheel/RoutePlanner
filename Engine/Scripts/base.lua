local utils = require('utils')

return {
	run = function(enginePath, outputDirectory)
		project "Base"
		kind "SharedLib"
		location = outputDirectory
		inputPath = enginePath.."/Source/Base"
		utils.addfiles(inputPath) 
		includedirs
		{
			enginePath.."/Source/Base/Includes",
			enginePath.."/extern/Include/VisualLeakDetector"
		}	
		libdirs 
		{
			enginePath.."/extern/Lib/VisualLeakDetector/Win32"
		}
		pchsource (enginePath.."/Source/Base/src/stdafx.cpp")
		defines {"BASE_EXPORTS"}
	end
}
