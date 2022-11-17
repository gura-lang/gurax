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
	return valueTarget.GetCustomProp(_iProp);
}

void PropSlotCustom_Instance::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const
{
	valueTarget.SetCustomProp(_iProp, value.Reference());
}

//------------------------------------------------------------------------------
// PropSlotCustom_Class
//------------------------------------------------------------------------------
Value* PropSlotCustom_Class::DoGetValue(Value& valueTarget, const Attribute& attr) const
{
	VTypeCustom& vtype = valueTarget.IsType(VTYPE_VType)?
		dynamic_cast<VTypeCustom&>(dynamic_cast<Value_VType&>(valueTarget).GetVTypeThis()) :
		dynamic_cast<VTypeCustom&>(valueTarget.GetVTypeCustom());
	return vtype.GetCustomPropOfClass(_iProp);
#if 0
	if (valueTarget.IsType(VTYPE_VType)) {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(dynamic_cast<Value_VType&>(valueTarget).GetVTypeThis());
		return vtype.GetCustomPropOfClass(_iProp);
	} else {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(valueTarget.GetVTypeCustom());
		return vtype.GetCustomPropOfClass(_iProp);
	}
#endif
}

void PropSlotCustom_Class::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const
{
	VTypeCustom& vtype = valueTarget.IsType(VTYPE_VType)?
		dynamic_cast<VTypeCustom&>(dynamic_cast<Value_VType&>(valueTarget).GetVTypeThis()) :
		dynamic_cast<VTypeCustom&>(valueTarget.GetVTypeCustom());
	vtype.SetCustomPropOfClass(_iProp, value.Reference());
#if 0
	if (valueTarget.IsType(VTYPE_VType)) {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(dynamic_cast<Value_VType&>(valueTarget).GetVTypeThis());
		vtype.SetCustomPropOfClass(_iProp, value.Reference());
	} else {
		VTypeCustom& vtype = dynamic_cast<VTypeCustom&>(valueTarget.GetVTypeCustom());
		vtype.SetCustomPropOfClass(_iProp, value.Reference());
	}
#endif
}

}
