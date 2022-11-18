﻿//==============================================================================
// VType_wxSizeEvent.cpp
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

${help.ComposePropertyHelp(wx.SizeEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SizeEvent, `en)}

${help.ComposeMethodHelp(wx.SizeEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SizeEvent#GetSize() {block?}
Gurax_DeclareMethodAlias(wxSizeEvent, GetSize_gurax, "GetSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSizeEvent, GetSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetSize()));
}

// wx.SizeEvent#SetSize(size as wx.Size)
Gurax_DeclareMethodAlias(wxSizeEvent, SetSize_gurax, "SetSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizeEvent, SetSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	// Function body
	pEntity_gurax->SetSize(size);
	return Gurax::Value::nil();
}

// wx.SizeEvent#GetRect() {block?}
Gurax_DeclareMethodAlias(wxSizeEvent, GetRect_gurax, "GetRect")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSizeEvent, GetRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->GetRect()));
}

// wx.SizeEvent#SetRect(rect as wx.Rect)
Gurax_DeclareMethodAlias(wxSizeEvent, SetRect_gurax, "SetRect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizeEvent, SetRect_gurax, processor_gurax, argument_gurax)
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
// VType_wxSizeEvent
//------------------------------------------------------------------------------
VType_wxSizeEvent VTYPE_wxSizeEvent("SizeEvent");

void VType_wxSizeEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSizeEvent, GetSize_gurax));
	Assign(Gurax_CreateMethod(wxSizeEvent, SetSize_gurax));
	Assign(Gurax_CreateMethod(wxSizeEvent, GetRect_gurax));
	Assign(Gurax_CreateMethod(wxSizeEvent, SetRect_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSizeEvent
//------------------------------------------------------------------------------
VType& Value_wxSizeEvent::vtype = VTYPE_wxSizeEvent;
EventValueFactoryDeriv<Value_wxSizeEvent> Value_wxSizeEvent::eventValueFactory;

String Value_wxSizeEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SizeEvent");
}

Gurax_EndModuleScope(wx)
