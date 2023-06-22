//==============================================================================
// Array.cpp
//==============================================================================
#include "stdafx.h"

#define InitElemTypeRtnForArithm(elemTypeRtn, elemTypeL, elemTypeR) \
_pElemTypeRtnForArithmTbl[ElemType::elemTypeL.id][ElemType::elemTypeR.id] = &ElemType::elemTypeRtn;

namespace Gurax {

//------------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------------
Array::Funcs Array::funcs;
const Array::ElemTypeT* Array::_pElemTypeRtnForArithmTbl[ElemTypeIdMax][ElemTypeIdMax];
Array::MapSymbolToElemType Array::_mapSymbolToElemType;
Array::MapSymbolToElemType Array::_mapAtSymbolToElemType;

Array::Array(const ElemTypeT& elemType, Memory* pMemory, DimSizes dimSizes, size_t byteOffset) :
		_elemType(elemType), _pMemory(pMemory), _dimSizes(std::move(dimSizes)), _byteOffset(byteOffset)
{
}

Array::Array(const Array& src) :
		_elemType(src._elemType), _pMemory(src._pMemory->Clone()), _dimSizes(src._dimSizes), _byteOffset(src._byteOffset)
{
}

Array::Array(Array&& src) :
		_elemType(src._elemType), _pMemory(src._pMemory->Reference()), _dimSizes(std::move(src._dimSizes)), _byteOffset(src._byteOffset)
{
}

Array* Array::Create(const ElemTypeT& elemType, Memory* pMemory, DimSizes dimSizes)
{
	return new Array(elemType, pMemory, std::move(dimSizes), 0);
}

Array* Array::Create(const ElemTypeT& elemType, DimSizes dimSizes)
{
	RefPtr<Memory> pMemory(new MemoryHeap(elemType.bytes * dimSizes.CalcLength()));
	pMemory->Fill(0);
	return new Array(elemType, pMemory.release(), std::move(dimSizes), 0);
}

Array* Array::CreateScalar(const ElemTypeT& elemType, Double num)
{
	RefPtr<Array> pArray(Create(elemType, DimSizes()));
	pArray->IndexSetDouble(0, num);
	return pArray.release();
}

Array* Array::CreateScalar(const ElemTypeT& elemType, const Complex& num)
{
	RefPtr<Array> pArray(Create(elemType, DimSizes()));
	*pArray->GetPointerC<Complex>() = num;
	return pArray.release();
}

Array* Array::CreateIdentity(const ElemTypeT& elemType, size_t n, Double mag)
{
	RefPtr<Array> pArray(Create(elemType, DimSizes(n, n)));
	size_t idx = 0;
	for (size_t i = 0; i < n; i++, idx += n + 1) pArray->IndexSetDouble(idx, mag);
	return pArray.release();
}

void Array::Reshape(RefPtr<Array>& pArrayRtn, const DimSizes& dimSizes) const
{
	pArrayRtn.reset(new Array(GetElemType(), GetMemory().Reference(), dimSizes, _byteOffset));
}

bool Array::Reshape(RefPtr<Array>& pArrayRtn, const ValueList& values) const
{
	DimSizes dimSizes;
	if (GetDimSizes().Reshape(dimSizes, values)) {
		Reshape(pArrayRtn, dimSizes);
		return true;
	}
	return false;
}

#if 0
Array* Array::Reshape(const ValueList& values) const
{
	DimSizes dimSizes;
	size_t len = GetDimSizes().CalcLength();
	dimSizes.reserve(values.size());
	int iUndetermined = -1;
	size_t dimSizeProd = 1;
	size_t i = 0;
	for (auto pValue : values) {
		if (pValue->IsType(VTYPE_Number)) {
			size_t dimSize = Value_Number::GetNumberPos<size_t>(*pValue);
			if (Error::IsIssued()) return nullptr;
			dimSizes.push_back(dimSize);
			dimSizeProd *= dimSize;
		} else if (pValue->IsInvalid()) {
			if (iUndetermined >= 0) {
				Error::Issue(ErrorType::ValueError, "more than one undetermined dimension");
				return nullptr;
			}
			dimSizes.push_back(0);
			iUndetermined = i;
		} else {
			Error::Issue(ErrorType::TypeError, "only Number value is acceptable");
			return nullptr;
		}
		i++;
	}
	if (len < dimSizeProd) {
		Error::Issue(ErrorType::RangeError, "specified dimension exceeds the memory amount");
		return nullptr;
	} else if (iUndetermined < 0 && len != dimSizeProd) {
		Error::Issue(ErrorType::ValueError, "specified dimension is less than the memory amount");
		return nullptr;
	} else if (len % dimSizeProd != 0) {
		Error::Issue(ErrorType::ValueError, "invalid dimension");
		return nullptr;
	}
	if (iUndetermined >= 0) dimSizes[iUndetermined] = len / dimSizeProd;
	return new Array(GetElemType(), GetMemory().Reference(), dimSizes, _byteOffset);
}
#endif

template<typename T_Elem> Value* FindMax_T(const Array& array, size_t axis, const ValueList& valuesDim)
{
	size_t strides = 0;
	const T_Elem* pElem = array.GetPointerC<T_Elem>() + array.GetDimSizes().CalcOffset(axis, valuesDim, &strides);
	if (Error::IsIssued()) return Value::nil();
	size_t dimSize = array.GetDimSizes()[axis];
	if (dimSize == 0) return Value::nil();
	int idx = 0;
	T_Elem numMax = *pElem;
	pElem += strides;
	idx++;
	for ( ; idx < dimSize; pElem += strides, idx++) {
		if (numMax < *pElem) numMax = *pElem;
	}
	return new Value_Number(numMax);
}

template<> Value* FindMax_T<Complex>(const Array& array, size_t axis, const ValueList& valuesDim) { return Value::nil(); }

template<typename T_Elem> Value* FindMin_T(const Array& array, size_t axis, const ValueList& valuesDim)
{
	size_t strides = 0;
	const T_Elem* pElem = array.GetPointerC<T_Elem>() + array.GetDimSizes().CalcOffset(axis, valuesDim, &strides);
	if (Error::IsIssued()) return Value::nil();
	size_t dimSize = array.GetDimSizes()[axis];
	if (dimSize == 0) return Value::nil();
	int idx = 0;
	T_Elem numMin = *pElem;
	pElem += strides;
	idx++;
	for ( ; idx < dimSize; pElem += strides, idx++) {
		if (numMin > *pElem) numMin = *pElem;
	}
	return new Value_Number(numMin);
}

template<> Value* FindMin_T<Complex>(const Array& array, size_t axis, const ValueList& valuesDim) { return Value::nil(); }

template<typename T_Elem> Value* ArgMax_T(const Array& array, size_t axis, const ValueList& valuesDim)
{
	size_t strides = 0;
	const T_Elem* pElem = array.GetPointerC<T_Elem>() + array.GetDimSizes().CalcOffset(axis, valuesDim, &strides);
	if (Error::IsIssued()) return Value::nil();
	size_t dimSize = array.GetDimSizes()[axis];
	if (dimSize == 0) return Value::nil();
	int idx = 0, idxMax = 0;
	T_Elem numMax = *pElem;
	pElem += strides;
	idx++;
	for ( ; idx < dimSize; pElem += strides, idx++) {
		if (numMax < *pElem) {
			numMax = *pElem;
			idxMax = idx;
		}
	}
	return new Value_Number(idxMax);
}

template<> Value* ArgMax_T<Complex>(const Array& array, size_t axis, const ValueList& valuesDim) { return Value::nil(); }

template<typename T_Elem> Value* ArgMin_T(const Array& array, size_t axis, const ValueList& valuesDim)
{
	size_t strides = 0;
	const T_Elem* pElem = array.GetPointerC<T_Elem>() + array.GetDimSizes().CalcOffset(axis, valuesDim, &strides);
	if (Error::IsIssued()) return Value::nil();
	size_t dimSize = array.GetDimSizes()[axis];
	if (dimSize == 0) return Value::nil();
	int idx = 0, idxMin = 0;
	T_Elem numMin = *pElem;
	pElem += strides;
	idx++;
	for ( ; idx < dimSize; pElem += strides, idx++) {
		if (numMin > *pElem) {
			numMin = *pElem;
			idxMin = idx;
		}
	}
	return new Value_Number(idxMin);
}

template<> Value* ArgMin_T<Complex>(const Array& array, size_t axis, const ValueList& valuesDim) { return Value::nil(); }

template<typename T_Elem> bool IndexSetValue_T(void* pv, size_t idx, const Value& value)
{
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + idx;
	if (value.IsType(VTYPE_Number)) {
		*p = Value_Number::GetNumber<T_Elem>(value);
	} else if (value.IsType(VTYPE_Bool)) {
		*p = value.GetBool()? 1 : 0;
	} else {
		Error::Issue(ErrorType::ValueError, "Number value is expected");
		return false;
	}
	return true;
}

template<> bool IndexSetValue_T<Bool>(void* pv, size_t idx, const Value& value)
{
	using T_Elem = Bool;
	*(reinterpret_cast<T_Elem*>(pv) + idx) = value.GetBool();
	return true;
}

template<> bool IndexSetValue_T<Complex>(void* pv, size_t idx, const Value& value)
{
	using T_Elem = Complex;
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + idx;
	if (value.IsType(VTYPE_Number)) {
		*p = Complex(Value_Number::GetNumber<Double>(value));
	} else if (value.IsType(VTYPE_Complex)) {
		*p = Value_Complex::GetComplex(value);
	} else if (value.IsType(VTYPE_Bool)) {
		*p = Complex(value.GetBool()? 1. : 0.);
	} else {
		Error::Issue(ErrorType::ValueError, "Number or Complex value is expected");
		return false;
	}
	return true;
}

template<typename T_Elem> bool IndexSetDouble_T(void* pv, size_t idx, Double num)
{
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + idx;
	*p = static_cast<T_Elem>(num);
	return true;
}

template<> bool IndexSetDouble_T<Bool>(void* pv, size_t idx, Double num)
{
	*(reinterpret_cast<Bool*>(pv) + idx) = (num > 0);
	return true;
}

template<> bool IndexSetDouble_T<Complex>(void* pv, size_t idx, Double num)
{
	Complex* p = reinterpret_cast<Complex*>(pv) + idx;
	*p = Complex(num);
	return true;
}

template<typename T_Elem> Value* IndexGetValue_T(const void* pv, size_t idx)
{
	return new Value_Number(*(reinterpret_cast<const T_Elem*>(pv) + idx));
}

template<> Value* IndexGetValue_T<Bool>(const void* pv, size_t idx)
{
	return new Value_Bool(*(reinterpret_cast<const Bool*>(pv) + idx));
}

template<> Value* IndexGetValue_T<Complex>(const void* pv, size_t idx)
{
	return new Value_Complex(*(reinterpret_cast<const Complex*>(pv) + idx));
}

template<typename T_Elem> Double IndexGetDouble_T(const void* pv, size_t idx)
{
	return static_cast<Double>(*(reinterpret_cast<const T_Elem*>(pv) + idx));
}

template<> Double IndexGetDouble_T<Bool>(const void* pv, size_t idx)
{
	return *(reinterpret_cast<const Bool*>(pv) + idx)? 1. : 0.;
}

template<> Double IndexGetDouble_T<Complex>(const void* pv, size_t idx)
{
	return 0.;
}

template<typename T_Elem> void InjectFromValueList_T(const ValueList& values, void* pv, size_t offset, size_t len)
{
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + offset;
	auto ppValue = values.begin();
	auto ppValueEnd = ppValue + len;
	for ( ; ppValue != ppValueEnd; p++, ppValue++) {
		*p = Value_Number::GetNumber<T_Elem>(**ppValue);
	}
}

template<> void InjectFromValueList_T<Bool>(const ValueList& values, void* pv, size_t offset, size_t len)
{
	using T_Elem = Bool;
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + offset;
	T_Elem* pEnd = p + len;
	auto ppValue = values.begin();
	for ( ; p != pEnd; p++, ppValue++) {
		*p = (*ppValue)->GetBool();
	}
}

template<> void InjectFromValueList_T<Complex>(const ValueList& values, void* pv, size_t offset, size_t len)
{
	using T_Elem = Complex;
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + offset;
	T_Elem* pEnd = p + len;
	auto ppValue = values.begin();
	for ( ; p != pEnd; p++, ppValue++) {
		*p = Value_Complex::GetComplexRobust(**ppValue);
	}
}

template<typename T_Elem> bool InjectFromIterator_T(Iterator& iterator, void* pv, size_t offset, size_t len)
{
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + offset;
	T_Elem* pEnd = p + len;
	for ( ; p != pEnd; p++) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		if (!pValue->IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "must be Number value");
			return false;
		}
		*p = Value_Number::GetNumber<T_Elem>(*pValue);
	}
	return !Error::IsIssued();
}

