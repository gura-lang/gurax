//==============================================================================
// VType_C_interp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.C_interp, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.C_interp, `en)}

${help.ComposeMethodHelp(model.obj.C_interp, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.C_interp() {block?}
Gurax_DeclareConstructor(C_interp)
{
	Declare(VTYPE_C_interp, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.C_interp` instance.
)""");
}

Gurax_ImplementConstructor(C_interp)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<C_interp> pC_interp(new C_interp());
	return argument.ReturnValue(processor, new Value_C_interp(pC_interp.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.C_interp#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(C_interp, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(C_interp, MethodSkeleton)
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
// model.obj.C_interp#propSkeleton
Gurax_DeclareProperty_R(C_interp, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(C_interp, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_C_interp
//------------------------------------------------------------------------------
VType_C_interp VTYPE_C_interp("C_interp");

void VType_C_interp::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(C_interp));
	// Assignment of method
	Assign(Gurax_CreateMethod(C_interp, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(C_interp, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_C_interp
//------------------------------------------------------------------------------
VType& Value_C_interp::vtype = VTYPE_C_interp;


String Value_C_interp::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetC_interp().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
