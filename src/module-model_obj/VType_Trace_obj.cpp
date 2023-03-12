//==============================================================================
// VType_Trace_obj.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Trace_obj, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Trace_obj, `en)}

${help.ComposeMethodHelp(model.obj.Trace_obj, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Trace_obj() {block?}
Gurax_DeclareConstructor(Trace_obj)
{
	Declare(VTYPE_Trace_obj, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Trace_obj` instance.
)""");
}

Gurax_ImplementConstructor(Trace_obj)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Trace_obj> pTrace_obj(new Trace_obj());
	return argument.ReturnValue(processor, new Value_Trace_obj(pTrace_obj.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Trace_obj#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Trace_obj, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Trace_obj, MethodSkeleton)
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
// model.obj.Trace_obj#propSkeleton
Gurax_DeclareProperty_R(Trace_obj, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Trace_obj, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Trace_obj
//------------------------------------------------------------------------------
VType_Trace_obj VTYPE_Trace_obj("Trace_obj");

void VType_Trace_obj::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Trace_obj));
	// Assignment of method
	Assign(Gurax_CreateMethod(Trace_obj, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Trace_obj, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Trace_obj
//------------------------------------------------------------------------------
VType& Value_Trace_obj::vtype = VTYPE_Trace_obj;


String Value_Trace_obj::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetTrace_obj().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