template<> bool InjectFromIterator_T<Bool>(Iterator& iterator, void* pv, size_t offset, size_t len)
{
	using T_Elem = Bool;
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + offset;
	T_Elem* pEnd = p + len;
	for ( ; p != pEnd; p++) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		*p = pValue->GetBool();
	}
	return !Error::IsIssued();
}

template<> bool InjectFromIterator_T<Complex>(Iterator& iterator, void* pv, size_t offset, size_t len)
{
	using T_Elem = Complex;
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + offset;
	T_Elem* pEnd = p + len;
	for ( ; p != pEnd; p++) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		if (pValue->IsType(VTYPE_Number)) {
			*p = Value_Number::GetNumber<Double>(*pValue);
		} else if (pValue->IsType(VTYPE_Complex)) {
			*p = Value_Complex::GetComplex(*pValue);
		} else {
			Error::Issue(ErrorType::TypeError, "must be Complex or Number value");
			return false;
		}
	}
	return !Error::IsIssued();
}

template<typename T_Elem> void ExtractElems_T(ValueOwner& values, const void* pv, size_t offset, size_t len)
{
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv) + offset;
	const T_Elem* pEnd = p + len;
	for ( ; p != pEnd; p++) values.push_back(new Value_Number(*p));
}

template<> void ExtractElems_T<Bool>(ValueOwner& values, const void* pv, size_t offset, size_t len)
{
	using T_Elem = Bool;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv) + offset;
	const T_Elem* pEnd = p + len;
	for ( ; p != pEnd; p++) values.push_back(new Value_Bool(!!*p));
}

template<> void ExtractElems_T<Complex>(ValueOwner& values, const void* pv, size_t offset, size_t len)
{
	using T_Elem = Complex;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv) + offset;
	const T_Elem* pEnd = p + len;
	for ( ; p != pEnd; p++) values.push_back(new Value_Complex(*p));
}

template<typename T_Elem> void Put_T(void* pvDst, const void* pvSrc)
{
	*reinterpret_cast<T_Elem*>(pvDst) = *reinterpret_cast<const T_Elem*>(pvSrc);
}

template<typename T_Elem> void ToStringElem_T(const StringStyle& ss, String& str, const T_Elem* p)
{
	Number<T_Elem>::ToString(str, *p);
}

template<> void ToStringElem_T<Bool>(const StringStyle& ss, String& str, const Bool* p)
{
	str.Format("%s", *p? "true" : "false");
}
template<> void ToStringElem_T<Complex>(const StringStyle& ss, String& str, const Complex* p)
{
	p->ToString(str);
}

template<typename T_Elem> void ToString_T(const StringStyle& ss, String& str, const void* pv, size_t offset, size_t len)
{
	const T_Elem* pBegin = reinterpret_cast<const T_Elem*>(pv) + offset;
	if (len == 0) {
		ToStringElem_T(ss, str, pBegin);
	} else {
		const char* strComma = ss.IsCram()? "," : ", ";
		const T_Elem* pEnd = pBegin + len;
		for (const T_Elem* p = pBegin; p != pEnd; p++) {
			if (p != pBegin) str += strComma;
			ToStringElem_T(ss, str, p);
		}
	}
}

template<typename T_ElemDst, typename T_ElemSrc> void CopyElems_T(void* pvDst, const void* pvSrc, size_t offset, size_t len)
{
	T_ElemDst* pDst = reinterpret_cast<T_ElemDst*>(pvDst);
	T_ElemDst* pDstEnd = pDst + len;
	const T_ElemSrc* pSrc = reinterpret_cast<const T_ElemSrc*>(pvSrc) + offset;
	for ( ; pDst != pDstEnd; pDst++, pSrc++) {
		*pDst = static_cast<T_ElemDst>(*pSrc);
	}
}

template<typename T_ElemDst, typename T_ElemSrc> void Transpose2d_T(void* pvDst, const void* pvSrc, size_t nRows, size_t nCols)
{
	T_ElemDst* pDst = reinterpret_cast<T_ElemDst*>(pvDst);
	const T_ElemSrc* pSrcSave = reinterpret_cast<const T_ElemSrc*>(pvSrc);
	for (size_t iRow = 0; iRow < nRows; iRow++, pSrcSave++) {
		const T_ElemSrc* pSrc = pSrcSave;
		for (size_t iCol = 0; iCol < nCols; iCol++, pDst++, pSrc += nRows) {
			*pDst = static_cast<T_ElemDst>(*pSrc);
		}
	}
}

template<typename T_ElemDst, typename T_ElemSrc> void TransposeMulti_T(void** ppvDst, const void* pvSrc,
		const DimSizes& dimSizesSrc, NumList<size_t>::const_iterator pAxis, NumList<size_t>::const_iterator pAxisEnd)
{
	T_ElemDst*& pDst = *reinterpret_cast<T_ElemDst**>(ppvDst);
	const T_ElemSrc* pSrc = reinterpret_cast<const T_ElemSrc*>(pvSrc);
	const size_t dimSizeSrc = dimSizesSrc[*pAxis];
	size_t stridesSrc = dimSizesSrc.CalcStrides(*pAxis);
	if (pAxis + 1 == pAxisEnd) {
		for (size_t i = 0; i < dimSizeSrc; i++, pSrc += stridesSrc, pDst++) *pDst = static_cast<T_ElemDst>(*pSrc);
	} else {
		for (size_t i = 0; i < dimSizeSrc; i++, pSrc += stridesSrc) {
			TransposeMulti_T<T_ElemDst, T_ElemSrc>(reinterpret_cast<void **>(&pDst), reinterpret_cast<const void *>(pSrc), dimSizesSrc, pAxis + 1, pAxisEnd);
		}
	}
}

template<typename T_Elem>
void Neg_Array_T(void* pvRtn, const void* pv, size_t len)
{
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++) {
		*pRtn = -static_cast<T_Elem>(static_cast<T_Elem>(*p));
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Add_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) + static_cast<T_ElemRtn>(*pR));
	}
}

template<typename T_ElemL>
void Add_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	T_ElemRtn numRCasted = static_cast<T_ElemRtn>(numR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) + numRCasted);
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void And_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<UInt64>(*pL) & static_cast<UInt64>(*pR));
	}
}

template<typename T_ElemL>
void And_ArrayNumber_T(void* pvRtn, const void* pvL, UInt64 numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<UInt64>(*pL) & numR);
	}
}

template<typename T_ElemL>
void Add_ArrayComplex_T(void* pvRtn, const void* pvL, const Complex& numR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) + numR);
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Sub_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) - static_cast<T_ElemRtn>(*pR));
	}
}

template<typename T_ElemL>
void Sub_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	T_ElemRtn numRCasted = static_cast<T_ElemRtn>(numR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) - numRCasted);
	}
}

template<typename T_ElemR>
void Sub_NumberArray_T(void* pvRtn, Double numL, const void* pvR, size_t len)
{
	using T_ElemRtn = T_ElemR;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	T_ElemRtn numLCasted = static_cast<T_ElemRtn>(numL);
	for( ; pRtn != pRtnEnd; pRtn++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(numLCasted - static_cast<T_ElemRtn>(*pR));
	}
}

template<typename T_ElemL>
void Sub_ArrayComplex_T(void* pvRtn, const void* pvL, const Complex& numR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) - numR);
	}
}

template<typename T_ElemR>
void Sub_ComplexArray_T(void* pvRtn, const Complex& numL, const void* pvR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(numL - static_cast<T_ElemRtn>(*pR));
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Mul_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) * static_cast<T_ElemRtn>(*pR));
	}
}

template<typename T_ElemL>
void Mul_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	T_ElemRtn numRCasted = static_cast<T_ElemRtn>(numR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) * numRCasted);
	}
}

template<typename T_ElemL>
void Mul_ArrayComplex_T(void* pvRtn, const void* pvL, const Complex& numR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) * numR);
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
bool Div_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		auto elemR = *pR;
		if (elemR == static_cast<T_ElemR>(0)) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return false;
		}
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) / elemR);
	}
	return true;
}

template<typename T_ElemL>
bool Div_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	T_ElemRtn numRCasted = static_cast<T_ElemRtn>(numR);
	if (numRCasted == 0.) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return false;
	}
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) / numRCasted);
	}
	return true;
}

