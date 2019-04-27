//==============================================================================
// VType_Module.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Module
//------------------------------------------------------------------------------
VType_Module VTYPE_Module("Module");

void VType_Module::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_Module
//------------------------------------------------------------------------------
String Value_Module::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%s>", GetModule().GetDottedSymbol().ToString().c_str());
	return str;
}

String Value_Module::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

Value* Value_Module::DoPropGet(const Symbol* pSymbol, const Attribute& attr)
{
	const PropHandler* pPropHandler = GetModule().LookupPropHandler(pSymbol);
	if (!pPropHandler) {
		return GetModule().GetFrame().Lookup(pSymbol);
	} else if (pPropHandler->IsReadable()) {
		return pPropHandler->DoGetValue(*this, attr);
	} else {
		return nullptr;
	}
}

bool Value_Module::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	const PropHandler* pPropHandler = GetModule().LookupPropHandler(pSymbol);
	if (!pPropHandler) {
		GetModule().GetFrame().Assign(pSymbol, pValue.release());
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
