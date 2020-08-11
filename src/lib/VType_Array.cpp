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
// Array(elemType:Symbol, init*) {block?}
Gurax_DeclareConstructor(Array)
{
	Declare(VTYPE_Array, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("init", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
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
	const ValueList& values = args.PickList();
	RefPtr<Array> pArray;
	if (values.empty()) {
		pArray.reset(Array::Create1d(elemType, 1));
	} else if (values.size() == 1 && values.front()->IsType(VTYPE_List)) {
		pArray.reset(Value_List::GetValueOwner(*values.front()).CreateArray(elemType));
	} else if (values.GetVTypeOfElems().IsIdentical(VTYPE_Number)) {
		DimSizes dimSizes(Value_Number::GetNumListPos<size_t>(values));
		if (Error::IsIssued()) return Value::nil();
		pArray.reset(Array::Create(elemType, std::move(dimSizes)));
	} else {
		Error::Issue(ErrorType::TypeError, "invalid argument");
	}
	if (!pArray) return Value::nil();
	// Function body
	return argument.ReturnValue(processor, new Value_Array(pArray.release()));
}

// ConstructArray(init*) {block?}
Gurax_DeclareFunction(ConstructArray)
{
	Declare(VTYPE_Array, Flag::None);
	DeclareArg("init", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(ConstructArray)
{
	// Arguments
	ArgPicker args(argument);
	Array::ElemTypeT& elemType = Array::AtSymbolToElemType(GetSymbol());
	const ValueList& values = args.PickList();
	RefPtr<Array> pArray;
	if (values.empty()) {
		pArray.reset(Array::Create1d(elemType, 1));
	} else if (values.size() == 1 && values.front()->IsType(VTYPE_List)) {
		pArray.reset(Value_List::GetValueOwner(*values.front()).CreateArray(elemType));
	} else if (values.GetVTypeOfElems().IsIdentical(VTYPE_Number)) {
		DimSizes dimSizes(Value_Number::GetNumListPos<size_t>(values));
		if (Error::IsIssued()) return Value::nil();
		pArray.reset(Array::Create(elemType, std::move(dimSizes)));
	} else {
		Error::Issue(ErrorType::TypeError, "invalid argument");
	}
	if (!pArray) return Value::nil();
	// Function body
	return argument.ReturnValue(processor, new Value_Array(pArray.release()));
}

//-----------------------------------------------------------------------------
// Implementation of class method
//-----------------------------------------------------------------------------
// Array.Identity(elemType:Symbol, n:Number)
Gurax_DeclareClassMethod(Array, Identity)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethod(Array, Identity)
{
	// Arguments
	ArgPicker args(argument);
	Array::ElemTypeT& elemType = Array::SymbolToElemType(args.PickSymbol());
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::SymbolError, "invalid symbol for elemType");
		return Value::nil();
	}
	Int n = args.PickNumberPos<Int>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Array> pArray(Array::CreateIdentity(elemType, n, 1.));
	return new Value_Array(pArray.release());
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
	codec.GetDecoder().Decode(str, array.GetPointerC<UInt8>(), array.GetDimSizes().CalcLength());
	return new Value_String(str);
}

// Array#Transpose() {block?}
Gurax_DeclareMethod(Array, Transpose)
{
	Declare(VTYPE_Array, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Array, Transpose)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	Array& array = valueThis.GetArray();
	RefPtr<Array> pArray(array.Transpose());
	if (!pArray) return Value::nil();
	return argument.ReturnValue(processor, new Value_Array(pArray.release()));
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
		"The `array`'s whole size in bytes.");
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
		"The `Array`'s element size in bytes.");
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
		"A symbol that represents the `Array`'s element type.");
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
		"The number of elements in the `Array`.");
}

Gurax_ImplementPropertyGetter(Array, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetArray().GetDimSizes().CalcLength());
}

// Array#p
Gurax_DeclareProperty_R(Array, p)
{
	Declare(VTYPE_Pointer, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A `Pointer` instance that points at the first address of the `Array`'s buffer.");
}

Gurax_ImplementPropertyGetter(Array, p)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Memory& memory = valueThis.GetArray().GetMemory();
	return new Value_Pointer(new Pointer_Memory(memory.Reference()));
}