template<typename T_ElemR>
bool Div_NumberArray_T(void* pvRtn, Double numL, const void* pvR, size_t len)
{
	using T_ElemRtn = T_ElemR;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	T_ElemRtn numLCasted = static_cast<T_ElemRtn>(numL);
	for( ; pRtn != pRtnEnd; pRtn++, pR++) {
		auto elemR = static_cast<T_ElemRtn>(*pR);
		if (elemR == static_cast<T_ElemR>(0)) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return false;
		}
		*pRtn = static_cast<T_ElemRtn>(numLCasted / elemR);
	}
	return true;
}

template<typename T_ElemL>
bool Div_ArrayComplex_T(void* pvRtn, const void* pvL, const Complex& numR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	if (numR.IsZero()) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return false;
	}
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) / numR);
	}
	return true;
}

template<typename T_ElemR>
bool Div_ComplexArray_T(void* pvRtn, const Complex& numL, const void* pvR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pR++) {
		auto elemR = *pR;
		if (elemR == static_cast<T_ElemR>(0)) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return false;
		}
		*pRtn = static_cast<T_ElemRtn>(numL / elemR);
	}
	return true;
}

Double Pow(Half base, Half exponent) { return std::pow(static_cast<Double>(base), static_cast<Double>(exponent)); }
Double Pow(Double base, Double exponent) { return std::pow(base, exponent); }
Complex Pow(Double base, const Complex& exponent) { return std::pow(base, exponent); }
Complex Pow(const Complex& base, Double exponent) { return std::pow(base, exponent); }
Complex Pow(const Complex& base, const Complex& exponent) { return std::pow(base, exponent); }

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
bool Pow_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		auto elemR = *pR;
		*pRtn = static_cast<T_ElemRtn>(Pow(static_cast<T_ElemRtn>(*pL), elemR));
	}
	return true;
}

template<typename T_ElemL>
bool Pow_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	T_ElemRtn numRCasted = static_cast<T_ElemRtn>(numR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(Pow(static_cast<T_ElemRtn>(*pL), numRCasted));
	}
	return true;
}

template<typename T_ElemR>
bool Pow_NumberArray_T(void* pvRtn, Double numL, const void* pvR, size_t len)
{
	using T_ElemRtn = T_ElemR;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	T_ElemRtn numLCasted = static_cast<T_ElemRtn>(numL);
	for( ; pRtn != pRtnEnd; pRtn++, pR++) {
		auto elemR = static_cast<T_ElemRtn>(*pR);
		*pRtn = static_cast<T_ElemRtn>(Pow(numLCasted, elemR));
	}
	return true;
}

template<typename T_ElemL>
bool Pow_ArrayComplex_T(void* pvRtn, const void* pvL, const Complex& numR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(Pow(static_cast<T_ElemRtn>(*pL), numR));
	}
	return true;
}

template<typename T_ElemR>
bool Pow_ComplexArray_T(void* pvRtn, const Complex& numL, const void* pvR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pR++) {
		auto elemR = *pR;
		*pRtn = static_cast<T_ElemRtn>(Pow(numL, elemR));
	}
	return true;
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Or_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<UInt64>(*pL) | static_cast<UInt64>(*pR));
	}
}

template<typename T_ElemL>
void Or_ArrayNumber_T(void* pvRtn, const void* pvL, UInt64 numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<UInt64>(*pL) | numR);
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Xor_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<UInt64>(*pL) ^ static_cast<UInt64>(*pR));
	}
}

template<typename T_ElemL>
void Xor_ArrayNumber_T(void* pvRtn, const void* pvL, UInt64 numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<UInt64>(*pL) ^ numR);
	}
}

template<typename T_ElemL, typename T_ElemR>
void Eq_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		*pRtn = (*pL == *pR);
	}
}

template<typename T_ElemL>
void Eq_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = (*pL == numR);
	}
}

template<typename T_ElemL>
void Eq_ArrayComplex_T(void* pvRtn, const void* pvL, const Complex& numR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = (*pL == numR);
	}
}

template<typename T_ElemL, typename T_ElemR>
void Ne_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		*pRtn = (*pL != *pR);
	}
}

template<typename T_ElemL>
void Ne_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = (*pL != numR);
	}
}

template<typename T_ElemL>
void Ne_ArrayComplex_T(void* pvRtn, const void* pvL, const Complex& numR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = (*pL != numR);
	}
}

template<typename T_ElemL, typename T_ElemR>
void Lt_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		*pRtn = (*pL < *pR);
	}
}

template<typename T_ElemL>
void Lt_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = (*pL < numR);
	}
}

template<typename T_ElemR>
void Lt_NumberArray_T(void* pvRtn, Double numL, const void* pvR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pR++) {
		*pRtn = (numL < *pR);
	}
}

template<typename T_ElemL, typename T_ElemR>
void Le_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		*pRtn = (*pL <= *pR);
	}
}

template<typename T_ElemL>
void Le_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = (*pL <= numR);
	}
}

template<typename T_ElemR>
void Le_NumberArray_T(void* pvRtn, Double numL, const void* pvR, size_t len)
{
	using T_ElemRtn = Bool;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pR++) {
		*pRtn = (numL <= *pR);
	}
}

template<typename T_ElemL, typename T_ElemR>
void Cmp_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	using T_ElemRtn = Int8;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pL++, pR++) {
		*pRtn = (*pL < *pR)? -1 : (*pL > *pR)? + 1 : 0;
	}
}

template<typename T_ElemL>
void Cmp_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = Int8;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for( ; pRtn != pRtnEnd; pRtn++, pL++) {
		*pRtn = (*pL < numR)? -1 : (*pL > numR)? +1 : 0;
	}
}

template<typename T_ElemR>
void Cmp_NumberArray_T(void* pvRtn, Double numL, const void* pvR, size_t len)
{
	using T_ElemRtn = Int8;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	T_ElemRtn* pRtnEnd = pRtn + len;
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for( ; pRtn != pRtnEnd; pRtn++, pR++) {
		*pRtn = (numL < *pR)? -1 : (numL > *pR)? +1 : 0;
	}
}

// [m, n] = dot([m, l], [l, n])
template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Dot_ArrayArray_T(void* pvRtn, size_t m, size_t n, const void* pvL, const void* pvR, size_t l)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pBaseL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pBaseR = reinterpret_cast<const T_ElemR*>(pvR);
	for (size_t i = 0; i < m; i++, pBaseL += l) {
		const T_ElemR* pSaveR = pBaseR;
		for (size_t j = 0; j < n; j++, pRtn++, pSaveR++) {
			T_ElemRtn elemRtn = 0;
			const T_ElemL* pL = pBaseL;
			const T_ElemR* pR = pSaveR;
			for (size_t k = 0; k < l; k++, pL++, pR += n) {
				elemRtn += static_cast<T_ElemRtn>(*pL) * static_cast<T_ElemRtn>(*pR);
			}
			*pRtn = elemRtn;
		}
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Cross_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t n)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	T_ElemRtn a1 = static_cast<T_ElemRtn>(pL[0]);
	T_ElemRtn a2 = static_cast<T_ElemRtn>(pL[1]);
	T_ElemRtn a3 = static_cast<T_ElemRtn>(pL[2]);
	T_ElemRtn b1 = static_cast<T_ElemRtn>(pR[0]);
	T_ElemRtn b2 = static_cast<T_ElemRtn>(pR[1]);
	T_ElemRtn b3 = static_cast<T_ElemRtn>(pR[2]);
	pRtn[0] = static_cast<T_ElemRtn>(a2 * b3 - a3 * b2);
	pRtn[1] = static_cast<T_ElemRtn>(a3 * b1 - a1 * b3);
	pRtn[2] = static_cast<T_ElemRtn>(a1 * b2 - a2 * b1); 
}

