local function addfiles(inputpath)
  files
	{ 
		inputPath.."**.h", 
		inputPath.."**.hxx", 
		inputPath.."**.hpp", 
		inputPath.."**.cpp", 
	}
end

local f
local function CreateDirs(filePath, newPathPrefix)
	local pathName = path.rebase(filePath, os.getcwd(), "../");
	os.mkdir(newPathPrefix..pathName)
	--f:write("Dir : "..filePath.." : "..pathName.."\n")
end

local function CopyFiles(filePath, newPathPrefix)
	local pathName = path.rebase(filePath, os.getcwd(), "../");
	os.copyfile(filePath, newPathPrefix..pathName)
	--f:write("File : "..filePath.." : "..pathName.."\n")
end

local function CreateProjectForGithub(dirPath)

	for _, fname in ipairs(os.matchdirs(dirPath.."/**")) do
		os.rmdir(fname)
	end
	os.mkdir(dirPath)
	--f = io.open("fileList.txt", "w")
	for _, fname in ipairs(os.matchdirs("../**")) do
		if string.match(fname, "Engine") ~= nil then
			if string.match(fname, "Engine/Doc") ~= nil then
				if string.match(fname, "PublicDoc") ~= nil then
					CreateDirs(fname, dirPath.."/")
				end
			elseif string.match(fname, "Engine/Source/") ~= nil then
				if string.match(fname, "Includes") ~= nil then
					CreateDirs(fname, dirPath.."/")
				end
			elseif string.match(fname, "Engine/extern/") ~= nil then
				if string.match(fname, "VisualLeakDetector") ~= nil or string.match(fname, "Tools") ~= nil 
				or string.match(fname, "Scripts") ~= nil then
					CreateDirs(fname, dirPath.."/")
				end
			elseif string.match(fname, "Engine/Tests") ~= nil then
				if string.match(fname, "/Obj") == nil and string.match(fname, "Projects") == nil then
					CreateDirs(fname, dirPath.."/")
				end
			else
				CreateDirs(fname, dirPath.."/")
			end
		elseif string.match(fname, "/Obj") == nil and string.match(fname, "Projects") == nil then
			CreateDirs(fname, dirPath.."/")
		end
	end

	for _, fname in ipairs(os.matchfiles("../**")) do
		if string.match(fname, "Debug") ~= nil or string.match(fname, "bin") ~= nil then
			if string.match(fname, "lib") ~= nil or string.match(fname, "dll") ~= nil 
			or string.match(fname, "ini") ~= nil or string.match(fname, "xsl") ~= nil 
			or string.match(fname, "html") ~= nil or string.match(fname, "manifest") ~= nil then
				CopyFiles(fname, dirPath.."/")
			end
		elseif string.match(fname, "Engine") ~= nil then
			if string.match(fname, "Debug") == nil or string.match(fname, "bin") == nil then
				CopyFiles(fname, dirPath.."/")
			end
		else
		-- if string.match(fname, "Source") ~= nil then
			CopyFiles(fname, dirPath.."/")

		end
	end
	
	-- for _, fname in ipairs(os.matchfiles("../bin/**")) do
		-- if string.match(fname, "lib") ~= nil or string.match(fname, "dll") ~= nil 
		-- or string.match(fname, "ini") ~= nil or string.match(fname, "xsl") ~= nil 
		-- or string.match(fname, "html") ~= nil then
			-- CopyFiles(fname, dirPath.."/")
		-- end
	-- end
	
	-- for _, fname in ipairs(os.matchfiles("../Debug/**")) do
		-- if string.match(fname, "lib") ~= nil or string.match(fname, "dll") ~= nil 
		-- or string.match(fname, "ini") ~= nil or string.match(fname, "manifest") ~= nil 
		-- or string.match(fname, "xsl") ~= nil or string.match(fname, "html") ~= nil then
			-- CopyFiles(fname, dirPath.."/")
		-- end
	-- end
	--f:close()
end

return {
  addfiles = addfiles,
  CreateProjectForGithub = CreateProjectForGithub
}