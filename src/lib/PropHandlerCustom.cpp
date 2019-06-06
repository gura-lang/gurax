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
	ValueCustom& valueTargetEx = dynamic_cast<ValueCustom&>(valueTarget);
	return valueTargetEx.GetCustomProp(_iProp);
}

void PropHandlerCustom::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const
{
	ValueCustom& valueTargetEx = dynamic_cast<ValueCustom&>(valueTarget);
	valueTargetEx.SetCustomProp(_iProp, value.Reference());
}

}
