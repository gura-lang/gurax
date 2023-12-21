﻿//==============================================================================
// VType_wxTextEntry.cpp
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

${help.ComposePropertyHelp(wx.TextEntry, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.TextEntry, `en)}

${help.ComposeMethodHelp(wx.TextEntry, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.TextEntry, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.TextEntry, `ja)}

${help.ComposeMethodHelp(wx.TextEntry, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.TextEntry#AppendText(text as String)
Gurax_DeclareMethodAlias(wxTextEntry, AppendText_gurax, "AppendText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, AppendText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString text(args_gurax.PickString());
	// Function body
	pEntity_gurax->AppendText(text);
	return Gurax::Value::nil();
}

// wx.TextEntry#AutoComplete(choices[] as String)
Gurax_DeclareMethodAlias(wxTextEntry, AutoComplete_gurax, "AutoComplete")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("choices", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementMethodEx(wxTextEntry, AutoComplete_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxArrayString choices = Util::CreateArrayString(args_gurax.PickList());
	// Function body
	bool rtn = pEntity_gurax->AutoComplete(choices);
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntry#AutoCompleteFileNames()
Gurax_DeclareMethodAlias(wxTextEntry, AutoCompleteFileNames_gurax, "AutoCompleteFileNames")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, AutoCompleteFileNames_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->AutoCompleteFileNames();
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntry#AutoCompleteDirectories()
Gurax_DeclareMethodAlias(wxTextEntry, AutoCompleteDirectories_gurax, "AutoCompleteDirectories")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, AutoCompleteDirectories_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->AutoCompleteDirectories();
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntry#CanCopy()
Gurax_DeclareMethodAlias(wxTextEntry, CanCopy_gurax, "CanCopy")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, CanCopy_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanCopy();
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntry#CanCut()
Gurax_DeclareMethodAlias(wxTextEntry, CanCut_gurax, "CanCut")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, CanCut_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanCut();
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntry#CanPaste()
Gurax_DeclareMethodAlias(wxTextEntry, CanPaste_gurax, "CanPaste")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, CanPaste_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanPaste();
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntry#CanRedo()
Gurax_DeclareMethodAlias(wxTextEntry, CanRedo_gurax, "CanRedo")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, CanRedo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanRedo();
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntry#CanUndo()
Gurax_DeclareMethodAlias(wxTextEntry, CanUndo_gurax, "CanUndo")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, CanUndo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanUndo();
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntry#ChangeValue(value as String)
Gurax_DeclareMethodAlias(wxTextEntry, ChangeValue_gurax, "ChangeValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, ChangeValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString value(args_gurax.PickString());
	// Function body
	pEntity_gurax->ChangeValue(value);
	return Gurax::Value::nil();
}

// wx.TextEntry#Clear()
Gurax_DeclareMethodAlias(wxTextEntry, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Clear();
	return Gurax::Value::nil();
}

// wx.TextEntry#Copy()
Gurax_DeclareMethodAlias(wxTextEntry, Copy_gurax, "Copy")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, Copy_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Copy();
	return Gurax::Value::nil();
}

// wx.TextEntry#Cut()
Gurax_DeclareMethodAlias(wxTextEntry, Cut_gurax, "Cut")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, Cut_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Cut();
	return Gurax::Value::nil();
}

// wx.TextEntry#GetInsertionPoint()
Gurax_DeclareMethodAlias(wxTextEntry, GetInsertionPoint_gurax, "GetInsertionPoint")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, GetInsertionPoint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetInsertionPoint();
	return new Gurax::Value_Number(rtn);
}

// wx.TextEntry#GetLastPosition()
Gurax_DeclareMethodAlias(wxTextEntry, GetLastPosition_gurax, "GetLastPosition")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, GetLastPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetLastPosition();
	return new Gurax::Value_Number(rtn);
}

