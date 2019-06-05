//==============================================================================
// PropHandlerCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PropHandlerCustom
//------------------------------------------------------------------------------
Value* PropHandlerCustom::DoGetValue(Value& valueTarget, const Attribute& attr) const
{
	return Value::nil();
}

void PropHandlerCustom::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const
{
}

}
