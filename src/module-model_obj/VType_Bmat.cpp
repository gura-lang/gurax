//==============================================================================
// VType_Bmat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Bmat, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Bmat, `en)}

${help.ComposeMethodHelp(model.obj.Bmat, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Bmat() {block?}
Gurax_DeclareConstructor(Bmat)
{
	Declare(VTYPE_Bmat, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Bmat` instance.
)""");
}

Gurax_ImplementConstructor(Bmat)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Bmat> pBmat(new Bmat());
	return argument.ReturnValue(processor, new Value_Bmat(pBmat.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Bmat#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Bmat, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Bmat, MethodSkeleton)
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
// model.obj.Bmat#propSkeleton
Gurax_DeclareProperty_R(Bmat, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Bmat, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Bmat
//------------------------------------------------------------------------------
VType_Bmat VTYPE_Bmat("Bmat");

void VType_Bmat::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Bmat));
	// Assignment of method
	Assign(Gurax_CreateMethod(Bmat, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Bmat, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Bmat
//------------------------------------------------------------------------------
VType& Value_Bmat::vtype = VTYPE_Bmat;

String Value_Bmat::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetBmat().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
