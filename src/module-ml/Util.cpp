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
	size_t stridesRow = strides, stridesCol = strides;
	size_t paddingRow = padding, paddingCol = padding;
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
	const UInt8* pElemSample = arrayIn.GetPointerC<UInt8>();
	for (size_t iSample = 0; iSample < nSamples; iSample++, pElemSample += bytesPerSample) {
		const UInt8* pElemKernelRow = pElemSample;
		for (size_t iRowIn = 0, iRowOut = 0; iRowOut < nRowsOut; iRowIn += stridesRow, iRowOut++, pElemKernelRow += bytesStridesRow) {
			if (iRowIn < paddingRow) {
				
			} else if (iRowIn < paddingRow + nRowsIn) {
				const UInt8* pElemKernelCol = pElemKernelRow;
				for (size_t iColIn = 0, iColOut = 0; iColOut < nColsOut; iColIn += stridesCol, iColOut++) {
					size_t iColInFilterRight = iColIn + nColsFilter;
					if (iColInFilterRight <= paddingCol) {
						pElemOut += bytesFilterCol * nRowsFilter * nChannels;
					} else if (iColIn < paddingCol) {
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
					} else if (iColInFilterRight <= paddingCol + nColsIn) {
						const UInt8* pElemChannel = pElemKernelCol;
						for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
							const UInt8* pElemIn = pElemChannel;
							for (size_t iRowFilter = 0; iRowFilter < nRowsFilter; iRowFilter++, pElemIn += bytesPerRow) {
								::memcpy(pElemOut, pElemIn, bytesFilterCol);
								pElemOut += bytesFilterCol;
							}
						}
						pElemKernelCol += bytesStridesCol;
					} else if (iColIn < paddingCol + nColsIn) {
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
					} else {
						pElemOut += bytesFilterCol * nRowsFilter * nChannels;
					}
				}
			} else {

			}
		}

	}
	return true;
}

Gurax_EndModuleScope(ml)
