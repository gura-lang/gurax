//==============================================================================
// VType_wxSpinButton.cpp
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
// wx.SpinButton(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(SpinButton_gurax, "SpinButton")
{
	Declare(VTYPE_wxSpinButton, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.SpinButton.");
}

Gurax_ImplementConstructorEx(SpinButton_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxSP_VERTICAL;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "wxSpinButton";
	// Function body
	auto pEntity_gurax = new Value_wxSpinButton::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxSpinButton> pValue_gurax(new Value_wxSpinButton(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SpinButton#GetMax()
Gurax_DeclareMethodAlias(wxSpinButton, GetMax_gurax, "GetMax")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinButton, GetMax_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMax();
	return new Gurax::Value_Number(rtn);
}

// wx.SpinButton#GetMin()
Gurax_DeclareMethodAlias(wxSpinButton, GetMin_gurax, "GetMin")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinButton, GetMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMin();
	return new Gurax::Value_Number(rtn);
}

// wx.SpinButton#GetValue()
Gurax_DeclareMethodAlias(wxSpinButton, GetValue_gurax, "GetValue")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinButton, GetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetValue();
	return new Gurax::Value_Number(rtn);
}

// wx.SpinButton#SetRange(min as Number, max as Number)
Gurax_DeclareMethodAlias(wxSpinButton, SetRange_gurax, "SetRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("max", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinButton, SetRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int min = args_gurax.PickNumber<int>();
	int max = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetRange(min, max);
	return Gurax::Value::nil();
}

// wx.SpinButton#SetValue(value as Number)
Gurax_DeclareMethodAlias(wxSpinButton, SetValue_gurax, "SetValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinButton, SetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int value = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetValue(value);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSpinButton
//------------------------------------------------------------------------------
VType_wxSpinButton VTYPE_wxSpinButton("SpinButton");

void VType_wxSpinButton::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(SpinButton_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSpinButton, GetMax_gurax));
	Assign(Gurax_CreateMethod(wxSpinButton, GetMin_gurax));
	Assign(Gurax_CreateMethod(wxSpinButton, GetValue_gurax));
	Assign(Gurax_CreateMethod(wxSpinButton, SetRange_gurax));
	Assign(Gurax_CreateMethod(wxSpinButton, SetValue_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSpinButton
//------------------------------------------------------------------------------
VType& Value_wxSpinButton::vtype = VTYPE_wxSpinButton;

String Value_wxSpinButton::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SpinButton");
}

//------------------------------------------------------------------------------
// Value_wxSpinButton::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
