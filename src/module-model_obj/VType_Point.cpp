//==============================================================================
// VType_Point.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Point, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Point, `en)}

${help.ComposeMethodHelp(model.obj.Point, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Point#GetV(idx as Number)
Gurax_DeclareMethod(Point, GetV)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Point, GetV)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	int iIndex = args.PickNumber<int>();
	// Function body
	const Vertex4* pV = valueThis.GetPoint().GetV(valueThis.GetContent(), iIndex);
	if (pV) return new Value_Vertex4(pV->Reference());
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// model.obj.Point#nElements
Gurax_DeclareProperty_R(Point, nElements)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Point, nElements)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPoint().GetIndexList().size());
}

//------------------------------------------------------------------------------
// VType_Point
//------------------------------------------------------------------------------
VType_Point VTYPE_Point("Point");

void VType_Point::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Point, GetV));
	// Assignment of property
	Assign(Gurax_CreateProperty(Point, nElements));
}

//------------------------------------------------------------------------------
// Value_Point
//------------------------------------------------------------------------------
VType& Value_Point::vtype = VTYPE_Point;

String Value_Point::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetPoint().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
