﻿//==============================================================================
// VType_wxFileSystemWatcherEvent.cpp
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

${help.ComposePropertyHelp(wx.FileSystemWatcherEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FileSystemWatcherEvent, `en)}

${help.ComposeMethodHelp(wx.FileSystemWatcherEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FileSystemWatcherEvent#GetPath() {block?}
Gurax_DeclareMethodAlias(wxFileSystemWatcherEvent, GetPath_gurax, "GetPath")
{
	Declare(VTYPE_wxFileName, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileSystemWatcherEvent, GetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFileName(
		pEntity_gurax->GetPath()));
}

// wx.FileSystemWatcherEvent#GetNewPath() {block?}
Gurax_DeclareMethodAlias(wxFileSystemWatcherEvent, GetNewPath_gurax, "GetNewPath")
{
	Declare(VTYPE_wxFileName, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileSystemWatcherEvent, GetNewPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFileName(
		pEntity_gurax->GetNewPath()));
}

// wx.FileSystemWatcherEvent#GetChangeType()
Gurax_DeclareMethodAlias(wxFileSystemWatcherEvent, GetChangeType_gurax, "GetChangeType")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileSystemWatcherEvent, GetChangeType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetChangeType();
	return new Gurax::Value_Number(rtn);
}

// wx.FileSystemWatcherEvent#IsError()
Gurax_DeclareMethodAlias(wxFileSystemWatcherEvent, IsError_gurax, "IsError")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileSystemWatcherEvent, IsError_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsError();
	return new Gurax::Value_Bool(rtn);
}

// wx.FileSystemWatcherEvent#GetErrorDescription()
Gurax_DeclareMethodAlias(wxFileSystemWatcherEvent, GetErrorDescription_gurax, "GetErrorDescription")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileSystemWatcherEvent, GetErrorDescription_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetErrorDescription();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileSystemWatcherEvent#GetWarningType()
Gurax_DeclareMethodAlias(wxFileSystemWatcherEvent, GetWarningType_gurax, "GetWarningType")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileSystemWatcherEvent, GetWarningType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxFSWWarningType rtn = pEntity_gurax->GetWarningType();
	return new Gurax::Value_Number(rtn);
}

// wx.FileSystemWatcherEvent#ToString()
Gurax_DeclareMethodAlias(wxFileSystemWatcherEvent, ToString_gurax, "ToString")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileSystemWatcherEvent, ToString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->ToString();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFileSystemWatcherEvent
//------------------------------------------------------------------------------
VType_wxFileSystemWatcherEvent VTYPE_wxFileSystemWatcherEvent("FileSystemWatcherEvent");

void VType_wxFileSystemWatcherEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFileSystemWatcherEvent, GetPath_gurax));
	Assign(Gurax_CreateMethod(wxFileSystemWatcherEvent, GetNewPath_gurax));
	Assign(Gurax_CreateMethod(wxFileSystemWatcherEvent, GetChangeType_gurax));
	Assign(Gurax_CreateMethod(wxFileSystemWatcherEvent, IsError_gurax));
	Assign(Gurax_CreateMethod(wxFileSystemWatcherEvent, GetErrorDescription_gurax));
	Assign(Gurax_CreateMethod(wxFileSystemWatcherEvent, GetWarningType_gurax));
	Assign(Gurax_CreateMethod(wxFileSystemWatcherEvent, ToString_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFileSystemWatcherEvent
//------------------------------------------------------------------------------
VType& Value_wxFileSystemWatcherEvent::vtype = VTYPE_wxFileSystemWatcherEvent;
EventValueFactoryDeriv<Value_wxFileSystemWatcherEvent> Value_wxFileSystemWatcherEvent::eventValueFactory;

String Value_wxFileSystemWatcherEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FileSystemWatcherEvent");
}

Gurax_EndModuleScope(wx)
