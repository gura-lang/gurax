//==============================================================================
// VType_App.cpp
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
	Declare(VTYPE_App, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.App` instance.");
}

Gurax_ImplementConstructor(App)
{
	// Function body
	auto pEntity = new Value_App::EntityT();
	RefPtr<Value_App> pValue(new Value_App(pEntity));
	pEntity->SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.App#OnInit()
Gurax_DeclareMethod(App, OnInit)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(App, OnInit)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Value> pValueRtn(new Value_Bool(valueThis.GetEntity()->OnInit()));
	return pValueRtn.release();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// wx.App#propSkeleton
Gurax_DeclareProperty_R(App, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(App, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_App
//------------------------------------------------------------------------------
VType_App VTYPE_App("App");

void VType_App::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(App));
	// Assignment of method
	Assign(Gurax_CreateMethod(App, OnInit));
	// Assignment of property
	Assign(Gurax_CreateProperty(App, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_App
//------------------------------------------------------------------------------
VType& Value_App::vtype = VTYPE_App;

String Value_App::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.App");
}


//------------------------------------------------------------------------------
// Value_App::EntityT
//------------------------------------------------------------------------------
bool Value_App::EntityT::OnInit()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnInit");
	do {
		Function* pFunc;
		RefPtr<Argument> pArgument;
		if (!PrepareMethod(pSymbolFunc, &pFunc, pArgument)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc->Eval(GetProcessor(), *pArgument));
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Bool)) break;
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return EntitySuper::OnInit();
}

bool Value_App::EntityT::SafeYield(wxWindow* win, bool onlyIfNeeded)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("SafeYield");
	do {
		Function* pFunc;
		RefPtr<Argument> pArgument;
		if (!PrepareMethod(pSymbolFunc, &pFunc, pArgument)) break;
		// Argument
		ArgFeeder args(*pArgument, GetProcessor().GetFrameCur());
		if (!args.FeedValue(new Value_Window(dynamic_cast<Value_Window::EntityT*>(win)))) break;
		if (!args.FeedValue(new Value_Bool(onlyIfNeeded))) break;
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc->Eval(GetProcessor(), *pArgument));
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Bool)) break;
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return EntitySuper::SafeYield(win, onlyIfNeeded);
}

bool Value_App::EntityT::PrepareMethod(const Symbol* pSymbolFunc, Function** ppFunc, RefPtr<Argument>& pArgument) const
{
	RefPtr<Value_App> pValueThis(LockValue());
	if (!pValueThis) return false;
	*ppFunc = &pValueThis->LookupMethod(pSymbolFunc);
	if ((*ppFunc)->IsEmpty()) return false;
	pArgument.reset(new Argument(**ppFunc));
	pArgument->SetValueThis(pValueThis.release());
	return true;
}

Gurax_EndModuleScope(wx)
