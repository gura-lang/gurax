//==============================================================================
// VType_Attribute.cpp
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
// VType_Attribute
//------------------------------------------------------------------------------
VType_Attribute VTYPE_Attribute("Attribute");

void VType_Attribute::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaretion of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Attribute
//------------------------------------------------------------------------------
VType& Value_Attribute::vtype = VTYPE_Attribute;

String Value_Attribute::ToString(const StringStyle& ss) const
{
	return String().Format("<Attribute:%s>", GetAttr().ToString(ss).c_str());
}

}