void Array::Bootup()
{
	auto AssocSymbol = [](const Symbol* pSymbol, const Symbol* pAtSymbol, const ElemTypeT& elemType) {
		_mapSymbolToElemType[pSymbol] = &elemType;
		_mapAtSymbolToElemType[pAtSymbol] = &elemType;
	};
	//                       Return     Left        Right
	InitElemTypeRtnForArithm(Bool,		Bool,		Bool);
	InitElemTypeRtnForArithm(Int8,		Int8,		Bool);
	InitElemTypeRtnForArithm(UInt8,		UInt8,		Bool);
	InitElemTypeRtnForArithm(Int16,		Int16,		Bool);
	InitElemTypeRtnForArithm(UInt16,	UInt16,		Bool);
	InitElemTypeRtnForArithm(Int32,		Int32,		Bool);
	InitElemTypeRtnForArithm(UInt32,	UInt32,		Bool);
	InitElemTypeRtnForArithm(Int64,		Int64,		Bool);
	InitElemTypeRtnForArithm(UInt64,	UInt64,		Bool);
	InitElemTypeRtnForArithm(Half,		Half,		Bool);
	InitElemTypeRtnForArithm(Float,		Float,		Bool);
	InitElemTypeRtnForArithm(Double,	Double,		Bool);
	InitElemTypeRtnForArithm(Complex,	Complex,	Bool);
	InitElemTypeRtnForArithm(Int8,		Bool,		Int8);
	InitElemTypeRtnForArithm(Int8,		Int8,		Int8);
	InitElemTypeRtnForArithm(UInt8,		UInt8,		Int8);
	InitElemTypeRtnForArithm(Int16,		Int16,		Int8);
	InitElemTypeRtnForArithm(UInt16,	UInt16,		Int8);
	InitElemTypeRtnForArithm(Int32,		Int32,		Int8);
	InitElemTypeRtnForArithm(UInt32,	UInt32,		Int8);
	InitElemTypeRtnForArithm(Int64,		Int64,		Int8);
	InitElemTypeRtnForArithm(UInt64,	UInt64,		Int8);
	InitElemTypeRtnForArithm(Half,		Half,		Int8);
	InitElemTypeRtnForArithm(Float,		Float,		Int8);
	InitElemTypeRtnForArithm(Double,	Double,		Int8);
	InitElemTypeRtnForArithm(Complex,	Complex,	Int8);
	InitElemTypeRtnForArithm(UInt8,		Bool,		UInt8);
	InitElemTypeRtnForArithm(UInt8,		Int8,		UInt8);
	InitElemTypeRtnForArithm(UInt8,		UInt8,		UInt8);
	InitElemTypeRtnForArithm(Int16,		Int16,		UInt8);
	InitElemTypeRtnForArithm(UInt16,	UInt16,		UInt8);
	InitElemTypeRtnForArithm(Int32,		Int32,		UInt8);
	InitElemTypeRtnForArithm(UInt32,	UInt32,		UInt8);
	InitElemTypeRtnForArithm(Int64,		Int64,		UInt8);
	InitElemTypeRtnForArithm(UInt64,	UInt64,		UInt8);
	InitElemTypeRtnForArithm(Half,		Half,		UInt8);
	InitElemTypeRtnForArithm(Float,		Float,		UInt8);
	InitElemTypeRtnForArithm(Double,	Double,		UInt8);
	InitElemTypeRtnForArithm(Complex,	Complex,	UInt8);
	InitElemTypeRtnForArithm(Int16,		Bool,		Int16);
	InitElemTypeRtnForArithm(Int16,		Int8,		Int16);
	InitElemTypeRtnForArithm(Int16,		UInt8,		Int16);
	InitElemTypeRtnForArithm(Int16,		Int16,		Int16);
	InitElemTypeRtnForArithm(UInt16,	UInt16,		Int16);
	InitElemTypeRtnForArithm(Int32,		Int32,		Int16);
	InitElemTypeRtnForArithm(UInt32,	UInt32,		Int16);
	InitElemTypeRtnForArithm(Int64,		Int64,		Int16);
	InitElemTypeRtnForArithm(UInt64,	UInt64,		Int16);
	InitElemTypeRtnForArithm(Half,		Half,		Int16);
	InitElemTypeRtnForArithm(Float,		Float,		Int16);
	InitElemTypeRtnForArithm(Double,	Double,		Int16);
	InitElemTypeRtnForArithm(Complex,	Complex,	Int16);
	InitElemTypeRtnForArithm(UInt16,	Bool,		UInt16);
	InitElemTypeRtnForArithm(UInt16,	Int8,		UInt16);
	InitElemTypeRtnForArithm(UInt16,	UInt8,		UInt16);
	InitElemTypeRtnForArithm(UInt16,	Int16,		UInt16);
	InitElemTypeRtnForArithm(UInt16,	UInt16,		UInt16);
	InitElemTypeRtnForArithm(Int32,		Int32,		UInt16);
	InitElemTypeRtnForArithm(UInt32,	UInt32,		UInt16);
	InitElemTypeRtnForArithm(Int64,		Int64,		UInt16);
	InitElemTypeRtnForArithm(UInt64,	UInt64,		UInt16);
	InitElemTypeRtnForArithm(Half,		Half,		UInt16);
	InitElemTypeRtnForArithm(Float,		Float,		UInt16);
	InitElemTypeRtnForArithm(Double,	Double,		UInt16);
	InitElemTypeRtnForArithm(Complex,	Complex,	UInt16);
	InitElemTypeRtnForArithm(Int32,		Bool,		Int32);
	InitElemTypeRtnForArithm(Int32,		Int8,		Int32);
	InitElemTypeRtnForArithm(Int32,		UInt8,		Int32);
	InitElemTypeRtnForArithm(Int32,		Int16,		Int32);
	InitElemTypeRtnForArithm(Int32,		UInt16,		Int32);
	InitElemTypeRtnForArithm(Int32,		Int32,		Int32);
	InitElemTypeRtnForArithm(UInt32,	UInt32,		Int32);
	InitElemTypeRtnForArithm(Int64,		Int64,		Int32);
	InitElemTypeRtnForArithm(UInt64,	UInt64,		Int32);
	InitElemTypeRtnForArithm(Half,		Half,		Int32);
	InitElemTypeRtnForArithm(Float,		Float,		Int32);
	InitElemTypeRtnForArithm(Double,	Double,		Int32);
	InitElemTypeRtnForArithm(Complex,	Complex,	Int32);
	InitElemTypeRtnForArithm(UInt32,	Bool,		UInt32);
	InitElemTypeRtnForArithm(UInt32,	Int8,		UInt32);
	InitElemTypeRtnForArithm(UInt32,	UInt8,		UInt32);
	InitElemTypeRtnForArithm(UInt32,	Int16,		UInt32);
	InitElemTypeRtnForArithm(UInt32,	UInt16,		UInt32);
	InitElemTypeRtnForArithm(UInt32,	Int32,		UInt32);
	InitElemTypeRtnForArithm(UInt32,	UInt32,		UInt32);
	InitElemTypeRtnForArithm(Int64,		Int64,		UInt32);
	InitElemTypeRtnForArithm(UInt64,	UInt64,		UInt32);
	InitElemTypeRtnForArithm(Half,		Half,		UInt32);
	InitElemTypeRtnForArithm(Float,		Float,		UInt32);
	InitElemTypeRtnForArithm(Double,	Double,		UInt32);
	InitElemTypeRtnForArithm(Complex,	Complex,	UInt32);
	InitElemTypeRtnForArithm(Int64,		Bool,		Int64);
	InitElemTypeRtnForArithm(Int64,		Int8,		Int64);
	InitElemTypeRtnForArithm(Int64,		UInt8,		Int64);
	InitElemTypeRtnForArithm(Int64,		Int16,		Int64);
	InitElemTypeRtnForArithm(Int64,		UInt16,		Int64);
	InitElemTypeRtnForArithm(Int64,		Int32,		Int64);
	InitElemTypeRtnForArithm(Int64,		UInt32,		Int64);
	InitElemTypeRtnForArithm(Int64,		Int64,		Int64);
	InitElemTypeRtnForArithm(UInt64,	UInt64,		Int64);
	InitElemTypeRtnForArithm(Half,		Half,		Int64);
	InitElemTypeRtnForArithm(Float,		Float,		Int64);
	InitElemTypeRtnForArithm(Double,	Double,		Int64);
	InitElemTypeRtnForArithm(Complex,	Complex,	Int64);
	InitElemTypeRtnForArithm(UInt64,	Bool,		UInt64);
	InitElemTypeRtnForArithm(UInt64,	Int8,		UInt64);
	InitElemTypeRtnForArithm(UInt64,	UInt8,		UInt64);
	InitElemTypeRtnForArithm(UInt64,	Int16,		UInt64);
	InitElemTypeRtnForArithm(UInt64,	UInt16,		UInt64);
	InitElemTypeRtnForArithm(UInt64,	Int32,		UInt64);
	InitElemTypeRtnForArithm(UInt64,	UInt32,		UInt64);
	InitElemTypeRtnForArithm(UInt64,	Int64,		UInt64);
	InitElemTypeRtnForArithm(UInt64,	UInt64,		UInt64);
	InitElemTypeRtnForArithm(Half,		Half,		UInt64);
	InitElemTypeRtnForArithm(Float,		Float,		UInt64);
	InitElemTypeRtnForArithm(Double,	Double,		UInt64);
	InitElemTypeRtnForArithm(Complex,	Complex,	UInt64);
	InitElemTypeRtnForArithm(Half,		Bool,		Half);
	InitElemTypeRtnForArithm(Half,		Int8,		Half);
	InitElemTypeRtnForArithm(Half,		UInt8,		Half);
	InitElemTypeRtnForArithm(Half,		Int16,		Half);
	InitElemTypeRtnForArithm(Half,		UInt16,		Half);
	InitElemTypeRtnForArithm(Half,		Int32,		Half);
	InitElemTypeRtnForArithm(Half,		UInt32,		Half);
	InitElemTypeRtnForArithm(Half,		Int64,		Half);
	InitElemTypeRtnForArithm(Half,		UInt64,		Half);
	InitElemTypeRtnForArithm(Half,		Half,		Half);
	InitElemTypeRtnForArithm(Float,		Float,		Half);
	InitElemTypeRtnForArithm(Double,	Double,		Half);
	InitElemTypeRtnForArithm(Complex,	Complex,	Half);
	InitElemTypeRtnForArithm(Float,		Bool,		Float);
	InitElemTypeRtnForArithm(Float,		Int8,		Float);
	InitElemTypeRtnForArithm(Float,		UInt8,		Float);
	InitElemTypeRtnForArithm(Float,		Int16,		Float);
	InitElemTypeRtnForArithm(Float,		UInt16,		Float);
	InitElemTypeRtnForArithm(Float,		Int32,		Float);
	InitElemTypeRtnForArithm(Float,		UInt32,		Float);
	InitElemTypeRtnForArithm(Float,		Int64,		Float);
	InitElemTypeRtnForArithm(Float,		UInt64,		Float);
	InitElemTypeRtnForArithm(Float,		Half,		Float);
	InitElemTypeRtnForArithm(Float,		Float,		Float);
	InitElemTypeRtnForArithm(Double,	Double,		Float);
	InitElemTypeRtnForArithm(Complex,	Complex,	Float);
	InitElemTypeRtnForArithm(Double,	Bool,		Double);
	InitElemTypeRtnForArithm(Double,	Int8,		Double);
	InitElemTypeRtnForArithm(Double,	UInt8,		Double);
	InitElemTypeRtnForArithm(Double,	Int16,		Double);
	InitElemTypeRtnForArithm(Double,	UInt16,		Double);
	InitElemTypeRtnForArithm(Double,	Int32,		Double);
	InitElemTypeRtnForArithm(Double,	UInt32,		Double);
	InitElemTypeRtnForArithm(Double,	Int64,		Double);
	InitElemTypeRtnForArithm(Double,	UInt64,		Double);
	InitElemTypeRtnForArithm(Double,	Half,		Double);
	InitElemTypeRtnForArithm(Double,	Float,		Double);
	InitElemTypeRtnForArithm(Double,	Double,		Double);
	InitElemTypeRtnForArithm(Complex,	Complex,	Double);
	InitElemTypeRtnForArithm(Complex,	Bool,		Complex);
	InitElemTypeRtnForArithm(Complex,	Int8,		Complex);
	InitElemTypeRtnForArithm(Complex,	UInt8,		Complex);
	InitElemTypeRtnForArithm(Complex,	Int16,		Complex);
	InitElemTypeRtnForArithm(Complex,	UInt16,		Complex);
	InitElemTypeRtnForArithm(Complex,	Int32,		Complex);
	InitElemTypeRtnForArithm(Complex,	UInt32,		Complex);
	InitElemTypeRtnForArithm(Complex,	Int64,		Complex);
	InitElemTypeRtnForArithm(Complex,	UInt64,		Complex);
	InitElemTypeRtnForArithm(Complex,	Half,		Complex);
	InitElemTypeRtnForArithm(Complex,	Float,		Complex);
	InitElemTypeRtnForArithm(Complex,	Double,		Complex);
	InitElemTypeRtnForArithm(Complex,	Complex,	Complex);
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
	Gurax_SetArrayFuncSingle(funcs.FindMax,				FindMax_T);
	Gurax_SetArrayFuncSingle(funcs.FindMin,				FindMin_T);
	Gurax_SetArrayFuncSingle(funcs.ArgMax,				ArgMax_T);
	Gurax_SetArrayFuncSingle(funcs.ArgMin,				ArgMin_T);
	Gurax_SetArrayFuncSingle(funcs.IndexSetValue,		IndexSetValue_T);
	Gurax_SetArrayFuncSingle(funcs.IndexGetValue,		IndexGetValue_T);
	Gurax_SetArrayFuncSingle(funcs.IndexSetDouble,		IndexSetDouble_T);
	Gurax_SetArrayFuncSingle(funcs.IndexGetDouble,		IndexGetDouble_T);
	Gurax_SetArrayFuncSingle(funcs.InjectFromValueList,	InjectFromValueList_T);
	Gurax_SetArrayFuncSingle(funcs.InjectFromIterator,	InjectFromIterator_T);
	Gurax_SetArrayFuncSingle(funcs.ExtractElems,		ExtractElems_T);
	Gurax_SetArrayFuncSingle(funcs.Put,					Put_T);
	Gurax_SetArrayFuncSingle(funcs.ToString,			ToString_T);
	Gurax_SetArrayFuncDouble(funcs.CopyElems,			CopyElems_T);
	Gurax_SetArrayFuncDouble(funcs.Transpose2d,			Transpose2d_T);
	Gurax_SetArrayFuncDouble(funcs.TransposeMulti,		TransposeMulti_T);
	Gurax_SetArrayFuncSingle(funcs.Neg_Array,			Neg_Array_T);
	Gurax_SetArrayFuncArithm(funcs.Add_ArrayArray,		Add_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Add_ArrayNumber,		Add_ArrayNumber_T);
	Gurax_SetArrayFuncSingle(funcs.Add_ArrayComplex,	Add_ArrayComplex_T);
	Gurax_SetArrayFuncArithm(funcs.And_ArrayArray,		And_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.And_ArrayNumber,		And_ArrayNumber_T);
	Gurax_SetArrayFuncArithm(funcs.Sub_ArrayArray,		Sub_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Sub_ArrayNumber,		Sub_ArrayNumber_T);
	Gurax_SetArrayFuncSingle(funcs.Sub_NumberArray,		Sub_NumberArray_T);
	Gurax_SetArrayFuncSingle(funcs.Sub_ArrayComplex,	Sub_ArrayComplex_T);
	Gurax_SetArrayFuncSingle(funcs.Sub_ComplexArray,	Sub_ComplexArray_T);
	Gurax_SetArrayFuncArithm(funcs.Mul_ArrayArray,		Mul_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Mul_ArrayNumber,		Mul_ArrayNumber_T);
	Gurax_SetArrayFuncSingle(funcs.Mul_ArrayComplex,	Mul_ArrayComplex_T);
	Gurax_SetArrayFuncArithm(funcs.Div_ArrayArray,		Div_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Div_ArrayNumber,		Div_ArrayNumber_T);
	Gurax_SetArrayFuncSingle(funcs.Div_NumberArray,		Div_NumberArray_T);
	Gurax_SetArrayFuncSingle(funcs.Div_ArrayComplex,	Div_ArrayComplex_T);
	Gurax_SetArrayFuncSingle(funcs.Div_ComplexArray,	Div_ComplexArray_T);
	Gurax_SetArrayFuncArithm(funcs.Pow_ArrayArray,		Pow_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Pow_ArrayNumber,		Pow_ArrayNumber_T);
	Gurax_SetArrayFuncSingle(funcs.Pow_NumberArray,		Pow_NumberArray_T);
	Gurax_SetArrayFuncSingle(funcs.Pow_ArrayComplex,	Pow_ArrayComplex_T);
	Gurax_SetArrayFuncSingle(funcs.Pow_ComplexArray,	Pow_ComplexArray_T);
	Gurax_SetArrayFuncArithm(funcs.Or_ArrayArray,		Or_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Or_ArrayNumber,		Or_ArrayNumber_T);
	Gurax_SetArrayFuncArithm(funcs.Xor_ArrayArray,		Xor_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Xor_ArrayNumber,		Xor_ArrayNumber_T);
	Gurax_SetArrayFuncDouble(funcs.Eq_ArrayArray,		Eq_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Eq_ArrayNumber,		Eq_ArrayNumber_T);
	Gurax_SetArrayFuncSingle(funcs.Eq_ArrayComplex,		Eq_ArrayComplex_T);
	Gurax_SetArrayFuncDouble(funcs.Ne_ArrayArray,		Ne_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Ne_ArrayNumber,		Ne_ArrayNumber_T);
	Gurax_SetArrayFuncSingle(funcs.Ne_ArrayComplex,		Ne_ArrayComplex_T);
	Gurax_SetArrayFuncDouble(funcs.Lt_ArrayArray,		Lt_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Lt_ArrayNumber,		Lt_ArrayNumber_T);
	Gurax_SetArrayFuncSingle(funcs.Lt_NumberArray,		Lt_NumberArray_T);
	Gurax_SetArrayFuncDouble(funcs.Le_ArrayArray,		Le_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Le_ArrayNumber,		Le_ArrayNumber_T);
	Gurax_SetArrayFuncSingle(funcs.Le_NumberArray,		Le_NumberArray_T);
	Gurax_SetArrayFuncDouble(funcs.Cmp_ArrayArray,		Cmp_ArrayArray_T);
	Gurax_SetArrayFuncSingle(funcs.Cmp_ArrayNumber,		Cmp_ArrayNumber_T);
	Gurax_SetArrayFuncSingle(funcs.Cmp_NumberArray,		Cmp_NumberArray_T);
	Gurax_SetArrayFuncArithm(funcs.Dot_ArrayArray,		Dot_ArrayArray_T);
	Gurax_SetArrayFuncArithm(funcs.Cross_ArrayArray,	Cross_ArrayArray_T);
}

