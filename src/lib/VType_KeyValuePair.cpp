//==============================================================================
// VType_KeyValuePair.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(KeyValuePair, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(KeyValuePair, `en)}

${help.ComposeMethodHelp(KeyValuePair, `en)}
)**";

//------------------------------------------------------------------------------
// VType_KeyValuePair
//------------------------------------------------------------------------------
VType_KeyValuePair VTYPE_KeyValuePair("KeyValuePair");

void VType_KeyValuePair::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_KeyValuePair
//------------------------------------------------------------------------------
VType& Value_KeyValuePair::vtype = VTYPE_KeyValuePair;

}
