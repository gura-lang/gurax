//==============================================================================
// VType_CallObj.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.CallObj, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.CallObj, `en)}

${help.ComposeMethodHelp(model.obj.CallObj, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.CallObj() {block?}
Gurax_DeclareConstructor(CallObj)
{
	Declare(VTYPE_CallObj, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.CallObj` instance.
)""");
}

Gurax_ImplementConstructor(CallObj)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<CallObj> pCallObj(new CallObj());
	return argument.ReturnValue(processor, new Value_CallObj(pCallObj.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.CallObj#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(CallObj, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(CallObj, MethodSkeleton)
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
// model.obj.CallObj#propSkeleton
Gurax_DeclareProperty_R(CallObj, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(CallObj, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_CallObj
//------------------------------------------------------------------------------
VType_CallObj VTYPE_CallObj("CallObj");

void VType_CallObj::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(CallObj));
	// Assignment of method
	Assign(Gurax_CreateMethod(CallObj, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(CallObj, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_CallObj
//------------------------------------------------------------------------------
VType& Value_CallObj::vtype = VTYPE_CallObj;

String Value_CallObj::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetCallObj().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