Value* Array::FindMax(int axis, const ValueList& valuesDim) const
{
	if (!GetDimSizes().RegulateAxis(&axis)) return Value::nil();
	if (GetDimSizes().size() != valuesDim.size() + 1) {
		Error::Issue(ErrorType::ArgumentError, "invalid number of arguments");
		return Value::nil();
	}
	return funcs.FindMax[_elemType.id](*this, axis, valuesDim);
}

Value* Array::FindMin(int axis, const ValueList& valuesDim) const
{
	if (!GetDimSizes().RegulateAxis(&axis)) return Value::nil();
	if (GetDimSizes().size() != valuesDim.size() + 1) {
		Error::Issue(ErrorType::ArgumentError, "invalid number of arguments");
		return Value::nil();
	}
	return funcs.FindMin[_elemType.id](*this, axis, valuesDim);
}

Value* Array::ArgMax(int axis, const ValueList& valuesDim) const
{
	if (!GetDimSizes().RegulateAxis(&axis)) return Value::nil();
	if (GetDimSizes().size() != valuesDim.size() + 1) {
		Error::Issue(ErrorType::ArgumentError, "invalid number of arguments");
		return Value::nil();
	}
	return funcs.ArgMax[_elemType.id](*this, axis, valuesDim);
}

Value* Array::ArgMin(int axis, const ValueList& valuesDim) const
{
	if (!GetDimSizes().RegulateAxis(&axis)) return Value::nil();
	if (GetDimSizes().size() != valuesDim.size() + 1) {
		Error::Issue(ErrorType::ArgumentError, "invalid number of arguments");
		return Value::nil();
	}
	return funcs.ArgMin[_elemType.id](*this, axis, valuesDim);
}

void Array::InjectElems(ValueList& values, size_t offset, size_t len)
{
	//::printf("%p\n", &funcs.InjectFromValueList[_elemType.id]);
	funcs.InjectFromValueList[_elemType.id](values, GetPointerC<void>(), offset, len);
}

void Array::InjectElems(ValueList& values, size_t offset)
{
	InjectElems(values, offset, std::min(values.size(), _dimSizes.CalcLength() - offset));
}

bool Array::InjectElems(Iterator& iterator, size_t offset, size_t len)
{
	return funcs.InjectFromIterator[_elemType.id](iterator, GetPointerC<void>(), offset, len);
}

bool Array::InjectElems(Iterator& iterator, size_t offset)
{
	return InjectElems(iterator, offset, _dimSizes.CalcLength() - offset);
}

void Array::InjectElems(const void* pSrc, const ElemTypeT& elemType, size_t offset, size_t len)
{
	funcs.CopyElems[_elemType.id][elemType.id](GetPointerC<void>(), pSrc, offset, len);
}

