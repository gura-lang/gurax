﻿//==============================================================================
// VType_wxFindReplaceData.cpp
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

${help.ComposePropertyHelp(wx.FindReplaceData, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FindReplaceData, `en)}

${help.ComposeMethodHelp(wx.FindReplaceData, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.FindReplaceData(flags? as Number) {block?}
Gurax_DeclareConstructorAlias(FindReplaceData_gurax, "FindReplaceData")
{
	Declare(VTYPE_wxFindReplaceData, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.FindReplaceData.");
}

Gurax_ImplementConstructorEx(FindReplaceData_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool flags_validFlag = args_gurax.IsValid();
	wxUint32 flags = flags_validFlag? args_gurax.PickNumber<wxUint32>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFindReplaceData(
		wxFindReplaceData(flags)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FindReplaceData#GetFindString()
Gurax_DeclareMethodAlias(wxFindReplaceData, GetFindString_gurax, "GetFindString")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFindReplaceData, GetFindString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetFindString();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FindReplaceData#GetFlags()
Gurax_DeclareMethodAlias(wxFindReplaceData, GetFlags_gurax, "GetFlags")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFindReplaceData, GetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFlags();
	return new Gurax::Value_Number(rtn);
}

// wx.FindReplaceData#GetReplaceString()
Gurax_DeclareMethodAlias(wxFindReplaceData, GetReplaceString_gurax, "GetReplaceString")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFindReplaceData, GetReplaceString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetReplaceString();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FindReplaceData#SetFindString(str as String)
Gurax_DeclareMethodAlias(wxFindReplaceData, SetFindString_gurax, "SetFindString")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFindReplaceData, SetFindString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* str = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetFindString(str);
	return Gurax::Value::nil();
}

// wx.FindReplaceData#SetFlags(flags as Number)
Gurax_DeclareMethodAlias(wxFindReplaceData, SetFlags_gurax, "SetFlags")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFindReplaceData, SetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxUint32 flags = args_gurax.PickNumber<wxUint32>();
	// Function body
	pEntity_gurax->SetFlags(flags);
	return Gurax::Value::nil();
}

// wx.FindReplaceData#SetReplaceString(str as String)
Gurax_DeclareMethodAlias(wxFindReplaceData, SetReplaceString_gurax, "SetReplaceString")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFindReplaceData, SetReplaceString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* str = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetReplaceString(str);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFindReplaceData
//------------------------------------------------------------------------------
VType_wxFindReplaceData VTYPE_wxFindReplaceData("FindReplaceData");

void VType_wxFindReplaceData::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable, Gurax_CreateConstructor(FindReplaceData_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFindReplaceData, GetFindString_gurax));
	Assign(Gurax_CreateMethod(wxFindReplaceData, GetFlags_gurax));
	Assign(Gurax_CreateMethod(wxFindReplaceData, GetReplaceString_gurax));
	Assign(Gurax_CreateMethod(wxFindReplaceData, SetFindString_gurax));
	Assign(Gurax_CreateMethod(wxFindReplaceData, SetFlags_gurax));
	Assign(Gurax_CreateMethod(wxFindReplaceData, SetReplaceString_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFindReplaceData
//------------------------------------------------------------------------------
VType& Value_wxFindReplaceData::vtype = VTYPE_wxFindReplaceData;

String Value_wxFindReplaceData::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FindReplaceData");
}

Gurax_EndModuleScope(wx)
