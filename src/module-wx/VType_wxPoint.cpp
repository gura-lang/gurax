//==============================================================================
// VType_wxPoint.cpp
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
// wx.Point(x? as Number, y? as Number) {block?}
Gurax_DeclareConstructorAlias(Point_gurax, "Point")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wxPoint.");
}

Gurax_ImplementConstructorEx(Point_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.IsValid()? args_gurax.PickNumber<int>() : 0;
	int y = args_gurax.IsValid()? args_gurax.PickNumber<int>() : 0;
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

//------------------------------------------------------------------------------
// VType_wxPoint
//------------------------------------------------------------------------------
VType_wxPoint VTYPE_wxPoint("Point");

void VType_wxPoint::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Point_gurax));
	// Assignment of method
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
