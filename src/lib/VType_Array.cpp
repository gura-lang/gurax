//==============================================================================
// VType_Array.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax-tentative.h>

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
// Array(elemType:Symbol) {block?}
Gurax_DeclareConstructor(Array)
{
	Declare(VTYPE_Array, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Array` instance.");
}

Gurax_ImplementConstructor(Array)
{
	// Arguments
	ArgPicker args(argument);
	Array::ElemType elemType = Array::SymbolToElemType(args.PickSymbol());
	if (elemType == Array::ElemType::None) {
		Error::Issue(ErrorType::SymbolError, "invalid symbol for elemType");
		return Value::nil();
	}
	// Function body
	RefPtr<Array> pArray(new Array(elemType, nullptr));
	return argument.ReturnValue(processor, new Value_Array(pArray.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Array#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Array, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Array, MethodSkeleton)
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
// Array#propSkeleton
Gurax_DeclareProperty_R(Array, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Array, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Array
//------------------------------------------------------------------------------
VType_Array VTYPE_Array("Array");

void VType_Array::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Array));
	// Assignment of method
	Assign(Gurax_CreateMethod(Array, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Array, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Array
//------------------------------------------------------------------------------
VType& Value_Array::vtype = VTYPE_Array;

String Value_Array::ToString(const StringStyle& ss) const
{
	return String().Format("<Array:%s>", GetArray().ToString(ss).c_str());
}

}
