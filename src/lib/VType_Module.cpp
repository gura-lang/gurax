//==============================================================================
// VType_Module.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
#if 0
// ********************
// Module#__prop__(symbol:Symbol):map {block?}
Gurax_DeclareMethod(Module, __prop__)
{
	Declare(VTYPE_PropSlot, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Module, __prop__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	const PropSlot* pPropSlot = valueThis.GetModule().LookupPropSlot(pSymbol);
	if (!pPropSlot) {
		Error::Issue(ErrorType::PropertyError, "no property named '%s'", pSymbol->GetName());
		return Value::nil();
	}
	return argument.ReturnValue(processor, new Value_PropSlot(pPropSlot->Reference()));
}
#endif

//------------------------------------------------------------------------------
// VType_Module
//------------------------------------------------------------------------------
VType_Module VTYPE_Module("Module");

void VType_Module::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(Module, __prop__));
}

//------------------------------------------------------------------------------
// Value_Module
//------------------------------------------------------------------------------
VType& Value_Module::vtype = VTYPE_Module;

String Value_Module::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Format(":%s:%s>",
			   GetModule().GetDottedSymbol().ToString().c_str(),
			   GetModule().GetPathName());
	return str;
}

String Value_Module::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

void Value_Module::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	const Help* pHelp = GetHelpHolder()->Lookup(pLangCode);
	if (pHelp) Basement::Inst.Present(processor, pHelp->GetDocReferable().Reference());
}

Value* Value_Module::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	const PropSlot* pPropSlot = GetModule().LookupPropSlot(pSymbol);
	if (pPropSlot) {
		if (!pPropSlot->CheckValidAttribute(attr)) return nullptr;
		if (!pPropSlot->IsSet(PropSlot::Flag::Readable)) {
			Error::Issue(ErrorType::PropertyError, "property '%s' is not readable", pSymbol->GetName());
			return nullptr;
		}
		return pPropSlot->GetValue(*this, attr);
	}
	Value* pValue = GetModule().GetFrame().GetValue2Local(pSymbol);
	if (pValue) return pValue->Reference();
	if (notFoundErrorFlag) {
		Error::Issue(ErrorType::PropertyError,
					 "module '%s' doesn't have a property '%s'",
					 GetModule().GetDottedSymbol().ToString().c_str(), pSymbol->GetName());
	}
	return nullptr;
}

bool Value_Module::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	const PropSlot* pPropSlot = GetModule().LookupPropSlot(pSymbol);
	if (!pPropSlot) {
		GetModule().GetFrame().Assign(pSymbol, pValue.release());
		return true;
	}
	if (!pPropSlot->CheckValidAttribute(attr)) return false;
	if (!pPropSlot->IsSet(PropSlot::Flag::Writable)) {
		Error::Issue(ErrorType::PropertyError, "property '%s' is not writable", pSymbol->GetName());
		return false;
	}
	return pPropSlot->SetValue(*this, *pValue, attr);
}

}
