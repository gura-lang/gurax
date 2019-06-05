//==============================================================================
// VTypeCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VTypeCustom
//------------------------------------------------------------------------------
//VType_Any VTYPE_Any("Any");

#if 0
void VType_Any::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VType::Empty, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Any, ToString));
}

Value* VType_Any::DoCastFrom(const Value& value) const
{
	return value.Reference();
}
#endif

//------------------------------------------------------------------------------
// ValueCustom
//------------------------------------------------------------------------------

}