void Array::ExtractElems(ValueOwner& values, size_t offset, size_t len) const
{
	values.reserve(values.size() + len);
	funcs.ExtractElems[_elemType.id](values, GetPointerC<void>(), offset, len);
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

void Array::ToString(const StringStyle& ss, String& str, size_t offset, size_t len) const
{
	funcs.ToString[_elemType.id](ss, str, GetPointerC<void>(), offset, len);
}

void Array::ToStringSub(const StringStyle& ss, String& str, size_t& offset, DimSizes::const_iterator pDimSize) const
{
	str += "[";
	if (pDimSize + 1 == _dimSizes.end()) {
		ToString(ss, str, offset, *pDimSize);
		offset += *pDimSize;
	} else {
		const char* strComma = ss.IsCram()? "," : ", ";
		for (size_t i = 0; i < *pDimSize; i++) {
			if (i > 0) str += strComma;
			ToStringSub(ss, str, offset, pDimSize + 1);
		}
	}
	str += "]";
}

void Array::ToString(const StringStyle& ss, String& str) const
{
	if (_dimSizes.empty()) {
		ToString(ss, str, 0, 0);
	} else {
		size_t offset = 0;
		ToStringSub(ss, str, offset, _dimSizes.begin());
	}
}

bool Array::Transpose2d(RefPtr<Array>& pArrayRtn) const
{
	const DimSizes& dimSizes = GetDimSizes();
	if (dimSizes.size() < 2) {
		pArrayRtn.reset(Clone());
		return true;
	}
	DimSizes dimSizesRtn;
	dimSizesRtn.reserve(dimSizes.size());
	size_t nRtns = 1;
	for (auto pDim = dimSizes.begin(); pDim != dimSizes.begin() + dimSizes.size() - 2; pDim++) {
		nRtns *= *pDim;
		dimSizesRtn.push_back(*pDim);
	}
	size_t nRows = dimSizes.GetColSize();
	size_t nCols = dimSizes.GetRowSize();
	size_t nFwd = nRows * nCols;
	dimSizesRtn.push_back(nRows);
	dimSizesRtn.push_back(nCols);
	pArrayRtn.reset(Create(GetElemType(), dimSizesRtn));
	auto func = funcs.Transpose2d[GetElemType().id][GetElemType().id];
	void* pvDst = pArrayRtn->GetPointerC<void>();
	const void* pvSrc = GetPointerC<void>();
	for (size_t iRtn = 0; iRtn < nRtns; iRtn++) {
		func(pvDst, pvSrc, nRows, nCols);
		pvDst = pArrayRtn->FwdPointer(pvDst, nFwd);
		pvSrc = FwdPointer(pvSrc, nFwd);
	}
	return true;
}

bool Array::TransposeMulti(RefPtr<Array>& pArrayRtn, const NumList<size_t>& axes) const
{
	DimSizes dimSizesRtn;
	for (size_t axis : axes) {
		if (axis >= _dimSizes.size()) {
			Error::Issue(ErrorType::RangeError, "specified axis is out of range");
			return false;
		}
		dimSizesRtn.push_back(_dimSizes[axis]);
	}
	pArrayRtn.reset(Create(GetElemType(), dimSizesRtn));
	auto func = funcs.TransposeMulti[GetElemType().id][GetElemType().id];
	void* pvDst = pArrayRtn->GetPointerC<void>();
	const void* pvSrc = GetPointerC<void>();
	func(&pvDst, pvSrc, _dimSizes, axes.begin(), axes.end());
	return true;
}

bool Array::GenericUnaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Array& array,
	const std::function<void (void* pvRtn, const void* pv, size_t len)>& func)
{
	if (!pArrayRtn) pArrayRtn.reset(Create(elemTypeRtn, array.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pv = array.GetPointerC<void>();
	size_t len = array.GetDimSizes().CalcLength();
	func(pvRtn, pv, len);
	return true;
}

bool Array::GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Array& arrayL, const Array& arrayR,
	const std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>& func, const char* opDisp)
{
	size_t nRtns = 1;
	size_t nFwdRtn = 0;
	size_t nFwdL = 0, nFwdR = 0;
	const DimSizes* pDimSizesRtn = DimSizes::DetermineResult(arrayL.GetDimSizes(), arrayR.GetDimSizes(), &nRtns, &nFwdRtn, &nFwdL, &nFwdR);
	if (!pDimSizesRtn) {
		Error::Issue(ErrorType::SizeError, "unmatched array size: %s %s %s",
				arrayL.ToString(StringStyle::BriefCram).c_str(), opDisp, arrayR.ToString(StringStyle::BriefCram).c_str());
		return nullptr;
	}
	if (!pArrayRtn) pArrayRtn.reset(Create(elemTypeRtn, *pDimSizesRtn));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	for (size_t iRtn = 0; iRtn < nRtns; iRtn++) {
		func(pvRtn, pvL, pvR, nFwdRtn);
		pvRtn = pArrayRtn->FwdPointer(pvRtn, nFwdRtn);
		pvL = arrayL.FwdPointer(pvL, nFwdL);
		pvR = arrayR.FwdPointer(pvR, nFwdR);
	}
	return true;
}

bool Array::GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Array& arrayL, Double numR,
	const std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>& func, const char* opDisp)
{
	if (!pArrayRtn) pArrayRtn.reset(Create(elemTypeRtn, arrayL.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	size_t len = arrayL.GetDimSizes().CalcLength();
	func(pvRtn, pvL, numR, len);
	return true;
}

bool Array::GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, Double numL, const Array& arrayR,
	const std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>& func, const char* opDisp)
{
	if (!pArrayRtn) pArrayRtn.reset(Create(elemTypeRtn, arrayR.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	size_t len = arrayR.GetDimSizes().CalcLength();
	func(pvRtn, numL, pvR, len);
	return true;
}

bool Array::GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Array& arrayL, UInt64 numR,
	const std::function<void (void* pvRtn, const void* pvL, UInt64 numR, size_t len)>& func, const char* opDisp)
{
	if (!pArrayRtn) pArrayRtn.reset(Create(elemTypeRtn, arrayL.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	size_t len = arrayL.GetDimSizes().CalcLength();
	func(pvRtn, pvL, numR, len);
	return true;
}

bool Array::GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, UInt64 numL, const Array& arrayR,
	const std::function<void (void* pvRtn, UInt64 numL, const void* pvR, size_t len)>& func, const char* opDisp)
{
	if (!pArrayRtn) pArrayRtn.reset(Create(elemTypeRtn, arrayR.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	size_t len = arrayR.GetDimSizes().CalcLength();
	func(pvRtn, numL, pvR, len);
	return true;
}

bool Array::GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Array& arrayL, const Complex& numR,
	const std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>& func, const char* opDisp)
{
	if (!pArrayRtn) pArrayRtn.reset(Create(elemTypeRtn, arrayL.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	size_t len = arrayL.GetDimSizes().CalcLength();
	func(pvRtn, pvL, numR, len);
	return true;
}

bool Array::GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Complex& numL, const Array& arrayR,
	const std::function<void (void* pvRtn, const Complex& numL, const void* pvR, size_t len)>& func, const char* opDisp)
{
	if (!pArrayRtn) pArrayRtn.reset(Create(elemTypeRtn, arrayR.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	size_t len = arrayR.GetDimSizes().CalcLength();
	func(pvRtn, numL, pvR, len);
	return true;
}

bool Array::Neg(RefPtr<Array>& pArrayRtn, const Array& array)
{
	return GenericUnaryOp(pArrayRtn, array.GetElemType(), array, funcs.Neg_Array[array.GetElemType().id]);
}

bool Array::Add(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, GetElemTypeRtnForArithm(arrayL, arrayR), arrayL, arrayR, funcs.Add_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "+");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Add(pArrayRtn, arrayL, arrayR.GetScalarDouble());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		return Add(pArrayRtn, arrayL, arrayR.GetScalarComplex());
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Add(pArrayRtn, arrayR, arrayL.GetScalarDouble());
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		return Add(pArrayRtn, arrayR, arrayL.GetScalarComplex());
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Double, arrayL.GetScalarDouble() + arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarDouble() + arrayR.GetScalarComplex()));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarComplex() + arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarComplex() + arrayR.GetScalarComplex()));
		return true;
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Add(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR)
{
	return GenericBinaryOp(pArrayRtn, arrayL.GetElemType(), arrayL, numR, funcs.Add_ArrayNumber[arrayL.GetElemType().id], "+");
}

bool Array::Add(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Complex, arrayL, numR, funcs.Add_ArrayComplex[arrayL.GetElemType().id], "+");
}

bool Array::And(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, GetElemTypeRtnForArithm(arrayL, arrayR), arrayL, arrayR, funcs.And_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "+");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return And(pArrayRtn, arrayL, arrayR.GetScalarUInt64());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return And(pArrayRtn, arrayR, arrayL.GetScalarUInt64());
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Double, arrayL.GetScalarUInt64() & arrayR.GetScalarUInt64()));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		// unsupported operation
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::And(RefPtr<Array>& pArrayRtn, const Array& arrayL, UInt64 numR)
{
	return GenericBinaryOp(pArrayRtn, arrayL.GetElemType(), arrayL, numR, funcs.And_ArrayNumber[arrayL.GetElemType().id], "&");
}

bool Array::Sub(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, GetElemTypeRtnForArithm(arrayL, arrayR), arrayL, arrayR, funcs.Sub_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "-");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Sub(pArrayRtn, arrayL, arrayR.GetScalarDouble());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		return Sub(pArrayRtn, arrayL, arrayR.GetScalarComplex());
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Sub(pArrayRtn, arrayL.GetScalarDouble(), arrayR);
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		return Sub(pArrayRtn, arrayL.GetScalarComplex(), arrayR);
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Double, arrayL.GetScalarDouble() - arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarDouble() - arrayR.GetScalarComplex()));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarComplex() - arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarComplex() - arrayR.GetScalarComplex()));
		return true;
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Sub(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR)
{
	return GenericBinaryOp(pArrayRtn, arrayL.GetElemType(), arrayL, numR, funcs.Sub_ArrayNumber[arrayL.GetElemType().id], "-");
}

bool Array::Sub(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR)
{
	return GenericBinaryOp(pArrayRtn, arrayR.GetElemType(), numL, arrayR, funcs.Sub_NumberArray[arrayR.GetElemType().id], "-");
}

bool Array::Sub(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Complex, arrayL, numR, funcs.Sub_ArrayComplex[arrayL.GetElemType().id], "-");
}

bool Array::Sub(RefPtr<Array>& pArrayRtn, const Complex& numL, const Array& arrayR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Complex, numL, arrayR, funcs.Sub_ComplexArray[arrayR.GetElemType().id], "-");
}

bool Array::Mul(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, GetElemTypeRtnForArithm(arrayL, arrayR), arrayL, arrayR, funcs.Mul_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "*");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Mul(pArrayRtn, arrayL, arrayR.GetScalarDouble());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		return Mul(pArrayRtn, arrayL, arrayR.GetScalarComplex());
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Mul(pArrayRtn, arrayR, arrayL.GetScalarDouble());
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		return Mul(pArrayRtn, arrayR, arrayL.GetScalarComplex());
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Double, arrayL.GetScalarDouble() * arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarDouble() * arrayR.GetScalarComplex()));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarComplex() * arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarComplex() * arrayR.GetScalarComplex()));
		return true;
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Mul(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR)
{
	return GenericBinaryOp(pArrayRtn, arrayL.GetElemType(), arrayL, numR, funcs.Mul_ArrayNumber[arrayL.GetElemType().id], "*");
}

bool Array::Mul(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Complex, arrayL, numR, funcs.Mul_ArrayComplex[arrayL.GetElemType().id], "*");
}

