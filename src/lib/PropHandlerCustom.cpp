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
	if (valueTarget.IsType(VTYPE_VType)) {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(dynamic_cast<Value_VType&>(valueTarget).GetVTypeThis());
		return vtype.GetCustomPropOfClass(_iProp);
	} else {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(valueTarget.GetVType());
		return vtype.GetCustomPropOfClass(_iProp);
	}
}

void PropHandlerCustom_Class::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const
{
	if (valueTarget.IsType(VTYPE_VType)) {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(dynamic_cast<Value_VType&>(valueTarget).GetVTypeThis());
		vtype.SetCustomPropOfClass(_iProp, value.Reference());
	} else {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(valueTarget.GetVType());
		vtype.SetCustomPropOfClass(_iProp, value.Reference());
	}
}

}
