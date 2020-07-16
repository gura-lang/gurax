//==============================================================================
// Array.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax-tentative.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------------
Array::Array(ElemTypeT& elemType, size_t nElems, Memory* pMemory) :
				_elemType(elemType), _nElems(nElems), _pMemory(pMemory)
{
}

template<typename T_Elem> void IndexSet_T(void* p, size_t idx, const Value& value)
{
	*(reinterpret_cast<T_Elem*>(p) + idx) = Value_Number::GetNumber<T_Elem>(value);
}

template<> void IndexSet_T<Complex>(void* p, size_t idx, const Value& value)
{
	*(reinterpret_cast<Complex*>(p) + idx) = Value_Complex::GetComplexRobust(value);
}

template<typename T_Elem> Value* IndexGet_T(const void* p, size_t idx)
{
	return new Value_Number(*(reinterpret_cast<const T_Elem*>(p) + idx));
}

template<> Value* IndexGet_T<Complex>(const void* p, size_t idx)
{
	return new Value_Complex(*(reinterpret_cast<const Complex*>(p) + idx));
}

template<typename T_Elem> void InjectElems_T(void* p, size_t offset, size_t nElems, const ValueList& values)
{
	T_Elem* pElem = reinterpret_cast<T_Elem*>(p) + offset;
	auto ppValue = values.begin();
	for (size_t i = 0; i < nElems; i++, pElem++, ppValue++) {
		*pElem = Value_Number::GetNumber<T_Elem>(**ppValue);
	}
}

template<> void InjectElems_T<Complex>(void* p, size_t offset, size_t nElems, const ValueList& values)
{
	Complex* pElem = reinterpret_cast<Complex*>(p) + offset;
	auto ppValue = values.begin();
	for (size_t i = 0; i < nElems; i++, pElem++, ppValue++) {
		*pElem = Value_Complex::GetComplexRobust(**ppValue);
	}
}

template<typename T_Elem> void ExtractElems_T(const void* p, size_t offset, size_t nElems, ValueOwner& values)
{
	const T_Elem* pElem = reinterpret_cast<const T_Elem*>(p) + offset;
	for (size_t i = 0; i < nElems; i++, pElem++) values.push_back(new Value_Number(*pElem));
}

template<> void ExtractElems_T<Complex>(const void* p, size_t offset, size_t nElems, ValueOwner& values)
{
	const Complex* pElem = reinterpret_cast<const Complex*>(p) + offset;
	for (size_t i = 0; i < nElems; i++, pElem++) values.push_back(new Value_Complex(*pElem));
}

#define SetFuncBurst(func, funcTmpl) do { \
	ElemType::Bool.func		= funcTmpl<Bool>; \
	ElemType::Int8.func		= funcTmpl<Int8>; \
	ElemType::UInt8.func	= funcTmpl<UInt8>; \
	ElemType::Int16.func	= funcTmpl<Int16>; \
	ElemType::UInt16.func	= funcTmpl<UInt16>; \
	ElemType::Int32.func	= funcTmpl<Int32>; \
	ElemType::UInt32.func	= funcTmpl<UInt32>; \
	ElemType::Int64.func	= funcTmpl<Int64>; \
	ElemType::UInt64.func	= funcTmpl<UInt64>; \
	ElemType::Half.func		= funcTmpl<Half>; \
	ElemType::Float.func	= funcTmpl<Float>; \
	ElemType::Double.func	= funcTmpl<Double>; \
	ElemType::Complex.func	= funcTmpl<Complex>; \
} while (0)

void Array::Bootup()
{
	ElemType::None.pSymbol			= Symbol::Empty;
	ElemType::Bool.pSymbol			= Gurax_Symbol(bool_);
	ElemType::Int8.pSymbol			= Gurax_Symbol(int8);
	ElemType::UInt8.pSymbol			= Gurax_Symbol(uint8);
	ElemType::Int16.pSymbol			= Gurax_Symbol(int16);
	ElemType::UInt16.pSymbol		= Gurax_Symbol(uint16);
	ElemType::Int32.pSymbol			= Gurax_Symbol(int32);
	ElemType::UInt32.pSymbol		= Gurax_Symbol(uint32);
	ElemType::Int64.pSymbol			= Gurax_Symbol(int64);
	ElemType::UInt64.pSymbol		= Gurax_Symbol(uint64);
	ElemType::Half.pSymbol			= Gurax_Symbol(half);
	ElemType::Float.pSymbol			= Gurax_Symbol(float_);
	ElemType::Double.pSymbol		= Gurax_Symbol(double_);
	ElemType::Complex.pSymbol		= Gurax_Symbol(complex);
	SetFuncBurst(IndexSet,			IndexSet_T);
	SetFuncBurst(IndexGet,			IndexGet_T);
	SetFuncBurst(InjectElems,		InjectElems_T);
	SetFuncBurst(ExtractElems,		ExtractElems_T);
}

void Array::InjectElems(ValueList& values, size_t offset, size_t nElems)
{
	_elemType.InjectElems(GetPointerC<void>(), offset, nElems, values);
}

void Array::InjectElems(ValueList& values, size_t offset)
{
	InjectElems(values, offset, values.size());
}

void Array::ExtractElems(ValueOwner& values, size_t offset, size_t nElems) const
{
	values.reserve(values.size() + nElems);
	_elemType.ExtractElems(GetPointerC<void>(), offset, nElems, values);
}

void Array::ExtractElems(ValueOwner& values, size_t offset) const
{
	ExtractElems(values, offset, CountElems() - offset);
}

void Array::ExtractElems(ValueOwner& values) const
{
	ExtractElems(values, 0, CountElems());
}

String Array::ToString(const StringStyle& ss) const
{
	return String().Format("Array:%s", _elemType.pSymbol->GetName());
}

//------------------------------------------------------------------------------
// Array::ElemType
//------------------------------------------------------------------------------
Array::ElemTypeT Array::ElemType::None(0);
Array::ElemTypeT Array::ElemType::Bool(sizeof(Bool));
Array::ElemTypeT Array::ElemType::Int8(sizeof(Int8));
Array::ElemTypeT Array::ElemType::UInt8(sizeof(UInt8));
Array::ElemTypeT Array::ElemType::Int16(sizeof(Int16));
Array::ElemTypeT Array::ElemType::UInt16(sizeof(UInt16));
Array::ElemTypeT Array::ElemType::Int32(sizeof(Int32));
Array::ElemTypeT Array::ElemType::UInt32(sizeof(UInt32));
Array::ElemTypeT Array::ElemType::Int64(sizeof(Int64));
Array::ElemTypeT Array::ElemType::UInt64(sizeof(UInt64));
Array::ElemTypeT Array::ElemType::Half(sizeof(Half));
Array::ElemTypeT Array::ElemType::Float(sizeof(Float));
Array::ElemTypeT Array::ElemType::Double(sizeof(Double));
Array::ElemTypeT Array::ElemType::Complex(sizeof(Complex));

bool Array::ElemTypeT::IsNone() const
{
	return IsIdentical(ElemType::None);
}

}
