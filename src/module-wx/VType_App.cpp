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
// wx.App#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(App, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(App, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
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
	Assign(Gurax_CreateMethod(App, MethodSkeleton));
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
	RefPtr<Value_App> pValueThis(LockValue());
	if (!pValueThis) return EntitySuper::OnInit();
	Function& func = pValueThis->LookupMethod(pSymbolFunc);
	if (func.IsEmpty()) return EntitySuper::OnInit();
	RefPtr<Argument> pArgument(new Argument(func));
	pArgument->SetValueThis(pValueThis.release());
	
	RefPtr<Value> pValueRtn(func.Eval(GetProcessor(), *pArgument));
	if (!pValueRtn->IsValid()) return false;
	return Value_Bool::GetBool(*pValueRtn);
}

bool Value_App::EntityT::SafeYield(wxWindow* win, bool onlyIfNeeded)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("SafeYield");
	RefPtr<Value_App> pValueThis(LockValue());
	if (!pValueThis) return EntitySuper::SafeYield(win, onlyIfNeeded);
	Function& func = pValueThis->LookupMethod(pSymbolFunc);
	if (func.IsEmpty()) return EntitySuper::SafeYield(win, onlyIfNeeded);
	RefPtr<Argument> pArgument(new Argument(func));
	pArgument->SetValueThis(pValueThis.release());
	
	RefPtr<Value> pValueRtn(func.Eval(GetProcessor(), *pArgument));
	if (!pValueRtn->IsValid()) return false;
	return Value_Bool::GetBool(*pValueRtn);
}

Gurax_EndModuleScope(wx)
