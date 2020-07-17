//==============================================================================
// Array.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------------
Array::Array(ElemTypeT& elemType, Memory* pMemory, Array::DimSizes dimSizes) :
		_elemType(elemType), _pMemory(pMemory), _dimSizes(std::move(dimSizes))
{
}

Array* Array::Create(ElemTypeT& elemType, Array::DimSizes dimSizes)
{
	RefPtr<Memory> pMemory(new MemoryHeap(elemType.bytes * dimSizes.GetLength()));
	pMemory->Fill(0);
	return new Array(elemType, pMemory.release(), std::move(dimSizes));
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

template<typename T_Elem> void InjectFromValueList_T(const ValueList& values, void* p, size_t offset, size_t len)
{
	T_Elem* pElem = reinterpret_cast<T_Elem*>(p) + offset;
	auto ppValue = values.begin();
	for (size_t i = 0; i < len; i++, pElem++, ppValue++) {
		*pElem = Value_Number::GetNumber<T_Elem>(**ppValue);
	}
}

template<> void InjectFromValueList_T<Complex>(const ValueList& values, void* p, size_t offset, size_t len)
{
	Complex* pElem = reinterpret_cast<Complex*>(p) + offset;
	auto ppValue = values.begin();
	for (size_t i = 0; i < len; i++, pElem++, ppValue++) {
		*pElem = Value_Complex::GetComplexRobust(**ppValue);
	}
}

template<typename T_Elem> void ExtractToValueOwner_T(ValueOwner& values, const void* p, size_t offset, size_t len)
{
	const T_Elem* pElem = reinterpret_cast<const T_Elem*>(p) + offset;
	for (size_t i = 0; i < len; i++, pElem++) values.push_back(new Value_Number(*pElem));
}

template<> void ExtractToValueOwner_T<Complex>(ValueOwner& values, const void* p, size_t offset, size_t len)
{
	const Complex* pElem = reinterpret_cast<const Complex*>(p) + offset;
	for (size_t i = 0; i < len; i++, pElem++) values.push_back(new Value_Complex(*pElem));
}

template<typename T_ElemDst, typename T_ElemSrc> void CopyElems_T(void* pDst, const void* pSrc, size_t offset, size_t len)
{
	T_ElemDst* pElemDst = reinterpret_cast<T_ElemDst*>(pDst);
	const T_ElemSrc* pElemSrc = reinterpret_cast<const T_ElemSrc*>(pSrc) + offset;
	for (size_t i = 0; i < len; i++, pElemDst++, pElemSrc++) {
		*pElemDst = static_cast<T_ElemDst>(*pElemSrc);
	}
}

#define SetFuncBurst(func, funcTmpl) do { \
	Array::ElemType::Bool.func		= funcTmpl<Bool>; \
	Array::ElemType::Int8.func		= funcTmpl<Int8>; \
	Array::ElemType::UInt8.func		= funcTmpl<UInt8>; \
	Array::ElemType::Int16.func		= funcTmpl<Int16>; \
	Array::ElemType::UInt16.func	= funcTmpl<UInt16>; \
	Array::ElemType::Int32.func		= funcTmpl<Int32>; \
	Array::ElemType::UInt32.func	= funcTmpl<UInt32>; \
	Array::ElemType::Int64.func		= funcTmpl<Int64>; \
	Array::ElemType::UInt64.func	= funcTmpl<UInt64>; \
	Array::ElemType::Half.func		= funcTmpl<Half>; \
	Array::ElemType::Float.func		= funcTmpl<Float>; \
	Array::ElemType::Double.func	= funcTmpl<Double>; \
	Array::ElemType::Complex.func	= funcTmpl<Complex>; \
} while (0)

