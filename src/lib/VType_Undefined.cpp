//==============================================================================
// VType_Undefined.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Undefined#ToString()
Gurax_DeclareMethod(Undefined, ToString)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Converts the object to a string.\n");
}

Gurax_ImplementMethod(Undefined, ToString)
{
	// Function body
	return new Value_String("Undefined");
}

//------------------------------------------------------------------------------
// VType_Undefined
//------------------------------------------------------------------------------
VType_Undefined VTYPE_Undefined("Undefined");

void VType_Undefined::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VType::Empty, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Undefined, ToString));
}

//------------------------------------------------------------------------------
// Value_Undefined
//------------------------------------------------------------------------------
VType& Value_Undefined::vtype = VTYPE_Undefined;

}