// wx.TextEntry#GetRange(from as Number, to as Number)
Gurax_DeclareMethodAlias(wxTextEntry, GetRange_gurax, "GetRange")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, GetRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long from = args_gurax.PickNumber<long>();
	long to = args_gurax.PickNumber<long>();
	// Function body
	wxString rtn = pEntity_gurax->GetRange(from, to);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.TextEntry#GetSelection(&from:nilRef as Number, &to:nilRef as Number)
Gurax_DeclareMethodAlias(wxTextEntry, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementMethodEx(wxTextEntry, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Referencer> from(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> to(args_gurax.PickReferencer().Reference());
	// Function body
	long from_, to_;
	pEntity_gurax->GetSelection(&from_, &to_);
	from->SetValue(new Value_Number(from_));
	to->SetValue(new Value_Number(to_));
	return Value::nil();
}

// wx.TextEntry#GetStringSelection()
Gurax_DeclareMethodAlias(wxTextEntry, GetStringSelection_gurax, "GetStringSelection")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, GetStringSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetStringSelection();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.TextEntry#GetValue()
Gurax_DeclareMethodAlias(wxTextEntry, GetValue_gurax, "GetValue")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, GetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetValue();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.TextEntry#IsEditable()
Gurax_DeclareMethodAlias(wxTextEntry, IsEditable_gurax, "IsEditable")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, IsEditable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsEditable();
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntry#IsEmpty()
Gurax_DeclareMethodAlias(wxTextEntry, IsEmpty_gurax, "IsEmpty")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, IsEmpty_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsEmpty();
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntry#Paste()
Gurax_DeclareMethodAlias(wxTextEntry, Paste_gurax, "Paste")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, Paste_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Paste();
	return Gurax::Value::nil();
}

// wx.TextEntry#Redo()
Gurax_DeclareMethodAlias(wxTextEntry, Redo_gurax, "Redo")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, Redo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Redo();
	return Gurax::Value::nil();
}

// wx.TextEntry#Remove(from as Number, to as Number)
Gurax_DeclareMethodAlias(wxTextEntry, Remove_gurax, "Remove")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, Remove_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long from = args_gurax.PickNumber<long>();
	long to = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->Remove(from, to);
	return Gurax::Value::nil();
}

// wx.TextEntry#Replace(from as Number, to as Number, value as String)
Gurax_DeclareMethodAlias(wxTextEntry, Replace_gurax, "Replace")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, Replace_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long from = args_gurax.PickNumber<long>();
	long to = args_gurax.PickNumber<long>();
	wxString value(args_gurax.PickString());
	// Function body
	pEntity_gurax->Replace(from, to, value);
	return Gurax::Value::nil();
}

// wx.TextEntry#SetEditable(editable as Bool)
Gurax_DeclareMethodAlias(wxTextEntry, SetEditable_gurax, "SetEditable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("editable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, SetEditable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool editable = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetEditable(editable);
	return Gurax::Value::nil();
}

// wx.TextEntry#SetInsertionPoint(pos as Number)
Gurax_DeclareMethodAlias(wxTextEntry, SetInsertionPoint_gurax, "SetInsertionPoint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, SetInsertionPoint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long pos = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetInsertionPoint(pos);
	return Gurax::Value::nil();
}

// wx.TextEntry#SetInsertionPointEnd()
Gurax_DeclareMethodAlias(wxTextEntry, SetInsertionPointEnd_gurax, "SetInsertionPointEnd")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, SetInsertionPointEnd_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->SetInsertionPointEnd();
	return Gurax::Value::nil();
}

// wx.TextEntry#SetMaxLength(len as Number)
Gurax_DeclareMethodAlias(wxTextEntry, SetMaxLength_gurax, "SetMaxLength")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, SetMaxLength_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned long len = args_gurax.PickNumber<unsigned long>();
	// Function body
	pEntity_gurax->SetMaxLength(len);
	return Gurax::Value::nil();
}

// wx.TextEntry#SetSelection(from as Number, to as Number)
Gurax_DeclareMethodAlias(wxTextEntry, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, SetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long from = args_gurax.PickNumber<long>();
	long to = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetSelection(from, to);
	return Gurax::Value::nil();
}

