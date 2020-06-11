//==============================================================================
// VType_ArgSlot.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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

//------------------------------------------------------------------------------
// VType_ArgSlot
//------------------------------------------------------------------------------
VType_ArgSlot VTYPE_ArgSlot("ArgSlot");

void VType_ArgSlot::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaretion of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_ArgSlot
//------------------------------------------------------------------------------
VType& Value_ArgSlot::vtype = VTYPE_ArgSlot;

String Value_ArgSlot::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetArgSlot().ToString(ss));
}

}
