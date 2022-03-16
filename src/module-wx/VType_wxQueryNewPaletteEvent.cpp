//==============================================================================
// VType_wxQueryNewPaletteEvent.cpp
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
// wx.QueryNewPaletteEvent#SetPaletteRealized(realized as Bool)
Gurax_DeclareMethodAlias(wxQueryNewPaletteEvent, SetPaletteRealized_gurax, "SetPaletteRealized")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("realized", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryNewPaletteEvent, SetPaletteRealized_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool realized = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetPaletteRealized(realized);
	return Gurax::Value::nil();
}

// wx.QueryNewPaletteEvent#GetPaletteRealized()
Gurax_DeclareMethodAlias(wxQueryNewPaletteEvent, GetPaletteRealized_gurax, "GetPaletteRealized")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryNewPaletteEvent, GetPaletteRealized_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetPaletteRealized();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxQueryNewPaletteEvent
//------------------------------------------------------------------------------
VType_wxQueryNewPaletteEvent VTYPE_wxQueryNewPaletteEvent("QueryNewPaletteEvent");

void VType_wxQueryNewPaletteEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxQueryNewPaletteEvent, SetPaletteRealized_gurax));
	Assign(Gurax_CreateMethod(wxQueryNewPaletteEvent, GetPaletteRealized_gurax));
}

//------------------------------------------------------------------------------
// Value_wxQueryNewPaletteEvent
//------------------------------------------------------------------------------
VType& Value_wxQueryNewPaletteEvent::vtype = VTYPE_wxQueryNewPaletteEvent;
EventValueFactoryDeriv<Value_wxQueryNewPaletteEvent> Value_wxQueryNewPaletteEvent::eventValueFactory;

String Value_wxQueryNewPaletteEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.QueryNewPaletteEvent");
}

Gurax_EndModuleScope(wx)