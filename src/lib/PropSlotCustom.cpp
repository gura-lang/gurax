//==============================================================================
// PropSlotCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PropSlotCustom_Instance
//------------------------------------------------------------------------------
Value* PropSlotCustom_Instance::DoGetValue(Value& valueTarget, const Attribute& attr) const
{
	//ValueCustom& valueTargetEx = dynamic_cast<ValueCustom&>(valueTarget);
	//return valueTargetEx.GetCustomProp(_iProp);
	return valueTarget.GetCustomProp(_iProp);
}

void PropSlotCustom_Instance::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const
{
	//ValueCustom& valueTargetEx = dynamic_cast<ValueCustom&>(valueTarget);
	//valueTargetEx.SetCustomProp(_iProp, value.Reference());
	valueTarget.SetCustomProp(_iProp, value.Reference());
}

//------------------------------------------------------------------------------
// PropSlotCustom_Class
//------------------------------------------------------------------------------
Value* PropSlotCustom_Class::DoGetValue(Value& valueTarget, const Attribute& attr) const
{
	if (valueTarget.IsType(VTYPE_VType)) {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(dynamic_cast<Value_VType&>(valueTarget).GetVTypeThis());
		return vtype.GetCustomPropOfClass(_iProp);
	} else {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(valueTarget.GetVTypeCustom());
		return vtype.GetCustomPropOfClass(_iProp);
	}
}

void PropSlotCustom_Class::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const
{
	if (valueTarget.IsType(VTYPE_VType)) {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(dynamic_cast<Value_VType&>(valueTarget).GetVTypeThis());
		vtype.SetCustomPropOfClass(_iProp, value.Reference());
	} else {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(valueTarget.GetVTypeCustom());
		vtype.SetCustomPropOfClass(_iProp, value.Reference());
	}
}

}
