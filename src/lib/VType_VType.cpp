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

bool Value_VType::IsCallable() const
{
	//const Function& constructor = GetVTypeThis().GetConstructor();
	//return !constructor.IsEmpty();
	return false;
}

const DeclCallable* Value_VType::GetDeclCallable() const
{
	const Function& constructor = GetVTypeThis().GetConstructor();
	if (constructor.IsEmpty()) {
		Error::Issue(ErrorType::ValueError,
					 "value type %s does not have a constructor", GetVTypeThis().MakeFullName().c_str());
		return nullptr;
	}
	return &constructor.GetDeclCallable();
}

void Value_VType::DoCall(Processor& processor, Argument& argument)
{
	const Function& constructor = GetVTypeThis().GetConstructor();
	constructor.DoCall(processor, argument);
}

Value* Value_VType::DoPropGet(const Symbol* pSymbol, const Attribute& attr)
{
	const PropHandler* pPropHandler = GetVTypeThis().LookupPropHandlerOfClass(pSymbol);
	if (!pPropHandler) {
		return GetVTypeThis().GetFrame().Lookup(pSymbol);
	} else if (pPropHandler->IsSet(PropHandler::Flag::Readable)) {
		return pPropHandler->GetValue(*this, attr);
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
	} else if (pPropHandler->IsSet(PropHandler::Flag::Writable)) {
		return pPropHandler->SetValue(*this, *pValue, attr);
	} else {
		return false;
	}
}

}
