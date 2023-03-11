//==============================================================================
// VType_Csh.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Csh, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Csh, `en)}

${help.ComposeMethodHelp(model.obj.Csh, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Csh() {block?}
Gurax_DeclareConstructor(Csh)
{
	Declare(VTYPE_Csh, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Csh` instance.
)""");
}

Gurax_ImplementConstructor(Csh)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Csh> pCsh(new Csh());
	return argument.ReturnValue(processor, new Value_Csh(pCsh.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Csh#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Csh, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Csh, MethodSkeleton)
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
// model.obj.Csh#propSkeleton
Gurax_DeclareProperty_R(Csh, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Csh, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Csh
//------------------------------------------------------------------------------
VType_Csh VTYPE_Csh("Csh");

void VType_Csh::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Csh));
	// Assignment of method
	Assign(Gurax_CreateMethod(Csh, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Csh, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Csh
//------------------------------------------------------------------------------
VType& Value_Csh::vtype = VTYPE_Csh;

String Value_Csh::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetCsh().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
