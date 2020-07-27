//==============================================================================
// Array.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------------
Array::MapSymbolToElemType Array::_mapSymbolToElemType;
Array::MapSymbolToElemType Array::_mapAtSymbolToElemType;

Array::Array(ElemTypeT& elemType, Memory* pMemory, DimSizes dimSizes) :
		_elemType(elemType), _pMemory(pMemory), _dimSizes(std::move(dimSizes))
{
}

Array* Array::Create(ElemTypeT& elemType, DimSizes dimSizes)
{
	RefPtr<Memory> pMemory(new MemoryHeap(elemType.bytes * dimSizes.GetLength()));
	pMemory->Fill(0);
	return new Array(elemType, pMemory.release(), std::move(dimSizes));
}

template<typename T_Elem> bool IndexSet_T(void* p, size_t idx, const Value& value)
{
	T_Elem* pElem = reinterpret_cast<T_Elem*>(p) + idx;
	if (value.IsType(VTYPE_Number)) {
		*pElem = Value_Number::GetNumber<Double>(value);
	} else {
		Error::Issue(ErrorType::ValueError, "Number value is expected");
		return false;
	}
	return true;
}

template<> bool IndexSet_T<Bool>(void* p, size_t idx, const Value& value)
{
	*(reinterpret_cast<Bool*>(p) + idx) = value.GetBool();
	return true;
}

template<> bool IndexSet_T<Complex>(void* p, size_t idx, const Value& value)
{
	Complex* pElem = reinterpret_cast<Complex*>(p) + idx;
	if (value.IsType(VTYPE_Number)) {
		*pElem = Complex(Value_Number::GetNumber<Double>(value));
	} else if (value.IsType(VTYPE_Complex)) {
		*pElem = Value_Complex::GetComplex(value);
	} else {
		Error::Issue(ErrorType::ValueError, "Number or Complex value is expected");
		return false;
	}
	return true;
}

template<typename T_Elem> Value* IndexGet_T(const void* p, size_t idx)
{
	return new Value_Number(*(reinterpret_cast<const T_Elem*>(p) + idx));
}

template<> Value* IndexGet_T<Bool>(const void* p, size_t idx)
{
	return new Value_Bool(!!*(reinterpret_cast<const Bool*>(p) + idx));
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

template<> void InjectFromValueList_T<Bool>(const ValueList& values, void* p, size_t offset, size_t len)
{
	Bool* pElem = reinterpret_cast<Bool*>(p) + offset;
	auto ppValue = values.begin();
	for (size_t i = 0; i < len; i++, pElem++, ppValue++) {
		*pElem = (*ppValue)->GetBool();
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

template<typename T_Elem> bool InjectFromIterator_T(Iterator& iterator, void* p, size_t offset, size_t len)
{
	T_Elem* pElem = reinterpret_cast<T_Elem*>(p) + offset;
	for (size_t i = 0; i < len; i++, pElem++) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		if (!pValue->IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "must be Number value");
			return false;
		}
		*pElem = Value_Number::GetNumber<T_Elem>(*pValue);
	}
	return !Error::IsIssued();
}

template<> bool InjectFromIterator_T<Bool>(Iterator& iterator, void* p, size_t offset, size_t len)
{
	Bool* pElem = reinterpret_cast<Bool*>(p) + offset;
	for (size_t i = 0; i < len; i++, pElem++) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		*pElem = pValue->GetBool();
	}
	return !Error::IsIssued();
}

template<> bool InjectFromIterator_T<Complex>(Iterator& iterator, void* p, size_t offset, size_t len)
{
	Complex* pElem = reinterpret_cast<Complex*>(p) + offset;
	for (size_t i = 0; i < len; i++, pElem++) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		if (pValue->IsType(VTYPE_Number)) {
			*pElem = Value_Number::GetNumber<Double>(*pValue);
		} else if (pValue->IsType(VTYPE_Complex)) {
			*pElem = Value_Complex::GetComplex(*pValue);
		} else {
			Error::Issue(ErrorType::TypeError, "must be Complex or Number value");
			return false;
		}
	}
	return !Error::IsIssued();
}

template<typename T_Elem> void ExtractToValueOwner_T(ValueOwner& values, const void* p, size_t offset, size_t len)
{
	const T_Elem* pElem = reinterpret_cast<const T_Elem*>(p) + offset;
	for (size_t i = 0; i < len; i++, pElem++) values.push_back(new Value_Number(*pElem));
}

