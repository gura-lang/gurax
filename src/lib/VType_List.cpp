//==============================================================================
// VType_List.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_List
//------------------------------------------------------------------------------
VType_List VTYPE_List("List");

void VType_List::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Mutable);
	frame.AssignVType(*this);
}

//------------------------------------------------------------------------------
// Value_List
//------------------------------------------------------------------------------
Value* Value_List::DoIndexGet(const Index& index) const
{
	return Value::nil();
}

void Value_List::DoIndexSet(const Index& index, Value* pValue)
{
}

}
