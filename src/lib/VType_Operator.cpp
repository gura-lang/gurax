//==============================================================================
// VType_Operator.cpp
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
// Operator(symbol:Symbol) {block?}
Gurax_DeclareConstructor(Operator)
{
	Declare(VTYPE_Operator, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Operator` instance.");
}

Gurax_ImplementConstructor(Operator)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	
	//RefPtr<Operator> pOperator(new Operator());
	//return argument.ReturnValue(processor, new Value_Operator(pOperator.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Operator#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Operator, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Operator, MethodSkeleton)
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
// Operator#propSkeleton
Gurax_DeclareProperty_R(Operator, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Operator, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Operator
//------------------------------------------------------------------------------
VType_Operator VTYPE_Operator("Operator");

void VType_Operator::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Operator));
	// Assignment of method
	Assign(Gurax_CreateMethod(Operator, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Operator, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Operator
//------------------------------------------------------------------------------
VType& Value_Operator::vtype = VTYPE_Operator;

String Value_Operator::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "Operator");
}

}
