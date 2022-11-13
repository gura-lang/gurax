﻿//==============================================================================
// VType_wxLog.cpp
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

${help.ComposePropertyHelp(wx.Log, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Log, `en)}

${help.ComposeMethodHelp(wx.Log, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Log.AddTraceMask(mask as String)
Gurax_DeclareClassMethodAlias(wxLog, AddTraceMask_gurax, "AddTraceMask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, AddTraceMask_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* mask = args_gurax.PickString();
	// Function body
	wxLog::AddTraceMask(mask);
	return Gurax::Value::nil();
}

// wx.Log.ClearTraceMasks()
Gurax_DeclareClassMethodAlias(wxLog, ClearTraceMasks_gurax, "ClearTraceMasks")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, ClearTraceMasks_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxLog::ClearTraceMasks();
	return Gurax::Value::nil();
}

// wx.Log.GetTraceMasks()
Gurax_DeclareClassMethodAlias(wxLog, GetTraceMasks_gurax, "GetTraceMasks")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, GetTraceMasks_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxArrayString rtn = wxLog::GetTraceMasks();
	return Util::CreateList(rtn);
}

// wx.Log.IsAllowedTraceMask(mask as String)
Gurax_DeclareClassMethodAlias(wxLog, IsAllowedTraceMask_gurax, "IsAllowedTraceMask")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("mask", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, IsAllowedTraceMask_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* mask = args_gurax.PickString();
	// Function body
	bool rtn = wxLog::IsAllowedTraceMask(mask);
	return new Gurax::Value_Bool(rtn);
}

// wx.Log.RemoveTraceMask(mask as String)
Gurax_DeclareClassMethodAlias(wxLog, RemoveTraceMask_gurax, "RemoveTraceMask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, RemoveTraceMask_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* mask = args_gurax.PickString();
	// Function body
	wxLog::RemoveTraceMask(mask);
	return Gurax::Value::nil();
}

// wx.Log.DontCreateOnDemand()
Gurax_DeclareClassMethodAlias(wxLog, DontCreateOnDemand_gurax, "DontCreateOnDemand")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, DontCreateOnDemand_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxLog::DontCreateOnDemand();
	return Gurax::Value::nil();
}

// wx.Log.GetActiveTarget() {block?}
Gurax_DeclareClassMethodAlias(wxLog, GetActiveTarget_gurax, "GetActiveTarget")
{
	Declare(VTYPE_wxLog, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, GetActiveTarget_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxLog(
		wxLog::GetActiveTarget()));
}

// wx.Log.SetActiveTarget(logtarget as wx.Log) {block?}
Gurax_DeclareClassMethodAlias(wxLog, SetActiveTarget_gurax, "SetActiveTarget")
{
	Declare(VTYPE_wxLog, Flag::None);
	DeclareArg("logtarget", VTYPE_wxLog, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, SetActiveTarget_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxLog& value_logtarget = args_gurax.Pick<Value_wxLog>();
	wxLog* logtarget = value_logtarget.GetEntityPtr();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxLog(
		wxLog::SetActiveTarget(logtarget)));
}

// wx.Log.SetThreadActiveTarget(logger as wx.Log) {block?}
Gurax_DeclareClassMethodAlias(wxLog, SetThreadActiveTarget_gurax, "SetThreadActiveTarget")
{
	Declare(VTYPE_wxLog, Flag::None);
	DeclareArg("logger", VTYPE_wxLog, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, SetThreadActiveTarget_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxLog& value_logger = args_gurax.Pick<Value_wxLog>();
	wxLog* logger = value_logger.GetEntityPtr();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxLog(
		wxLog::SetThreadActiveTarget(logger)));
}

// wx.Log.FlushActive()
Gurax_DeclareClassMethodAlias(wxLog, FlushActive_gurax, "FlushActive")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, FlushActive_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxLog::FlushActive();
	return Gurax::Value::nil();
}

// wx.Log.Resume()
Gurax_DeclareClassMethodAlias(wxLog, Resume_gurax, "Resume")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, Resume_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxLog::Resume();
	return Gurax::Value::nil();
}

// wx.Log.Suspend()
Gurax_DeclareClassMethodAlias(wxLog, Suspend_gurax, "Suspend")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, Suspend_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxLog::Suspend();
	return Gurax::Value::nil();
}

// wx.Log.GetLogLevel()
Gurax_DeclareClassMethodAlias(wxLog, GetLogLevel_gurax, "GetLogLevel")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, GetLogLevel_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxLogLevel rtn = wxLog::GetLogLevel();
	return new Gurax::Value_Number(rtn);
}

// wx.Log.IsLevelEnabled(level as Number, component as String)
Gurax_DeclareClassMethodAlias(wxLog, IsLevelEnabled_gurax, "IsLevelEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("component", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, IsLevelEnabled_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxLogLevel level = args_gurax.PickNumber<wxLogLevel>();
	const char* component = args_gurax.PickString();
	// Function body
	bool rtn = wxLog::IsLevelEnabled(level, component);
	return new Gurax::Value_Bool(rtn);
}

// wx.Log.SetComponentLevel(component as String, level as Number)
Gurax_DeclareClassMethodAlias(wxLog, SetComponentLevel_gurax, "SetComponentLevel")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("component", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, SetComponentLevel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* component = args_gurax.PickString();
	wxLogLevel level = args_gurax.PickNumber<wxLogLevel>();
	// Function body
	wxLog::SetComponentLevel(component, level);
	return Gurax::Value::nil();
}

// wx.Log.SetLogLevel(logLevel as Number)
Gurax_DeclareClassMethodAlias(wxLog, SetLogLevel_gurax, "SetLogLevel")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("logLevel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, SetLogLevel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxLogLevel logLevel = args_gurax.PickNumber<wxLogLevel>();
	// Function body
	wxLog::SetLogLevel(logLevel);
	return Gurax::Value::nil();
}

// wx.Log.EnableLogging(enable? as Bool)
Gurax_DeclareClassMethodAlias(wxLog, EnableLogging_gurax, "EnableLogging")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, EnableLogging_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool enable = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = wxLog::EnableLogging(enable);
	return new Gurax::Value_Bool(rtn);
}

// wx.Log.IsEnabled()
Gurax_DeclareClassMethodAlias(wxLog, IsEnabled_gurax, "IsEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, IsEnabled_gurax, processor_gurax, argument_gurax)
{
	// Function body
	bool rtn = wxLog::IsEnabled();
	return new Gurax::Value_Bool(rtn);
}

// wx.Log.GetRepetitionCounting()
Gurax_DeclareClassMethodAlias(wxLog, GetRepetitionCounting_gurax, "GetRepetitionCounting")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, GetRepetitionCounting_gurax, processor_gurax, argument_gurax)
{
	// Function body
	bool rtn = wxLog::GetRepetitionCounting();
	return new Gurax::Value_Bool(rtn);
}

// wx.Log.SetRepetitionCounting(repetCounting? as Bool)
Gurax_DeclareClassMethodAlias(wxLog, SetRepetitionCounting_gurax, "SetRepetitionCounting")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("repetCounting", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, SetRepetitionCounting_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool repetCounting = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	wxLog::SetRepetitionCounting(repetCounting);
	return Gurax::Value::nil();
}

// wx.Log.GetTimestamp()
Gurax_DeclareClassMethodAlias(wxLog, GetTimestamp_gurax, "GetTimestamp")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, GetTimestamp_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxString rtn = wxLog::GetTimestamp();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.Log.SetTimestamp(format as String)
Gurax_DeclareClassMethodAlias(wxLog, SetTimestamp_gurax, "SetTimestamp")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, SetTimestamp_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* format = args_gurax.PickString();
	// Function body
	wxLog::SetTimestamp(format);
	return Gurax::Value::nil();
}

// wx.Log.DisableTimestamp()
Gurax_DeclareClassMethodAlias(wxLog, DisableTimestamp_gurax, "DisableTimestamp")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, DisableTimestamp_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxLog::DisableTimestamp();
	return Gurax::Value::nil();
}

// wx.Log.GetVerbose()
Gurax_DeclareClassMethodAlias(wxLog, GetVerbose_gurax, "GetVerbose")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, GetVerbose_gurax, processor_gurax, argument_gurax)
{
	// Function body
	bool rtn = wxLog::GetVerbose();
	return new Gurax::Value_Bool(rtn);
}

// wx.Log.SetVerbose(verbose? as Bool)
Gurax_DeclareClassMethodAlias(wxLog, SetVerbose_gurax, "SetVerbose")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("verbose", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethodEx(wxLog, SetVerbose_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool verbose = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	wxLog::SetVerbose(verbose);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxLog
//------------------------------------------------------------------------------
VType_wxLog VTYPE_wxLog("Log");

void VType_wxLog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxLog, AddTraceMask_gurax));
	Assign(Gurax_CreateMethod(wxLog, ClearTraceMasks_gurax));
	Assign(Gurax_CreateMethod(wxLog, GetTraceMasks_gurax));
	Assign(Gurax_CreateMethod(wxLog, IsAllowedTraceMask_gurax));
	Assign(Gurax_CreateMethod(wxLog, RemoveTraceMask_gurax));
	Assign(Gurax_CreateMethod(wxLog, DontCreateOnDemand_gurax));
	Assign(Gurax_CreateMethod(wxLog, GetActiveTarget_gurax));
	Assign(Gurax_CreateMethod(wxLog, SetActiveTarget_gurax));
	Assign(Gurax_CreateMethod(wxLog, SetThreadActiveTarget_gurax));
	Assign(Gurax_CreateMethod(wxLog, FlushActive_gurax));
	Assign(Gurax_CreateMethod(wxLog, Resume_gurax));
	Assign(Gurax_CreateMethod(wxLog, Suspend_gurax));
	Assign(Gurax_CreateMethod(wxLog, GetLogLevel_gurax));
	Assign(Gurax_CreateMethod(wxLog, IsLevelEnabled_gurax));
	Assign(Gurax_CreateMethod(wxLog, SetComponentLevel_gurax));
	Assign(Gurax_CreateMethod(wxLog, SetLogLevel_gurax));
	Assign(Gurax_CreateMethod(wxLog, EnableLogging_gurax));
	Assign(Gurax_CreateMethod(wxLog, IsEnabled_gurax));
	Assign(Gurax_CreateMethod(wxLog, GetRepetitionCounting_gurax));
	Assign(Gurax_CreateMethod(wxLog, SetRepetitionCounting_gurax));
	Assign(Gurax_CreateMethod(wxLog, GetTimestamp_gurax));
	Assign(Gurax_CreateMethod(wxLog, SetTimestamp_gurax));
	Assign(Gurax_CreateMethod(wxLog, DisableTimestamp_gurax));
	Assign(Gurax_CreateMethod(wxLog, GetVerbose_gurax));
	Assign(Gurax_CreateMethod(wxLog, SetVerbose_gurax));
}

//------------------------------------------------------------------------------
// Value_wxLog
//------------------------------------------------------------------------------
VType& Value_wxLog::vtype = VTYPE_wxLog;

String Value_wxLog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Log");
}

Gurax_EndModuleScope(wx)
