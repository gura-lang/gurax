//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

void ImageToColumn(RefPtr<Array> pArrayOut, const Array& arrayIn, size_t nRowsFilter, size_t nColsFilter, size_t strides, size_t padding)
{
	const DimSizes& dimSizesIn = arrayIn.GetDimSizes();
	size_t nSamples = dimSizesIn[0];
	size_t nChannels = dimSizesIn[1];
	size_t nRowsIn = dimSizesIn[2];
	size_t nColsIn = dimSizesIn[3];
	size_t nRowsOut = (nRowsIn + 2 * padding - nRowsFilter) / strides + 1;
	size_t nColsOut = (nColsIn + 2 * padding - nColsFilter) / strides + 1;
	size_t bytesStridesRowIn = nColsIn * arrayIn.GetElemType().bytes;
	size_t bytesStridesChannel = bytesStridesRowIn * nRowsIn;
	size_t bytesStridesSample = bytesStridesChannel * nChannels;
	pArrayOut.reset(Array::Create2d(arrayIn.GetElemType(), nSamples * nRowsOut * nColsOut, nChannels * nRowsFilter * nColsFilter));
	UInt8* pElemOut = pArrayOut->GetPointerC<UInt8>();
	size_t bytesToCopy = nColsFilter * arrayIn.GetElemType().bytes;
	const UInt8* pElemSample = arrayIn.GetPointerC<UInt8>();
	for (size_t iSample = 0; iSample < nSamples; iSample++, pElemSample += bytesStridesSample) {
		const UInt8* pElemChannel = pElemSample;
		
		for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesStridesChannel) {
			const UInt8* pElemIn = pElemChannel;
			for (size_t iRowFilter = 0; iRowFilter < nRowsFilter; iRowFilter++, pElemIn += bytesStridesRowIn) {
				::memcpy(pElemOut, pElemIn, bytesToCopy);
				pElemOut += bytesToCopy;
			}
		}
	}
}

Gurax_EndModuleScope(ml)
