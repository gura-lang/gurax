//==============================================================================
// module-glu.cpp
//==============================================================================
#include "stdafx.h"

#define AssignConst(name) frame.Assign(#name, new Value_Number(name))

Gurax_BeginModule(glu)

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
	// Assignment of VType
	Assign(VTYPE_GLUnurbs);
	Assign(VTYPE_GLUquadric);
	Assign(VTYPE_GLUtesselator);
	// Assignment of constant
	AssignConsts(frame);
	// Assignment of function
	AssignFunctions(frame);
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(glu)