bool Array::Div(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, GetElemTypeRtnForArithm(arrayL, arrayR), arrayL, arrayR, funcs.Div_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "/");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Div(pArrayRtn, arrayL, arrayR.GetScalarDouble());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		return Div(pArrayRtn, arrayL, arrayR.GetScalarComplex());
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Div(pArrayRtn, arrayL.GetScalarDouble(), arrayR);
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		return Div(pArrayRtn, arrayL.GetScalarComplex(), arrayR);
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		Double num = arrayR.GetScalarDouble();
		if (num == 0.) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return false;
		}
		pArrayRtn.reset(Array::CreateScalar(ElemType::Double, arrayL.GetScalarDouble() / num));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		const Complex& num = arrayR.GetScalarComplex();
		if (num.IsZero()) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return false;
		}
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarDouble() / num));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		Double num = arrayR.GetScalarDouble();
		if (num == 0.) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return false;
		}
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarComplex() / num));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		const Complex& num = arrayR.GetScalarComplex();
		if (num.IsZero()) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return false;
		}
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, arrayL.GetScalarComplex() / num));
		return true;
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Div(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR)
{
	return GenericBinaryOp(pArrayRtn, arrayL.GetElemType(), arrayL, numR, funcs.Div_ArrayNumber[arrayL.GetElemType().id], "/");
}

bool Array::Div(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR)
{
	return GenericBinaryOp(pArrayRtn, arrayR.GetElemType(), numL, arrayR, funcs.Div_NumberArray[arrayR.GetElemType().id], "/");
}

bool Array::Div(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Complex, arrayL, numR, funcs.Div_ArrayComplex[arrayL.GetElemType().id], "/");
}

bool Array::Div(RefPtr<Array>& pArrayRtn, const Complex& numL, const Array& arrayR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Complex, numL, arrayR, funcs.Div_ComplexArray[arrayR.GetElemType().id], "/");
}

bool Array::Pow(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, GetElemTypeRtnForArithm(arrayL, arrayR), arrayL, arrayR, funcs.Pow_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "**");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Pow(pArrayRtn, arrayL, arrayR.GetScalarDouble());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		return Pow(pArrayRtn, arrayL, arrayR.GetScalarComplex());
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Pow(pArrayRtn, arrayL.GetScalarDouble(), arrayR);
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		return Pow(pArrayRtn, arrayL.GetScalarComplex(), arrayR);
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Double, std::pow(arrayL.GetScalarDouble(), arrayR.GetScalarDouble())));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, std::pow(arrayL.GetScalarDouble(), arrayR.GetScalarComplex())));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, std::pow(arrayL.GetScalarComplex(), arrayR.GetScalarDouble())));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Complex, std::pow(arrayL.GetScalarComplex(), arrayR.GetScalarComplex())));
		return true;
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Pow(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR)
{
	return GenericBinaryOp(pArrayRtn, arrayL.GetElemType(), arrayL, numR, funcs.Pow_ArrayNumber[arrayL.GetElemType().id], "**");
}

bool Array::Pow(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR)
{
	return GenericBinaryOp(pArrayRtn, arrayR.GetElemType(), numL, arrayR, funcs.Pow_NumberArray[arrayR.GetElemType().id], "**");
}

bool Array::Pow(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Complex, arrayL, numR, funcs.Pow_ArrayComplex[arrayL.GetElemType().id], "**");
}

bool Array::Pow(RefPtr<Array>& pArrayRtn, const Complex& numL, const Array& arrayR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Complex, numL, arrayR, funcs.Pow_ComplexArray[arrayR.GetElemType().id], "**");
}

bool Array::Or(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, GetElemTypeRtnForArithm(arrayL, arrayR), arrayL, arrayR, funcs.Or_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "|");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Or(pArrayRtn, arrayL, arrayR.GetScalarUInt64());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Or(pArrayRtn, arrayR, arrayL.GetScalarUInt64());
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Double, arrayL.GetScalarUInt64() | arrayR.GetScalarUInt64()));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		// unsupported operation
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Or(RefPtr<Array>& pArrayRtn, const Array& arrayL, UInt64 numR)
{
	return GenericBinaryOp(pArrayRtn, arrayL.GetElemType(), arrayL, numR, funcs.Or_ArrayNumber[arrayL.GetElemType().id], "|");
}

bool Array::Xor(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, GetElemTypeRtnForArithm(arrayL, arrayR), arrayL, arrayR, funcs.Xor_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "^");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Xor(pArrayRtn, arrayL, arrayR.GetScalarUInt64());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Xor(pArrayRtn, arrayR, arrayL.GetScalarUInt64());
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Double, arrayL.GetScalarUInt64() ^ arrayR.GetScalarUInt64()));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		// unsupported operation
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Xor(RefPtr<Array>& pArrayRtn, const Array& arrayL, UInt64 numR)
{
	return GenericBinaryOp(pArrayRtn, arrayL.GetElemType(), arrayL, numR, funcs.Xor_ArrayNumber[arrayL.GetElemType().id], "^");
}

bool Array::Eq(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, ElemType::Bool, arrayL, arrayR, funcs.Eq_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "==");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Eq(pArrayRtn, arrayL, arrayR.GetScalarDouble());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		return Eq(pArrayRtn, arrayL, arrayR.GetScalarComplex());
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Eq(pArrayRtn, arrayR, arrayL.GetScalarDouble());
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		return Eq(pArrayRtn, arrayR, arrayL.GetScalarComplex());
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Bool, arrayL.GetScalarDouble() == arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Bool, arrayL.GetScalarDouble() == arrayR.GetScalarComplex()));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Bool, arrayL.GetScalarComplex() == arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Bool, arrayL.GetScalarComplex() == arrayR.GetScalarComplex()));
		return true;
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Eq(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Bool, arrayL, numR, funcs.Eq_ArrayNumber[arrayL.GetElemType().id], "==");
}

bool Array::Eq(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Bool, arrayL, numR, funcs.Eq_ArrayComplex[arrayL.GetElemType().id], "==");
}

bool Array::Ne(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, ElemType::Bool, arrayL, arrayR, funcs.Ne_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "!=");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Ne(pArrayRtn, arrayL, arrayR.GetScalarDouble());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		return Ne(pArrayRtn, arrayL, arrayR.GetScalarComplex());
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Ne(pArrayRtn, arrayR, arrayL.GetScalarDouble());
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		return Ne(pArrayRtn, arrayR, arrayL.GetScalarComplex());
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Bool, arrayL.GetScalarDouble() != arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Bool, arrayL.GetScalarDouble() != arrayR.GetScalarComplex()));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Bool, arrayL.GetScalarComplex() != arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Bool, arrayL.GetScalarComplex() != arrayR.GetScalarComplex()));
		return true;
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Ne(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Bool, arrayL, numR, funcs.Ne_ArrayNumber[arrayL.GetElemType().id], "!=");
}

bool Array::Ne(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Bool, arrayL, numR, funcs.Ne_ArrayComplex[arrayL.GetElemType().id], "!=");
}

bool Array::Lt(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, ElemType::Bool, arrayL, arrayR, funcs.Lt_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "<");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Lt(pArrayRtn, arrayL, arrayR.GetScalarDouble());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Lt(pArrayRtn, arrayL.GetScalarDouble(), arrayR);
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Bool, arrayL.GetScalarDouble() < arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		// unsupported operation
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Lt(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Bool, arrayL, numR, funcs.Lt_ArrayNumber[arrayL.GetElemType().id], "<");
}

bool Array::Lt(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Bool, numL, arrayR, funcs.Lt_NumberArray[arrayR.GetElemType().id], "<");
}

bool Array::Le(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, ElemType::Bool, arrayL, arrayR, funcs.Le_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "<=");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Le(pArrayRtn, arrayL, arrayR.GetScalarDouble());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Le(pArrayRtn, arrayL.GetScalarDouble(), arrayR);
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Bool, arrayL.GetScalarDouble() <= arrayR.GetScalarDouble()));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		// unsupported operation
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Le(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Bool, arrayL, numR, funcs.Le_ArrayNumber[arrayL.GetElemType().id], "<=");
}

bool Array::Le(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Bool, numL, arrayR, funcs.Le_NumberArray[arrayR.GetElemType().id], "<=");
}

bool Array::Cmp(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	if (arrayL.IsArray() && arrayR.IsArray()) {
		return GenericBinaryOp(pArrayRtn, ElemType::Int8, arrayL, arrayR, funcs.Cmp_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id], "<=>");
	} else if (arrayL.IsArray() && arrayR.IsScalarNumber()) {
		return Cmp(pArrayRtn, arrayL, arrayR.GetScalarDouble());
	} else if (arrayL.IsArray() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsArray()) {
		return Cmp(pArrayRtn, arrayL.GetScalarDouble(), arrayR);
	} else if (arrayL.IsScalarComplex() && arrayR.IsArray()) {
		// unsupported operation
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarNumber()) {
		pArrayRtn.reset(Array::CreateScalar(ElemType::Int8, Number<Double>::Cmp(arrayL.GetScalarDouble(), arrayR.GetScalarDouble())));
		return true;
	} else if (arrayL.IsScalarNumber() && arrayR.IsScalarComplex()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarNumber()) {
		// unsupported operation
	} else if (arrayL.IsScalarComplex() && arrayR.IsScalarComplex()) {
		// unsupported operation
	}
	Error::Issue(ErrorType::ValueError, "unsupported operation");
	return false;
}

bool Array::Cmp(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Int8, arrayL, numR, funcs.Cmp_ArrayNumber[arrayL.GetElemType().id], "<=>");
}

bool Array::Cmp(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR)
{
	return GenericBinaryOp(pArrayRtn, ElemType::Int8, numL, arrayR, funcs.Cmp_NumberArray[arrayR.GetElemType().id], "<=>");
}

