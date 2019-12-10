//==============================================================================
// VType_DirRecord.cpp
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
// VType_DirRecord
//------------------------------------------------------------------------------
VType_DirRecord VTYPE_DirRecord("DirRecord");

void VType_DirRecord::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_DirRecord
//------------------------------------------------------------------------------
VType& Value_DirRecord::vtype = VTYPE_DirRecord;

}
