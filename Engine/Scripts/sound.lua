local utils = require('utils')

return {
	run = function(enginePath, outputDirectory)
		project "Sound"
		kind "SharedLib"
		location = outputDirectory
		inputPath = enginePath.."/Source/Sound"
		utils.addfiles(inputPath) 
		includedirs
		{
			enginePath.."/Source/Base/Includes",
			enginePath.."/Source/Utilities/Includes",
			enginePath.."/Source/Sound/Includes",
			enginePath.."/extern/Include/ogg",
			enginePath.."/extern/Include/VisualLeakDetector",
			enginePath.."/extern/Include/DirectX"
		}
		libdirs 
		{
			enginePath.."/extern/Lib/VisualLeakDetector/Win32",
			enginePath.."/extern/Lib/DirectX/x86"
		}
		if _ACTION == "vs2010" then
			libdirs 
			{
				enginePath.."/extern/Lib/Ogg/VS2010"
			}
		end
		pchsource (enginePath.."/Source/Sound/src/stdafx.cpp")
		defines {"SOUND_EXPORTS"}
		links {"libogg_static", "libvorbis_static", "libvorbisfile_static"}
		configuration ("Debug")
			links { "Base_d", "Utilities_d" }
		configuration ("Release")
			links { "Base", "Utilities" }
	end
}