bool Array::Dot(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	auto func = funcs.Dot_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id];
	const DimSizes& dimSizesL = arrayL.GetDimSizes();
	const DimSizes& dimSizesR = arrayR.GetDimSizes();
	if (dimSizesL.size() < 2 || dimSizesR.size() < 2 || dimSizesL.GetColSize() != dimSizesR.GetRowSize()) {
		Error::Issue(ErrorType::SizeError, "unmatched array size: %s |.| %s",
				arrayL.ToString(StringStyle::BriefCram).c_str(), arrayR.ToString(StringStyle::BriefCram).c_str());
		return false;
	}
	size_t nRtns = 1;
	size_t nFwdRtn = 0;
	size_t nFwdL = 0, nFwdR = 0;
	DimSizes dimSizesRtn;
	if (dimSizesL.size() >= 2 && dimSizesR.size() == 2) {
		auto pBegin = dimSizesL.begin(), pEnd = dimSizesL.begin() + dimSizesL.size() - 2;
		dimSizesRtn.insert(dimSizesRtn.begin(), pBegin, pEnd);
		nFwdL = DimSizes::CalcLength(pBegin, pEnd) * dimSizesL.GetColSize() * dimSizesL.GetRowSize();
	} else if (dimSizesL.size() == 2 && dimSizesR.size() >= 2) {
		auto pBegin = dimSizesR.begin(), pEnd = dimSizesR.begin() + dimSizesR.size() - 2;
		dimSizesRtn.insert(dimSizesRtn.begin(), pBegin, pEnd);
		nFwdR = DimSizes::CalcLength(pBegin, pEnd) * dimSizesR.GetColSize() * dimSizesR.GetRowSize();
	} else {
		Error::Issue(ErrorType::SizeError, "unmatched array size: %s |.| %s",
				arrayL.ToString(StringStyle::BriefCram).c_str(), arrayR.ToString(StringStyle::BriefCram).c_str());
		return false;
	}
	dimSizesRtn.push_back(dimSizesL.GetRowSize());
	dimSizesRtn.push_back(dimSizesR.GetColSize());
	if (!pArrayRtn) pArrayRtn.reset(Create(GetElemTypeRtnForArithm(arrayL, arrayR), dimSizesRtn));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	for (size_t iRtn = 0; iRtn < nRtns; iRtn++) {
		func(pvRtn, dimSizesRtn.GetRowSize(), dimSizesRtn.GetColSize(), pvL, pvR, dimSizesL.GetColSize());
		pvRtn = pArrayRtn->FwdPointer(pvRtn, nFwdRtn);
		pvL = arrayL.FwdPointer(pvL, nFwdL);
		pvR = arrayR.FwdPointer(pvR, nFwdR);
	}
	return true;
}

bool Array::Cross(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR)
{
	const DimSizes& dimSizesL = arrayL.GetDimSizes();
	const DimSizes& dimSizesR = arrayR.GetDimSizes();
	if (dimSizesL.size() != 1 || dimSizesR.size() != 1 || dimSizesL[0] != 3 || dimSizesR[0] != 3) {
		Error::Issue(ErrorType::SizeError, "unmatched array size: %s |^| %s",
				arrayL.ToString(StringStyle::BriefCram).c_str(), arrayR.ToString(StringStyle::BriefCram).c_str());
		return nullptr;
	}
	size_t n = 3;
	if (!pArrayRtn) pArrayRtn.reset(Create(GetElemTypeRtnForArithm(arrayL, arrayR), DimSizes(n)));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	auto func = funcs.Cross_ArrayArray[arrayL.GetElemType().id][arrayR.GetElemType().id];
	func(pvRtn, pvL, pvR, n);
	return true;
}

Value_List* Array::ToList() const
{
	RefPtr<ValueOwner> pValues(new ValueOwner());
	ExtractElems(*pValues);
	VType& vtypeOfElems = pValues->GetVTypeOfElemsQuick();
	return new Value_List(vtypeOfElems, pValues.release());
}

Value* Array::ToValue() const
{
	return IsScalar()? IndexGetValue(0) : new Value_Array(Reference());
}

Array* Array::CreateLike() const
{
	return Create(GetElemType(), GetDimSizes());
}

Array* Array::CreateCasted(const ElemTypeT& elemType) const
{
	RefPtr<Array> pArray(Create(elemType, _dimSizes));
	pArray->InjectElems(GetPointerC<void>(), GetElemType(), 0, _dimSizes.CalcLength());
	return pArray.release();
}

const Array::ElemTypeT& Array::SymbolToElemType(const Symbol* pSymbol)
{
	auto iter = _mapSymbolToElemType.find(pSymbol);
	return (iter == _mapSymbolToElemType.end())? ElemType::None : *iter->second;
}

const Array::ElemTypeT& Array::AtSymbolToElemType(const Symbol* pSymbol)
{
	auto iter = _mapAtSymbolToElemType.find(pSymbol);
	return (iter == _mapAtSymbolToElemType.end())? ElemType::None : *iter->second;
}

String Array::ToString(const StringStyle& ss) const
{
	if (ss.IsBracket()) {
		return String().Format("Array:@%s(%s)",
				GetElemTypeName(), GetDimSizes().ToString(StringStyle::Cram, ss.GetComma()).c_str());
	} else if (ss.IsBrief()) {
		return String().Format("@%s(%s)",
				GetElemTypeName(), GetDimSizes().ToString(ss, ss.GetComma()).c_str());
	} else {
		String str;
		ToString(ss, str);
		return str;
	}
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
DimSizes::DimSizes(const ValueList& values)
{
	reserve(values.size());
	for (const Value* pValue : values) {
		push_back(Value_Number::GetNumberPos<size_t>(*pValue));
		if (Error::IsIssued()) break;
	}
}

size_t DimSizes::CalcLength(const_iterator pDimSizeBegin, const_iterator pDimSizeEnd)
{
	size_t len = 1;
	for (auto pDimSize = pDimSizeBegin; pDimSize != pDimSizeEnd; pDimSize++) len *= *pDimSize;
	return len;
}

size_t DimSizes::CalcOffset(size_t axis, const ValueList& valuesDim, size_t* pStrides) const
{
	size_t offset = 0;
	auto ppValueDim = valuesDim.rbegin();
	size_t axisEach = size() - 1;
	size_t strides = 1;
	for (auto pDimSize = rbegin(); pDimSize != rend(); pDimSize++, axisEach--) {
		size_t dimSize = *pDimSize;
		if (axis == axisEach) {
			*pStrides = strides;
		} else {
			int dim = Value_Number::GetNumber<int>(**ppValueDim);
			if (dim < 0) dim += dimSize;
			if (dim < 0 || dim >= dimSize) {
				Error::Issue(ErrorType::RangeError, "specified dimension is out of range");
				return 0;
			}
			offset += dim * strides;
			ppValueDim++;
		}
		strides *= dimSize;
	}
	return offset;
}

const DimSizes* DimSizes::DetermineResult(const DimSizes& dimSizesL, const DimSizes& dimSizesR,
					size_t* pnRtns, size_t* pnFwdRtn, size_t* pnFwdL, size_t* pnFwdR)
{
	if (dimSizesL.size() >= dimSizesR.size()) {
		size_t nDimsHead = dimSizesL.size() - dimSizesR.size();
		*pnRtns = CalcLength(dimSizesL.begin(), dimSizesL.begin() + nDimsHead);
		*pnFwdL = *pnFwdRtn = dimSizesR.CalcLength();
		*pnFwdR = 0;
		if (dimSizesR.DoesMatch(dimSizesL, nDimsHead)) return &dimSizesL;
	} else {
		size_t nDimsHead = dimSizesR.size() - dimSizesL.size();
		*pnRtns = CalcLength(dimSizesR.begin(), dimSizesR.begin() + nDimsHead);
		*pnFwdR = *pnFwdRtn = dimSizesL.CalcLength();
		*pnFwdL = 0;
		if (dimSizesL.DoesMatch(dimSizesR, nDimsHead)) return &dimSizesR;
	}
	return nullptr;
}

bool DimSizes::IsEqual(const DimSizes& dimSizes) const
{
	if (size() != dimSizes.size()) return false;
	auto pDimSize1 = begin();
	auto pDimSize2 = dimSizes.begin();
	for ( ; pDimSize1 != end(); pDimSize1++, pDimSize2++) {
		if (*pDimSize1 != *pDimSize2) return false;
	}
	return true;
}

bool DimSizes::DoesMatch(const DimSizes& dimSizes, size_t offset) const
{
	auto pDimSize1 = begin();
	auto pDimSize2 = dimSizes.begin() + offset;
	if (size() != dimSizes.size() - offset) return false;
	for ( ; pDimSize1 != end(); pDimSize1++, pDimSize2++) {
		if (*pDimSize1 != *pDimSize2) return false;
	}
	return true;
}

bool DimSizes::DoesMatchDot(const DimSizes& dimSizes, size_t offset) const
{
	auto pDimSize1 = begin();
	auto pDimSize2 = dimSizes.begin() + offset;
	if (size() != dimSizes.size() - offset) return false;
	auto pDimSizeEnd1 = begin() + size() - 2;
	for ( ; pDimSize1 != pDimSizeEnd1; pDimSize1++, pDimSize2++) {
		if (*pDimSize1 != *pDimSize2) return false;
	}
	return GetColSize() == dimSizes.GetRowSize();
}

bool DimSizes::Verify(const ValueList& values) const
{
	auto pDimSize = begin();
	auto ppValue = values.begin();
	for ( ; pDimSize != end() && ppValue != values.end(); pDimSize++, ppValue++) {
		if (*pDimSize != Value_Number::GetNumber<size_t>(**ppValue)) return false;
	}
	return pDimSize == end() && ppValue == values.end();
}

bool DimSizes::Reshape(DimSizes& dimSizesRtn, const ValueList& values) const
{
	size_t len = CalcLength();
	dimSizesRtn.reserve(values.size());
	int iUndetermined = -1;
	size_t dimSizeProd = 1;
	size_t i = 0;
	for (auto pValue : values) {
		if (pValue->IsType(VTYPE_Number)) {
			size_t dimSize = Value_Number::GetNumberPos<size_t>(*pValue);
			if (Error::IsIssued()) return false;
			dimSizesRtn.push_back(dimSize);
			dimSizeProd *= dimSize;
		} else if (pValue->IsInvalid()) {
			if (iUndetermined >= 0) {
				Error::Issue(ErrorType::ValueError, "more than one undetermined dimension");
				return false;
			}
			dimSizesRtn.push_back(0);
			iUndetermined = i;
		} else {
			Error::Issue(ErrorType::TypeError, "only Number value is acceptable");
			return false;
		}
		i++;
	}
	if (len < dimSizeProd) {
		Error::Issue(ErrorType::RangeError, "specified dimension exceeds the memory amount");
		return false;
	} else if (iUndetermined < 0 && len != dimSizeProd) {
		Error::Issue(ErrorType::ValueError, "specified dimension is less than the memory amount");
		return false;
	} else if (len % dimSizeProd != 0) {
		Error::Issue(ErrorType::ValueError, "invalid dimension");
		return false;
	}
	if (iUndetermined >= 0) dimSizesRtn[iUndetermined] = len / dimSizeProd;
	return true;
}

bool DimSizes::RegulateAxis(int *pAxis) const
{
	if (*pAxis < 0) *pAxis += size();
	if (*pAxis < 0 || *pAxis >= size()) {
		Error::Issue(ErrorType::RangeError, "specified axis is out of range");
		return false;
	}
	return true;
}

String DimSizes::ToString(const StringStyle& ss, const char* sep) const
{
	if (empty()) return "scalar";
	String str;
	for (size_t dimSize : *this) {
		if (!str.empty()) str += sep;
		str.Format("%zu", dimSize);
	}
	return str;
}

}
