//==============================================================================
// VType_Solid.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.stl.Solid, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.stl.Solid, `en)}

${help.ComposeMethodHelp(model.stl.Solid, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.stl.Solid(stream as Stream) {block?}
Gurax_DeclareConstructor(Solid)
{
	Declare(VTYPE_Solid, Flag::None);
	DeclareArg("stream", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `model.stl.Solid` instance.
)**");
}

Gurax_ImplementConstructor(Solid)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Solid> pSolid(new Solid(stream.Reference()));
	return argument.ReturnValue(processor, new Value_Solid(pSolid.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.stl.Solid#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Solid, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Solid, MethodSkeleton)
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
// model.stl.Solid#propSkeleton
Gurax_DeclareProperty_R(Solid, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Solid, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Solid
//------------------------------------------------------------------------------
VType_Solid VTYPE_Solid("Solid");

void VType_Solid::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Solid));
	// Assignment of method
	Assign(Gurax_CreateMethod(Solid, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Solid, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Solid
//------------------------------------------------------------------------------
VType& Value_Solid::vtype = VTYPE_Solid;

String Value_Solid::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSolid().ToString(ss));
}

Gurax_EndModuleScope(model_stl)
