//==============================================================================
// VType_Any.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Any
//------------------------------------------------------------------------------
VType_Any VTYPE_Any("Any");

void VType_Any::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VType::Empty, Flag::Immutable);
	frameOuter.Assign(*this);
}

Value* VType_Any::DoCastFrom(const Value& value) const
{
	return value.Reference();
}

//------------------------------------------------------------------------------
// Value_Any
//------------------------------------------------------------------------------

}
