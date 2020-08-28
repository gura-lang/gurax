//==============================================================================
// VType_Tuple.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Tuple() {block?}
Gurax_DeclareConstructor(Tuple)
{
	Declare(VTYPE_Tuple, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Tuple` instance.");
}

Gurax_ImplementConstructor(Tuple)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	//RefPtr<Tuple> pTuple(new Tuple());
	//return argument.ReturnValue(processor, new Value_Tuple(pTuple.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Tuple#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Tuple, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Tuple, MethodSkeleton)
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
// Tuple#propSkeleton
Gurax_DeclareProperty_R(Tuple, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Tuple, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Tuple
//------------------------------------------------------------------------------
VType_Tuple VTYPE_Tuple("Tuple");

void VType_Tuple::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Tuple));
	// Assignment of method
	Assign(Gurax_CreateMethod(Tuple, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Tuple, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Tuple
//------------------------------------------------------------------------------
VType& Value_Tuple::vtype = VTYPE_Tuple;

String Value_Tuple::ToString(const StringStyle& ss) const
{
	if (ss.IsBracket()) {
		return ToStringGeneric(ss, String().Format("%zuitems", GetValueOwner().size()));
	}
	return GetValueOwner().ToString(StringStyle::Quote_NilVisible);
}

}
