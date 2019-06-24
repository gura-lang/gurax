//==============================================================================
// VType_VType.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// VType#__PropHandler__(symbol:Symbol):map {block?}
Gurax_DeclareMethod(VType, __PropHandler__)
{
	Declare(VTYPE_PropHandler, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(VType, __PropHandler__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	const PropHandler* pPropHandler = valueThis.GetVTypeThis().LookupPropHandler(pSymbol);
	if (!pPropHandler) {
		Error::Issue(ErrorType::PropertyError, "no property named '%s'", pSymbol->GetName());
		return Value::nil();
	}
	return ReturnValue(processor, argument, new Value_PropHandler(pPropHandler->Reference()));
}

//------------------------------------------------------------------------------
// VType_VType
//------------------------------------------------------------------------------
VType_VType VTYPE_VType("VType");

void VType_VType::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(VType, __PropHandler__));
}

//------------------------------------------------------------------------------
// Value_VType
//------------------------------------------------------------------------------
String Value_VType::ToStringDigest(const StringStyle& ss) const
{
	const Function& constructor = GetVTypeThis().GetConstructor();
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += constructor.IsEmpty()?
		GetVTypeThis().MakeFullName() : constructor.ToString(StringStyle().Cram());
	str += ">";
	return str;
}

String Value_VType::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

bool Value_VType::IsCallable() const
{
	const Function& constructor = GetVTypeThis().GetConstructor();
	return !constructor.IsEmpty();
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
		Value* pValue = GetVTypeThis().GetFrame().Lookup(pSymbol);
		return pValue? pValue : Value::DoPropGet(pSymbol, attr);
	}
	if (!pPropHandler->IsSet(PropHandler::Flag::Readable)) {
		Error::Issue(ErrorType::PropertyError, "property '%s' is not readable", pSymbol->GetName());
		return nullptr;
	}
	return pPropHandler->GetValue(*this, attr);
}

bool Value_VType::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	const PropHandler* pPropHandler = GetVTypeThis().LookupPropHandler(pSymbol);
	if (!pPropHandler) {
		GetVTypeThis().GetFrame().Assign(pSymbol, pValue.release());
		return true;
	}
	if (!pPropHandler->IsSet(PropHandler::Flag::Writable)) {
		Error::Issue(ErrorType::PropertyError, "property '%s' is not writable", pSymbol->GetName());
		return false;
	}
	return pPropHandler->SetValue(*this, *pValue, attr);
}

}
