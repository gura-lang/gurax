//==============================================================================
// VType_VType.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_VType
//------------------------------------------------------------------------------
VType_VType VTYPE_VType("VType");

void VType_VType::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_VType
//------------------------------------------------------------------------------
String Value_VType::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetVTypeThis().MakeFullName();
	str += ">";
	return str;
}

String Value_VType::ToStringDetail(const StringStyle& ss) const
{
	return GetVTypeThis().MakeFullName();
}

Value* Value_VType::DoPropGet(const Symbol* pSymbol, const Attribute& attr)
{
	const PropHandler* pPropHandler = GetVTypeThis().LookupPropHandlerOfClass(pSymbol);
	if (!pPropHandler) {
		return GetVTypeThis().GetFrame().Lookup(pSymbol);
	} else if (pPropHandler->IsReadable()) {
		return pPropHandler->DoGetValue(*this, attr);
	} else {
		return nullptr;
	}
}

bool Value_VType::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	const PropHandler* pPropHandler = GetVTypeThis().LookupPropHandler(pSymbol);
	if (!pPropHandler) {
		GetVTypeThis().GetFrame().Assign(pSymbol, pValue.release());
		return true;
	} else if (pPropHandler->IsWritable()) {
		RefPtr<Value> pValueCasted(pPropHandler->GetVType().Cast(*pValue, pPropHandler->GetListVarFlag()));
		if (!pValueCasted) return false;
		pPropHandler->DoSetValue(*this, *pValueCasted, attr);
		return true;
	} else {
		return false;
	}
}

}
