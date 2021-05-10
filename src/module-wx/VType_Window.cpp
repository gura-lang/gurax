//==============================================================================
// VType_Window.cpp
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
// wx.Window() {block?}
Gurax_DeclareConstructor(Window)
{
	Declare(VTYPE_Window, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Window` instance.");
}

Gurax_ImplementConstructor(Window)
{
	// Function body
	auto pEntity = new Value_Window::EntityT();
	RefPtr<Value_Window> pValue(new Value_Window(pEntity));
	pEntity->SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// wx.Window#propSkeleton
Gurax_DeclareProperty_R(Window, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Window, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Window
//------------------------------------------------------------------------------
VType_Window VTYPE_Window("Window");

void VType_Window::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Window));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Window, OnInit));
	// Assignment of property
	Assign(Gurax_CreateProperty(Window, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Window
//------------------------------------------------------------------------------
VType& Value_Window::vtype = VTYPE_Window;

String Value_Window::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Window");
}

//------------------------------------------------------------------------------
// Value_Window::EntityT
//------------------------------------------------------------------------------
bool Value_Window::EntityT::PrepareMethod(const Symbol* pSymbolFunc, Function** ppFunc, RefPtr<Argument>& pArgument) const
{
	RefPtr<Value_Window> pValueThis(LockValue());
	if (!pValueThis) return false;
	*ppFunc = &pValueThis->LookupMethod(pSymbolFunc);
	if ((*ppFunc)->IsEmpty()) return false;
	pArgument.reset(new Argument(**ppFunc));
	pArgument->SetValueThis(pValueThis.release());
	return true;
}

Gurax_EndModuleScope(wx)
