//==============================================================================
// VType_Module.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Module, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Module, `en)}

${help.ComposeMethodHelp(Module, `en)}
)""";

//------------------------------------------------------------------------------
// VType_Module
//------------------------------------------------------------------------------
VType_Module VTYPE_Module("Module");

void VType_Module::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
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
