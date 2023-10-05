﻿//==============================================================================
// VType_wxStyledTextEvent.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.StyledTextEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.StyledTextEvent, `en)}

${help.ComposeMethodHelp(wx.StyledTextEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.StyledTextEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.StyledTextEvent, `ja)}

${help.ComposeMethodHelp(wx.StyledTextEvent, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.StyledTextEvent#SetPosition(pos as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetPosition_gurax, "SetPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int pos = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetPosition(pos);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetKey(k as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetKey_gurax, "SetKey")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("k", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetKey_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int k = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetKey(k);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetModifiers(m as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetModifiers_gurax, "SetModifiers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetModifiers_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int m = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetModifiers(m);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetModificationType(t as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetModificationType_gurax, "SetModificationType")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("t", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetModificationType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int t = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetModificationType(t);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetText(t as String)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetText_gurax, "SetText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("t", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* t = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetText(t);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetLength(len as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetLength_gurax, "SetLength")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetLength_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int len = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetLength(len);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetLinesAdded(num as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetLinesAdded_gurax, "SetLinesAdded")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetLinesAdded_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int num = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetLinesAdded(num);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetLine(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetLine_gurax, "SetLine")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetLine_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetLine(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetFoldLevelNow(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetFoldLevelNow_gurax, "SetFoldLevelNow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetFoldLevelNow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetFoldLevelNow(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetFoldLevelPrev(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetFoldLevelPrev_gurax, "SetFoldLevelPrev")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetFoldLevelPrev_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetFoldLevelPrev(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetMargin(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetMargin_gurax, "SetMargin")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetMargin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMargin(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetMessage(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetMessage_gurax, "SetMessage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMessage(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetWParam(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetWParam_gurax, "SetWParam")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetWParam_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetWParam(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetLParam(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetLParam_gurax, "SetLParam")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetLParam_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetLParam(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetListType(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetListType_gurax, "SetListType")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetListType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetListType(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetX(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetX_gurax, "SetX")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetX(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetY(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetY_gurax, "SetY")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetY(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetToken(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetToken_gurax, "SetToken")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetToken_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetToken(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetAnnotationLinesAdded(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetAnnotationLinesAdded_gurax, "SetAnnotationLinesAdded")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetAnnotationLinesAdded_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetAnnotationLinesAdded(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetUpdated(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetUpdated_gurax, "SetUpdated")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetUpdated_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int val = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetUpdated(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetDragText(val as String)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetDragText_gurax, "SetDragText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetDragText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* val = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetDragText(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetDragFlags(flags as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetDragFlags_gurax, "SetDragFlags")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetDragFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flags = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetDragFlags(flags);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#SetDragResult(val as Number)
Gurax_DeclareMethodAlias(wxStyledTextEvent, SetDragResult_gurax, "SetDragResult")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("val", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, SetDragResult_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxDragResult val = args_gurax.PickNumber<wxDragResult>();
	// Function body
	pEntity_gurax->SetDragResult(val);
	return Gurax::Value::nil();
}

// wx.StyledTextEvent#GetPosition()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetPosition();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetKey()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetKey_gurax, "GetKey")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetKey_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetKey();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetModifiers()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetModifiers_gurax, "GetModifiers")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetModifiers_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetModifiers();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetModificationType()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetModificationType_gurax, "GetModificationType")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetModificationType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetModificationType();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetText()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetText_gurax, "GetText")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetText();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.StyledTextEvent#GetLength()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetLength_gurax, "GetLength")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetLength_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetLength();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetLinesAdded()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetLinesAdded_gurax, "GetLinesAdded")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetLinesAdded_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetLinesAdded();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetLine()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetLine_gurax, "GetLine")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetLine_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetLine();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetFoldLevelNow()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetFoldLevelNow_gurax, "GetFoldLevelNow")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetFoldLevelNow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFoldLevelNow();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetFoldLevelPrev()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetFoldLevelPrev_gurax, "GetFoldLevelPrev")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetFoldLevelPrev_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFoldLevelPrev();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetMargin()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetMargin_gurax, "GetMargin")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetMargin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMargin();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetMessage()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetMessage_gurax, "GetMessage")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMessage();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetWParam()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetWParam_gurax, "GetWParam")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetWParam_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetWParam();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetLParam()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetLParam_gurax, "GetLParam")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetLParam_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetLParam();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetListType()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetListType_gurax, "GetListType")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetListType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetListType();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetX()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetX_gurax, "GetX")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetX();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetY()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetY_gurax, "GetY")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetY();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetToken()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetToken_gurax, "GetToken")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetToken_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetToken();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetAnnotationsLinesAdded()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetAnnotationsLinesAdded_gurax, "GetAnnotationsLinesAdded")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetAnnotationsLinesAdded_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetAnnotationsLinesAdded();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetUpdated()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetUpdated_gurax, "GetUpdated")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetUpdated_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetUpdated();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetDragText()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetDragText_gurax, "GetDragText")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetDragText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetDragText();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.StyledTextEvent#GetDragFlags()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetDragFlags_gurax, "GetDragFlags")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetDragFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetDragFlags();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetDragResult()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetDragResult_gurax, "GetDragResult")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetDragResult_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxDragResult rtn = pEntity_gurax->GetDragResult();
	return new Gurax::Value_Number(rtn);
}

// wx.StyledTextEvent#GetShift()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetShift_gurax, "GetShift")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetShift_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetShift();
	return new Gurax::Value_Bool(rtn);
}

// wx.StyledTextEvent#GetControl()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetControl_gurax, "GetControl")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetControl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetControl();
	return new Gurax::Value_Bool(rtn);
}

// wx.StyledTextEvent#GetAlt()
Gurax_DeclareMethodAlias(wxStyledTextEvent, GetAlt_gurax, "GetAlt")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxStyledTextEvent, GetAlt_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetAlt();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxStyledTextEvent
//------------------------------------------------------------------------------
VType_wxStyledTextEvent VTYPE_wxStyledTextEvent("StyledTextEvent");

void VType_wxStyledTextEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetPosition_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetKey_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetModifiers_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetModificationType_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetText_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetLength_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetLinesAdded_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetLine_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetFoldLevelNow_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetFoldLevelPrev_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetMargin_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetMessage_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetWParam_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetLParam_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetListType_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetX_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetY_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetToken_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetAnnotationLinesAdded_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetUpdated_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetDragText_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetDragFlags_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, SetDragResult_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetKey_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetModifiers_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetModificationType_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetText_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetLength_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetLinesAdded_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetLine_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetFoldLevelNow_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetFoldLevelPrev_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetMargin_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetMessage_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetWParam_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetLParam_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetListType_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetX_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetY_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetToken_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetAnnotationsLinesAdded_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetUpdated_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetDragText_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetDragFlags_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetDragResult_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetShift_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetControl_gurax));
	Assign(Gurax_CreateMethod(wxStyledTextEvent, GetAlt_gurax));
}

//------------------------------------------------------------------------------
// Value_wxStyledTextEvent
//------------------------------------------------------------------------------
VType& Value_wxStyledTextEvent::vtype = VTYPE_wxStyledTextEvent;
EventValueFactoryDeriv<Value_wxStyledTextEvent> Value_wxStyledTextEvent::eventValueFactory;

String Value_wxStyledTextEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StyledTextEvent");
}

Gurax_EndModuleScope(wx)