#define SetFuncBurstM_Sub(func, funcTmpl, elemTypeSub) do { \
	Array::ElemType::Bool.func[ElemType::elemTypeSub.id]	= funcTmpl<Bool, elemTypeSub>; \
	Array::ElemType::Int8.func[ElemType::elemTypeSub.id]	= funcTmpl<Int8, elemTypeSub>; \
	Array::ElemType::UInt8.func[ElemType::elemTypeSub.id]	= funcTmpl<UInt8, elemTypeSub>; \
	Array::ElemType::Int16.func[ElemType::elemTypeSub.id]	= funcTmpl<Int16, elemTypeSub>; \
	Array::ElemType::UInt16.func[ElemType::elemTypeSub.id]	= funcTmpl<UInt16, elemTypeSub>; \
	Array::ElemType::Int32.func[ElemType::elemTypeSub.id]	= funcTmpl<Int32, elemTypeSub>; \
	Array::ElemType::UInt32.func[ElemType::elemTypeSub.id]	= funcTmpl<UInt32, elemTypeSub>; \
	Array::ElemType::Int64.func[ElemType::elemTypeSub.id]	= funcTmpl<Int64, elemTypeSub>; \
	Array::ElemType::UInt64.func[ElemType::elemTypeSub.id]	= funcTmpl<UInt64, elemTypeSub>; \
	Array::ElemType::Half.func[ElemType::elemTypeSub.id]	= funcTmpl<Half, elemTypeSub>; \
	Array::ElemType::Float.func[ElemType::elemTypeSub.id]	= funcTmpl<Float, elemTypeSub>; \
	Array::ElemType::Double.func[ElemType::elemTypeSub.id]	= funcTmpl<Double, elemTypeSub>; \
	Array::ElemType::Complex.func[ElemType::elemTypeSub.id]	= funcTmpl<Complex, elemTypeSub>; \
} while (0)

#define SetFuncBurstM(func, funcTmpl) do { \
	SetFuncBurstM_Sub(func, funcTmpl, Bool); \
	SetFuncBurstM_Sub(func, funcTmpl, Int8); \
	SetFuncBurstM_Sub(func, funcTmpl, UInt8); \
	SetFuncBurstM_Sub(func, funcTmpl, Int16); \
	SetFuncBurstM_Sub(func, funcTmpl, UInt16); \
	SetFuncBurstM_Sub(func, funcTmpl, Int32); \
	SetFuncBurstM_Sub(func, funcTmpl, UInt32); \
	SetFuncBurstM_Sub(func, funcTmpl, Int64); \
	SetFuncBurstM_Sub(func, funcTmpl, UInt64); \
	SetFuncBurstM_Sub(func, funcTmpl, Half); \
	SetFuncBurstM_Sub(func, funcTmpl, Float); \
	SetFuncBurstM_Sub(func, funcTmpl, Double); \
	SetFuncBurstM_Sub(func, funcTmpl, Complex); \
} while (0)

void Array::Bootup()
{
	ElemType::None.pSymbol				= Symbol::Empty;
	ElemType::Bool.pSymbol				= Gurax_Symbol(bool_);
	ElemType::Int8.pSymbol				= Gurax_Symbol(int8);
	ElemType::UInt8.pSymbol				= Gurax_Symbol(uint8);
	ElemType::Int16.pSymbol				= Gurax_Symbol(int16);
	ElemType::UInt16.pSymbol			= Gurax_Symbol(uint16);
	ElemType::Int32.pSymbol				= Gurax_Symbol(int32);
	ElemType::UInt32.pSymbol			= Gurax_Symbol(uint32);
	ElemType::Int64.pSymbol				= Gurax_Symbol(int64);
	ElemType::UInt64.pSymbol			= Gurax_Symbol(uint64);
	ElemType::Half.pSymbol				= Gurax_Symbol(half);
	ElemType::Float.pSymbol				= Gurax_Symbol(float_);
	ElemType::Double.pSymbol			= Gurax_Symbol(double_);
	ElemType::Complex.pSymbol			= Gurax_Symbol(complex);
	SetFuncBurst(IndexSet,				IndexSet_T);
	SetFuncBurst(IndexGet,				IndexGet_T);
	SetFuncBurst(InjectFromValueList,	InjectFromValueList_T);
	SetFuncBurst(ExtractToValueOwner,	ExtractToValueOwner_T);
	SetFuncBurstM(CopyElems,			CopyElems_T);
}

void Array::InjectElems(ValueList& values, size_t offset, size_t len)
{
	_elemType.InjectFromValueList(values, GetPointerC<void>(), offset, len);
}

void Array::InjectElems(ValueList& values, size_t offset)
{
	InjectElems(values, offset, values.size());
}

