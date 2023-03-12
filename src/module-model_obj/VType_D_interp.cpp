//==============================================================================
// VType_D_interp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.D_interp, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.D_interp, `en)}

${help.ComposeMethodHelp(model.obj.D_interp, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.D_interp() {block?}
Gurax_DeclareConstructor(D_interp)
{
	Declare(VTYPE_D_interp, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.D_interp` instance.
)""");
}

Gurax_ImplementConstructor(D_interp)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<D_interp> pD_interp(new D_interp());
	return argument.ReturnValue(processor, new Value_D_interp(pD_interp.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.D_interp#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(D_interp, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(D_interp, MethodSkeleton)
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
// model.obj.D_interp#propSkeleton
Gurax_DeclareProperty_R(D_interp, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(D_interp, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_D_interp
//------------------------------------------------------------------------------
VType_D_interp VTYPE_D_interp("D_interp");

void VType_D_interp::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(D_interp));
	// Assignment of method
	Assign(Gurax_CreateMethod(D_interp, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(D_interp, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_D_interp
//------------------------------------------------------------------------------
VType& Value_D_interp::vtype = VTYPE_D_interp;


String Value_D_interp::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetD_interp().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
