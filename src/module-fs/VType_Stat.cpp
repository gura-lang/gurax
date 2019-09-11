//==============================================================================
// VType_Stat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(fs)

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Stat
//------------------------------------------------------------------------------
VType_Stat VTYPE_Stat("Stat");

void VType_Stat::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of class method
	//Assign(Gurax_CreateClassMethod(Stat, Basic));
	//Assign(Gurax_CreateClassMethod(Stat, WebSafe));
	//Assign(Gurax_CreateClassMethod(Stat, Win256));
}

//------------------------------------------------------------------------------
// Value_Stat
//------------------------------------------------------------------------------
VType& Value_Stat::vtype = VTYPE_Stat;

Gurax_EndModuleScope(fs)