#if 0
void Array::InjectElems(Iterator& iterator, size_t offset, size_t len)
{
	_elemType.InjectElems(iterator, GetPointerC<void>(), offset, len);
}

void Array::InjectElems(Iterator& iterator, size_t offset)
{
	InjectElems(iterator, offset, values.size());
}
#endif

void Array::InjectElems(const void* pSrc, ElemTypeT& elemType, size_t offset, size_t len)
{
	_elemType.CopyElems[elemType.id](GetPointerC<void>(), pSrc, offset, len);
}

void Array::ExtractElems(ValueOwner& values, size_t offset, size_t len) const
{
	values.reserve(values.size() + len);
	_elemType.ExtractToValueOwner(values, GetPointerC<void>(), offset, len);
}

void Array::ExtractElemsSub(ValueOwner& values, size_t& offset, DimSizes::const_iterator pDimSize) const
{
	if (pDimSize + 1 == _dimSizes.end()) {
		ExtractElems(values, offset, *pDimSize);
		offset += *pDimSize;
	} else {
		for (size_t i = 0; i < *pDimSize; i++) {
			RefPtr<ValueOwner> pValues(new ValueOwner());
			ExtractElemsSub(*pValues, offset, pDimSize + 1);
			VType& vtypeOfElems = pValues->GetVTypeOfElemsQuick();
			values.push_back(new Value_List(vtypeOfElems, pValues.release()));
		}
	}
}

void Array::ExtractElems(ValueOwner& values) const
{
	size_t offset = 0;
	ExtractElemsSub(values, offset, _dimSizes.begin());
}

Value_List* Array::ToList() const
{
	RefPtr<ValueOwner> pValues(new ValueOwner());
	ExtractElems(*pValues);
	VType& vtypeOfElems = pValues->GetVTypeOfElemsQuick();
	return new Value_List(vtypeOfElems, pValues.release());
}

Array* Array::CreateCasted(ElemTypeT& elemType) const
{
	RefPtr<Array> pArray(Array::Create(elemType, _dimSizes));
	pArray->InjectElems(GetPointerC<void>(), GetElemType(), 0, _dimSizes.GetLength());
	return pArray.release();
}

String Array::ToString(const StringStyle& ss) const
{
	return String().Format("Array:%s:[%s]",
		_elemType.pSymbol->GetName(), _dimSizes.ToString(StringStyle::Cram).c_str());
}

//------------------------------------------------------------------------------
// Array::ElemType
//------------------------------------------------------------------------------
Array::ElemTypeT Array::ElemType::None(-1, 0);
Array::ElemTypeT Array::ElemType::Bool(0, sizeof(Bool));
Array::ElemTypeT Array::ElemType::Int8(1, sizeof(Int8));
Array::ElemTypeT Array::ElemType::UInt8(2, sizeof(UInt8));
Array::ElemTypeT Array::ElemType::Int16(3, sizeof(Int16));
Array::ElemTypeT Array::ElemType::UInt16(4, sizeof(UInt16));
Array::ElemTypeT Array::ElemType::Int32(5, sizeof(Int32));
Array::ElemTypeT Array::ElemType::UInt32(6, sizeof(UInt32));
Array::ElemTypeT Array::ElemType::Int64(7, sizeof(Int64));
Array::ElemTypeT Array::ElemType::UInt64(8, sizeof(UInt64));
Array::ElemTypeT Array::ElemType::Half(9, sizeof(Half));
Array::ElemTypeT Array::ElemType::Float(10, sizeof(Float));
Array::ElemTypeT Array::ElemType::Double(11, sizeof(Double));
Array::ElemTypeT Array::ElemType::Complex(12, sizeof(Complex));

bool Array::ElemTypeT::IsNone() const
{
	return IsIdentical(ElemType::None);
}

//------------------------------------------------------------------------------
// Array::DimSizes
//------------------------------------------------------------------------------
size_t Array::DimSizes::GetLength() const
{
	size_t len = 1;
	for (size_t dimSize : *this) len *= dimSize;
	return len;
}

String Array::DimSizes::ToString(const StringStyle& ss) const
{
	String str;
	for (size_t dimSize : *this) {
		if (!str.empty()) str += ss.GetComma();
		str.Format("%zu", dimSize);
	}
	return str;
}

}
