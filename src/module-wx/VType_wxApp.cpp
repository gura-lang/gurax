//==============================================================================
// VType_wxApp.cpp
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
Gurax_DeclareConstructor(App)
{
	Declare(VTYPE_wxApp, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.App` instance.");
}

Gurax_ImplementConstructor(App)
{
	// Function body
	auto pEntity = new Value_wxApp::EntityT();
	RefPtr<Value_wxApp> pValue(new Value_wxApp(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.App#OnInit()
Gurax_DeclareMethod(wxApp, OnInit)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(wxApp, OnInit)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	auto pEntity = valueThis.GetEntity();
	if (!pEntity) return Value::nil();
	// Function body
	RefPtr<Value> pValueRtn(new Value_Bool(pEntity->OnInit()));
	return pValueRtn.release();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// wx.App#propSkeleton
Gurax_DeclareProperty_R(wxApp, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(wxApp, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_wxApp
//------------------------------------------------------------------------------
VType_wxApp VTYPE_wxApp("App");

void VType_wxApp::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxAppConsole, Flag::Immutable, Gurax_CreateConstructor(App));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxApp, OnInit));
	// Assignment of property
	Assign(Gurax_CreateProperty(wxApp, propSkeleton));
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
bool Value_wxApp::EntityT::OnInit()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnInit");
	do {
		Function* pFunc;
		RefPtr<Argument> pArgument;
		if (!core.PrepareMethod(pSymbolFunc, &pFunc, pArgument)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc->Eval(core.GetProcessor(), *pArgument));
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
		Function* pFunc;
		RefPtr<Argument> pArgument;
		if (!core.PrepareMethod(pSymbolFunc, &pFunc, pArgument)) break;
		// Argument
		ArgFeeder args(*pArgument, core.GetProcessor().GetFrameCur());
		if (!args.FeedValue(new Value_wxWindow(dynamic_cast<Value_wxWindow::EntityT*>(win)))) break;
		if (!args.FeedValue(new Value_Bool(onlyIfNeeded))) break;
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc->Eval(core.GetProcessor(), *pArgument));
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Bool)) break;
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return wxApp::SafeYield(win, onlyIfNeeded);
}

Gurax_EndModuleScope(wx)
