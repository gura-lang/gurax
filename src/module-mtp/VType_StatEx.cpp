//==============================================================================
// VType_StatEx.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_StatEx
//------------------------------------------------------------------------------
VType_StatEx VTYPE_StatEx("StatEx");

void VType_StatEx::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Stat, Flag::Immutable);
	// Assignment of method
	// Assignment of property
}

//------------------------------------------------------------------------------
// Value_StatEx
//------------------------------------------------------------------------------
VType& Value_StatEx::vtype = VTYPE_StatEx;

Gurax_EndModuleScope(mtp)
