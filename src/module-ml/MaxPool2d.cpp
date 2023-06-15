//==============================================================================
// MaxPool2d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// MaxPool2d
//------------------------------------------------------------------------------
MaxPool2d::MaxPool2d(size_t nRowsKernel, size_t nColsKernel, size_t strides) :
				_nRowsKernel(nRowsKernel), _nColsKernel(nColsKernel), _strides(strides)
{
}

void MaxPool2d::Initialize()
{
}

bool MaxPool2d::ValidateArrayFilter(const Array& arrayFilter)
{
	return true;
}

bool MaxPool2d::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn)
{
	//if (!pArrayFwdOut) {
	//	pArrayFwdOut.reset(Array::Create(arrayFwdIn.GetElemType(), arrayFwdIn.GetDimSizes()));
	//	if (!pArrayFwdOut) return false;
	//	_pArrayFwdSaved.reset(pArrayFwdOut.Reference());
	//}
	return true;
}

bool MaxPool2d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn)
{
	//if (!pArrayBwdOut) {
	//	pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
	//	if (!pArrayBwdOut) return false;
	//}
	return true;
}

String MaxPool2d::ToString(const StringStyle& ss) const
{
	return String().Format("ml.MaxPool2d");
}

//------------------------------------------------------------------------------
// MaxPool2dList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MaxPool2dOwner
//------------------------------------------------------------------------------
void MaxPool2dOwner::Clear()
{
	for (MaxPool2d* pMaxPool2d : *this) MaxPool2d::Delete(pMaxPool2d);
	clear();
}

Gurax_EndModuleScope(ml)
