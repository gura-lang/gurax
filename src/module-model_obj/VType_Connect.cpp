//==============================================================================
// VType_Connect.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Connect, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Connect, `en)}

${help.ComposeMethodHelp(model.obj.Connect, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Connect() {block?}
Gurax_DeclareConstructor(Connect)
{
	Declare(VTYPE_Connect, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Connect` instance.
)""");
}

Gurax_ImplementConstructor(Connect)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Connect> pConnect(new Connect());
	return argument.ReturnValue(processor, new Value_Connect(pConnect.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Connect#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Connect, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Connect, MethodSkeleton)
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
// model.obj.Connect#propSkeleton
Gurax_DeclareProperty_R(Connect, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Connect, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Connect
//------------------------------------------------------------------------------
VType_Connect VTYPE_Connect("Connect");

void VType_Connect::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Connect));
	// Assignment of method
	Assign(Gurax_CreateMethod(Connect, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Connect, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Connect
//------------------------------------------------------------------------------
VType& Value_Connect::vtype = VTYPE_Connect;

String Value_Connect::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetConnect().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