// Array#shape
Gurax_DeclareProperty_R(Array, shape)
{
	Declare(VTYPE_Pointer, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A list of dimension of the array.");
}

Gurax_ImplementPropertyGetter(Array, shape)
{
	auto& valueThis = GetValueThis(valueTarget);
	const DimSizes& dimSizes = valueThis.GetArray().GetDimSizes();
	RefPtr<ValueOwner> pValues(new ValueOwner());
	pValues->reserve(dimSizes.size());
	for (size_t dimSize : dimSizes) pValues->push_back(new Value_Number(dimSize));
	return new Value_List(VTYPE_Number, pValues.release());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Array + Array
Gurax_ImplementOpBinary(Add, Array, Array)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Add(arrayL, arrayR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array + Number
Gurax_ImplementOpBinary(Add, Array, Number)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	RefPtr<Array> pArrayRtn(Array::Add(arrayL, numR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Number + Array
Gurax_ImplementOpBinary(Add, Number, Array)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Add(arrayR, numL));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array + Complex
Gurax_ImplementOpBinary(Add, Array, Complex)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	RefPtr<Array> pArrayRtn(Array::Add(arrayL, numR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Complex + Array
Gurax_ImplementOpBinary(Add, Complex, Array)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Add(arrayR, numL));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array - Array
Gurax_ImplementOpBinary(Sub, Array, Array)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Sub(arrayL, arrayR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array - Number
Gurax_ImplementOpBinary(Sub, Array, Number)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	RefPtr<Array> pArrayRtn(Array::Sub(arrayL, numR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Number - Array
Gurax_ImplementOpBinary(Sub, Number, Array)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Sub(numL, arrayR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array - Complex
Gurax_ImplementOpBinary(Sub, Array, Complex)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	RefPtr<Array> pArrayRtn(Array::Sub(arrayL, numR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Complex - Array
Gurax_ImplementOpBinary(Sub, Complex, Array)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Sub(numL, arrayR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array * Array
Gurax_ImplementOpBinary(Mul, Array, Array)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Mul(arrayL, arrayR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array * Number
Gurax_ImplementOpBinary(Mul, Array, Number)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	RefPtr<Array> pArrayRtn(Array::Mul(arrayL, numR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Number * Array
Gurax_ImplementOpBinary(Mul, Number, Array)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Mul(arrayR, numL));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array * Complex
Gurax_ImplementOpBinary(Mul, Array, Complex)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	RefPtr<Array> pArrayRtn(Array::Mul(arrayL, numR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Complex * Array
Gurax_ImplementOpBinary(Mul, Complex, Array)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Mul(arrayR, numL));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array / Array
Gurax_ImplementOpBinary(Div, Array, Array)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Div(arrayL, arrayR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array / Number
Gurax_ImplementOpBinary(Div, Array, Number)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	RefPtr<Array> pArrayRtn(Array::Div(arrayL, numR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Number / Array
Gurax_ImplementOpBinary(Div, Number, Array)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Div(numL, arrayR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array / Complex
Gurax_ImplementOpBinary(Div, Array, Complex)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	RefPtr<Array> pArrayRtn(Array::Div(arrayL, numR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Complex / Array
Gurax_ImplementOpBinary(Div, Complex, Array)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Div(numL, arrayR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
}

// Array |.| Array
Gurax_ImplementOpBinary(Dot, Array, Array)
{
	const Array& arrayL = Value_Array::GetArray(valueL);
	const Array& arrayR = Value_Array::GetArray(valueR);
	RefPtr<Array> pArrayRtn(Array::Dot(arrayL, arrayR));
	if (!pArrayRtn) return Value::nil();
	return new Value_Array(pArrayRtn.release());
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
	// Constructor
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@bool"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@int8"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@uint8"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@int16"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@uint16"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@int32"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@uint32"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@int64"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@uint64"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@half"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@float"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@double"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@complex"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@char"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@uchar"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@short"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@ushort"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@int"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@uint"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@long"));
	frameOuter.Assign(Gurax_CreateFunctionAlias(ConstructArray, "@ulong"));
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Array, Identity));
	// Assignment of method
	Assign(Gurax_CreateMethod(Array, Cast));
	Assign(Gurax_CreateMethod(Array, Each));
	Assign(Gurax_CreateMethod(Array, Inject));
	Assign(Gurax_CreateMethod(Array, ToList));
	Assign(Gurax_CreateMethod(Array, ToString));
	Assign(Gurax_CreateMethod(Array, Transpose));
	// Assignment of property
	Assign(Gurax_CreateProperty(Array, bytes));
	Assign(Gurax_CreateProperty(Array, bytesPerElem));
	Assign(Gurax_CreateProperty(Array, elemType));
	Assign(Gurax_CreateProperty(Array, len));
	Assign(Gurax_CreateProperty(Array, p));
	Assign(Gurax_CreateProperty(Array, shape));
	// Assignment of operator
	Gurax_AssignOpBinary(Add,	Array, Array);
	Gurax_AssignOpBinary(Add,	Array, Number);
	Gurax_AssignOpBinary(Add,	Number, Array);
	Gurax_AssignOpBinary(Add,	Array, Complex);
	Gurax_AssignOpBinary(Add,	Complex, Array);
	Gurax_AssignOpBinary(Sub,	Array, Array);
	Gurax_AssignOpBinary(Mul,	Array, Array);
	Gurax_AssignOpBinary(Div,	Array, Array);
	Gurax_AssignOpBinary(Dot,	Array, Array);
}

//------------------------------------------------------------------------------
// VType_Array::Iterator_Each
//------------------------------------------------------------------------------

Value* VType_Array::Iterator_Each::DoNextValue()
{
	if (_idx >= _len) return nullptr;
	RefPtr<Value> pValue(_pArray->IndexGetValue(_idx));
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
	const DimSizes& dimSizes = array.GetDimSizes();
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
	return array.IndexGetValue(idx);
}

void Value_Array::DoIndexSet(const Index& index, RefPtr<Value> pValue)
{
	Array& array = GetArray();
	const ValueList& valuesIndex = index.GetValueOwner();
	const DimSizes& dimSizes = array.GetDimSizes();
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
	array.IndexSetValue(idx, *pValue);
}

}
