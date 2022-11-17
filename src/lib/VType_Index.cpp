//==============================================================================
// VType_Index.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Index, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Index, `en)}

${help.ComposeMethodHelp(Index, `en)}
)**";

//------------------------------------------------------------------------------
// VType_Index
//------------------------------------------------------------------------------
VType_Index VTYPE_Index("Index");

void VType_Index::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Index
//------------------------------------------------------------------------------
VType& Value_Index::vtype = VTYPE_Index;

String Value_Index::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetIndex().ToString(ss));
}

}
