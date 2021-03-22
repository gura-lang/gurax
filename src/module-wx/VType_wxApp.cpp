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
// wx.wxApp() {block?}
Gurax_DeclareConstructor(wxApp)
{
	Declare(VTYPE_wxApp, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.App` instance.");
}

Gurax_ImplementConstructor(wxApp)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	wxApp* pEntity = new wxApp();
	return argument.ReturnValue(processor, new Value_wxApp(pEntity));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.wxApp#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(wxApp, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(wxApp, MethodSkeleton)
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
// wx.wxApp#propSkeleton
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
VType_wxApp VTYPE_wxApp("wxApp");

void VType_wxApp::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(wxApp));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxApp, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(wxApp, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxApp
//------------------------------------------------------------------------------
VType& Value_wxApp::vtype = VTYPE_wxApp;

String Value_wxApp::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wxApp");
}

Gurax_EndModuleScope(wx)
