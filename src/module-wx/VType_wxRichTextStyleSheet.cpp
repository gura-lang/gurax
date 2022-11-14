﻿//==============================================================================
// VType_wxRichTextStyleSheet.cpp
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

${help.ComposePropertyHelp(wx.RichTextStyleSheet, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextStyleSheet, `en)}

${help.ComposeMethodHelp(wx.RichTextStyleSheet, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.RichTextStyleSheet() {block?}
Gurax_DeclareConstructorAlias(RichTextStyleSheet_gurax, "RichTextStyleSheet")
{
	Declare(VTYPE_wxRichTextStyleSheet, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.RichTextStyleSheet.
)**");
}

Gurax_ImplementConstructorEx(RichTextStyleSheet_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextStyleSheet(
		wxRichTextStyleSheet()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RichTextStyleSheet#AddCharacterStyle(def as wx.RichTextCharacterStyleDefinition)
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, AddCharacterStyle_gurax, "AddCharacterStyle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("def", VTYPE_wxRichTextCharacterStyleDefinition, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, AddCharacterStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextCharacterStyleDefinition& value_def = args_gurax.Pick<Value_wxRichTextCharacterStyleDefinition>();
	wxRichTextCharacterStyleDefinition* def = value_def.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->AddCharacterStyle(def);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextStyleSheet#AddListStyle(def as wx.RichTextListStyleDefinition)
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, AddListStyle_gurax, "AddListStyle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("def", VTYPE_wxRichTextListStyleDefinition, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, AddListStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextListStyleDefinition& value_def = args_gurax.Pick<Value_wxRichTextListStyleDefinition>();
	wxRichTextListStyleDefinition* def = value_def.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->AddListStyle(def);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextStyleSheet#AddParagraphStyle(def as wx.RichTextParagraphStyleDefinition)
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, AddParagraphStyle_gurax, "AddParagraphStyle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("def", VTYPE_wxRichTextParagraphStyleDefinition, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, AddParagraphStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextParagraphStyleDefinition& value_def = args_gurax.Pick<Value_wxRichTextParagraphStyleDefinition>();
	wxRichTextParagraphStyleDefinition* def = value_def.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->AddParagraphStyle(def);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextStyleSheet#AddStyle(def as wx.RichTextStyleDefinition)
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, AddStyle_gurax, "AddStyle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("def", VTYPE_wxRichTextStyleDefinition, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, AddStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextStyleDefinition& value_def = args_gurax.Pick<Value_wxRichTextStyleDefinition>();
	wxRichTextStyleDefinition* def = value_def.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->AddStyle(def);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextStyleSheet#DeleteStyles()
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, DeleteStyles_gurax, "DeleteStyles")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, DeleteStyles_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->DeleteStyles();
	return Gurax::Value::nil();
}

// wx.RichTextStyleSheet#FindCharacterStyle(name as String, recurse? as Bool) {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, FindCharacterStyle_gurax, "FindCharacterStyle")
{
	Declare(VTYPE_wxRichTextCharacterStyleDefinition, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("recurse", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, FindCharacterStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	bool recurse = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextCharacterStyleDefinition(
		pEntity_gurax->FindCharacterStyle(name, recurse)));
}

// wx.RichTextStyleSheet#FindListStyle(name as String, recurse? as Bool) {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, FindListStyle_gurax, "FindListStyle")
{
	Declare(VTYPE_wxRichTextListStyleDefinition, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("recurse", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, FindListStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	bool recurse = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextListStyleDefinition(
		pEntity_gurax->FindListStyle(name, recurse)));
}

// wx.RichTextStyleSheet#FindParagraphStyle(name as String, recurse? as Bool) {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, FindParagraphStyle_gurax, "FindParagraphStyle")
{
	Declare(VTYPE_wxRichTextParagraphStyleDefinition, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("recurse", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, FindParagraphStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	bool recurse = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextParagraphStyleDefinition(
		pEntity_gurax->FindParagraphStyle(name, recurse)));
}

// wx.RichTextStyleSheet#FindStyle(name as String) {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, FindStyle_gurax, "FindStyle")
{
	Declare(VTYPE_wxRichTextStyleDefinition, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, FindStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextStyleDefinition(
		pEntity_gurax->FindStyle(name)));
}

// wx.RichTextStyleSheet#GetCharacterStyle(n as Number) {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, GetCharacterStyle_gurax, "GetCharacterStyle")
{
	Declare(VTYPE_wxRichTextCharacterStyleDefinition, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, GetCharacterStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t n = args_gurax.PickNumber<size_t>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextCharacterStyleDefinition(
		pEntity_gurax->GetCharacterStyle(n)));
}

// wx.RichTextStyleSheet#GetCharacterStyleCount()
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, GetCharacterStyleCount_gurax, "GetCharacterStyleCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, GetCharacterStyleCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetCharacterStyleCount();
	return new Gurax::Value_Number(rtn);
}

// wx.RichTextStyleSheet#GetDescription()
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, GetDescription_gurax, "GetDescription")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, GetDescription_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetDescription();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.RichTextStyleSheet#GetListStyle(n as Number) {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, GetListStyle_gurax, "GetListStyle")
{
	Declare(VTYPE_wxRichTextListStyleDefinition, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, GetListStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t n = args_gurax.PickNumber<size_t>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextListStyleDefinition(
		pEntity_gurax->GetListStyle(n)));
}

// wx.RichTextStyleSheet#GetListStyleCount()
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, GetListStyleCount_gurax, "GetListStyleCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, GetListStyleCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetListStyleCount();
	return new Gurax::Value_Number(rtn);
}

// wx.RichTextStyleSheet#GetName()
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, GetName_gurax, "GetName")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, GetName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetName();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.RichTextStyleSheet#GetParagraphStyle(n as Number) {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, GetParagraphStyle_gurax, "GetParagraphStyle")
{
	Declare(VTYPE_wxRichTextParagraphStyleDefinition, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, GetParagraphStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t n = args_gurax.PickNumber<size_t>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextParagraphStyleDefinition(
		pEntity_gurax->GetParagraphStyle(n)));
}

// wx.RichTextStyleSheet#GetParagraphStyleCount()
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, GetParagraphStyleCount_gurax, "GetParagraphStyleCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, GetParagraphStyleCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetParagraphStyleCount();
	return new Gurax::Value_Number(rtn);
}

// wx.RichTextStyleSheet#RemoveCharacterStyle(def as wx.RichTextStyleDefinition, deleteStyle? as Bool)
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, RemoveCharacterStyle_gurax, "RemoveCharacterStyle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("def", VTYPE_wxRichTextStyleDefinition, ArgOccur::Once, ArgFlag::None);
	DeclareArg("deleteStyle", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, RemoveCharacterStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextStyleDefinition& value_def = args_gurax.Pick<Value_wxRichTextStyleDefinition>();
	wxRichTextStyleDefinition* def = value_def.GetEntityPtr();
	bool deleteStyle = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	bool rtn = pEntity_gurax->RemoveCharacterStyle(def, deleteStyle);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextStyleSheet#RemoveListStyle(def as wx.RichTextStyleDefinition, deleteStyle? as Bool)
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, RemoveListStyle_gurax, "RemoveListStyle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("def", VTYPE_wxRichTextStyleDefinition, ArgOccur::Once, ArgFlag::None);
	DeclareArg("deleteStyle", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, RemoveListStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextStyleDefinition& value_def = args_gurax.Pick<Value_wxRichTextStyleDefinition>();
	wxRichTextStyleDefinition* def = value_def.GetEntityPtr();
	bool deleteStyle = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	bool rtn = pEntity_gurax->RemoveListStyle(def, deleteStyle);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextStyleSheet#RemoveParagraphStyle(def as wx.RichTextStyleDefinition, deleteStyle? as Bool)
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, RemoveParagraphStyle_gurax, "RemoveParagraphStyle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("def", VTYPE_wxRichTextStyleDefinition, ArgOccur::Once, ArgFlag::None);
	DeclareArg("deleteStyle", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, RemoveParagraphStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextStyleDefinition& value_def = args_gurax.Pick<Value_wxRichTextStyleDefinition>();
	wxRichTextStyleDefinition* def = value_def.GetEntityPtr();
	bool deleteStyle = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	bool rtn = pEntity_gurax->RemoveParagraphStyle(def, deleteStyle);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextStyleSheet#RemoveStyle(def as wx.RichTextStyleDefinition, deleteStyle? as Bool)
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, RemoveStyle_gurax, "RemoveStyle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("def", VTYPE_wxRichTextStyleDefinition, ArgOccur::Once, ArgFlag::None);
	DeclareArg("deleteStyle", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, RemoveStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextStyleDefinition& value_def = args_gurax.Pick<Value_wxRichTextStyleDefinition>();
	wxRichTextStyleDefinition* def = value_def.GetEntityPtr();
	bool deleteStyle = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	bool rtn = pEntity_gurax->RemoveStyle(def, deleteStyle);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextStyleSheet#SetDescription(descr as String)
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, SetDescription_gurax, "SetDescription")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("descr", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, SetDescription_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* descr = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetDescription(descr);
	return Gurax::Value::nil();
}

// wx.RichTextStyleSheet#SetName(name as String)
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, SetName_gurax, "SetName")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, SetName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetName(name);
	return Gurax::Value::nil();
}

// wx.RichTextStyleSheet#GetProperties() {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, GetProperties_gurax, "GetProperties")
{
	Declare(VTYPE_wxRichTextProperties, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, GetProperties_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextProperties(
		pEntity_gurax->GetProperties()));
}

// wx.RichTextStyleSheet#SetProperties(props as wx.RichTextProperties)
Gurax_DeclareMethodAlias(wxRichTextStyleSheet, SetProperties_gurax, "SetProperties")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("props", VTYPE_wxRichTextProperties, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxRichTextStyleSheet, SetProperties_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextProperties& value_props = args_gurax.Pick<Value_wxRichTextProperties>();
	const wxRichTextProperties& props = value_props.GetEntity();
	// Function body
	pEntity_gurax->SetProperties(props);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRichTextStyleSheet
//------------------------------------------------------------------------------
VType_wxRichTextStyleSheet VTYPE_wxRichTextStyleSheet("RichTextStyleSheet");

void VType_wxRichTextStyleSheet::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(RichTextStyleSheet_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, AddCharacterStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, AddListStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, AddParagraphStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, AddStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, DeleteStyles_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, FindCharacterStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, FindListStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, FindParagraphStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, FindStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, GetCharacterStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, GetCharacterStyleCount_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, GetDescription_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, GetListStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, GetListStyleCount_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, GetName_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, GetParagraphStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, GetParagraphStyleCount_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, RemoveCharacterStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, RemoveListStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, RemoveParagraphStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, RemoveStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, SetDescription_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, SetName_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, GetProperties_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleSheet, SetProperties_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRichTextStyleSheet
//------------------------------------------------------------------------------
VType& Value_wxRichTextStyleSheet::vtype = VTYPE_wxRichTextStyleSheet;

String Value_wxRichTextStyleSheet::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextStyleSheet");
}

Gurax_EndModuleScope(wx)
