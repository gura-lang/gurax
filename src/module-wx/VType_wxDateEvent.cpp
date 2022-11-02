//==============================================================================
// VType_wxDateEvent.cpp
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

${help.ComposePropertyHelp(wxDateEvent)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxDateEvent)}

${help.ComposeMethodHelp(wxDateEvent)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DateEvent#GetDate() {block?}
Gurax_DeclareMethodAlias(wxDateEvent, GetDate_gurax, "GetDate")
{
	Declare(VTYPE_wxDateTime, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateEvent, GetDate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateTime(
		pEntity_gurax->GetDate()));
}

// wx.DateEvent#SetDate(date as wx.DateTime)
Gurax_DeclareMethodAlias(wxDateEvent, SetDate_gurax, "SetDate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("date", VTYPE_wxDateTime, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateEvent, SetDate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDateTime& value_date = args_gurax.Pick<Value_wxDateTime>();
	const wxDateTime& date = value_date.GetEntity();
	// Function body
	pEntity_gurax->SetDate(date);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDateEvent
//------------------------------------------------------------------------------
VType_wxDateEvent VTYPE_wxDateEvent("DateEvent");

void VType_wxDateEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDateEvent, GetDate_gurax));
	Assign(Gurax_CreateMethod(wxDateEvent, SetDate_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDateEvent
//------------------------------------------------------------------------------
VType& Value_wxDateEvent::vtype = VTYPE_wxDateEvent;
EventValueFactoryDeriv<Value_wxDateEvent> Value_wxDateEvent::eventValueFactory;

String Value_wxDateEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DateEvent");
}

Gurax_EndModuleScope(wx)