template<> void ExtractToValueOwner_T<Bool>(ValueOwner& values, const void* p, size_t offset, size_t len)
{
	const Bool* pElem = reinterpret_cast<const Bool*>(p) + offset;
	for (size_t i = 0; i < len; i++, pElem++) values.push_back(new Value_Bool(!!*pElem));
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
	auto AssocSymbol = [](const Symbol* pSymbol, const Symbol* pAtSymbol, ElemTypeT& elemType) {
		_mapSymbolToElemType[pSymbol] = &elemType;
		_mapAtSymbolToElemType[pAtSymbol] = &elemType;
	};
	AssocSymbol(Symbol::Empty,			Symbol::Empty,				ElemType::None);
	AssocSymbol(Gurax_Symbol(bool_),	Gurax_Symbol(at_bool),		ElemType::Bool);
	AssocSymbol(Gurax_Symbol(int8),		Gurax_Symbol(at_int8),		ElemType::Int8);
	AssocSymbol(Gurax_Symbol(uint8),	Gurax_Symbol(at_uint8),		ElemType::UInt8);
	AssocSymbol(Gurax_Symbol(int16),	Gurax_Symbol(at_int16),		ElemType::Int16);
	AssocSymbol(Gurax_Symbol(uint16),	Gurax_Symbol(at_uint16),	ElemType::UInt16);
	AssocSymbol(Gurax_Symbol(int32),	Gurax_Symbol(at_int32),		ElemType::Int32);
	AssocSymbol(Gurax_Symbol(uint32),	Gurax_Symbol(at_uint32),	ElemType::UInt32);
	AssocSymbol(Gurax_Symbol(int64),	Gurax_Symbol(at_int64),		ElemType::Int64);
	AssocSymbol(Gurax_Symbol(uint64),	Gurax_Symbol(at_uint64),	ElemType::UInt64);
	AssocSymbol(Gurax_Symbol(half),		Gurax_Symbol(at_half),		ElemType::Half);
	AssocSymbol(Gurax_Symbol(float_),	Gurax_Symbol(at_float),		ElemType::Float);
	AssocSymbol(Gurax_Symbol(double_),	Gurax_Symbol(at_double),	ElemType::Double);
	AssocSymbol(Gurax_Symbol(complex),	Gurax_Symbol(at_complex),	ElemType::Complex);
	AssocSymbol(Gurax_Symbol(char_),	Gurax_Symbol(at_char),		ElemType::Int8);
	AssocSymbol(Gurax_Symbol(uchar),	Gurax_Symbol(at_uchar),		ElemType::UInt8);
	AssocSymbol(Gurax_Symbol(short_),	Gurax_Symbol(at_short),		ElemType::Int16);
	AssocSymbol(Gurax_Symbol(ushort),	Gurax_Symbol(at_ushort),	ElemType::UInt16);
	AssocSymbol(Gurax_Symbol(int_),		Gurax_Symbol(at_int),		(sizeof(int) == sizeof(Int32))? ElemType::Int32 : ElemType::Int64);
	AssocSymbol(Gurax_Symbol(uint),		Gurax_Symbol(at_uint),		(sizeof(int) == sizeof(Int32))? ElemType::UInt32 : ElemType::UInt64);
	AssocSymbol(Gurax_Symbol(long_),	Gurax_Symbol(at_long),		(sizeof(long) == sizeof(Int32))? ElemType::Int32 : ElemType::Int64);
	AssocSymbol(Gurax_Symbol(ulong),	Gurax_Symbol(at_ulong),		(sizeof(long) == sizeof(Int32))? ElemType::UInt32 : ElemType::UInt64);
	ElemType::Bool.bytes				= sizeof(bool);
	ElemType::Int8.bytes				= sizeof(Int8);
	ElemType::UInt8.bytes				= sizeof(UInt8);
	ElemType::Int16.bytes				= sizeof(Int16);
	ElemType::UInt16.bytes				= sizeof(UInt16);
	ElemType::Int32.bytes				= sizeof(Int32);
	ElemType::UInt32.bytes				= sizeof(UInt32);
	ElemType::Int64.bytes				= sizeof(Int64);
	ElemType::UInt64.bytes				= sizeof(UInt64);
	ElemType::Half.bytes				= sizeof(Half);
	ElemType::Float.bytes				= sizeof(Float);
	ElemType::Double.bytes				= sizeof(Double);
	ElemType::Complex.bytes				= sizeof(Complex);
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
	SetFuncBurst(InjectFromIterator,	InjectFromIterator_T);
	SetFuncBurst(ExtractToValueOwner,	ExtractToValueOwner_T);
	SetFuncBurstM(CopyElems,			CopyElems_T);
}

void Array::InjectElems(ValueList& values, size_t offset, size_t len)
{
	_elemType.InjectFromValueList(values, GetPointerC<void>(), offset, len);
}

void Array::InjectElems(ValueList& values, size_t offset)
{
	InjectElems(values, offset, std::min(values.size(), _dimSizes.GetLength() - offset));
}

bool Array::InjectElems(Iterator& iterator, size_t offset, size_t len)
{
	return _elemType.InjectFromIterator(iterator, GetPointerC<void>(), offset, len);
}

bool Array::InjectElems(Iterator& iterator, size_t offset)
{
	return InjectElems(iterator, offset, _dimSizes.GetLength() - offset);
}
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
Array::ElemTypeT Array::ElemType::None(-1);
Array::ElemTypeT Array::ElemType::Bool(0);
Array::ElemTypeT Array::ElemType::Int8(1);
Array::ElemTypeT Array::ElemType::UInt8(2);
Array::ElemTypeT Array::ElemType::Int16(3);
Array::ElemTypeT Array::ElemType::UInt16(4);
Array::ElemTypeT Array::ElemType::Int32(5);
Array::ElemTypeT Array::ElemType::UInt32(6);
Array::ElemTypeT Array::ElemType::Int64(7);
Array::ElemTypeT Array::ElemType::UInt64(8);
Array::ElemTypeT Array::ElemType::Half(9);
Array::ElemTypeT Array::ElemType::Float(10);
Array::ElemTypeT Array::ElemType::Double(11);
Array::ElemTypeT Array::ElemType::Complex(12);

bool Array::ElemTypeT::IsNone() const
{
	return IsIdentical(ElemType::None);
}

//------------------------------------------------------------------------------
// DimSizes
//------------------------------------------------------------------------------
size_t DimSizes::GetLength() const
{
	size_t len = 1;
	for (size_t dimSize : *this) len *= dimSize;
	return len;
}

String DimSizes::ToString(const StringStyle& ss) const
{
	String str;
	for (size_t dimSize : *this) {
		if (!str.empty()) str += ss.GetComma();
		str.Format("%zu", dimSize);
	}
	return str;
}

}
