//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

bool Img2dToCol(RefPtr<Array>& pArrayOut, const Array& arrayIn, size_t nRowsFilter, size_t nColsFilter, size_t stridesRow, size_t stridesCol, size_t paddingRow, size_t paddingCol)
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
	size_t nRowsOut = (nRowsIn + 2 * paddingRow - nRowsFilter) / stridesRow + 1;
	size_t nColsOut = (nColsIn + 2 * paddingCol - nColsFilter) / stridesCol + 1;
	size_t bytesPerCol = elemType.bytes;
	size_t bytesPerRow = nColsIn * bytesPerCol;
	size_t bytesPerChannel = bytesPerRow * nRowsIn;
	size_t bytesPerSample = bytesPerChannel * nChannels;
	size_t bytesStridesCol = stridesCol * bytesPerCol;
	size_t bytesStridesRow = stridesRow * bytesPerRow;
	pArrayOut.reset(Array::Create2d(elemType, nSamples * nRowsOut * nColsOut, nChannels * nRowsFilter * nColsFilter));
	UInt8* pElemOut = pArrayOut->GetPointerC<UInt8>();
	size_t bytesFilterCol = nColsFilter * bytesPerCol;
	const UInt8* pElemSample = arrayIn.GetPointerC<UInt8>();
	for (size_t iSample = 0; iSample < nSamples; iSample++, pElemSample += bytesPerSample) {
		const UInt8* pElemKernelRow = pElemSample;
		size_t iRowIn = 0, iRowOut = 0;
		for ( ; iRowOut < nRowsOut; iRowIn += stridesRow, iRowOut++) {
			size_t bytesSkipRowPre = 0;
			size_t bytesSkipRowPost = 0;
			size_t nRowsFilterPart = 0;
			const UInt8* pElemKernelCol = pElemKernelRow;
			if (iRowIn + nRowsFilter < paddingRow) {
				// nothing to do
			} else if (iRowIn < paddingRow) {
				size_t nRowsSkipPre = paddingRow - iRowIn;
				bytesSkipRowPre = bytesFilterCol * nRowsSkipPre;
				nRowsFilterPart = nRowsFilter - nRowsSkipPre;
			} else if (iRowIn + nRowsFilter <= paddingRow + nRowsIn) {
				pElemKernelRow += bytesStridesRow;
				nRowsFilterPart = nRowsFilter;
			} else if (iRowIn < paddingRow + nRowsIn) {
				nRowsFilterPart = paddingRow + nRowsIn - iRowIn;
				size_t nRowsSkipPost = nRowsFilter - nRowsFilterPart;
				bytesSkipRowPost = bytesFilterCol * nRowsSkipPost;
				pElemKernelRow += bytesStridesRow;
			} else {
				// nothing to do
			}
			do {
				size_t iColIn = 0, iColOut = 0;
				size_t bytesFilterColRowChannel = bytesFilterCol * nRowsFilterPart * nChannels;
				if (nColsFilter < paddingCol) {
					size_t n = paddingCol - nColsFilter;
					iColIn += stridesCol * n;
					iColOut += n;
					pElemOut += bytesFilterColRowChannel * n;
				}
				for ( ; iColOut < nColsOut && iColIn < paddingCol; iColIn += stridesCol, iColOut++) {
					size_t bytesSkipColPre = (paddingCol - iColIn) * bytesPerCol;
					size_t bytesFilterColPart = bytesFilterCol - bytesSkipColPre;
					const UInt8* pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						const UInt8* pElemIn = pElemChannel;
						pElemOut += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemIn += bytesPerRow) {
							pElemOut += bytesSkipColPre;
							::memcpy(pElemOut, pElemIn, bytesFilterColPart);
							pElemOut += bytesFilterColPart;
						}
						pElemOut += bytesSkipRowPost;
					}
				}
				for ( ; iColOut < nColsOut && iColIn + nColsFilter <= paddingCol + nColsIn; iColIn += stridesCol, iColOut++) {
					const UInt8* pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						const UInt8* pElemIn = pElemChannel;
						pElemOut += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemIn += bytesPerRow) {
							::memcpy(pElemOut, pElemIn, bytesFilterCol);
							pElemOut += bytesFilterCol;
						}
						pElemOut += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStridesCol;
				}
				for ( ; iColOut < nColsOut && iColIn < paddingCol + nColsIn; iColIn += stridesCol, iColOut++) {
					size_t bytesFilterColPart = (paddingCol + nColsIn - iColIn) * bytesPerCol;
					size_t bytesSkipColPost = bytesFilterCol - bytesFilterColPart;
					const UInt8* pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						const UInt8* pElemIn = pElemChannel;
						pElemOut += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemIn += bytesPerRow) {
							::memcpy(pElemOut, pElemIn, bytesFilterColPart);
							pElemOut += bytesFilterColPart;
							pElemOut += bytesSkipColPost;
						}
						pElemOut += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStridesCol;
				}
				if (iColOut < nColsOut) {
					size_t n = nColsOut - iColOut;
					pElemOut += bytesFilterColRowChannel * n;
				}
			} while (0);
		}

	}
	return true;
}

Gurax_EndModuleScope(ml)
