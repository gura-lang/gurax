//==============================================================================
// VType_Line.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Line, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Line, `en)}

${help.ComposeMethodHelp(model.obj.Line, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Line() {block?}
Gurax_DeclareConstructor(Line)
{
	Declare(VTYPE_Line, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `model.obj.Line` instance.
)**");
}

Gurax_ImplementConstructor(Line)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Line> pLine(new Line());
	return argument.ReturnValue(processor, new Value_Line(pLine.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Line#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Line, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Line, MethodSkeleton)
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
// model.obj.Line#propSkeleton
Gurax_DeclareProperty_R(Line, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Line, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
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
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Line));
	// Assignment of method
	Assign(Gurax_CreateMethod(Line, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Line, propSkeleton));
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
