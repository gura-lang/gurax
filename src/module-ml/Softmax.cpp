//==============================================================================
// Softmax.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Softmax
//------------------------------------------------------------------------------
template<typename T_Elem> void Softmax_Forward_Array_T(Array& arrayFwdOut, const Array& arrayFwdIn, size_t axis)
{
	//const ArrayT<T_Elem> *pArrayT = dynamic_cast<const ArrayT<T_Elem> *>(pArray);
	const DimSizes& dimSizesFwdIn = arrayFwdIn.GetDimSizes();
	size_t lenFwdIn = dimSizesFwdIn.CalcLength();
	//size_t axis = pGear->GetAxis();
	if (axis > dimSizesFwdIn.size() - 1) axis = dimSizesFwdIn.size() - 1;
	DimSizes::const_iterator pDimAxis = dimSizesFwdIn.begin() + axis;
	//if (pArrayRtn.IsNull()) pArrayRtn.reset(ArrayT<T_Elem>::Create(dimSizesFwdIn));
	//pArrayRtn->FillZero();
	const T_Elem* pElemTop = arrayFwdIn.GetPointerC<T_Elem>();
	T_Elem* pElemRtn = arrayFwdOut.GetPointerC<T_Elem>();
	if (pDimAxis + 1 == dimSizesFwdIn.end()) {
		//size_t axisSize = pDimAxis->GetSize();
		size_t axisSize = 0;
		for (size_t offset = 0; offset < lenFwdIn; offset += axisSize) {
			const T_Elem* pElemHead = pElemTop + offset;
			T_Elem* pElemRtnHead = pElemRtn + offset;
			T_Elem numMax = 0;
			do {
				const T_Elem* pElemWk = pElemHead;
				numMax = *pElemWk;
				pElemWk++;
				for (size_t i = 1; i < axisSize; i++, pElemWk++) {
					if (numMax < *pElemWk) numMax = *pElemWk;
				}
			} while (0);
			T_Elem numSum = 0;
			do {
				const T_Elem* pElemWk = pElemHead;
				T_Elem* pElemRtnWk = pElemRtnHead;
				for (size_t i = 0; i < axisSize; i++, pElemWk++, pElemRtnWk++) {
					//T_Elem num = *pElemWk;
					T_Elem num = static_cast<T_Elem>(::exp(static_cast<Double>(*pElemWk - numMax)));
					*pElemRtnWk = num;
					numSum += num;
				}
			} while (0);
			do {
				const T_Elem* pElemWk = pElemHead;
				T_Elem* pElemRtnWk = pElemRtnHead;
				for (size_t i = 0; i < axisSize; i++, pElemWk++, pElemRtnWk++) {
					*pElemRtnWk /= numSum;
				}
			} while (0);
		}
	} else {
		//size_t strides = pDimAxis->GetStrides();
		//size_t axisSize = pDimAxis->GetSize();
		//size_t stepSize = pDimAxis->GetSize() * strides;
		size_t strides = 0;
		size_t axisSize = 0;
		size_t stepSize = 0;
		for (size_t offset = 0; offset < lenFwdIn; offset += stepSize) {
			for (size_t j = 0; j < strides; j++) {
				const T_Elem* pElemHead = pElemTop + offset + j;
				T_Elem* pElemRtnHead = pElemRtn + offset + j;
				T_Elem numMax = 0;
				do {
					const T_Elem* pElemWk = pElemHead;
					numMax = *pElemWk;
					pElemWk += strides;
					for (size_t i = 1; i < axisSize; i++, pElemWk += strides) {
						if (numMax < *pElemWk) numMax = *pElemWk;
					}
				} while (0);
				T_Elem numSum = 0;
				do {
					const T_Elem* pElemWk = pElemHead;
					T_Elem *pElemRtnWk = pElemRtnHead;
					for (size_t i = 0; i < axisSize; i++, pElemWk += strides, pElemRtnWk += strides) {
						//T_Elem num = *pElemWk;
						T_Elem num = static_cast<T_Elem>(::exp(static_cast<Double>(*pElemWk - numMax)));
						*pElemRtnWk = num;
						numSum += num;
					}
				} while (0);
				do {
					const T_Elem* pElemWk = pElemHead;
					T_Elem *pElemRtnWk = pElemRtnHead;
					for (size_t i = 0; i < axisSize; i++, pElemWk += strides, pElemRtnWk += strides) {
						*pElemRtnWk /= numSum;
					}
				} while (0);
			}
		}
	}
}

template<> void Softmax_Forward_Array_T<Half>(Array& arrayFwdOut, const Array& arrayFwdIn, size_t axis)
{
}

template<> void Softmax_Forward_Array_T<Complex>(Array& arrayFwdOut, const Array& arrayFwdIn, size_t axis) {}

template<typename T_Elem> void Softmax_Backward_Array_T(Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)
{
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdSaved = arrayFwdSaved.GetPointerC<T_Elem>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pFwdSaved++) {
		const T_Elem& bwdIn = *pBwdIn;
		const T_Elem& fwdSaved = *pFwdSaved;
		*pBwdOut = bwdIn * (1. - fwdSaved) * fwdSaved;
	}
}

template<> void Softmax_Backward_Array_T<Half>(Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)
{
}

std::function<void (Array& arrayFwdOut, const Array& arrayFwdIn, size_t axis)> Softmax_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)> Softmax_Backward_Array[Array::ElemTypeIdMax];

void Softmax::Initialize()
{
	Gurax_SetArrayFuncSingle(Softmax_Forward_Array, Softmax_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Softmax_Backward_Array, Softmax_Backward_Array_T);
}

bool Softmax::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn)
{
	if (!pArrayFwdOut) {
		pArrayFwdOut.reset(Array::Create(arrayFwdIn.GetElemType(), arrayFwdIn.GetDimSizes()));
		if (!pArrayFwdOut) return false;
		_pArrayFwdSaved.reset(pArrayFwdOut.Reference());
	}
	Softmax_Forward_Array[arrayFwdIn.GetElemType().id](*pArrayFwdOut, arrayFwdIn, _axis);
	return true;
}

bool Softmax::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn)
{
	if (!pArrayBwdOut) {
		pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
		if (!pArrayBwdOut) return false;
	}
	Softmax_Backward_Array[arrayBwdIn.GetElemType().id](*pArrayBwdOut, *_pArrayFwdSaved, arrayBwdIn);
	return true;
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
