//==============================================================================
// VType_DirStructure.cpp
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
// VType_DirStructure
//------------------------------------------------------------------------------
VType_DirStructure VTYPE_DirStructure("DirStructure");

void VType_DirStructure::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_DirStructure
//------------------------------------------------------------------------------
VType& Value_DirStructure::vtype = VTYPE_DirStructure;

}