// wx.TextEntry#SelectAll()
Gurax_DeclareMethodAlias(wxTextEntry, SelectAll_gurax, "SelectAll")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, SelectAll_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->SelectAll();
	return Gurax::Value::nil();
}

// wx.TextEntry#SelectNone()
Gurax_DeclareMethodAlias(wxTextEntry, SelectNone_gurax, "SelectNone")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, SelectNone_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->SelectNone();
	return Gurax::Value::nil();
}

// wx.TextEntry#SetHint(hint as String)
Gurax_DeclareMethodAlias(wxTextEntry, SetHint_gurax, "SetHint")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("hint", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, SetHint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString hint(args_gurax.PickString());
	// Function body
	bool rtn = pEntity_gurax->SetHint(hint);
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntry#GetHint()
Gurax_DeclareMethodAlias(wxTextEntry, GetHint_gurax, "GetHint")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, GetHint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetHint();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.TextEntry#GetMargins() {block?}
Gurax_DeclareMethodAlias(wxTextEntry, GetMargins_gurax, "GetMargins")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxTextEntry, GetMargins_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(pEntity_gurax->GetMargins()));
}

// wx.TextEntry#SetValue(value as String)
Gurax_DeclareMethodAlias(wxTextEntry, SetValue_gurax, "SetValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, SetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString value(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetValue(value);
	return Gurax::Value::nil();
}

// wx.TextEntry#Undo()
Gurax_DeclareMethodAlias(wxTextEntry, Undo_gurax, "Undo")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, Undo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Undo();
	return Gurax::Value::nil();
}

// wx.TextEntry#WriteText(text as String)
Gurax_DeclareMethodAlias(wxTextEntry, WriteText_gurax, "WriteText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, WriteText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString text(args_gurax.PickString());
	// Function body
	pEntity_gurax->WriteText(text);
	return Gurax::Value::nil();
}

// wx.TextEntry#SetMargins(args* as Any)
Gurax_DeclareMethodAlias(wxTextEntry, SetMargins_gurax, "SetMargins")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntry, SetMargins_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// SetMargins(pt as const_Point_r) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("pt", VTYPE_wxPoint);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxPoint& pt = args.Pick<Value_wxPoint>().GetEntity();
		bool rtn = pEntity_gurax->SetMargins(pt);
		return new Value_Bool(rtn);
	} while (0);
	Error::ClearIssuedFlag();
	// SetMargins(left as Coord, top as Coord = -1) as bool
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("left", VTYPE_Number);
			pDeclCallable->DeclareArg("top", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxCoord left = args.PickNumber<wxCoord>();
		wxCoord top = args.IsValid()? args.PickNumber<wxCoord>() : -1;
		bool rtn = pEntity_gurax->SetMargins(left, top);
		return new Value_Bool(rtn);
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxTextEntry
//------------------------------------------------------------------------------
VType_wxTextEntry VTYPE_wxTextEntry("TextEntry");

void VType_wxTextEntry::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxTextEntry, AppendText_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, AutoComplete_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, AutoCompleteFileNames_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, AutoCompleteDirectories_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, CanCopy_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, CanCut_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, CanPaste_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, CanRedo_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, CanUndo_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, ChangeValue_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, Clear_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, Copy_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, Cut_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, GetInsertionPoint_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, GetLastPosition_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, GetRange_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, GetStringSelection_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, GetValue_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, IsEditable_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, IsEmpty_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, Paste_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, Redo_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, Remove_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, Replace_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, SetEditable_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, SetInsertionPoint_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, SetInsertionPointEnd_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, SetMaxLength_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, SelectAll_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, SelectNone_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, SetHint_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, GetHint_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, GetMargins_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, SetValue_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, Undo_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, WriteText_gurax));
	Assign(Gurax_CreateMethod(wxTextEntry, SetMargins_gurax));
}

//------------------------------------------------------------------------------
// Value_wxTextEntry
//------------------------------------------------------------------------------
VType& Value_wxTextEntry::vtype = VTYPE_wxTextEntry;

String Value_wxTextEntry::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.TextEntry");
}

Gurax_EndModuleScope(wx)
