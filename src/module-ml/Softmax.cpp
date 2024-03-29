//==============================================================================
// Softmax.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Softmax
//------------------------------------------------------------------------------
template<typename T_Elem> void Softmax_Forward_Array_T(Array& arrayFwdOut, const Array& arrayFwdIn, int axis)
{
	const DimSizes& dimSizesFwdIn = arrayFwdIn.GetDimSizes();
	size_t lenFwdIn = dimSizesFwdIn.CalcLength();
	DimSizes::const_iterator pDimSizeAxis = dimSizesFwdIn.begin() + axis;
	const T_Elem* pFwdInTop = arrayFwdIn.GetPointerC<T_Elem>();
	T_Elem* pFwdOutTop = arrayFwdOut.GetPointerC<T_Elem>();
	size_t axisSize = dimSizesFwdIn.CalcLength(pDimSizeAxis);
	if (pDimSizeAxis + 1 == dimSizesFwdIn.end()) {
		for (size_t offset = 0; offset < lenFwdIn; offset += axisSize) {
			const T_Elem* pFwdInHead = pFwdInTop + offset;
			T_Elem* pFwdOutHead = pFwdOutTop + offset;
			T_Elem fwdInMax = 0;
			do {
				const T_Elem* pFwdIn = pFwdInHead;
				fwdInMax = *pFwdIn;
				pFwdIn++;
				for (size_t i = 1; i < axisSize; i++, pFwdIn++) {
					if (fwdInMax < *pFwdIn) fwdInMax = *pFwdIn;
				}
			} while (0);
			T_Elem fwdInSum = 0;
			do {
				const T_Elem* pFwdIn = pFwdInHead;
				T_Elem* pFwdOut = pFwdOutHead;
				for (size_t i = 0; i < axisSize; i++, pFwdIn++, pFwdOut++) {
					T_Elem fwdInExp = std::exp(*pFwdIn - fwdInMax);
					*pFwdOut = fwdInExp;
					fwdInSum += fwdInExp;
				}
			} while (0);
			do {
				T_Elem* pFwdOut = pFwdOutHead;
				for (size_t i = 0; i < axisSize; i++, pFwdOut++) {
					*pFwdOut /= fwdInSum;
				}
			} while (0);
		}
	} else {
		//::printf("check\n");
#if 0
		size_t stride = dimSizesFwdIn.CalcStride(pDimSizeAxis);
		size_t axisSize = dimSizesFwdIn.CalcLength(pDimSizeAxis);
		::printf("lenFwdIn:%zu stride:%zu axisSize:%zu\n", lenFwdIn, stride, axisSize);
		for (size_t offset = 0; offset < lenFwdIn; offset += axisSize) {
			for (size_t j = 0; j < stride; j++) {
				const T_Elem* pFwdInHead = pFwdInTop + offset + j;
				T_Elem* pFwdOutHead = pFwdOutTop + offset + j;
				T_Elem fwdInMax = 0;
				do {
					const T_Elem* pFwdIn = pFwdInHead;
					fwdInMax = *pFwdIn;
					pFwdIn += stride;
					for (size_t i = 1; i < axisSize; i++, pFwdIn += stride) {
						if (fwdInMax < *pFwdIn) fwdInMax = *pFwdIn;
					}
				} while (0);
				T_Elem fwdInSum = 0;
				do {
					const T_Elem* pFwdIn = pFwdInHead;
					T_Elem *pFwdOut = pFwdOutHead;
					for (size_t i = 0; i < axisSize; i++, pFwdIn += stride, pFwdOut += stride) {
						T_Elem fwdInExp = std::exp(*pFwdIn - fwdInMax);
						*pFwdOut = fwdInExp;
						fwdInSum += fwdInExp;
					}
				} while (0);
				do {
					const T_Elem* pFwdIn = pFwdInHead;
					T_Elem *pFwdOut = pFwdOutHead;
					for (size_t i = 0; i < axisSize; i++, pFwdIn += stride, pFwdOut += stride) {
						*pFwdOut /= fwdInSum;
					}
				} while (0);
			}
		}
#endif
	}
}

template<> void Softmax_Forward_Array_T<Half>(Array& arrayFwdOut, const Array& arrayFwdIn, int axis)
{
}

template<> void Softmax_Forward_Array_T<Complex>(Array& arrayFwdOut, const Array& arrayFwdIn, int axis) {}

template<typename T_Elem> void Softmax_Backward_Array_T(Array& arrayBwdOut, const Array& arrayFwdOutSaved, const Array& arrayBwdIn)
{
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdOutSaved = arrayFwdOutSaved.GetPointerC<T_Elem>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pFwdOutSaved++) {
		const T_Elem& bwdIn = *pBwdIn;
		*pBwdOut = bwdIn;
	}
}

template<> void Softmax_Backward_Array_T<Half>(Array& arrayBwdOut, const Array& arrayFwdOutSaved, const Array& arrayBwdIn)
{
}

std::function<void (Array& arrayFwdOut, const Array& arrayFwdIn, int axis)> Softmax_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayBwdOut, const Array& arrayFwdOutSaved, const Array& arrayBwdIn)> Softmax_Backward_Array[Array::ElemTypeIdMax];

void Softmax::Bootup()
{
	Gurax_SetArrayFuncSingle(Softmax_Forward_Array, Softmax_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Softmax_Backward_Array, Softmax_Backward_Array_T);
}

bool Softmax::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, const Controller& controller)
{
	if (!pArrayFwdOut) {
		pArrayFwdOut.reset(Array::Create(arrayFwdIn.GetElemType(), arrayFwdIn.GetDimSizes()));
		if (!pArrayFwdOut) return false;
		_pArrayFwdOutSaved.reset(pArrayFwdOut.Reference());
	}
	int axis = _axis;
	if (axis < 0) axis += arrayFwdIn.GetDimSizes().size();
	if (axis < 0 || axis >= arrayFwdIn.GetDimSizes().size()) {
		Error::Issue(ErrorType::RangeError, "axis is out of range");
		return false;
	}
	Softmax_Forward_Array[arrayFwdIn.GetElemType().id](*pArrayFwdOut, arrayFwdIn, axis);
	return true;
}

bool Softmax::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag)
{
	if (!bwdPropagationFlag) return true;
	if (!pArrayBwdOut) {
		pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
		if (!pArrayBwdOut) return false;
	}
	Softmax_Backward_Array[arrayBwdIn.GetElemType().id](*pArrayBwdOut, *_pArrayFwdOutSaved, arrayBwdIn);
	return true;
}

bool Softmax::Serialize(Stream& stream) const
{
	if (!stream.SerializeNumber<int>(_axis)) return false;
	return true;
}

Softmax* Softmax::Deserialize(Stream& stream)
{
	int axis;
	if (!stream.DeserializeNumber<int>(axis)) return false;
	return new Softmax(axis);
}

String Softmax::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Softmax");
}

//------------------------------------------------------------------------------
// SoftmaxList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SoftmaxOwner
//------------------------------------------------------------------------------
void SoftmaxOwner::Clear()
{
	for (Softmax* pSoftmax : *this) Softmax::Delete(pSoftmax);
	clear();
}

Gurax_EndModuleScope(ml)
