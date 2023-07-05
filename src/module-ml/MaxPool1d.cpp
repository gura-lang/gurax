//==============================================================================
// MaxPool1d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// MaxPool1d
//------------------------------------------------------------------------------
MaxPool1d::MaxPool1d(size_t nRowsKernel, size_t nColsKernel, size_t strideRow, size_t strideCol) : Gear(false),
	_nRowsKernel(nRowsKernel), _nColsKernel(nColsKernel), _strideRow(strideRow), _strideCol(strideCol)
{
}

void MaxPool1d::Initialize()
{
}

bool MaxPool1d::CalcSizeOut(size_t nRowsIn, size_t nColsIn, size_t* pnRowsOut, size_t* pnColsOut) const
{
	*pnRowsOut = (nRowsIn - _nRowsKernel) / _strideRow + 1;
	*pnColsOut = (nColsIn - _nColsKernel) / _strideCol + 1;
	return true;
}

bool MaxPool1d::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn)
{
	// arrayFwdIn  .. (*, nRowsFwdIn, nColsFwdIn)
	// arrayFwdOut .. (*, nRowsFwdOut, nColsFwdOut)
	const Array::ElemTypeT& elemType = arrayFwdIn.GetElemType();
	const DimSizes& dimSizesFwdIn = arrayFwdIn.GetDimSizes();
	if (dimSizesFwdIn.size() < 2) {
		Error::Issue(ErrorType::SizeError, "the array must have at least two dimensions");
		return false;
	}
	size_t nRowsFwdIn = dimSizesFwdIn.GetRowSize();
	size_t nColsFwdIn = dimSizesFwdIn.GetColSize();
	if (nRowsFwdIn < _nRowsKernel || nColsFwdIn < _nColsKernel) {
		Error::Issue(ErrorType::SizeError, "the array is smaller than the kernel size");
		return false;
	}
	size_t nRowsFwdOut = (nRowsFwdIn - _nRowsKernel) / _strideRow + 1;
	size_t nColsFwdOut = (nColsFwdIn - _nColsKernel) / _strideCol + 1;
	_pArrayFwdInSaved.reset(arrayFwdIn.Reference());
	if (!pArrayFwdOut) {
		DimSizes dimSizesFwdOut(dimSizesFwdIn.begin(), dimSizesFwdIn.begin() + dimSizesFwdIn.size() - 2);
		dimSizesFwdOut.push_back(nRowsFwdOut);
		dimSizesFwdOut.push_back(nColsFwdOut);
		pArrayFwdOut.reset(Array::Create(elemType, dimSizesFwdOut));
		_pArrayScanPosInSel.reset(Array::Create(Array::ElemType::UInt32, dimSizesFwdOut));
		if (!pArrayFwdOut) return false;
		_pArrayFwdOutSaved.reset(pArrayFwdOut.Reference());
	}
	size_t bytesPerCol = elemType.bytes;
	size_t bytesPerRow = nColsFwdIn * bytesPerCol;
	size_t bytesStrideCol = _strideCol * bytesPerCol;
	size_t bytesStrideRow = _strideRow * bytesPerRow;
	size_t scanPosStrideCol = _strideCol;
	size_t scanPosStrideRow = _strideRow * nColsFwdIn;
	size_t bytesPerUnit = bytesPerRow * nRowsFwdIn;
	auto funcPut = Array::funcs.Put[elemType.id];
	auto funcMaxPool = funcs.MaxPool[elemType.id];
	auto pElemPool = pArrayFwdOut->GetPointerC<UInt8>();
	auto pElemUnit = arrayFwdIn.GetPointerC<UInt8>();
	auto pScanPosInSel = _pArrayScanPosInSel->GetPointerC<UInt32>();
	size_t nUnits = DimSizes::CalcLength(dimSizesFwdIn.begin(), dimSizesFwdIn.begin() + dimSizesFwdIn.size() - 2);
	for (size_t iUnit = 0; iUnit < nUnits; iUnit++, pElemUnit += bytesPerUnit) {
		auto pElemKernelRow = pElemUnit;
		UInt32 scanPosInRow = 0;
		for (size_t iRowOut = 0; iRowOut < nRowsFwdOut; scanPosInRow += scanPosStrideRow, iRowOut++, pElemKernelRow += bytesStrideRow) {
			auto pElemKernelCol = pElemKernelRow;
			UInt32 scanPosInCol = scanPosInRow;
			for (size_t iColOut = 0; iColOut < nColsFwdOut;
					scanPosInCol += scanPosStrideCol, iColOut++, pElemKernelCol += bytesStrideCol, pElemPool += bytesPerCol, pScanPosInSel++) {
				auto pElemKernel = pElemKernelCol;
				UInt32 scanPosIn = scanPosInCol;
				*pScanPosInSel = scanPosInCol;
				funcPut(pElemPool, pElemKernel);
				for (size_t iRowKernel = 0; iRowKernel < _nRowsKernel; scanPosIn += nColsFwdIn, iRowKernel++, pElemKernel += bytesPerRow) {
					funcMaxPool(pElemPool, pElemKernel, _nColsKernel, scanPosIn, pScanPosInSel);
				}
			}
		}
	}
	return true;
}

