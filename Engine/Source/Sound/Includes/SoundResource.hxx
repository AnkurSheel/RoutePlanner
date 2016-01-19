// *****************************************************************************
//  SoundResource   version:  1.0   Ankur Sheel  date: 2012/12/29
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

#include "Resources.h"
#include "SoundDefines.h"

namespace Sound
{
	/********************************************//**
	 * @brief Encapsulates sound data 
	 *
	 * Use this class to manage sound resources
	 ***********************************************/
	class cSoundResource
		: public Utilities::cResource
	{
	public:
		SOUND_API cSoundResource(const Base::cString & strName);
		~cSoundResource();
		Utilities::IResHandle * VCreateHandle(const char * pBuffer,
			unsigned int uiSize, Utilities::IResCache * pResCache);
	};

	class ISoundResHandle
		: public Utilities::cResHandle
	{
	public:
		ISoundResHandle(Utilities::cResource & resource, unsigned char * pBuffer,
			unsigned int uiSize, Utilities::IResCache * pResCache);
		virtual ~ISoundResHandle(){};
		virtual bool VInitialize() = 0;
		virtual int VGetPCMBufferSize() const = 0;
		virtual char const * VGetPCMBuffer() const = 0;
	};
}