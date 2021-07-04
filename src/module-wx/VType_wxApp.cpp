//==============================================================================
// VType_wxApp.cpp
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
// wx.App() {block?}
Gurax_DeclareConstructorAlias(App_gurax, "App")
{
	Declare(VTYPE_wxApp, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.App.");
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
// wx.App#OnExit()
Gurax_DeclareMethodAlias(wxApp, OnExit_gurax, "OnExit")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxApp, OnExit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->OnExit();
	return new Gurax::Value_Number(rtn);
}

// wx.App#OnInit()
Gurax_DeclareMethodAlias(wxApp, OnInit_gurax, "OnInit")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxApp, OnInit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->OnInit();
	return new Gurax::Value_Bool(rtn);
}

// wx.App#SafeYield(win as wx.Window, onlyIfNeeded as Bool)
Gurax_DeclareMethodAlias(wxApp, SafeYield_gurax, "SafeYield")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("win", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("onlyIfNeeded", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxApp, SafeYield_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
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
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxAppConsole, Flag::Mutable, Gurax_CreateConstructor(App_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxApp, OnExit_gurax));
	Assign(Gurax_CreateMethod(wxApp, OnInit_gurax));
	Assign(Gurax_CreateMethod(wxApp, SafeYield_gurax));
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
int Value_wxApp::EntityT::OnExit()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnExit");
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
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Number)) break;
		return Value_Number::GetNumber<int>(*pValueRtn);
	} while (0);
	return wxApp::OnExit();
}

bool Value_wxApp::EntityT::OnInit()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnInit");
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
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Bool)) break;
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return wxApp::OnInit();
}

bool Value_wxApp::EntityT::SafeYield(wxWindow* win, bool onlyIfNeeded)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("SafeYield");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Value_wxWindow(win))) break;
		if (!args_gurax.FeedValue(new Gurax::Value_Bool(onlyIfNeeded))) break;
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
	return wxApp::SafeYield(win, onlyIfNeeded);
}

Gurax_EndModuleScope(wx)
