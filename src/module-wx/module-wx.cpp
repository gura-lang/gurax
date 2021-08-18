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
	AssignMultiEvents(frame);
	AssignVTypes(frame);
	do { // Predefined Objects of wxColour
		//frame.Assign("NullColour", new Value_Color(wxNullColour));
		/*
		Gura_AssignWxObjectEx(NullColour,		Colour, &wxNullColour);
		Gura_AssignWxObject(BLACK,				Colour);
		Gura_AssignWxObject(WHITE,				Colour);
		Gura_AssignWxObject(RED,				Colour);
		Gura_AssignWxObject(BLUE,				Colour);
		Gura_AssignWxObject(GREEN,				Colour);
		Gura_AssignWxObject(CYAN,				Colour);
		Gura_AssignWxObject(LIGHT_GREY,			Colour);
		*/
	} while (0);
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
