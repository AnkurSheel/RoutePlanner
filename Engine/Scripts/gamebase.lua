local utils = require('utils')

return {
	run = function(enginePath, outputDirectory)
		project "Gamebase"
		kind "SharedLib"
		location = outputDirectory
		inputPath = enginePath.."/Source/GameBase"
		utils.addfiles(inputPath) 
		includedirs
		{
			enginePath.."/Source/GameBase/Includes",
			enginePath.."/Source/Base/Includes",
			enginePath.."/Source/Utilities/Includes",
			enginePath.."/Source/AI/Includes",
			enginePath.."/Source/GraphicsEngine/Includes",
			enginePath.."/Source/Physics/Includes",
			enginePath.."/Source/Sound/Includes",
			enginePath.."/extern/Include/VisualLeakDetector"
		}
		libdirs 
		{
			enginePath.."/extern/Lib/VisualLeakDetector/Win32"
		}		
		pchsource (enginePath.."/Source/GameBase/src/stdafx.cpp")
		defines {"GAMEBASE_EXPORTS" }
		configuration ("Debug")
			links { "Base_d", "Utilities_d", "AI_d", "Graphics_d", "Physics_d", "Sound_d" }
		configuration ("Release")
			links { "Base", "Utilities", "AI", "Graphics", "Physics", "Sound" }
	end
}
