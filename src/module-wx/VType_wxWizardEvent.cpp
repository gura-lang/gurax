//==============================================================================
// VType_wxWizardEvent.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

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
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.WizardEvent#GetDirection()
Gurax_DeclareMethodAlias(wxWizardEvent, GetDirection_gurax, "GetDirection")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxWizardEvent, GetDirection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetDirection();
	return new Gurax::Value_Bool(rtn);
}

// wx.WizardEvent#GetPage() {block?}
Gurax_DeclareMethodAlias(wxWizardEvent, GetPage_gurax, "GetPage")
{
	Declare(VTYPE_wxWizardPage, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxWizardEvent, GetPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWizardPage(
		pEntity_gurax->GetPage()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxWizardEvent
//------------------------------------------------------------------------------
VType_wxWizardEvent VTYPE_wxWizardEvent("WizardEvent");

void VType_wxWizardEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxWizardEvent, GetDirection_gurax));
	Assign(Gurax_CreateMethod(wxWizardEvent, GetPage_gurax));
}

//------------------------------------------------------------------------------
// Value_wxWizardEvent
//------------------------------------------------------------------------------
VType& Value_wxWizardEvent::vtype = VTYPE_wxWizardEvent;
EventValueFactoryDeriv<Value_wxWizardEvent> Value_wxWizardEvent::eventValueFactory;

String Value_wxWizardEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.WizardEvent");
}

Gurax_EndModuleScope(wx)
