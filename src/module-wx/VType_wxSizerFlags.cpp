﻿//==============================================================================
// VType_wxSizerFlags.cpp
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

${help.ComposePropertyHelp(wx.SizerFlags, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SizerFlags, `en)}

${help.ComposeMethodHelp(wx.SizerFlags, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.SizerFlags(proportion? as Number) {block?}
Gurax_DeclareConstructorAlias(SizerFlags_gurax, "SizerFlags")
{
	Declare(VTYPE_wxSizerFlags, Flag::None);
	DeclareArg("proportion", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates an instance of wx.SizerFlags.
)**");
}

Gurax_ImplementConstructorEx(SizerFlags_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool proportion_validFlag = args_gurax.IsValid();
	int proportion = proportion_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizerFlags(
		wxSizerFlags(proportion)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SizerFlags#Align(alignment as Number)
Gurax_DeclareMethodAlias(wxSizerFlags, Align_gurax, "Align")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("alignment", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, Align_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int alignment = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->Align(alignment);
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#Border(direction? as Number, borderinpixels? as Number)
Gurax_DeclareMethodAlias(wxSizerFlags, Border_gurax, "Border")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("direction", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("borderinpixels", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, Border_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool direction_validFlag = args_gurax.IsValid();
	int direction = direction_validFlag? args_gurax.PickNumber<int>() : wxALL;
	bool borderinpixels_validFlag = args_gurax.IsValid();
	int borderinpixels = borderinpixels_validFlag? args_gurax.PickNumber<int>() : 1;
	// Function body
	pEntity_gurax->Border(direction, borderinpixels);
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#Bottom()
Gurax_DeclareMethodAlias(wxSizerFlags, Bottom_gurax, "Bottom")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, Bottom_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Bottom();
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#Center()
Gurax_DeclareMethodAlias(wxSizerFlags, Center_gurax, "Center")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, Center_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Center();
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#Centre()
Gurax_DeclareMethodAlias(wxSizerFlags, Centre_gurax, "Centre")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, Centre_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Centre();
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#DoubleBorder(direction? as Number)
Gurax_DeclareMethodAlias(wxSizerFlags, DoubleBorder_gurax, "DoubleBorder")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("direction", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, DoubleBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool direction_validFlag = args_gurax.IsValid();
	int direction = direction_validFlag? args_gurax.PickNumber<int>() : wxALL;
	// Function body
	pEntity_gurax->DoubleBorder(direction);
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#DoubleHorzBorder()
Gurax_DeclareMethodAlias(wxSizerFlags, DoubleHorzBorder_gurax, "DoubleHorzBorder")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, DoubleHorzBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->DoubleHorzBorder();
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#Expand()
Gurax_DeclareMethodAlias(wxSizerFlags, Expand_gurax, "Expand")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, Expand_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Expand();
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#FixedMinSize()
Gurax_DeclareMethodAlias(wxSizerFlags, FixedMinSize_gurax, "FixedMinSize")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, FixedMinSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->FixedMinSize();
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#ReserveSpaceEvenIfHidden()
Gurax_DeclareMethodAlias(wxSizerFlags, ReserveSpaceEvenIfHidden_gurax, "ReserveSpaceEvenIfHidden")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, ReserveSpaceEvenIfHidden_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->ReserveSpaceEvenIfHidden();
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#Left()
Gurax_DeclareMethodAlias(wxSizerFlags, Left_gurax, "Left")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, Left_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Left();
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#Proportion(proportion as Number)
Gurax_DeclareMethodAlias(wxSizerFlags, Proportion_gurax, "Proportion")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("proportion", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, Proportion_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int proportion = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->Proportion(proportion);
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#Right()
Gurax_DeclareMethodAlias(wxSizerFlags, Right_gurax, "Right")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, Right_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Right();
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#Shaped()
Gurax_DeclareMethodAlias(wxSizerFlags, Shaped_gurax, "Shaped")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, Shaped_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Shaped();
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#Top()
Gurax_DeclareMethodAlias(wxSizerFlags, Top_gurax, "Top")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, Top_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Top();
	return valueThis_gurax.Reference();
}

// wx.SizerFlags#TripleBorder(direction? as Number)
Gurax_DeclareMethodAlias(wxSizerFlags, TripleBorder_gurax, "TripleBorder")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("direction", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSizerFlags, TripleBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool direction_validFlag = args_gurax.IsValid();
	int direction = direction_validFlag? args_gurax.PickNumber<int>() : wxALL;
	// Function body
	pEntity_gurax->TripleBorder(direction);
	return valueThis_gurax.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSizerFlags
//------------------------------------------------------------------------------
VType_wxSizerFlags VTYPE_wxSizerFlags("SizerFlags");

void VType_wxSizerFlags::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(SizerFlags_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSizerFlags, Align_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, Border_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, Bottom_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, Center_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, Centre_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, DoubleBorder_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, DoubleHorzBorder_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, Expand_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, FixedMinSize_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, ReserveSpaceEvenIfHidden_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, Left_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, Proportion_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, Right_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, Shaped_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, Top_gurax));
	Assign(Gurax_CreateMethod(wxSizerFlags, TripleBorder_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSizerFlags
//------------------------------------------------------------------------------
VType& Value_wxSizerFlags::vtype = VTYPE_wxSizerFlags;

String Value_wxSizerFlags::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SizerFlags");
}

Gurax_EndModuleScope(wx)
