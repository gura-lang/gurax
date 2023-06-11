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
	size_t bytesPerRow = nColsIn * elemType.bytes;
	size_t bytesPerChannel = bytesPerRow * nRowsIn;
	size_t bytesPerSample = bytesPerChannel * nChannels;
	size_t bytesStridesCol = stridesCol * elemType.bytes;
	size_t bytesStridesRow = stridesRow * bytesPerRow;
	pArrayOut.reset(Array::Create2d(elemType, nSamples * nRowsOut * nColsOut, nChannels * nRowsFilter * nColsFilter));
	UInt8* pElemOut = pArrayOut->GetPointerC<UInt8>();
	size_t bytesFilterCol = nColsFilter * elemType.bytes;
	size_t bytesFilterColRowChannel = bytesFilterCol * nRowsFilter * nChannels;
	const UInt8* pElemSample = arrayIn.GetPointerC<UInt8>();
	for (size_t iSample = 0; iSample < nSamples; iSample++, pElemSample += bytesPerSample) {
		const UInt8* pElemKernelRow = pElemSample;
		for (size_t iRowIn = 0, iRowOut = 0; iRowOut < nRowsOut; iRowIn += stridesRow, iRowOut++, pElemKernelRow += bytesStridesRow) {
			if (iRowIn < paddingRow) {
				
			} else if (iRowIn < paddingRow + nRowsIn) {
				size_t iColIn = 0, iColOut = 0;
				const UInt8* pElemKernelCol = pElemKernelRow;
				if (nColsFilter <= paddingCol) {
					size_t n = paddingCol - nColsFilter;
					iColIn += stridesCol * n;
					iColOut += n;
					pElemOut += bytesFilterColRowChannel * n;
				}
				for ( ; iColOut < nColsOut && iColIn < paddingCol; iColIn += stridesCol, iColOut++) {
					size_t bytesToSkip = (paddingCol - iColIn) * elemType.bytes;
					size_t bytesFilterColPart = bytesFilterCol - bytesToSkip;
					const UInt8* pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						const UInt8* pElemIn = pElemChannel;
						for (size_t iRowFilter = 0; iRowFilter < nRowsFilter; iRowFilter++, pElemIn += bytesPerRow) {
							pElemOut += bytesToSkip;
							::memcpy(pElemOut, pElemIn, bytesFilterColPart);
							pElemOut += bytesFilterColPart;
						}
					}
				}
				for ( ; iColOut < nColsOut && iColIn + nColsFilter <= paddingCol + nColsIn; iColIn += stridesCol, iColOut++) {
					const UInt8* pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						const UInt8* pElemIn = pElemChannel;
						for (size_t iRowFilter = 0; iRowFilter < nRowsFilter; iRowFilter++, pElemIn += bytesPerRow) {
							::memcpy(pElemOut, pElemIn, bytesFilterCol);
							pElemOut += bytesFilterCol;
						}
					}
					pElemKernelCol += bytesStridesCol;
				}
				for ( ; iColOut < nColsOut && iColIn < paddingCol + nColsIn; iColIn += stridesCol, iColOut++) {
					size_t bytesFilterColPart = (paddingCol + nColsIn - iColIn) * elemType.bytes;
					size_t bytesToSkip = bytesFilterCol - bytesFilterColPart;
					const UInt8* pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						const UInt8* pElemIn = pElemChannel;
						for (size_t iRowFilter = 0; iRowFilter < nRowsFilter; iRowFilter++, pElemIn += bytesPerRow) {
							::memcpy(pElemOut, pElemIn, bytesFilterColPart);
							pElemOut += bytesFilterColPart;
							pElemOut += bytesToSkip;
						}
					}
					pElemKernelCol += bytesStridesCol;
				}
				if (iColOut < nColsOut) {
					size_t n = nColsOut - iColOut;
					pElemOut += bytesFilterColRowChannel * n;
				}
			} else {

			}
		}

	}
	return true;
}

Gurax_EndModuleScope(ml)
