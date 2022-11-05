//==============================================================================
// VType_wxEventLoopBase.cpp
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

${help.ComposePropertyHelp(wx.EventLoopBase, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.EventLoopBase, `en)}

${help.ComposeMethodHelp(wx.EventLoopBase, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.EventLoopBase#IsMain()
Gurax_DeclareMethodAlias(wxEventLoopBase, IsMain_gurax, "IsMain")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, IsMain_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsMain();
	return new Gurax::Value_Bool(rtn);
}

// wx.EventLoopBase#Run()
Gurax_DeclareMethodAlias(wxEventLoopBase, Run_gurax, "Run")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, Run_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->Run();
	return new Gurax::Value_Number(rtn);
}

// wx.EventLoopBase#IsRunning()
Gurax_DeclareMethodAlias(wxEventLoopBase, IsRunning_gurax, "IsRunning")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, IsRunning_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsRunning();
	return new Gurax::Value_Bool(rtn);
}

// wx.EventLoopBase#IsOk()
Gurax_DeclareMethodAlias(wxEventLoopBase, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

// wx.EventLoopBase#Exit(rc? as Number)
Gurax_DeclareMethodAlias(wxEventLoopBase, Exit_gurax, "Exit")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, Exit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool rc_validFlag = args_gurax.IsValid();
	int rc = rc_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->Exit(rc);
	return Gurax::Value::nil();
}

// wx.EventLoopBase#ScheduleExit(rc? as Number)
Gurax_DeclareMethodAlias(wxEventLoopBase, ScheduleExit_gurax, "ScheduleExit")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, ScheduleExit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool rc_validFlag = args_gurax.IsValid();
	int rc = rc_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->ScheduleExit(rc);
	return Gurax::Value::nil();
}

// wx.EventLoopBase#Pending()
Gurax_DeclareMethodAlias(wxEventLoopBase, Pending_gurax, "Pending")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, Pending_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Pending();
	return new Gurax::Value_Bool(rtn);
}

// wx.EventLoopBase#Dispatch()
Gurax_DeclareMethodAlias(wxEventLoopBase, Dispatch_gurax, "Dispatch")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, Dispatch_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Dispatch();
	return new Gurax::Value_Bool(rtn);
}

// wx.EventLoopBase#DispatchTimeout(timeout as Number)
Gurax_DeclareMethodAlias(wxEventLoopBase, DispatchTimeout_gurax, "DispatchTimeout")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("timeout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, DispatchTimeout_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned long timeout = args_gurax.PickNumber<unsigned long>();
	// Function body
	int rtn = pEntity_gurax->DispatchTimeout(timeout);
	return new Gurax::Value_Number(rtn);
}

// wx.EventLoopBase#WakeUp()
Gurax_DeclareMethodAlias(wxEventLoopBase, WakeUp_gurax, "WakeUp")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, WakeUp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->WakeUp();
	return Gurax::Value::nil();
}

// wx.EventLoopBase#WakeUpIdle()
Gurax_DeclareMethodAlias(wxEventLoopBase, WakeUpIdle_gurax, "WakeUpIdle")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, WakeUpIdle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->WakeUpIdle();
	return Gurax::Value::nil();
}

// wx.EventLoopBase#ProcessIdle()
Gurax_DeclareMethodAlias(wxEventLoopBase, ProcessIdle_gurax, "ProcessIdle")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, ProcessIdle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ProcessIdle();
	return new Gurax::Value_Bool(rtn);
}

// wx.EventLoopBase#IsYielding()
Gurax_DeclareMethodAlias(wxEventLoopBase, IsYielding_gurax, "IsYielding")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, IsYielding_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsYielding();
	return new Gurax::Value_Bool(rtn);
}

// wx.EventLoopBase#Yield(onlyIfNeeded? as Bool)
Gurax_DeclareMethodAlias(wxEventLoopBase, Yield_gurax, "Yield")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("onlyIfNeeded", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, Yield_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool onlyIfNeeded = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	bool rtn = pEntity_gurax->Yield(onlyIfNeeded);
	return new Gurax::Value_Bool(rtn);
}

// wx.EventLoopBase#YieldFor(eventsToProcess as Number)
Gurax_DeclareMethodAlias(wxEventLoopBase, YieldFor_gurax, "YieldFor")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("eventsToProcess", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, YieldFor_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long eventsToProcess = args_gurax.PickNumber<long>();
	// Function body
	bool rtn = pEntity_gurax->YieldFor(eventsToProcess);
	return new Gurax::Value_Bool(rtn);
}

// wx.EventLoopBase#IsEventAllowedInsideYield(cat as Number)
Gurax_DeclareMethodAlias(wxEventLoopBase, IsEventAllowedInsideYield_gurax, "IsEventAllowedInsideYield")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("cat", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEventLoopBase, IsEventAllowedInsideYield_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxEventCategory cat = args_gurax.PickNumber<wxEventCategory>();
	// Function body
	bool rtn = pEntity_gurax->IsEventAllowedInsideYield(cat);
	return new Gurax::Value_Bool(rtn);
}

// wx.EventLoopBase.GetActive() {block?}
Gurax_DeclareClassMethodAlias(wxEventLoopBase, GetActive_gurax, "GetActive")
{
	Declare(VTYPE_wxEventLoopBase, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxEventLoopBase, GetActive_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxEventLoopBase(
		wxEventLoopBase::GetActive()));
}

// wx.EventLoopBase.SetActive(loop as wx.EventLoopBase)
Gurax_DeclareClassMethodAlias(wxEventLoopBase, SetActive_gurax, "SetActive")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("loop", VTYPE_wxEventLoopBase, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxEventLoopBase, SetActive_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxEventLoopBase& value_loop = args_gurax.Pick<Value_wxEventLoopBase>();
	wxEventLoopBase* loop = value_loop.GetEntityPtr();
	// Function body
	wxEventLoopBase::SetActive(loop);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxEventLoopBase
//------------------------------------------------------------------------------
VType_wxEventLoopBase VTYPE_wxEventLoopBase("EventLoopBase");

void VType_wxEventLoopBase::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxEventLoopBase, IsMain_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, Run_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, IsRunning_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, IsOk_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, Exit_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, ScheduleExit_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, Pending_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, Dispatch_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, DispatchTimeout_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, WakeUp_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, WakeUpIdle_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, ProcessIdle_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, IsYielding_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, Yield_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, YieldFor_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, IsEventAllowedInsideYield_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, GetActive_gurax));
	Assign(Gurax_CreateMethod(wxEventLoopBase, SetActive_gurax));
}

//------------------------------------------------------------------------------
// Value_wxEventLoopBase
//------------------------------------------------------------------------------
VType& Value_wxEventLoopBase::vtype = VTYPE_wxEventLoopBase;

String Value_wxEventLoopBase::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.EventLoopBase");
}

Gurax_EndModuleScope(wx)
