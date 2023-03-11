﻿//==============================================================================
// VType_wxFileCtrlEvent.cpp
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

${help.ComposePropertyHelp(wx.FileCtrlEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FileCtrlEvent, `en)}

${help.ComposeMethodHelp(wx.FileCtrlEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.FileCtrlEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.FileCtrlEvent, `ja)}

${help.ComposeMethodHelp(wx.FileCtrlEvent, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FileCtrlEvent#GetDirectory()
Gurax_DeclareMethodAlias(wxFileCtrlEvent, GetDirectory_gurax, "GetDirectory")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxFileCtrlEvent, GetDirectory_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetDirectory();
	//return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.FileCtrlEvent#GetFile()
Gurax_DeclareMethodAlias(wxFileCtrlEvent, GetFile_gurax, "GetFile")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxFileCtrlEvent, GetFile_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetFile();
	//return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.FileCtrlEvent#GetFiles()
Gurax_DeclareMethodAlias(wxFileCtrlEvent, GetFiles_gurax, "GetFiles")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxFileCtrlEvent, GetFiles_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxArrayString rtn = pEntity_gurax->GetFiles();
	return Util::CreateList(rtn);
}

// wx.FileCtrlEvent#GetFilterIndex()
Gurax_DeclareMethodAlias(wxFileCtrlEvent, GetFilterIndex_gurax, "GetFilterIndex")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxFileCtrlEvent, GetFilterIndex_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFilterIndex();
	return new Gurax::Value_Number(rtn);
}

// wx.FileCtrlEvent#SetFiles(files[] as String)
Gurax_DeclareMethodAlias(wxFileCtrlEvent, SetFiles_gurax, "SetFiles")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("files", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementMethodEx(wxFileCtrlEvent, SetFiles_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxArrayString files = Util::CreateArrayString(args_gurax.PickList());
	// Function body
	pEntity_gurax->SetFiles(files);
	return Gurax::Value::nil();
}

// wx.FileCtrlEvent#SetDirectory(directory as String)
Gurax_DeclareMethodAlias(wxFileCtrlEvent, SetDirectory_gurax, "SetDirectory")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("directory", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFileCtrlEvent, SetDirectory_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* directory = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetDirectory(directory);
	return Gurax::Value::nil();
}

// wx.FileCtrlEvent#SetFilterIndex(index as Number)
Gurax_DeclareMethodAlias(wxFileCtrlEvent, SetFilterIndex_gurax, "SetFilterIndex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFileCtrlEvent, SetFilterIndex_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetFilterIndex(index);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFileCtrlEvent
//------------------------------------------------------------------------------
VType_wxFileCtrlEvent VTYPE_wxFileCtrlEvent("FileCtrlEvent");

void VType_wxFileCtrlEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFileCtrlEvent, GetDirectory_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrlEvent, GetFile_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrlEvent, GetFiles_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrlEvent, GetFilterIndex_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrlEvent, SetFiles_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrlEvent, SetDirectory_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrlEvent, SetFilterIndex_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFileCtrlEvent
//------------------------------------------------------------------------------
VType& Value_wxFileCtrlEvent::vtype = VTYPE_wxFileCtrlEvent;
EventValueFactoryDeriv<Value_wxFileCtrlEvent> Value_wxFileCtrlEvent::eventValueFactory;

String Value_wxFileCtrlEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FileCtrlEvent");
}

Gurax_EndModuleScope(wx)
