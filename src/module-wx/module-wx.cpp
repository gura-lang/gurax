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
	AssignConsts(GetFrame());
	AssignEvents(GetFrame());
	AssignFunctions(GetFrame());
	//AssignVTypes(GetFrame());
	Assign(VTYPE_App);
	Assign(VTYPE_AppConsole);
	//Assign(VTYPE_CommandEvent);
	Assign(VTYPE_Control);
	//Assign(VTYPE_Event);
	//Assign(VTYPE_EventType);
	//Assign(VTYPE_EvtHandler);
	Assign(VTYPE_Frame);
	Assign(VTYPE_Menu);
	Assign(VTYPE_MenuBar);
	Assign(VTYPE_MenuItem);
	Assign(VTYPE_Point);
	Assign(VTYPE_Size);
	Assign(VTYPE_StatusBar);
	Assign(VTYPE_Window);
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
