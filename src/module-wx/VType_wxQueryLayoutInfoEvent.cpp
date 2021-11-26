//==============================================================================
// VType_wxQueryLayoutInfoEvent.cpp
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
// wx.QueryLayoutInfoEvent#GetAlignment()
Gurax_DeclareMethodAlias(wxQueryLayoutInfoEvent, GetAlignment_gurax, "GetAlignment")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryLayoutInfoEvent, GetAlignment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxLayoutAlignment rtn = pEntity_gurax->GetAlignment();
	return new Gurax::Value_Number(rtn);
}

// wx.QueryLayoutInfoEvent#GetFlags()
Gurax_DeclareMethodAlias(wxQueryLayoutInfoEvent, GetFlags_gurax, "GetFlags")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryLayoutInfoEvent, GetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFlags();
	return new Gurax::Value_Number(rtn);
}

// wx.QueryLayoutInfoEvent#GetOrientation()
Gurax_DeclareMethodAlias(wxQueryLayoutInfoEvent, GetOrientation_gurax, "GetOrientation")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryLayoutInfoEvent, GetOrientation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxLayoutOrientation rtn = pEntity_gurax->GetOrientation();
	return new Gurax::Value_Number(rtn);
}

// wx.QueryLayoutInfoEvent#GetRequestedLength()
Gurax_DeclareMethodAlias(wxQueryLayoutInfoEvent, GetRequestedLength_gurax, "GetRequestedLength")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryLayoutInfoEvent, GetRequestedLength_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetRequestedLength();
	return new Gurax::Value_Number(rtn);
}

// wx.QueryLayoutInfoEvent#GetSize() {block?}
Gurax_DeclareMethodAlias(wxQueryLayoutInfoEvent, GetSize_gurax, "GetSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryLayoutInfoEvent, GetSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetSize()));
}

// wx.QueryLayoutInfoEvent#SetAlignment(alignment as Number)
Gurax_DeclareMethodAlias(wxQueryLayoutInfoEvent, SetAlignment_gurax, "SetAlignment")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("alignment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryLayoutInfoEvent, SetAlignment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxLayoutAlignment alignment = args_gurax.PickNumber<wxLayoutAlignment>();
	// Function body
	pEntity_gurax->SetAlignment(alignment);
	return Gurax::Value::nil();
}

// wx.QueryLayoutInfoEvent#SetFlags(flags as Number)
Gurax_DeclareMethodAlias(wxQueryLayoutInfoEvent, SetFlags_gurax, "SetFlags")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryLayoutInfoEvent, SetFlags_gurax, processor_gurax, argument_gurax)
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

// wx.QueryLayoutInfoEvent#SetOrientation(orientation as Number)
Gurax_DeclareMethodAlias(wxQueryLayoutInfoEvent, SetOrientation_gurax, "SetOrientation")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("orientation", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryLayoutInfoEvent, SetOrientation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxLayoutOrientation orientation = args_gurax.PickNumber<wxLayoutOrientation>();
	// Function body
	pEntity_gurax->SetOrientation(orientation);
	return Gurax::Value::nil();
}

// wx.QueryLayoutInfoEvent#SetRequestedLength(length as Number)
Gurax_DeclareMethodAlias(wxQueryLayoutInfoEvent, SetRequestedLength_gurax, "SetRequestedLength")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("length", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryLayoutInfoEvent, SetRequestedLength_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int length = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetRequestedLength(length);
	return Gurax::Value::nil();
}

// wx.QueryLayoutInfoEvent#SetSize(size as wx.Size)
Gurax_DeclareMethodAlias(wxQueryLayoutInfoEvent, SetSize_gurax, "SetSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxQueryLayoutInfoEvent, SetSize_gurax, processor_gurax, argument_gurax)
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

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxQueryLayoutInfoEvent
//------------------------------------------------------------------------------
VType_wxQueryLayoutInfoEvent VTYPE_wxQueryLayoutInfoEvent("QueryLayoutInfoEvent");

void VType_wxQueryLayoutInfoEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxQueryLayoutInfoEvent, GetAlignment_gurax));
	Assign(Gurax_CreateMethod(wxQueryLayoutInfoEvent, GetFlags_gurax));
	Assign(Gurax_CreateMethod(wxQueryLayoutInfoEvent, GetOrientation_gurax));
	Assign(Gurax_CreateMethod(wxQueryLayoutInfoEvent, GetRequestedLength_gurax));
	Assign(Gurax_CreateMethod(wxQueryLayoutInfoEvent, GetSize_gurax));
	Assign(Gurax_CreateMethod(wxQueryLayoutInfoEvent, SetAlignment_gurax));
	Assign(Gurax_CreateMethod(wxQueryLayoutInfoEvent, SetFlags_gurax));
	Assign(Gurax_CreateMethod(wxQueryLayoutInfoEvent, SetOrientation_gurax));
	Assign(Gurax_CreateMethod(wxQueryLayoutInfoEvent, SetRequestedLength_gurax));
	Assign(Gurax_CreateMethod(wxQueryLayoutInfoEvent, SetSize_gurax));
}

//------------------------------------------------------------------------------
// Value_wxQueryLayoutInfoEvent
//------------------------------------------------------------------------------
VType& Value_wxQueryLayoutInfoEvent::vtype = VTYPE_wxQueryLayoutInfoEvent;
EventValueFactoryDeriv<Value_wxQueryLayoutInfoEvent> Value_wxQueryLayoutInfoEvent::eventValueFactory;

String Value_wxQueryLayoutInfoEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.QueryLayoutInfoEvent");
}

Gurax_EndModuleScope(wx)