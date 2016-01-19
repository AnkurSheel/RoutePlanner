// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// TODO: reference additional headers your program requires here
#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif

//#define  DIRECTINPUT_VERSION 0x800
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <xnamath.h>
#include <DxErr.h>
#include <D3DCompiler.h>
#include "Logger.hxx"
#include "Includes.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Color.h"

inline void SetDebugObjectName(ID3D11DeviceChild* resource, const Base::cString & name)
{
#if defined(_DEBUG) || defined(PROFILE)
	resource->SetPrivateData(WKPDID_D3DDebugObjectName, name.GetLength(), name.GetData());
#endif
}
