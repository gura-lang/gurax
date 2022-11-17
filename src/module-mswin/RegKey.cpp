//==============================================================================
// RegKey.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mswin)

//------------------------------------------------------------------------------
// RegKey
//------------------------------------------------------------------------------
RegKey::RegKey(HKEY hKey, String name, bool ownerFlag) : _hKey(hKey), _name(name), _ownerFlag(ownerFlag)
{
}

RegKey::~RegKey()
{
	if (_ownerFlag) ::RegCloseKey(_hKey);
}

String RegKey::ToString(const StringStyle& ss) const
{
	return String().Format("mswin.RegKey:'%s'", GetName());
}

Gurax_EndModuleScope(mswin)
