//==============================================================================
// PropHandlerCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PropHandlerCustom_Instance
//------------------------------------------------------------------------------
Value* PropHandlerCustom_Instance::DoGetValue(Value& valueTarget, const Attribute& attr) const
{
	ValueCustom& valueTargetEx = dynamic_cast<ValueCustom&>(valueTarget);
	return valueTargetEx.GetCustomProp(_iProp);
}

void PropHandlerCustom_Instance::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const
{
	ValueCustom& valueTargetEx = dynamic_cast<ValueCustom&>(valueTarget);
	valueTargetEx.SetCustomProp(_iProp, value.Reference());
}

//------------------------------------------------------------------------------
// PropHandlerCustom_Class
//------------------------------------------------------------------------------
Value* PropHandlerCustom_Class::DoGetValue(Value& valueTarget, const Attribute& attr) const
{
	ValueCustom& valueTargetEx = dynamic_cast<ValueCustom&>(valueTarget);
	return valueTargetEx.GetCustomProp(_iProp);
}

void PropHandlerCustom_Class::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const
{
	ValueCustom& valueTargetEx = dynamic_cast<ValueCustom&>(valueTarget);
	valueTargetEx.SetCustomProp(_iProp, value.Reference());
}

}
