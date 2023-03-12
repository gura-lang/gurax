//==============================================================================
// VType_ObjectName.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.ObjectName, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.ObjectName, `en)}

${help.ComposeMethodHelp(model.obj.ObjectName, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.ObjectName() {block?}
Gurax_DeclareConstructor(ObjectName)
{
	Declare(VTYPE_ObjectName, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.ObjectName` instance.
)""");
}

Gurax_ImplementConstructor(ObjectName)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<ObjectName> pObjectName(new ObjectName());
	return argument.ReturnValue(processor, new Value_ObjectName(pObjectName.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.ObjectName#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(ObjectName, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(ObjectName, MethodSkeleton)
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
// model.obj.ObjectName#propSkeleton
Gurax_DeclareProperty_R(ObjectName, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(ObjectName, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_ObjectName
//------------------------------------------------------------------------------
VType_ObjectName VTYPE_ObjectName("ObjectName");

void VType_ObjectName::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(ObjectName));
	// Assignment of method
	Assign(Gurax_CreateMethod(ObjectName, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(ObjectName, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_ObjectName
//------------------------------------------------------------------------------
VType& Value_ObjectName::vtype = VTYPE_ObjectName;


String Value_ObjectName::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetObjectName().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
