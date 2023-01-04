﻿//==============================================================================
// VType_wxSetCursorEvent.cpp
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

${help.ComposePropertyHelp(wx.SetCursorEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SetCursorEvent, `en)}

${help.ComposeMethodHelp(wx.SetCursorEvent, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.SetCursorEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.SetCursorEvent, `ja)}

${help.ComposeMethodHelp(wx.SetCursorEvent, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SetCursorEvent#GetCursor() {block?}
Gurax_DeclareMethodAlias(wxSetCursorEvent, GetCursor_gurax, "GetCursor")
{
	Declare(VTYPE_wxCursor, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSetCursorEvent, GetCursor_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxCursor(
		pEntity_gurax->GetCursor()));
}

// wx.SetCursorEvent#GetX()
Gurax_DeclareMethodAlias(wxSetCursorEvent, GetX_gurax, "GetX")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSetCursorEvent, GetX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxCoord rtn = pEntity_gurax->GetX();
	return new Gurax::Value_Number(rtn);
}

// wx.SetCursorEvent#GetY()
Gurax_DeclareMethodAlias(wxSetCursorEvent, GetY_gurax, "GetY")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSetCursorEvent, GetY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxCoord rtn = pEntity_gurax->GetY();
	return new Gurax::Value_Number(rtn);
}

// wx.SetCursorEvent#HasCursor()
Gurax_DeclareMethodAlias(wxSetCursorEvent, HasCursor_gurax, "HasCursor")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxSetCursorEvent, HasCursor_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasCursor();
	return new Gurax::Value_Bool(rtn);
}

// wx.SetCursorEvent#SetCursor(cursor as wx.Cursor)
Gurax_DeclareMethodAlias(wxSetCursorEvent, SetCursor_gurax, "SetCursor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cursor", VTYPE_wxCursor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSetCursorEvent, SetCursor_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxCursor& value_cursor = args_gurax.Pick<Value_wxCursor>();
	const wxCursor& cursor = value_cursor.GetEntity();
	// Function body
	pEntity_gurax->SetCursor(cursor);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSetCursorEvent
//------------------------------------------------------------------------------
VType_wxSetCursorEvent VTYPE_wxSetCursorEvent("SetCursorEvent");

void VType_wxSetCursorEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSetCursorEvent, GetCursor_gurax));
	Assign(Gurax_CreateMethod(wxSetCursorEvent, GetX_gurax));
	Assign(Gurax_CreateMethod(wxSetCursorEvent, GetY_gurax));
	Assign(Gurax_CreateMethod(wxSetCursorEvent, HasCursor_gurax));
	Assign(Gurax_CreateMethod(wxSetCursorEvent, SetCursor_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSetCursorEvent
//------------------------------------------------------------------------------
VType& Value_wxSetCursorEvent::vtype = VTYPE_wxSetCursorEvent;
EventValueFactoryDeriv<Value_wxSetCursorEvent> Value_wxSetCursorEvent::eventValueFactory;

String Value_wxSetCursorEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SetCursorEvent");
}

Gurax_EndModuleScope(wx)
