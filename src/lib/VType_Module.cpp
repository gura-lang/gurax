//==============================================================================
// VType_Module.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
#if 0
// ********************
// Module#__PropHandler__(symbol:Symbol):map {block?}
Gurax_DeclareMethod(Module, __PropHandler__)
{
	Declare(VTYPE_PropHandler, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Module, __PropHandler__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	const PropHandler* pPropHandler = valueThis.GetModule().LookupPropHandler(pSymbol);
	if (!pPropHandler) {
		Error::Issue(ErrorType::PropertyError, "no property named '%s'", pSymbol->GetName());
		return Value::nil();
	}
	return argument.ReturnValue(processor, new Value_PropHandler(pPropHandler->Reference()));
}
#endif

//------------------------------------------------------------------------------
// VType_Module
//------------------------------------------------------------------------------
VType_Module VTYPE_Module("Module");

void VType_Module::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(Module, __PropHandler__));
}

//------------------------------------------------------------------------------
// Value_Module
//------------------------------------------------------------------------------
VType& Value_Module::vtype = VTYPE_Module;

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

Value* Value_Module::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	const PropHandler* pPropHandler = GetModule().LookupPropHandler(pSymbol);
	if (!pPropHandler) {
		Value* pValue = GetModule().GetFrame().Lookup(pSymbol);
		return pValue? pValue : Value::DoPropGet(pSymbol, attr, notFoundErrorFlag);
	}
	if (!pPropHandler->IsSet(PropHandler::Flag::Readable)) {
		Error::Issue(ErrorType::PropertyError, "property '%s' is not readable", pSymbol->GetName());
		return nullptr;
	}
	return pPropHandler->GetValue(*this, attr);
}

bool Value_Module::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	const PropHandler* pPropHandler = GetModule().LookupPropHandler(pSymbol);
	if (!pPropHandler) {
		GetModule().GetFrame().Assign(pSymbol, pValue.release());
		return true;
	}
	if (!pPropHandler->IsSet(PropHandler::Flag::Writable)) {
		Error::Issue(ErrorType::PropertyError, "property '%s' is not writable", pSymbol->GetName());
		return false;
	}
	return pPropHandler->SetValue(*this, *pValue, attr);
}

}
