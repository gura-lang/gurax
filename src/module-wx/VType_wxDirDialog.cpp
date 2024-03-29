﻿//==============================================================================
// VType_wxDirDialog.cpp
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

${help.ComposePropertyHelp(wx.DirDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DirDialog, `en)}

${help.ComposeMethodHelp(wx.DirDialog, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.DirDialog, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.DirDialog, `ja)}

${help.ComposeMethodHelp(wx.DirDialog, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.DirDialog(parent:nil as wx.Window, message? as String, defaultPath? as String, style? as Number, pos? as wx.Point, size? as wx.Size, name? as String) {block?}
Gurax_DeclareConstructorAlias(DirDialog_gurax, "DirDialog")
{
	Declare(VTYPE_wxDirDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("message", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("defaultPath", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(DirDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	bool message_validFlag = args_gurax.IsValid();
	wxString message = message_validFlag? wxString(args_gurax.PickString()) : wxDirSelectorPromptStr;
	bool defaultPath_validFlag = args_gurax.IsValid();
	wxString defaultPath = defaultPath_validFlag? wxString(args_gurax.PickString()) : "";
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDD_DEFAULT_STYLE;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : wxDirDialogNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxDirDialog::EntityT(parent, message, defaultPath, style, pos, size, name);
	RefPtr<Value_wxDirDialog> pValue_gurax(new Value_wxDirDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DirDialog#GetMessage()
Gurax_DeclareMethodAlias(wxDirDialog, GetMessage_gurax, "GetMessage")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxDirDialog, GetMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetMessage();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.DirDialog#GetPath()
Gurax_DeclareMethodAlias(wxDirDialog, GetPath_gurax, "GetPath")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxDirDialog, GetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetPath();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.DirDialog#SetMessage(message as String)
Gurax_DeclareMethodAlias(wxDirDialog, SetMessage_gurax, "SetMessage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxDirDialog, SetMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString message(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetMessage(message);
	return Gurax::Value::nil();
}

// wx.DirDialog#SetPath(path as String)
Gurax_DeclareMethodAlias(wxDirDialog, SetPath_gurax, "SetPath")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxDirDialog, SetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString path(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetPath(path);
	return Gurax::Value::nil();
}

// wx.DirDialog#ShowModal()
Gurax_DeclareMethodAlias(wxDirDialog, ShowModal_gurax, "ShowModal")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxDirDialog, ShowModal_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->ShowModal();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDirDialog
//------------------------------------------------------------------------------
VType_wxDirDialog VTYPE_wxDirDialog("DirDialog");

void VType_wxDirDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(DirDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDirDialog, GetMessage_gurax));
	Assign(Gurax_CreateMethod(wxDirDialog, GetPath_gurax));
	Assign(Gurax_CreateMethod(wxDirDialog, SetMessage_gurax));
	Assign(Gurax_CreateMethod(wxDirDialog, SetPath_gurax));
	Assign(Gurax_CreateMethod(wxDirDialog, ShowModal_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDirDialog
//------------------------------------------------------------------------------
VType& Value_wxDirDialog::vtype = VTYPE_wxDirDialog;

String Value_wxDirDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DirDialog");
}

//------------------------------------------------------------------------------
// Value_wxDirDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
