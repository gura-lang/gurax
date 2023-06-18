//==============================================================================
// MaxPool2d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// MaxPool2d
//------------------------------------------------------------------------------
MaxPool2d::MaxPool2d(size_t nRowsKernel, size_t nColsKernel, size_t stridesRow, size_t stridesCol) :
	_nRowsKernel(nRowsKernel), _nColsKernel(nColsKernel), _stridesRow(stridesRow), _stridesCol(stridesCol)
{
}

void MaxPool2d::Initialize()
{
}

bool MaxPool2d::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn)
{
	const Array::ElemTypeT& elemType = arrayFwdIn.GetElemType();
	const DimSizes& dimSizesSrc = arrayFwdIn.GetDimSizes();
	if (dimSizesSrc.size() < 2) {
		Error::Issue(ErrorType::SizeError, "the array must have at least two dimensions");
		return false;
	}
	size_t nRowsSrc = *(dimSizesSrc.rbegin() + 1);
	size_t nColsSrc = *dimSizesSrc.rbegin();
	if (nRowsSrc < _nRowsKernel || nColsSrc < _nColsKernel) {
		Error::Issue(ErrorType::SizeError, "the array is smaller than the kernel size");
		return false;
	}
	size_t nRowsOut = (nRowsSrc - _nRowsKernel) / _stridesRow + 1;
	size_t nColsOut = (nColsSrc - _nColsKernel) / _stridesCol + 1;
	if (!pArrayFwdOut) {
		DimSizes dimSizesPool(dimSizesSrc.begin(), dimSizesSrc.begin() + dimSizesSrc.size() - 2);
		dimSizesPool.push_back(nRowsOut);
		dimSizesPool.push_back(nColsOut);
		pArrayFwdOut.reset(Array::Create(elemType, dimSizesPool));
		if (!pArrayFwdOut) return false;
		_pArrayFwdSaved.reset(pArrayFwdOut.Reference());
	}
	size_t bytesPerCol = elemType.bytes;
	size_t bytesPerRow = nColsSrc * bytesPerCol;
	size_t bytesStridesCol = _stridesCol * bytesPerCol;
	size_t bytesStridesRow = _stridesRow * bytesPerRow;
	size_t bytesPerPlane = bytesPerRow * nRowsSrc;
	auto funcPut = Array::funcs.Put[elemType.id];
	auto funcMaxPool = funcs.MaxPool[elemType.id];
	auto pElemPool = pArrayFwdOut->GetPointerC<UInt8>();
	auto pElemPlane = arrayFwdIn.GetPointerC<UInt8>();
	size_t nPlanes = DimSizes::CalcLength(dimSizesSrc.begin(), dimSizesSrc.begin() + dimSizesSrc.size() - 2);
	for (size_t iPlane = 0; iPlane < nPlanes; iPlane++, pElemPlane += bytesPerPlane) {
		auto pElemKernelRow = pElemPlane;
		for (size_t iRowOut = 0; iRowOut < nRowsOut; iRowOut++, pElemKernelRow += bytesStridesRow) {
			auto pElemKernelCol = pElemKernelRow;
			for (size_t iColOut = 0; iColOut < nColsOut; iColOut++, pElemKernelCol += bytesStridesCol, pElemPool += bytesPerCol) {
				auto pElemKernel = pElemKernelCol;
				funcPut(pElemPool, pElemKernel);
				for (size_t iRowKernel = 0; iRowKernel < _nRowsKernel; iRowKernel++, pElemKernel += bytesPerRow) {
					funcMaxPool(pElemPool, pElemKernel, _nColsKernel);
				}
			}
		}
	}
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
