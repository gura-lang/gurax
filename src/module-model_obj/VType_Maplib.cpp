//==============================================================================
// VType_Maplib.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Maplib, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Maplib, `en)}

${help.ComposeMethodHelp(model.obj.Maplib, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Maplib() {block?}
Gurax_DeclareConstructor(Maplib)
{
	Declare(VTYPE_Maplib, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Maplib` instance.
)""");
}

Gurax_ImplementConstructor(Maplib)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Maplib> pMaplib(new Maplib());
	return argument.ReturnValue(processor, new Value_Maplib(pMaplib.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Maplib#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Maplib, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Maplib, MethodSkeleton)
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
// model.obj.Maplib#propSkeleton
Gurax_DeclareProperty_R(Maplib, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Maplib, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Maplib
//------------------------------------------------------------------------------
VType_Maplib VTYPE_Maplib("Maplib");

void VType_Maplib::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Maplib));
	// Assignment of method
	Assign(Gurax_CreateMethod(Maplib, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Maplib, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Maplib
//------------------------------------------------------------------------------
VType& Value_Maplib::vtype = VTYPE_Maplib;


String Value_Maplib::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetMaplib().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
