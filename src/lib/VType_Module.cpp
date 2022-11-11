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

${help.ComposePropertyHelp(Module, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Module, `en)}

${help.ComposeMethodHelp(Module, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Module#__help__(lang? as Symbol):map:[nil] {block?}
Gurax_DeclareMethod(Module, __help__)
{
	Declare(VTYPE_Help, Flag::Map);
	DeclareArg("lang", VTYPE_Symbol, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	DeclareAttrOpt(Gurax_Symbol(nil));
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Module, __help__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pLangCode = args.IsValid()? args.PickSymbol() : nullptr;
	bool nilFlag = argument.IsSet(Gurax_Symbol(nil));
	// Function body
	RefPtr<Value> pValueRtn(Value::nil());
	const Help* pHelp = valueThis.GetModule().GetHelpHolder().LookupLoose(pLangCode);
	if (pHelp) {
		pValueRtn.reset(new Value_Help(pHelp->Reference()));
	} else if (!nilFlag) {
		Error::Issue(ErrorType::SymbolError, "no help defined for language symbol %s", pLangCode->GetName());
		return Value::nil();
	}
	return argument.ReturnValue(processor, pValueRtn.release());
}

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
	Assign(Gurax_CreateMethod(Module, __help__));
}

//------------------------------------------------------------------------------
// Value_Module
//------------------------------------------------------------------------------
VType& Value_Module::vtype = VTYPE_Module;

String Value_Module::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetModule().ToString(ss));
}

void Value_Module::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	const Help* pHelp = GetHelpHolder(false)->LookupLoose(pLangCode);
	if (pHelp) Basement::Inst.Present(processor, pHelp->GetDocReferable().Reference());
}

Value* Value_Module::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
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
	RefPtr<Value> pValue(GetModule().GetFrame().RetrieveLocal(pSymbol));
	if (pValue) return pValue.release();
	if (notFoundErrorFlag) {
		Error::Issue(ErrorType::PropertyError,
					 "module '%s' doesn't have a property '%s'",
					 GetModule().GetDottedSymbol().ToString().c_str(), pSymbol->GetName());
	}
	return nullptr;
}

bool Value_Module::DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
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
