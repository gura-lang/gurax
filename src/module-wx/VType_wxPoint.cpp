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
Gurax_DeclareConstructor(Point)
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Point` instance.");
}

Gurax_ImplementConstructor(Point)
{
	// Argument
	ArgPicker args(argument);
	int x = args.IsValid()? args.PickNumber<int>() : 0;
	int y = args.IsValid()? args.PickNumber<int>() : 0;
	// Function body
	Value_wxPoint::EntityT entity(x, y);
	RefPtr<Value_wxPoint> pValue(new Value_wxPoint(entity));
	return argument.ReturnValue(processor, pValue.release());
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
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Point));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Point, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Point, propSkeleton));
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
