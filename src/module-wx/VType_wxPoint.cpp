//==============================================================================
// VType_wxPoint.cpp
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

${help.ComposePropertyHelp(wxPoint)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxPoint)}

${help.ComposeMethodHelp(wxPoint)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Point(x? as Number, y? as Number):map {block?}
Gurax_DeclareConstructorAlias(Point_gurax, "Point")
{
	Declare(VTYPE_wxPoint, Flag::Map);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Point.");
}

Gurax_ImplementConstructorEx(Point_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool x_validFlag = args_gurax.IsValid();
	int x = x_validFlag? args_gurax.PickNumber<int>() : 0;
	bool y_validFlag = args_gurax.IsValid();
	int y = y_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		wxPoint(x, y)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
Gurax_DeclareProperty_RW(wxPoint, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(wxPoint, x)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().x);
}

Gurax_ImplementPropertySetter(wxPoint, x)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int x = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().x = x;
}

Gurax_DeclareProperty_RW(wxPoint, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(wxPoint, y)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().y);
}

Gurax_ImplementPropertySetter(wxPoint, y)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int y = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().y = y;
}

//------------------------------------------------------------------------------
// VType_wxPoint
//------------------------------------------------------------------------------
VType_wxPoint VTYPE_wxPoint("Point");

void VType_wxPoint::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Point_gurax));
	// Assignment of method
	// Assignment of property
	Assign(Gurax_CreateProperty(wxPoint, x));
	Assign(Gurax_CreateProperty(wxPoint, y));
}

//------------------------------------------------------------------------------
// Value_wxPoint
//------------------------------------------------------------------------------
VType& Value_wxPoint::vtype = VTYPE_wxPoint;

String Value_wxPoint::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Point");
}

Gurax_EndModuleScope(wx)
