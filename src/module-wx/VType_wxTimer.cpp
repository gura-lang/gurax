//==============================================================================
// VType_wxTimer.cpp
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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Timer(owner? as wx.EvtHandler, id? as Number) {block?} {block?}
Gurax_DeclareConstructorAlias(Timer_gurax, "Timer")
{
	Declare(VTYPE_wxTimer, Flag::None);
	DeclareArg("owner", VTYPE_wxEvtHandler, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Timer.");
}

Gurax_ImplementConstructorEx(Timer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxEvtHandler* owner = args_gurax.IsValid()? args_gurax.Pick<Value_wxEvtHandler>().GetEntityPtr() : nullptr;
	bool id_validFlag = args_gurax.IsValid();
	int id = id_validFlag? args_gurax.PickNumber<int>() : -1;
	// Function body
	if (owner) {
		return new Value_wxTimer(new wxTimer(owner, id));
	} else {
		return new Value_wxTimer(new wxTimer());
	}
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Timer#GetId()
Gurax_DeclareMethodAlias(wxTimer, GetId_gurax, "GetId")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTimer, GetId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetId();
	return new Gurax::Value_Number(rtn);
}

// wx.Timer#GetInterval()
Gurax_DeclareMethodAlias(wxTimer, GetInterval_gurax, "GetInterval")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTimer, GetInterval_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetInterval();
	return new Gurax::Value_Number(rtn);
}

// wx.Timer#GetOwner() {block?}
Gurax_DeclareMethodAlias(wxTimer, GetOwner_gurax, "GetOwner")
{
	Declare(VTYPE_wxEvtHandler, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTimer, GetOwner_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxEvtHandler(
		pEntity_gurax->GetOwner()));
}

// wx.Timer#IsOneShot()
Gurax_DeclareMethodAlias(wxTimer, IsOneShot_gurax, "IsOneShot")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTimer, IsOneShot_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOneShot();
	return new Gurax::Value_Bool(rtn);
}

// wx.Timer#IsRunning()
Gurax_DeclareMethodAlias(wxTimer, IsRunning_gurax, "IsRunning")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTimer, IsRunning_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsRunning();
	return new Gurax::Value_Bool(rtn);
}

// wx.Timer#Notify()
Gurax_DeclareMethodAlias(wxTimer, Notify_gurax, "Notify")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTimer, Notify_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Notify();
	return Gurax::Value::nil();
}

// wx.Timer#SetOwner(owner as wx.EvtHandler, id? as Number)
Gurax_DeclareMethodAlias(wxTimer, SetOwner_gurax, "SetOwner")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("owner", VTYPE_wxEvtHandler, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTimer, SetOwner_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxEvtHandler& value_owner = args_gurax.Pick<Value_wxEvtHandler>();
	wxEvtHandler* owner = value_owner.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	int id = id_validFlag? args_gurax.PickNumber<int>() : -1;
	// Function body
	pEntity_gurax->SetOwner(owner, id);
	return Gurax::Value::nil();
}

// wx.Timer#Start(milliseconds? as Number, oneShot? as Bool)
Gurax_DeclareMethodAlias(wxTimer, Start_gurax, "Start")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("milliseconds", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("oneShot", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTimer, Start_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool milliseconds_validFlag = args_gurax.IsValid();
	int milliseconds = milliseconds_validFlag? args_gurax.PickNumber<int>() : -1;
	bool oneShot = args_gurax.IsValid()? args_gurax.PickBool() : wxTIMER_CONTINUOUS;
	// Function body
	bool rtn = pEntity_gurax->Start(milliseconds, oneShot);
	return new Gurax::Value_Bool(rtn);
}

// wx.Timer#StartOnce(milliseconds? as Number)
Gurax_DeclareMethodAlias(wxTimer, StartOnce_gurax, "StartOnce")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("milliseconds", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTimer, StartOnce_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool milliseconds_validFlag = args_gurax.IsValid();
	int milliseconds = milliseconds_validFlag? args_gurax.PickNumber<int>() : -1;
	// Function body
	bool rtn = pEntity_gurax->StartOnce(milliseconds);
	return new Gurax::Value_Bool(rtn);
}

// wx.Timer#Stop()
Gurax_DeclareMethodAlias(wxTimer, Stop_gurax, "Stop")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTimer, Stop_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Stop();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxTimer
//------------------------------------------------------------------------------
VType_wxTimer VTYPE_wxTimer("Timer");

void VType_wxTimer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvtHandler, Flag::Mutable, Gurax_CreateConstructor(Timer_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxTimer, GetId_gurax));
	Assign(Gurax_CreateMethod(wxTimer, GetInterval_gurax));
	Assign(Gurax_CreateMethod(wxTimer, GetOwner_gurax));
	Assign(Gurax_CreateMethod(wxTimer, IsOneShot_gurax));
	Assign(Gurax_CreateMethod(wxTimer, IsRunning_gurax));
	Assign(Gurax_CreateMethod(wxTimer, Notify_gurax));
	Assign(Gurax_CreateMethod(wxTimer, SetOwner_gurax));
	Assign(Gurax_CreateMethod(wxTimer, Start_gurax));
	Assign(Gurax_CreateMethod(wxTimer, StartOnce_gurax));
	Assign(Gurax_CreateMethod(wxTimer, Stop_gurax));
}

//------------------------------------------------------------------------------
// Value_wxTimer
//------------------------------------------------------------------------------
VType& Value_wxTimer::vtype = VTYPE_wxTimer;

String Value_wxTimer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Timer");
}

//------------------------------------------------------------------------------
// Value_wxTimer::EntityT
//------------------------------------------------------------------------------
void Value_wxTimer::EntityT::Notify()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("Notify");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
}

bool Value_wxTimer::EntityT::Start(int milliseconds, bool oneShot)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("Start");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Gurax::Value_Number(milliseconds))) break;
		if (!args_gurax.FeedValue(new Gurax::Value_Bool(oneShot))) break;
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Bool)) break;
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return wxTimer::Start(milliseconds, oneShot);
}

void Value_wxTimer::EntityT::Stop()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("Stop");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
}

Gurax_EndModuleScope(wx)
