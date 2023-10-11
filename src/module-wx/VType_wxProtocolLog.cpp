﻿//==============================================================================
// VType_wxProtocolLog.cpp
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

${help.ComposePropertyHelp(wx.ProtocolLog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ProtocolLog, `en)}

${help.ComposeMethodHelp(wx.ProtocolLog, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ProtocolLog, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ProtocolLog, `ja)}

${help.ComposeMethodHelp(wx.ProtocolLog, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ProtocolLog(traceMask as String) {block?}
Gurax_DeclareConstructorAlias(ProtocolLog_gurax, "ProtocolLog")
{
	Declare(VTYPE_wxProtocolLog, Flag::None);
	DeclareArg("traceMask", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(ProtocolLog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString traceMask(args_gurax.PickString());
	// Function body
	auto pEntity_gurax = new wxProtocolLog(traceMask);
	RefPtr<Value_wxProtocolLog> pValue_gurax(new Value_wxProtocolLog(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ProtocolLog#LogRequest(str as String)
Gurax_DeclareMethodAlias(wxProtocolLog, LogRequest_gurax, "LogRequest")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxProtocolLog, LogRequest_gurax, processor_gurax, argument_gurax)
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

// wx.ProtocolLog#LogResponse(str as String)
Gurax_DeclareMethodAlias(wxProtocolLog, LogResponse_gurax, "LogResponse")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxProtocolLog, LogResponse_gurax, processor_gurax, argument_gurax)
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
// VType_wxProtocolLog
//------------------------------------------------------------------------------
VType_wxProtocolLog VTYPE_wxProtocolLog("ProtocolLog");

void VType_wxProtocolLog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(ProtocolLog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxProtocolLog, LogRequest_gurax));
	Assign(Gurax_CreateMethod(wxProtocolLog, LogResponse_gurax));
}

//------------------------------------------------------------------------------
// Value_wxProtocolLog
//------------------------------------------------------------------------------
VType& Value_wxProtocolLog::vtype = VTYPE_wxProtocolLog;

String Value_wxProtocolLog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ProtocolLog");
}

Gurax_EndModuleScope(wx)
