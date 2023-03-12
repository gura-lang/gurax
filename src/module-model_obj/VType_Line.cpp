//==============================================================================
// VType_Line.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Line, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Line, `en)}

${help.ComposeMethodHelp(model.obj.Line, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Line#GetV(idx as Number)
Gurax_DeclareMethod(Line, GetV)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Line, GetV)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	int iIndex = args.PickNumber<int>();
	// Function body
	const Vertex4* pV = valueThis.GetLine().GetV(valueThis.GetContent(), iIndex);
	if (pV) return new Value_Vertex4(pV->Reference());
	return Value::nil();
}

// model.obj.Line#GetVt(idx as Number)
Gurax_DeclareMethod(Line, GetVt)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Line, GetVt)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	int iIndex = args.PickNumber<int>();
	// Function body
	const Vertex3* pVt = valueThis.GetLine().GetVt(valueThis.GetContent(), iIndex);
	if (pVt) return new Value_Vertex3(pVt->Reference());
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// model.obj.Line#nElements
Gurax_DeclareProperty_R(Line, nElements)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Line, nElements)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetLine().GetIndexPairList().size());
}

//------------------------------------------------------------------------------
// VType_Line
//------------------------------------------------------------------------------
VType_Line VTYPE_Line("Line");

void VType_Line::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Line, GetV));
	Assign(Gurax_CreateMethod(Line, GetVt));
	// Assignment of property
	Assign(Gurax_CreateProperty(Line, nElements));
}

//------------------------------------------------------------------------------
// Value_Line
//------------------------------------------------------------------------------
VType& Value_Line::vtype = VTYPE_Line;


String Value_Line::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetLine().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
