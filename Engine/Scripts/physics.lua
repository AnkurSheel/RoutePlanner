local utils = require('utils')

return {
	run = function(enginePath, outputDirectory)
		project "Physics"
		kind "SharedLib"
		location = outputDirectory
		inputPath = enginePath.."/Source/Physics"
		utils.addfiles(inputPath) 
		includedirs
		{
			enginePath.."/Source/Physics/Includes",
			enginePath.."/Source/Base/Includes",
			enginePath.."/Source/Utilities/Includes",
			enginePath.."/extern/Include/VisualLeakDetector"
		}
		libdirs 
		{
			enginePath.."/extern/Lib/VisualLeakDetector/Win32"
		}
		pchsource (enginePath.."/Source/Physics/src/stdafx.cpp")
		defines {"PHYSICS_EXPORTS"}
		configuration ("Debug")
			links { "Base_d", "Utilities_d" }
		configuration ("Release")
			links { "Base", "Utilities" }
	end
}
