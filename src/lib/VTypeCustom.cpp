//==============================================================================
// VTypeCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VTypeCustom
//------------------------------------------------------------------------------
VTypeCustom VTYPECustom("Custom");

void VTypeCustom::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Mutable);
}

Value* VTypeCustom::DoCastFrom(const Value& value) const
{
	return value.Reference();
}

//------------------------------------------------------------------------------
// ValueCustom
//------------------------------------------------------------------------------

}
