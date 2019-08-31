//==============================================================================
// VType_Codec.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Codec
//------------------------------------------------------------------------------
VType_Codec VTYPE_Codec("Codec");

void VType_Codec::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of class method
	//Assign(Gurax_CreateClassMethod(Codec, Basic));
	//Assign(Gurax_CreateClassMethod(Codec, WebSafe));
	//Assign(Gurax_CreateClassMethod(Codec, Win256));
}

//------------------------------------------------------------------------------
// Value_Codec
//------------------------------------------------------------------------------
VType& Value_Codec::vtype = VTYPE_Codec;

}