bool MaxPool1d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, bool bwdPropagationFlag, const Array& arrayBwdIn)
{
	// arrayBwdIn  .. (*, nRowsFwdOut, nColsFwdOut)
	// arrayBwdOut .. (*, nRowsFwdIn, nColsFwdIn)
	if (!bwdPropagationFlag) return true;
	const Array::ElemTypeT& elemType = _pArrayFwdInSaved->GetElemType();
	const DimSizes& dimSizesFwdIn = _pArrayFwdInSaved->GetDimSizes();
	const DimSizes& dimSizesBwdIn = arrayBwdIn.GetDimSizes();
	if (dimSizesFwdIn.size() < 2) {
		Error::Issue(ErrorType::SizeError, "the array must have at least two dimensions");
		return false;
	}
	size_t nRowsFwdIn = dimSizesFwdIn.GetRowSize();
	size_t nColsFwdIn = dimSizesFwdIn.GetColSize();
	size_t nRowsBwdIn = dimSizesBwdIn.GetRowSize();
	size_t nColsBwdIn = dimSizesBwdIn.GetColSize();
	size_t nRowsColsBwdIn = nRowsBwdIn * nColsBwdIn;
	if (pArrayBwdOut) {
		pArrayBwdOut->FillZero();
	} else {
		pArrayBwdOut.reset(_pArrayFwdInSaved->CreateLike());
	}
	size_t bytesPerCol = elemType.bytes;
	size_t bytesPerRow = nColsFwdIn * bytesPerCol;
	size_t bytesStrideCol = _strideCol * bytesPerCol;
	size_t bytesStrideRow = _strideRow * bytesPerRow;
	size_t bytesPerUnit = bytesPerRow * nRowsFwdIn;
	auto funcPut = Array::funcs.Put[elemType.id];
	auto funcPoolBackward = funcs.PoolBackward[elemType.id];
	auto pElemBwdIn = arrayBwdIn.GetPointerC<UInt8>();
	auto pElemBwdOut = pArrayBwdOut->GetPointerC<UInt8>();
	auto pScanPosInSel = _pArrayScanPosInSel->GetPointerC<UInt32>();
	size_t nUnits = DimSizes::CalcLength(dimSizesFwdIn.begin(), dimSizesFwdIn.begin() + dimSizesFwdIn.size() - 2);
	for (size_t iUnit = 0; iUnit < nUnits; iUnit++, pElemBwdOut += bytesPerUnit) {
		for (size_t i = 0; i < nRowsColsBwdIn; i++, pElemBwdIn += bytesPerCol, pScanPosInSel++) {
			funcPoolBackward(pElemBwdOut, *pScanPosInSel, pElemBwdIn);
		}
	}
	return true;
}

String MaxPool1d::ToString(const StringStyle& ss) const
{
	return String().Format("ml.MaxPool1d");
}

bool MaxPool1d::Serialize(Stream& stream) const
{
	return false;
}

MaxPool1d* MaxPool1d::Deserialize(Stream& stream)
{
	return nullptr;
}

//------------------------------------------------------------------------------
// MaxPool1dList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MaxPool1dOwner
//------------------------------------------------------------------------------
void MaxPool1dOwner::Clear()
{
	for (MaxPool1d* pMaxPool1d : *this) MaxPool1d::Delete(pMaxPool1d);
	clear();
}

Gurax_EndModuleScope(ml)
