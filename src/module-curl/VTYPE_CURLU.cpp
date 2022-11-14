//==============================================================================
// VType_CURLU.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(curl.CURLU, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(curl.CURLU, `en)}

${help.ComposeMethodHelp(curl.CURLU, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// curl.CURLU() {block?}
Gurax_DeclareConstructor(CURLU)
{
	Declare(VTYPE_CURLU, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `curl.CURLU` instance.
)**");
}

Gurax_ImplementConstructor(CURLU)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	//RefPtr<CURLU> CURLU(new CURLU());
	//return argument.ReturnValue(processor, new Value_CURLU(CURLU.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// curl.CURLU#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(CURLU, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(CURLU, MethodSkeleton)
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
// curl.CURLU#propSkeleton
Gurax_DeclareProperty_R(CURLU, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(CURLU, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_CURLU
//------------------------------------------------------------------------------
VType_CURLU VTYPE_CURLU("CURLU");

void VType_CURLU::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(CURLU));
	// Assignment of method
	Assign(Gurax_CreateMethod(CURLU, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(CURLU, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_CURLU
//------------------------------------------------------------------------------
VType& Value_CURLU::vtype = VTYPE_CURLU;

String Value_CURLU::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "curl.CURLU");
}

Gurax_EndModuleScope(curl)
