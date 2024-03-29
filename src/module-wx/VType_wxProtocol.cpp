﻿//==============================================================================
// VType_wxProtocol.cpp
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

${help.ComposePropertyHelp(wx.Protocol, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Protocol, `en)}

${help.ComposeMethodHelp(wx.Protocol, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.Protocol, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.Protocol, `ja)}

${help.ComposeMethodHelp(wx.Protocol, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Protocol#Abort()
Gurax_DeclareMethodAlias(wxProtocol, Abort_gurax, "Abort")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxProtocol, Abort_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Abort();
	return new Gurax::Value_Bool(rtn);
}

// wx.Protocol#GetContentType()
Gurax_DeclareMethodAlias(wxProtocol, GetContentType_gurax, "GetContentType")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxProtocol, GetContentType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetContentType();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.Protocol#GetError()
Gurax_DeclareMethodAlias(wxProtocol, GetError_gurax, "GetError")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxProtocol, GetError_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxProtocolError rtn = pEntity_gurax->GetError();
	return new Gurax::Value_Number(rtn);
}

// wx.Protocol#GetInputStream(path as String) {block?}
Gurax_DeclareMethodAlias(wxProtocol, GetInputStream_gurax, "GetInputStream")
{
	Declare(VTYPE_wxInputStream, Flag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxProtocol, GetInputStream_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString path(args_gurax.PickString());
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxInputStream(pEntity_gurax->GetInputStream(path)));
}

// wx.Protocol#Reconnect()
Gurax_DeclareMethodAlias(wxProtocol, Reconnect_gurax, "Reconnect")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxProtocol, Reconnect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Reconnect();
	return new Gurax::Value_Bool(rtn);
}

// wx.Protocol#SetPassword(user as String)
Gurax_DeclareMethodAlias(wxProtocol, SetPassword_gurax, "SetPassword")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("user", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxProtocol, SetPassword_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString user(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetPassword(user);
	return Gurax::Value::nil();
}

// wx.Protocol#SetUser(user as String)
Gurax_DeclareMethodAlias(wxProtocol, SetUser_gurax, "SetUser")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("user", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxProtocol, SetUser_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString user(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetUser(user);
	return Gurax::Value::nil();
}

// wx.Protocol#SetDefaultTimeout(Value as Number)
Gurax_DeclareMethodAlias(wxProtocol, SetDefaultTimeout_gurax, "SetDefaultTimeout")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("Value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxProtocol, SetDefaultTimeout_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxUint32 Value = args_gurax.PickNumber<wxUint32>();
	// Function body
	pEntity_gurax->SetDefaultTimeout(Value);
	return Gurax::Value::nil();
}

// wx.Protocol#SetLog(log as wx.ProtocolLog)
Gurax_DeclareMethodAlias(wxProtocol, SetLog_gurax, "SetLog")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("log", VTYPE_wxProtocolLog, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxProtocol, SetLog_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxProtocolLog& value_log = args_gurax.Pick<Value_wxProtocolLog>();
	wxProtocolLog* log = value_log.GetEntityPtr();
	// Function body
	pEntity_gurax->SetLog(log);
	return Gurax::Value::nil();
}

// wx.Protocol#GetLog() {block?}
Gurax_DeclareMethodAlias(wxProtocol, GetLog_gurax, "GetLog")
{
	Declare(VTYPE_wxProtocolLog, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxProtocol, GetLog_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxProtocolLog(pEntity_gurax->GetLog()));
}

// wx.Protocol#DetachLog() {block?}
Gurax_DeclareMethodAlias(wxProtocol, DetachLog_gurax, "DetachLog")
{
	Declare(VTYPE_wxProtocolLog, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxProtocol, DetachLog_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxProtocolLog(pEntity_gurax->DetachLog()));
}

// wx.Protocol#LogRequest(str as String)
Gurax_DeclareMethodAlias(wxProtocol, LogRequest_gurax, "LogRequest")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxProtocol, LogRequest_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString str(args_gurax.PickString());
	// Function body
	pEntity_gurax->LogRequest(str);
	return Gurax::Value::nil();
}

// wx.Protocol#LogResponse(str as String)
Gurax_DeclareMethodAlias(wxProtocol, LogResponse_gurax, "LogResponse")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxProtocol, LogResponse_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString str(args_gurax.PickString());
	// Function body
	pEntity_gurax->LogResponse(str);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxProtocol
//------------------------------------------------------------------------------
VType_wxProtocol VTYPE_wxProtocol("Protocol");

void VType_wxProtocol::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxSocketClient, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxProtocol, Abort_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, GetContentType_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, GetError_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, GetInputStream_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, Reconnect_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, SetPassword_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, SetUser_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, SetDefaultTimeout_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, SetLog_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, GetLog_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, DetachLog_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, LogRequest_gurax));
	Assign(Gurax_CreateMethod(wxProtocol, LogResponse_gurax));
}

//------------------------------------------------------------------------------
// Value_wxProtocol
//------------------------------------------------------------------------------
VType& Value_wxProtocol::vtype = VTYPE_wxProtocol;

String Value_wxProtocol::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Protocol");
}

Gurax_EndModuleScope(wx)
