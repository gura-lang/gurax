//==============================================================================
// VType_wxCalculateLayoutEvent.cpp
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
// wx.CalculateLayoutEvent#GetFlags()
Gurax_DeclareMethodAlias(wxCalculateLayoutEvent, GetFlags_gurax, "GetFlags")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalculateLayoutEvent, GetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFlags();
	return new Gurax::Value_Number(rtn);
}

// wx.CalculateLayoutEvent#GetRect() {block?}
Gurax_DeclareMethodAlias(wxCalculateLayoutEvent, GetRect_gurax, "GetRect")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalculateLayoutEvent, GetRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->GetRect()));
}

// wx.CalculateLayoutEvent#SetFlags(flags as Number)
Gurax_DeclareMethodAlias(wxCalculateLayoutEvent, SetFlags_gurax, "SetFlags")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalculateLayoutEvent, SetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flags = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetFlags(flags);
	return Gurax::Value::nil();
}

// wx.CalculateLayoutEvent#SetRect(rect as wx.Rect)
Gurax_DeclareMethodAlias(wxCalculateLayoutEvent, SetRect_gurax, "SetRect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalculateLayoutEvent, SetRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	const wxRect& rect = value_rect.GetEntity();
	// Function body
	pEntity_gurax->SetRect(rect);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxCalculateLayoutEvent
//------------------------------------------------------------------------------
VType_wxCalculateLayoutEvent VTYPE_wxCalculateLayoutEvent("CalculateLayoutEvent");

void VType_wxCalculateLayoutEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxCalculateLayoutEvent, GetFlags_gurax));
	Assign(Gurax_CreateMethod(wxCalculateLayoutEvent, GetRect_gurax));
	Assign(Gurax_CreateMethod(wxCalculateLayoutEvent, SetFlags_gurax));
	Assign(Gurax_CreateMethod(wxCalculateLayoutEvent, SetRect_gurax));
}

//------------------------------------------------------------------------------
// Value_wxCalculateLayoutEvent
//------------------------------------------------------------------------------
VType& Value_wxCalculateLayoutEvent::vtype = VTYPE_wxCalculateLayoutEvent;
EventValueFactoryDeriv<Value_wxCalculateLayoutEvent> Value_wxCalculateLayoutEvent::eventValueFactory;

String Value_wxCalculateLayoutEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CalculateLayoutEvent");
}

Gurax_EndModuleScope(wx)
