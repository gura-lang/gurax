//==============================================================================
// VType_Array.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

Value* ConstructArray(Processor& processor, Argument& argument,
	const Value& arg, const ValueList& values, Array::ElemTypeT& elemType);

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
// Array(elemType:Symbol, arg, dimSize*:Number) {block?}
Gurax_DeclareConstructor(Array)
{
	Declare(VTYPE_Array, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("arg", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dimSize", VTYPE_Number, ArgOccur::ZeroOrMore, ArgFlag::None);
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
	const Value& arg = args.PickValue();
	const ValueList& values = args.PickList();
	// Function body
	return ConstructArray(processor, argument, arg, values, elemType);
}

// Array.float(arg, dimSize*:Number) {block?}
Gurax_DeclareMethodAlias(Array, float_, "float")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("arg", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dimSize", VTYPE_Number, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Array, float_)
{
	// Arguments
	ArgPicker args(argument);
	const Value& arg = args.PickValue();
	const ValueList& values = args.PickList();
	// Function body
	return ConstructArray(processor, argument, arg, values, Array::ElemType::Float);
}

Value* ConstructArray(Processor& processor, Argument& argument,
	const Value& arg, const ValueList& values, Array::ElemTypeT& elemType)
{
	RefPtr<Array> pArray;
	if (arg.IsType(VTYPE_Number)) {
		Array::DimSizes dimSizes;
		dimSizes.reserve(values.size() + 1);
		dimSizes.push_back(Value_Number::GetNumberPos<size_t>(arg));
		for (const Value* pValue : values) {
			dimSizes.push_back(Value_Number::GetNumberPos<size_t>(*pValue));
		}
		if (Error::IsIssued()) return Value::nil();
		pArray.reset(Array::Create(elemType, std::move(dimSizes)));
		if (!pArray) return Value::nil();
	} else if (arg.IsType(VTYPE_List)) {

	} else {
		Error::Issue(ErrorType::TypeError, "invalid argument type");
		return Value::nil();
	}
	return argument.ReturnValue(processor, new Value_Array(pArray.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Array#Cast(elemType:Symbol) {block?}
Gurax_DeclareMethod(Array, Cast)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a new Array that contains elements casted by the specified element type.\n");
}

Gurax_ImplementMethod(Array, Cast)
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
	return argument.ReturnValue(processor,
				new Value_Array(valueThis.GetArray().CreateCasted(elemType)));
}

// Array#Each() {block?}
Gurax_DeclareMethod(Array, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Array, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new VType_Array::Iterator_Each(valueThis.GetArray().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// Array#Inject(values:Iterator, offset?:Number):reduce
Gurax_DeclareMethod(Array, Inject)
{
	Declare(VTYPE_Iterator, Flag::Reduce);
	DeclareArg("values", VTYPE_Iterator, ArgOccur::Once, ArgFlag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Injects values from an Iterator.");
}

Gurax_ImplementMethod(Array, Inject)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Iterator& iterator = args.PickIterator();
	size_t offset = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	if (!valueThis.GetArray().InjectElems(iterator, offset)) return Value::nil();
	return valueThis.Reference();
}

// Array#ToList()
Gurax_DeclareMethod(Array, ToList)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Convets the Array to a List.");
}

Gurax_ImplementMethod(Array, ToList)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return valueThis.GetArray().ToList();
}

// Array#ToString(codec?:Codec)
Gurax_DeclareMethod(Array, ToString)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("codec", VTYPE_Codec, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Array, ToString)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Codec& codec = args.IsValid()? args.Pick<Value_Codec>().GetCodec() : *Codec::Dumb;
	// Function body
	Array& array = valueThis.GetArray();
	String str;
	codec.GetDecoder().Decode(str, array.GetPointerC<UInt8>(), array.GetDimSizes().GetLength());
	return new Value_String(str);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Array#bytes
Gurax_DeclareProperty_R(Array, bytes)
{
	Declare(VTYPE_Number, Flag::None);
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

// Array#bytesPerElem
Gurax_DeclareProperty_R(Array, bytesPerElem)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The array's element size in bytes.");
}

Gurax_ImplementPropertyGetter(Array, bytesPerElem)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetArray().GetElemType().bytes);
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
	Declare(VTYPE_Number, Flag::None);
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
	Assign(Gurax_CreateMethod(Array, Cast));
	Assign(Gurax_CreateMethod(Array, Each));
	Assign(Gurax_CreateMethod(Array, Inject));
	Assign(Gurax_CreateMethod(Array, ToList));
	Assign(Gurax_CreateMethod(Array, ToString));
	// Assignment of property
	Assign(Gurax_CreateProperty(Array, bytes));
	Assign(Gurax_CreateProperty(Array, bytesPerElem));
	Assign(Gurax_CreateProperty(Array, elemType));
	Assign(Gurax_CreateProperty(Array, len));
	Assign(Gurax_CreateProperty(Array, p));
}

//------------------------------------------------------------------------------
// VType_Array::Iterator_Each
//------------------------------------------------------------------------------

Value* VType_Array::Iterator_Each::DoNextValue()
{
	if (_idx >= _len) return nullptr;
	RefPtr<Value> pValue(_pArray->IndexGet(_idx));
	_idx++;
	return pValue.release();
}

String VType_Array::Iterator_Each::ToString(const StringStyle& ss) const
{
	return "Array.Each";
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
	const Array& array = GetArray();
	const ValueList& valuesIndex = index.GetValueOwner();
	const Array::DimSizes& dimSizes = array.GetDimSizes();
	if (valuesIndex.size() != dimSizes.size()) {
		Error::Issue(ErrorType::IndexError, "invalid number of indices");
		return Value::nil();
	}
	size_t idx = 0;
	size_t idxMult = 1;
	auto ppValueIndex = valuesIndex.rbegin();
	auto pDimSize = dimSizes.rbegin();
	for (;;) {
		const Value& valueIndex = **ppValueIndex;
		if (!valueIndex.IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::IndexError, "invalid value type of indices");
			return Value::nil();
		}
		size_t dim = Value_Number::GetNumberNonNeg<size_t>(valueIndex);
		if (Error::IsIssued()) return Value::nil();
		if (dim >= *pDimSize) {
			Error::Issue(ErrorType::IndexError, "index is out of range");
			return Value::nil();
		}
		idx += dim * idxMult;
		ppValueIndex++;
		if (ppValueIndex == valuesIndex.rend()) break;
		idxMult *= *pDimSize;
		pDimSize++;
	}
	return array.IndexGet(idx);
}

void Value_Array::DoIndexSet(const Index& index, RefPtr<Value> pValue)
{
	Array& array = GetArray();
	const ValueList& valuesIndex = index.GetValueOwner();
	const Array::DimSizes& dimSizes = array.GetDimSizes();
	if (valuesIndex.size() != dimSizes.size()) {
		Error::Issue(ErrorType::IndexError, "invalid number of indices");
		return;
	}
	size_t idx = 0;
	size_t idxMult = 1;
	auto ppValueIndex = valuesIndex.rbegin();
	auto pDimSize = dimSizes.rbegin();
	for (;;) {
		const Value& valueIndex = **ppValueIndex;
		if (!valueIndex.IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::IndexError, "invalid value type of indices");
			return;
		}
		size_t dim = Value_Number::GetNumberNonNeg<size_t>(valueIndex);
		if (Error::IsIssued()) return;
		if (dim >= *pDimSize) {
			Error::Issue(ErrorType::IndexError, "index is out of range");
			return;
		}
		idx += dim * idxMult;
		ppValueIndex++;
		if (ppValueIndex == valuesIndex.rend()) break;
		idxMult *= *pDimSize;
		pDimSize++;
	}
	array.IndexSet(idx, *pValue);
}

}
