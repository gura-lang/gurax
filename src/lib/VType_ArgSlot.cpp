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

${help.ComposePropertyHelp(ArgSlot, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ArgSlot, `en)}

${help.ComposeMethodHelp(ArgSlot, `en)}
)**";

//------------------------------------------------------------------------------
// VType_ArgSlot
//------------------------------------------------------------------------------
VType_ArgSlot VTYPE_ArgSlot("ArgSlot");

void VType_ArgSlot::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
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
