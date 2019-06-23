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
}

//------------------------------------------------------------------------------
// Value_Module
//------------------------------------------------------------------------------
String Value_Module::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%s:%s>",
			   GetModule().GetDottedSymbol().ToString().c_str(),
			   GetModule().GetPathName());
	return str;
}

String Value_Module::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

Value* Value_Module::DoPropGet(const Symbol* pSymbol, const Attribute& attr)
{
	const PropHandler* pPropHandler = GetModule().LookupPropHandler(pSymbol);
	if (pPropHandler) {
		if (!pPropHandler->IsSet(PropHandler::Flag::Readable)) {
			Error::Issue(ErrorType::PropertyError, "property '%s' is not readable", pSymbol->GetName());
			return nullptr;
		}
		return pPropHandler->GetValue(*this, attr);
	}
	Value* pValue = GetModule().GetFrame().Lookup(pSymbol);
	//return pValue? pValue : Value::DoPropGet(pSymbol, attr);
	return pValue;
}

bool Value_Module::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	const PropHandler* pPropHandler = GetModule().LookupPropHandler(pSymbol);
	if (pPropHandler) {
		if (!pPropHandler->IsSet(PropHandler::Flag::Writable)) {
			Error::Issue(ErrorType::PropertyError, "property '%s' is not writable", pSymbol->GetName());
			return false;
		}
		return pPropHandler->SetValue(*this, *pValue, attr);
	}
	GetModule().GetFrame().Assign(pSymbol, pValue.release());
	return true;
}

}
