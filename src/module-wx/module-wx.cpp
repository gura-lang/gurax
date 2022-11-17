//==============================================================================
// module-wx.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(wx)

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	Frame& frame = GetFrame();
	AssignConsts(frame);
	AssignEvents(frame);
	AssignFunctions(frame);
	AssignOperators(frame);
	AssignMultiEvents(frame);
	AssignVTypes(frame);
	AssignObjects(frame);
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(wx)

#if defined(__WXMSW__)
WXDLLIMPEXP_BASE void wxSetInstance(HINSTANCE hInst);

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved)
{
	// This is necessary to load resources correctly.
	::wxSetInstance(hInst);
	return TRUE;
}
#endif
