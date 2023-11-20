﻿//==============================================================================
// VType_wxHtmlHelpData.cpp
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

${help.ComposePropertyHelp(wx.HtmlHelpData, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HtmlHelpData, `en)}

${help.ComposeMethodHelp(wx.HtmlHelpData, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.HtmlHelpData, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.HtmlHelpData, `ja)}

${help.ComposeMethodHelp(wx.HtmlHelpData, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.HtmlHelpData() {block?}
Gurax_DeclareConstructorAlias(HtmlHelpData_gurax, "HtmlHelpData")
{
	Declare(VTYPE_wxHtmlHelpData, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(HtmlHelpData_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new wxHtmlHelpData();
	RefPtr<Value_wxHtmlHelpData> pValue_gurax(new Value_wxHtmlHelpData(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HtmlHelpData#AddBook(book_url as String)
Gurax_DeclareMethodAlias(wxHtmlHelpData, AddBook_gurax, "AddBook")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("book_url", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHtmlHelpData, AddBook_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString book_url(args_gurax.PickString());
	// Function body
	bool rtn = pEntity_gurax->AddBook(book_url);
	return new Gurax::Value_Bool(rtn);
}

// wx.HtmlHelpData#FindPageById(id as Number)
Gurax_DeclareMethodAlias(wxHtmlHelpData, FindPageById_gurax, "FindPageById")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHtmlHelpData, FindPageById_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	// Function body
	wxString rtn = pEntity_gurax->FindPageById(id);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.HtmlHelpData#FindPageByName(page as String)
Gurax_DeclareMethodAlias(wxHtmlHelpData, FindPageByName_gurax, "FindPageByName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("page", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHtmlHelpData, FindPageByName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString page(args_gurax.PickString());
	// Function body
	wxString rtn = pEntity_gurax->FindPageByName(page);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.HtmlHelpData#GetBookRecArray() {block?}
Gurax_DeclareMethodAlias(wxHtmlHelpData, GetBookRecArray_gurax, "GetBookRecArray")
{
	Declare(VTYPE_wxHtmlBookRecArray, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxHtmlHelpData, GetBookRecArray_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxHtmlBookRecArray(pEntity_gurax->GetBookRecArray()));
}

// wx.HtmlHelpData#GetContentsArray() {block?}
Gurax_DeclareMethodAlias(wxHtmlHelpData, GetContentsArray_gurax, "GetContentsArray")
{
	Declare(VTYPE_wxHtmlHelpDataItems, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxHtmlHelpData, GetContentsArray_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxHtmlHelpDataItems(pEntity_gurax->GetContentsArray()));
}

// wx.HtmlHelpData#GetIndexArray() {block?}
Gurax_DeclareMethodAlias(wxHtmlHelpData, GetIndexArray_gurax, "GetIndexArray")
{
	Declare(VTYPE_wxHtmlHelpDataItems, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxHtmlHelpData, GetIndexArray_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxHtmlHelpDataItems(pEntity_gurax->GetIndexArray()));
}

// wx.HtmlHelpData#SetTempDir(path as String)
Gurax_DeclareMethodAlias(wxHtmlHelpData, SetTempDir_gurax, "SetTempDir")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHtmlHelpData, SetTempDir_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString path(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetTempDir(path);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHtmlHelpData
//------------------------------------------------------------------------------
VType_wxHtmlHelpData VTYPE_wxHtmlHelpData("HtmlHelpData");

void VType_wxHtmlHelpData::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(HtmlHelpData_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHtmlHelpData, AddBook_gurax));
	Assign(Gurax_CreateMethod(wxHtmlHelpData, FindPageById_gurax));
	Assign(Gurax_CreateMethod(wxHtmlHelpData, FindPageByName_gurax));
	Assign(Gurax_CreateMethod(wxHtmlHelpData, GetBookRecArray_gurax));
	Assign(Gurax_CreateMethod(wxHtmlHelpData, GetContentsArray_gurax));
	Assign(Gurax_CreateMethod(wxHtmlHelpData, GetIndexArray_gurax));
	Assign(Gurax_CreateMethod(wxHtmlHelpData, SetTempDir_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHtmlHelpData
//------------------------------------------------------------------------------
VType& Value_wxHtmlHelpData::vtype = VTYPE_wxHtmlHelpData;

String Value_wxHtmlHelpData::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlHelpData");
}

Gurax_EndModuleScope(wx)
