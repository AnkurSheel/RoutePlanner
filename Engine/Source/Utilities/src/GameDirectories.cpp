//  *******************************************************************************************************************
//  GameDirectories   version:  1.0   Ankur Sheel  date: 2013/01/22
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "GameDirectories.h"
#include "ParamLoaders.hxx"
#include "XMLFileIO.hxx"
#include "ResCache.hxx"
#include "ResourceManager.hxx"

using namespace Utilities;
using namespace Base;

cString cGameDirectories::MediaDirectory;
cString cGameDirectories::FontDirectory;
cString cGameDirectories::ShaderDirectory;
cString cGameDirectories::SpriteDirectory;
cString cGameDirectories::SoundSFXDirectory;
cString cGameDirectories::SoundMusicDirectory;
cString cGameDirectories::ModelDirectory;
cString cGameDirectories::DesignDirectory;
cString cGameDirectories::UiDirectory;

//  *******************************************************************************************************************
cGameDirectories::cGameDirectories()
{
}

//  *******************************************************************************************************************
cGameDirectories::~cGameDirectories()
{
}

//  *******************************************************************************************************************
void cGameDirectories::Initialize(const Base::cString & AssetsPath)
{
	IXMLFileIO * pFile = IXMLFileIO::CreateXMLFile();

	IResource * pResource = IResource::CreateResource("directories.xml");
	shared_ptr<IResHandle> directoriesXML = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	
	if(directoriesXML != NULL)
	{
		pFile->VParse(directoriesXML->GetBuffer(), directoriesXML->GetSize());
		MediaDirectory = AssetsPath;
		FontDirectory = pFile->VGetNodeValue("FontDirectory");
		ShaderDirectory = pFile->VGetNodeValue("ShaderDirectory");
		SpriteDirectory = pFile->VGetNodeValue("SpriteDirectory");
		cString SoundDirectory = pFile->VGetNodeValue("SoundDirectory");
		SoundSFXDirectory = SoundDirectory + pFile->VGetNodeAttribute("SoundDirectory", "SFX");
		SoundMusicDirectory = SoundDirectory + pFile->VGetNodeAttribute("SoundDirectory", "Music");
		ModelDirectory = pFile->VGetNodeValue("ModelDirectory");
		DesignDirectory = pFile->VGetNodeValue("DesignDirectory");
		UiDirectory = pFile->VGetNodeValue("UiDirectory");
	}
	SafeDelete(&pResource);
	SafeDelete(&pFile);
}