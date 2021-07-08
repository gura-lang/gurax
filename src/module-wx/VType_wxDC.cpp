//==============================================================================
// VType_wxDC.cpp
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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DC#CopyAttributes(dc as wx.DC)
Gurax_DeclareMethodAlias(wxDC, CopyAttributes_gurax, "CopyAttributes")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDC, CopyAttributes_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	const wxDC& dc = value_dc.GetEntity();
	// Function body
	pEntity_gurax->CopyAttributes(dc);
	return Gurax::Value::nil();
}

// wx.DC#GetDepth()
Gurax_DeclareMethodAlias(wxDC, GetDepth_gurax, "GetDepth")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDC, GetDepth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetDepth();
	return new Gurax::Value_Number(rtn);
}

// wx.DC#GetDeviceOrigin()
Gurax_DeclareMethodAlias(wxDC, GetDeviceOrigin_gurax, "GetDeviceOrigin")
{
	Declare(VTYPE_wxPoint, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDC, GetDeviceOrigin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetDeviceOrigin()));
}

// wx.DC#GetLogicalFunction()
Gurax_DeclareMethodAlias(wxDC, GetLogicalFunction_gurax, "GetLogicalFunction")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDC, GetLogicalFunction_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxRasterOperationMode rtn = pEntity_gurax->GetLogicalFunction();
	return new Gurax::Value_Number(rtn);
}

// wx.DC#GetMapMode()
Gurax_DeclareMethodAlias(wxDC, GetMapMode_gurax, "GetMapMode")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDC, GetMapMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxMappingMode rtn = pEntity_gurax->GetMapMode();
	return new Gurax::Value_Number(rtn);
}

// wx.DC#GetPixel(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxDC, GetPixel_gurax, "GetPixel")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDC, GetPixel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxCoord x = args_gurax.PickNumber<wxCoord>();
	wxCoord y = args_gurax.PickNumber<wxCoord>();
	// Function body
	wxColour colour;
	bool rtn = pEntity_gurax->GetPixel(x, y, &colour);
	if (!rtn) return Value::nil();
	return new Value_wxColour(colour);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDC
//------------------------------------------------------------------------------
VType_wxDC VTYPE_wxDC("DC");

void VType_wxDC::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDC, CopyAttributes_gurax));
	Assign(Gurax_CreateMethod(wxDC, GetDepth_gurax));
	Assign(Gurax_CreateMethod(wxDC, GetDeviceOrigin_gurax));
	Assign(Gurax_CreateMethod(wxDC, GetLogicalFunction_gurax));
	Assign(Gurax_CreateMethod(wxDC, GetMapMode_gurax));
	Assign(Gurax_CreateMethod(wxDC, GetPixel_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDC
//------------------------------------------------------------------------------
VType& Value_wxDC::vtype = VTYPE_wxDC;

String Value_wxDC::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DC");
}

Gurax_EndModuleScope(wx)
