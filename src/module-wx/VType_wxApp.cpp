﻿//==============================================================================
// VType_wxApp.cpp
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

${help.ComposePropertyHelp(wx.App, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.App, `en)}

${help.ComposeMethodHelp(wx.App, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.App, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.App, `ja)}

${help.ComposeMethodHelp(wx.App, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.App() {block?}
Gurax_DeclareConstructorAlias(App_gurax, "App")
{
	Declare(VTYPE_wxApp, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(App_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxApp::EntityT();
	RefPtr<Value_wxApp> pValue_gurax(new Value_wxApp(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.App#GetDisplayMode() {block?}
Gurax_DeclareMethodAlias(wxApp, GetDisplayMode_gurax, "GetDisplayMode")
{
	Declare(VTYPE_wxVideoMode, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxApp, GetDisplayMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxVideoMode(pEntity_gurax->GetDisplayMode()));
}

// wx.App#GetExitOnFrameDelete()
Gurax_DeclareMethodAlias(wxApp, GetExitOnFrameDelete_gurax, "GetExitOnFrameDelete")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxApp, GetExitOnFrameDelete_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetExitOnFrameDelete();
	return new Gurax::Value_Bool(rtn);
}

// wx.App#GetLayoutDirection()
Gurax_DeclareMethodAlias(wxApp, GetLayoutDirection_gurax, "GetLayoutDirection")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxApp, GetLayoutDirection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxLayoutDirection rtn = pEntity_gurax->GetLayoutDirection();
	return new Gurax::Value_Number(rtn);
}

// wx.App#GetUseBestVisual()
Gurax_DeclareMethodAlias(wxApp, GetUseBestVisual_gurax, "GetUseBestVisual")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxApp, GetUseBestVisual_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetUseBestVisual();
	return new Gurax::Value_Bool(rtn);
}

// wx.App#GetTopWindow() {block?}
Gurax_DeclareMethodAlias(wxApp, GetTopWindow_gurax, "GetTopWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxApp, GetTopWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(pEntity_gurax->GetTopWindow()));
}

// wx.App#OnInit()
Gurax_DeclareMethodAlias(wxApp, OnInit_gurax, "OnInit")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxApp, OnInit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->OnInit();
	return new Gurax::Value_Bool(rtn);
}

// wx.App#IsActive()
Gurax_DeclareMethodAlias(wxApp, IsActive_gurax, "IsActive")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxApp, IsActive_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsActive();
	return new Gurax::Value_Bool(rtn);
}

// wx.App#SafeYield(win as wx.Window, onlyIfNeeded as Bool)
Gurax_DeclareMethodAlias(wxApp, SafeYield_gurax, "SafeYield")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("win", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("onlyIfNeeded", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxApp, SafeYield_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_win = args_gurax.Pick<Value_wxWindow>();
	wxWindow* win = value_win.GetEntityPtr();
	bool onlyIfNeeded = args_gurax.PickBool();
	// Function body
	bool rtn = pEntity_gurax->SafeYield(win, onlyIfNeeded);
	return new Gurax::Value_Bool(rtn);
}

// wx.App#SafeYieldFor(win as wx.Window, eventsToProcess as Number)
Gurax_DeclareMethodAlias(wxApp, SafeYieldFor_gurax, "SafeYieldFor")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("win", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("eventsToProcess", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxApp, SafeYieldFor_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_win = args_gurax.Pick<Value_wxWindow>();
	wxWindow* win = value_win.GetEntityPtr();
	long eventsToProcess = args_gurax.PickNumber<long>();
	// Function body
	bool rtn = pEntity_gurax->SafeYieldFor(win, eventsToProcess);
	return new Gurax::Value_Bool(rtn);
}

// wx.App#SetDisplayMode(info as wx.VideoMode)
Gurax_DeclareMethodAlias(wxApp, SetDisplayMode_gurax, "SetDisplayMode")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("info", VTYPE_wxVideoMode, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxApp, SetDisplayMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxVideoMode& value_info = args_gurax.Pick<Value_wxVideoMode>();
	const wxVideoMode& info = value_info.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->SetDisplayMode(info);
	return new Gurax::Value_Bool(rtn);
}

// wx.App#SetExitOnFrameDelete(flag as Bool)
Gurax_DeclareMethodAlias(wxApp, SetExitOnFrameDelete_gurax, "SetExitOnFrameDelete")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxApp, SetExitOnFrameDelete_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool flag = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetExitOnFrameDelete(flag);
	return Gurax::Value::nil();
}

// wx.App#SetNativeTheme(theme as String)
Gurax_DeclareMethodAlias(wxApp, SetNativeTheme_gurax, "SetNativeTheme")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("theme", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxApp, SetNativeTheme_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString theme(args_gurax.PickString());
	// Function body
	bool rtn = pEntity_gurax->SetNativeTheme(theme);
	return new Gurax::Value_Bool(rtn);
}

// wx.App#SetTopWindow(window as wx.Window)
Gurax_DeclareMethodAlias(wxApp, SetTopWindow_gurax, "SetTopWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxApp, SetTopWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	// Function body
	pEntity_gurax->SetTopWindow(window);
	return Gurax::Value::nil();
}

// wx.App#SetUseBestVisual(flag as Bool, forceTrueColour? as Bool)
Gurax_DeclareMethodAlias(wxApp, SetUseBestVisual_gurax, "SetUseBestVisual")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("forceTrueColour", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxApp, SetUseBestVisual_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool flag = args_gurax.PickBool();
	bool forceTrueColour = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	pEntity_gurax->SetUseBestVisual(flag, forceTrueColour);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxApp
//------------------------------------------------------------------------------
VType_wxApp VTYPE_wxApp("App");

void VType_wxApp::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxAppConsole, Flag::Mutable, Gurax_CreateConstructor(App_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxApp, GetDisplayMode_gurax));
	Assign(Gurax_CreateMethod(wxApp, GetExitOnFrameDelete_gurax));
	Assign(Gurax_CreateMethod(wxApp, GetLayoutDirection_gurax));
	Assign(Gurax_CreateMethod(wxApp, GetUseBestVisual_gurax));
	Assign(Gurax_CreateMethod(wxApp, GetTopWindow_gurax));
	Assign(Gurax_CreateMethod(wxApp, OnInit_gurax));
	Assign(Gurax_CreateMethod(wxApp, IsActive_gurax));
	Assign(Gurax_CreateMethod(wxApp, SafeYield_gurax));
	Assign(Gurax_CreateMethod(wxApp, SafeYieldFor_gurax));
	Assign(Gurax_CreateMethod(wxApp, SetDisplayMode_gurax));
	Assign(Gurax_CreateMethod(wxApp, SetExitOnFrameDelete_gurax));
	Assign(Gurax_CreateMethod(wxApp, SetNativeTheme_gurax));
	Assign(Gurax_CreateMethod(wxApp, SetTopWindow_gurax));
	Assign(Gurax_CreateMethod(wxApp, SetUseBestVisual_gurax));
}

//------------------------------------------------------------------------------
// Value_wxApp
//------------------------------------------------------------------------------
VType& Value_wxApp::vtype = VTYPE_wxApp;

String Value_wxApp::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.App");
}

//------------------------------------------------------------------------------
// Value_wxApp::EntityT
//------------------------------------------------------------------------------
bool Value_wxApp::EntityT::SafeYield(wxWindow* win, bool onlyIfNeeded)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("SafeYield");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Value_wxWindow(win))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Gurax::Value_Bool(onlyIfNeeded))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsInstanceOf(VTYPE_Bool)) {
			Error::IssueWith(ErrorType::TypeError, pFunc_gurax->GetDeclCallable().GetExprSrc(),
				"the function SafeYield is expected to return a value of %s or its derived class",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_SafeYield(win, onlyIfNeeded);
}

bool Value_wxApp::EntityT::SafeYieldFor(wxWindow* win, long eventsToProcess)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("SafeYieldFor");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Value_wxWindow(win))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Gurax::Value_Number(eventsToProcess))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsInstanceOf(VTYPE_Bool)) {
			Error::IssueWith(ErrorType::TypeError, pFunc_gurax->GetDeclCallable().GetExprSrc(),
				"the function SafeYieldFor is expected to return a value of %s or its derived class",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_SafeYieldFor(win, eventsToProcess);
}

bool Value_wxApp::EntityT::SetDisplayMode(const wxVideoMode& info)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("SetDisplayMode");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Value_wxVideoMode(info))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsInstanceOf(VTYPE_Bool)) {
			Error::IssueWith(ErrorType::TypeError, pFunc_gurax->GetDeclCallable().GetExprSrc(),
				"the function SetDisplayMode is expected to return a value of %s or its derived class",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_SetDisplayMode(info);
}

bool Value_wxApp::EntityT::SetNativeTheme(const wxString& theme)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("SetNativeTheme");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Gurax::Value_String(theme.utf8_str().data()))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsInstanceOf(VTYPE_Bool)) {
			Error::IssueWith(ErrorType::TypeError, pFunc_gurax->GetDeclCallable().GetExprSrc(),
				"the function SetNativeTheme is expected to return a value of %s or its derived class",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_SetNativeTheme(theme);
}

Gurax_EndModuleScope(wx)
