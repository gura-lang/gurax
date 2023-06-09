//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

bool Img2dToCol(RefPtr<Array>& pArrayOut, const Array& arrayIn, size_t nRowsFilter, size_t nColsFilter, size_t strides, size_t padding)
{
	const Array::ElemTypeT& elemType = arrayIn.GetElemType();
	const DimSizes& dimSizesIn = arrayIn.GetDimSizes();
	if (dimSizesIn.size() != 4) {
		Error::Issue(ErrorType::SizeError, "the array must have four dimensions");
		return false;
	}
	size_t nSamples = dimSizesIn[0];
	size_t nChannels = dimSizesIn[1];
	size_t nRowsIn = dimSizesIn[2];
	size_t nColsIn = dimSizesIn[3];
	size_t nRowsOut = (nRowsIn + 2 * padding - nRowsFilter) / strides + 1;
	size_t nColsOut = (nColsIn + 2 * padding - nColsFilter) / strides + 1;
	size_t bytesPerRow = nColsIn * elemType.bytes;
	size_t bytesPerChannel = bytesPerRow * nRowsIn;
	size_t bytesPerSample = bytesPerChannel * nChannels;
	size_t bytesStridesCol = strides * elemType.bytes;
	size_t bytesStridesRow = strides * bytesPerRow;
	pArrayOut.reset(Array::Create2d(elemType, nSamples * nRowsOut * nColsOut, nChannels * nRowsFilter * nColsFilter));
	UInt8* pElemOut = pArrayOut->GetPointerC<UInt8>();
	size_t bytesToCopy = nColsFilter * elemType.bytes;
	const UInt8* pElemSample = arrayIn.GetPointerC<UInt8>();
	for (size_t iSample = 0; iSample < nSamples; iSample++, pElemSample += bytesPerSample) {
		const UInt8* pElemKernelRow = pElemSample;
		for (size_t iRowOut = 0; iRowOut < nRowsOut; iRowOut++, pElemKernelRow += bytesStridesRow) {
			const UInt8* pElemKernelCol = pElemKernelRow;
			for (size_t iColOut = 0; iColOut < nColsOut; iColOut++, pElemKernelCol += bytesStridesCol) {
				const UInt8* pElemChannel = pElemKernelCol;
				for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
					const UInt8* pElemIn = pElemChannel;
					for (size_t iRowFilter = 0; iRowFilter < nRowsFilter; iRowFilter++, pElemIn += bytesPerRow) {
						::memcpy(pElemOut, pElemIn, bytesToCopy);
					}
				}
			}
		}
	}
	return true;
}

Gurax_EndModuleScope(ml)
