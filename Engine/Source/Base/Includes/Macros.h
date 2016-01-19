//  *******************************************************************************************************************
//  Macros   version:  1.0   Ankur Sheel  date: 2011/04/12
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __MACROS_H__
#define __MACROS_H__

#define OVERRIDE override

#define SP_FILE __FILE__
#define SP_LINE __LINE__
#define SP_FUNCTION_NAME __FUNCTION__

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define BREAK_HERE __asm { int 3 }

#ifdef _DEBUG
#define DEBUG_NEW   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif 

#endif  // __MACROS_H__

