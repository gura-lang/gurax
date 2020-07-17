//==============================================================================
// VType_Array.cpp
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
// Array(elemType:Symbol, dimSize+:Number) {block?}
Gurax_DeclareConstructor(Array)
{
	Declare(VTYPE_Array, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dimSize", VTYPE_Number, ArgOccur::OnceOrMore, ArgFlag::None);
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
	Array::DimSizes dimSizes = args.PickNumListPos<size_t>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Array> pArray(Array::Create(elemType, std::move(dimSizes)));
	if (!pArray) return Value::nil();
	return argument.ReturnValue(processor, new Value_Array(pArray.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Array#CreateCasted(elemType:Symbol)
Gurax_DeclareMethod(Array, CreateCasted)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a new Array that contains elements casted by the specified element type.\n");
}

Gurax_ImplementMethod(Array, CreateCasted)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Array::ElemTypeT& elemType = Array::SymbolToElemType(args.PickSymbol());
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::SymbolError, "invalid symbol for elemType");
		return Value::nil();
	}
	// Function body
	return new Value_Array(valueThis.GetArray().CreateCasted(elemType));
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

// Array#elemType
Gurax_DeclareProperty_R(Array, elemType)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A symbol that represents the array's element type.");
}

Gurax_ImplementPropertyGetter(Array, elemType)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetArray().GetElemType().pSymbol);
}

// Array#len
Gurax_DeclareProperty_R(Array, len)
{
	Declare(VTYPE_Pointer, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The number of elements in the array.");
}

Gurax_ImplementPropertyGetter(Array, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetArray().GetDimSizes().GetLength());
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
	Assign(Gurax_CreateMethod(Array, CreateCasted));
	// Assignment of property
	Assign(Gurax_CreateProperty(Array, bytes));
	Assign(Gurax_CreateProperty(Array, elemType));
	Assign(Gurax_CreateProperty(Array, len));
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
#if 0
	Array& array = GetArray();
	size_t idx;
	Double num;
	array.GetElemType().IndexSet(array.GetPointerC<void>(), idx, num);
#endif
}

}
