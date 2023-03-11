//==============================================================================
// VType_Usemtl.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Usemtl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Usemtl, `en)}

${help.ComposeMethodHelp(model.obj.Usemtl, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Usemtl() {block?}
Gurax_DeclareConstructor(Usemtl)
{
	Declare(VTYPE_Usemtl, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Usemtl` instance.
)""");
}

Gurax_ImplementConstructor(Usemtl)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Usemtl> pUsemtl(new Usemtl());
	return argument.ReturnValue(processor, new Value_Usemtl(pUsemtl.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Usemtl#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Usemtl, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Usemtl, MethodSkeleton)
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
// model.obj.Usemtl#propSkeleton
Gurax_DeclareProperty_R(Usemtl, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Usemtl, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Usemtl
//------------------------------------------------------------------------------
VType_Usemtl VTYPE_Usemtl("Usemtl");

void VType_Usemtl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Usemtl));
	// Assignment of method
	Assign(Gurax_CreateMethod(Usemtl, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Usemtl, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Usemtl
//------------------------------------------------------------------------------
VType& Value_Usemtl::vtype = VTYPE_Usemtl;

String Value_Usemtl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetUsemtl().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
