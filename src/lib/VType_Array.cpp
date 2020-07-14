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
// Array(elemType:Symbol, n:Number) {block?}
Gurax_DeclareConstructor(Array)
{
	Declare(VTYPE_Array, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an `Array` instance.");
}

Gurax_ImplementConstructor(Array)
{
	// Arguments
	ArgPicker args(argument);
	Array::ElemTypeT& elemType = Array::SymbolToElemType(args.PickSymbol());
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::SymbolError, "invalid symbol for elemType");
		return Value::nil();
	}
	size_t nElems = args.PickNumberPos<size_t>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Array> pArray(new Array(elemType, nElems, new MemoryHeap(elemType.bytes * nElems)));
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
// Array#bytes
Gurax_DeclareProperty_R(Array, bytes)
{
	Declare(VTYPE_Pointer, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The array's size in bytes.");
}

Gurax_ImplementPropertyGetter(Array, bytes)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Memory& memory = valueThis.GetArray().GetMemory();
	return new Value_Number(memory.GetBytes());
}

// Array#p
Gurax_DeclareProperty_R(Array, p)
{
	Declare(VTYPE_Pointer, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A `Pointer` instance that points at the first address of the Array's buffer.");
}

Gurax_ImplementPropertyGetter(Array, p)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Memory& memory = valueThis.GetArray().GetMemory();
	return new Value_Pointer(new Pointer_Memory(memory.Reference()));
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
	Assign(Gurax_CreateProperty(Array, bytes));
	Assign(Gurax_CreateProperty(Array, p));
}

//------------------------------------------------------------------------------
// Value_Array
//------------------------------------------------------------------------------
VType& Value_Array::vtype = VTYPE_Array;

String Value_Array::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetArray().ToString(ss));
}

Value* Value_Array::DoIndexGet(const Index& index) const
{
	//const ValueList& valuesIndex = index.GetValueOwner();
	return Value::nil();
}

void Value_Array::DoIndexSet(const Index& index, RefPtr<Value> pValue)
{
	//const ValueList& valuesIndex = index.GetValueOwner();
	Array& array = GetArray();
	size_t idx;
	Double num;
	array.GetElemType().IndexSet(array.GetPointerC<void>(), idx, num);
}

}
