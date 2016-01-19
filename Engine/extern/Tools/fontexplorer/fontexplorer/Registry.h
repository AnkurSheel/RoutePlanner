/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  3-Jun-99 | Created
*  3-Jun-99 | REG #002: DWordArray values overloaded on UINT for IDS_name
* 24-Mar-04 | REG #005: Added support to get key path
* 24-Mar-04 | REG #005: Added font support
* 26-Mar-04 | REG #006: Upgraded to new versions of EnumRegistryKeys,
*  3-May-04 | REG #009: Added Window Placement calls
*  3-May-04 | REG #010: Added FindKey and CreateKey routines
*  3-May-04 | REG #011: Allow programs to obtain the base keypath
*  3-May-04 | REG #012: Use RegOpenKeyEx, added rights to various calls
*           | EnumRegistryValues, Set/SetRegistryDWordArray
* 28-Mar-05 | REG #013: SetLastError(ERROR_SUCCESS) when TRUE is ambiguous
*****************************************************************************/
// Copyright © 2005, Joseph M. Newcomer, All Rights Reserved
// You must record any changes you make to this source by putting // and your
// initials at the end of each line you change. You may not remove any lines
// from this source; instead, put // in front of them and your initials at the end.
// You may not charge any fee for the redistribution, nor incorporate this code in
// any commercial product. This is freeware, and must remain so.
//
BOOL GetRegistryString(HKEY root, const CString &var, CString &val);
BOOL SetRegistryString(HKEY root, const CString &var, const CString &val);

BOOL GetRegistryString(HKEY root, const CString &path, const CString &var, CString &val);
BOOL SetRegistryString(HKEY root, const CString &path, const CString &var, const CString &val);
BOOL GetRegistryString(HKEY root, const CString &path, UINT var, CString &val);
BOOL SetRegistryString(HKEY root, const CString &path, UINT var, const CString &val);

         BOOL SetRegistryInt(HKEY root, const CString &var, DWORD val);
__inline BOOL SetRegistryInt(HKEY root, const CString &var, int val) {return SetRegistryInt(root, var, (DWORD)val); }

         BOOL GetRegistryInt(HKEY root, const CString &var, DWORD & val);
__inline BOOL GetRegistryInt(HKEY root, const CString &var, int & val) { return GetRegistryInt(root, var, (DWORD &) val); }

         BOOL GetRegistryInt(HKEY root, const CString &path, const CString &var, DWORD & val);
__inline BOOL GetRegistryInt(HKEY root, const CString &path, const CString &var, int & val) { return GetRegistryInt(root, path, var, (DWORD &)val); }

         BOOL SetRegistryInt(HKEY root, const CString &path, const CString &var, DWORD val);

         BOOL GetRegistryInt(HKEY root, const CString &path, UINT var, DWORD &val);

         BOOL SetRegistryInt(HKEY root, const CString &path, UINT var, DWORD val);
__inline BOOL SetRegistryInt(HKEY root, const CString &path, UINT var, int val) { return SetRegistryInt(root, path, var, (DWORD)val); }

BOOL GetRegistryGUID(HKEY root, const CString &var, GUID &val);
BOOL SetRegistryGUID(HKEY root, const CString &var, const GUID &val);

BOOL DeleteRegistryValue(HKEY root, const CString & var);
BOOL DeleteRegistryValue(HKEY root, const CString & path, const CString & name); // REG #018
BOOL DeleteRegistryKey(HKEY root, const CString & keyname);

BOOL GetRegistryKey(HKEY root, const CString & name, HKEY & key, DWORD access = KEY_ALL_ACCESS);// REG #012
BOOL FindRegistryKey(HKEY root, const CString & keyname, HKEY & key, DWORD access = KEY_ALL_ACCESS);// REG #012

BOOL EnumRegistryKeys(HKEY root, const CString & group, CStringArray & keys);// REG #006
BOOL EnumRegistryKeys(HKEY root, UINT group, CStringArray & keys); // REG #006

BOOL EnumRegistryValues(HKEY root, const CString & group, CStringArray & keys);// REG #006

BOOL SetRegistryValues(HKEY root, const CString & group, const CStringArray & values);
BOOL SetRegistryValues(HKEY root, UINT group, const CStringArray & values);
BOOL SetRegistryValues(HKEY root, const CString & group, const CDWordArray & values);
BOOL SetRegistryValues(HKEY root, UINT group, const CDWordArray & values);

BOOL GetRegistryValues(HKEY root, const CString & group, CStringArray & values);
BOOL GetRegistryValues(HKEY root, UINT group, CStringArray & values);
BOOL GetRegistryValues(HKEY root, const CString & group, CDWordArray & values);
BOOL GetRegistryValues(HKEY root, UINT group, CDWordArray & values);

BOOL GetRegistryDWordArray(HKEY root, const CString &var, CDWordArray & data);       // REG #002
BOOL GetRegistryDWordArray(HKEY root, UINT id,            CDWordArray & data);       // REG #002
BOOL SetRegistryDWordArray(HKEY root, const CString & var, const CDWordArray & data);// REG #002
BOOL SetRegistryDWordArray(HKEY root, UINT var,            const CDWordArray & data);// REG #002

BOOL CreateKey(HKEY root, const CString & key, DWORD access = KEY_ALL_ACCESS); // REG #010
HKEY OpenKey(HKEY root, const CString & path, DWORD access = KEY_ALL_ACCESS);  // REG #010

CString GetKeyPath(const CString & key);                                // REG #011
CString GetKeyPath(UINT key);                                           // REG #011

BOOL GetRegistryFont(HKEY root, const CString & var, LPLOGFONT f);      // REG #005
BOOL SetRegistryFont(HKEY root, const CString & var, const LOGFONT * f);// REG #005

BOOL GetRegistryWindowPlacement(HKEY root, const CString & var, WINDOWPLACEMENT & wp);      // REG #009
BOOL SetRegistryWindowPlacement(HKEY root, const CString & var, const WINDOWPLACEMENT & wp);// REG #009

         BOOL GetRegistryInt64(HKEY root, const CString & var,          __int64 & val); // REG #013
__inline BOOL GetRegistryInt64(HKEY root, const CString & var, unsigned __int64 & val) { return GetRegistryInt64(root, var, (__int64 &)val); } // REG #013

         BOOL SetRegistryInt64(HKEY root, const CString & var,          __int64 val);   // REG #013
__inline BOOL SetRegistryInt64(HKEY root, const CString & var, unsigned __int64 val) { return SetRegistryInt64(root, var, (__int64)val); }   // REG #013
