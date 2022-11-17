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

${help.ComposePropertyHelp(mtp.StatEx, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(mtp.StatEx, `en)}

${help.ComposeMethodHelp(mtp.StatEx, `en)}
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
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
