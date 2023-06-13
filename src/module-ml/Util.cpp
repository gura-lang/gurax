//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

void PrintCol(const void* pv, size_t bytes)
{
	const Float* p = reinterpret_cast<const Float*>(pv);
	for (size_t i = 0; i < bytes / sizeof(Float); i++, p++) {
		::printf("  %g", *p);
	}
	::printf("\n");
}

bool Img2dToCol(RefPtr<Array>& pArrayExp, const Array& arrayImg, size_t nRowsFilter, size_t nColsFilter,
				size_t stridesRow, size_t stridesCol, size_t paddingRow, size_t paddingCol)
{
	const Array::ElemTypeT& elemType = arrayImg.GetElemType();
	const DimSizes& dimSizesImg = arrayImg.GetDimSizes();
	if (dimSizesImg.size() != 4) {
		Error::Issue(ErrorType::SizeError, "the array must have four dimensions");
		return false;
	}
	size_t nSamples = dimSizesImg[0];
	size_t nChannels = dimSizesImg[1];
	size_t nRowsImg = dimSizesImg[2];
	size_t nColsImg = dimSizesImg[3];
	size_t nRowsExp = (nRowsImg + 2 * paddingRow - nRowsFilter) / stridesRow + 1;
	size_t nColsExp = (nColsImg + 2 * paddingCol - nColsFilter) / stridesCol + 1;
	size_t bytesPerCol = elemType.bytes;
	size_t bytesPerRow = nColsImg * bytesPerCol;
	size_t bytesPerChannel = bytesPerRow * nRowsImg;
	size_t bytesPerSample = bytesPerChannel * nChannels;
	size_t bytesStridesCol = stridesCol * bytesPerCol;
	size_t bytesStridesRow = stridesRow * bytesPerRow;
	pArrayExp.reset(Array::Create2d(elemType, nSamples * nRowsExp * nColsExp, nChannels * nRowsFilter * nColsFilter));
	auto pElemExp = pArrayExp->GetPointerC<UInt8>();
	size_t bytesFilterCol = nColsFilter * bytesPerCol;
	auto pElemSample = arrayImg.GetPointerC<UInt8>();
	for (size_t iSample = 0; iSample < nSamples; iSample++, pElemSample += bytesPerSample) {
		auto pElemKernelRow = pElemSample;
		size_t iRowImg = 0, iRowExp = 0;
		for ( ; iRowExp < nRowsExp; iRowImg += stridesRow, iRowExp++) {
			size_t bytesSkipRowPre = 0;
			size_t bytesSkipRowPost = 0;
			size_t nRowsFilterPart = 0;
			auto pElemKernelColBase = pElemKernelRow;
			if (iRowImg + nRowsFilter < paddingRow) {
				// nothing to do
			} else if (iRowImg < paddingRow) {
				size_t nRowsSkipPre = paddingRow - iRowImg;
				bytesSkipRowPre = bytesFilterCol * nRowsSkipPre;
				nRowsFilterPart = nRowsFilter - nRowsSkipPre;
				if (iRowImg + stridesRow >= paddingRow) {
					pElemKernelRow = pElemSample + (iRowImg + stridesRow - paddingRow) * bytesPerRow;
				}
			} else if (iRowImg + nRowsFilter <= paddingRow + nRowsImg) {
				nRowsFilterPart = nRowsFilter;
				pElemKernelRow += bytesStridesRow;
			} else if (iRowImg < paddingRow + nRowsImg) {
				nRowsFilterPart = paddingRow + nRowsImg - iRowImg;
				size_t nRowsSkipPost = nRowsFilter - nRowsFilterPart;
				bytesSkipRowPost = bytesFilterCol * nRowsSkipPost;
				pElemKernelRow += bytesStridesRow;
			} else {
				// nothing to do
			}
			do {
				size_t iColImg = 0, iColExp = 0;
				size_t bytesFilterColRowChannel = bytesFilterCol * nRowsFilterPart * nChannels;
				auto pElemKernelCol = pElemKernelColBase;
				if (nColsFilter < paddingCol) {
					size_t n = paddingCol - nColsFilter;
					iColImg += stridesCol * n;
					iColExp += n;
					pElemExp += bytesFilterColRowChannel * n;
				}
				for ( ; iColExp < nColsExp && iColImg < paddingCol; iColImg += stridesCol, iColExp++) {
					size_t nColsSkipPre = paddingCol - iColImg;
					size_t nColsFilterPart = nColsFilter - nColsSkipPre;
					size_t bytesSkipColPre = nColsSkipPre * bytesPerCol;
					size_t bytesFilterColPart = nColsFilterPart * bytesPerCol;
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemImg += bytesPerRow) {
							pElemExp += bytesSkipColPre;
							::memcpy(pElemExp, pElemImg, bytesFilterColPart);
							pElemExp += bytesFilterColPart;
						}
						pElemExp += bytesSkipRowPost;
					}
				}
				pElemKernelCol = pElemKernelColBase + (iColImg - paddingCol) * bytesPerCol;
				for ( ; iColExp < nColsExp && iColImg + nColsFilter <= paddingCol + nColsImg; iColImg += stridesCol, iColExp++) {
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemImg += bytesPerRow) {
							::memcpy(pElemExp, pElemImg, bytesFilterCol);
							pElemExp += bytesFilterCol;
						}
						pElemExp += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStridesCol;
				}
				for ( ; iColExp < nColsExp && iColImg < paddingCol + nColsImg; iColImg += stridesCol, iColExp++) {
					size_t nColsFilterPart = paddingCol + nColsImg - iColImg;
					size_t bytesFilterColPart = nColsFilterPart * bytesPerCol;
					size_t bytesSkipColPost = bytesFilterCol - bytesFilterColPart;
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemImg += bytesPerRow) {
							::memcpy(pElemExp, pElemImg, bytesFilterColPart);
							pElemExp += bytesFilterColPart;
							pElemExp += bytesSkipColPost;
						}
						pElemExp += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStridesCol;
				}
				if (iColExp < nColsExp) {
					size_t n = nColsExp - iColExp;
					pElemExp += bytesFilterColRowChannel * n;
				}
			} while (0);
		}
	}
	return true;
}

bool ColToImg2d(RefPtr<Array>& pArrayImg, const DimSizes& dimSizesImg, const Array& arrayExp, size_t nRowsFilter, size_t nColsFilter,
				size_t stridesRow, size_t stridesCol, size_t paddingRow, size_t paddingCol)
{
	const Array::ElemTypeT& elemType = arrayExp.GetElemType();
	const DimSizes& dimSizesExp = arrayExp.GetDimSizes();
	if (dimSizesImg.size() != 4) {
		Error::Issue(ErrorType::SizeError, "the array must have four dimensions");
		return false;
	}
	size_t nSamples = dimSizesImg[0];
	size_t nChannels = dimSizesImg[1];
	size_t nRowsImg = dimSizesImg[2];
	size_t nColsImg = dimSizesImg[3];
	size_t nRowsExp = (nRowsImg + 2 * paddingRow - nRowsFilter) / stridesRow + 1;
	size_t nColsExp = (nColsImg + 2 * paddingCol - nColsFilter) / stridesCol + 1;
	if (!(dimSizesExp.size() == 2 && dimSizesExp[0] == nSamples * nRowsExp * nColsExp && dimSizesExp[1] == nChannels * nRowsFilter * nColsFilter)) {
		Error::Issue(ErrorType::SizeError, "invalid size of Array");
		return false;
	}
	auto funcAdd = Array::funcs.Add_ArrayArray[elemType.id][elemType.id];
	size_t bytesPerCol = elemType.bytes;
	size_t bytesPerRow = nColsImg * bytesPerCol;
	size_t bytesPerChannel = bytesPerRow * nRowsImg;
	size_t bytesPerSample = bytesPerChannel * nChannels;
	size_t bytesStridesCol = stridesCol * bytesPerCol;
	size_t bytesStridesRow = stridesRow * bytesPerRow;
	pArrayImg.reset(Array::Create(elemType, dimSizesImg));
	auto pElemExp = arrayExp.GetPointerC<UInt8>();
	size_t bytesFilterCol = nColsFilter * bytesPerCol;
	auto pElemSample = pArrayImg->GetPointerC<UInt8>();
	for (size_t iSample = 0; iSample < nSamples; iSample++, pElemSample += bytesPerSample) {
		auto pElemKernelRow = pElemSample;
		size_t iRowImg = 0, iRowExp = 0;
		for ( ; iRowExp < nRowsExp; iRowImg += stridesRow, iRowExp++) {
			size_t bytesSkipRowPre = 0;
			size_t bytesSkipRowPost = 0;
			size_t nRowsFilterPart = 0;
			auto pElemKernelColBase = pElemKernelRow;
			if (iRowImg + nRowsFilter < paddingRow) {
				// nothing to do
			} else if (iRowImg < paddingRow) {
				size_t nRowsSkipPre = paddingRow - iRowImg;
				bytesSkipRowPre = bytesFilterCol * nRowsSkipPre;
				nRowsFilterPart = nRowsFilter - nRowsSkipPre;
				if (iRowImg + stridesRow >= paddingRow) {
					pElemKernelRow = pElemSample + (iRowImg + stridesRow - paddingRow) * bytesPerRow;
				}
			} else if (iRowImg + nRowsFilter <= paddingRow + nRowsImg) {
				nRowsFilterPart = nRowsFilter;
				pElemKernelRow += bytesStridesRow;
			} else if (iRowImg < paddingRow + nRowsImg) {
				nRowsFilterPart = paddingRow + nRowsImg - iRowImg;
				size_t nRowsSkipPost = nRowsFilter - nRowsFilterPart;
				bytesSkipRowPost = bytesFilterCol * nRowsSkipPost;
				pElemKernelRow += bytesStridesRow;
			} else {
				// nothing to do
			}
			do {
				size_t iColImg = 0, iColExp = 0;
				size_t bytesFilterColRowChannel = bytesFilterCol * nRowsFilterPart * nChannels;
				auto pElemKernelCol = pElemKernelColBase;
				if (nColsFilter < paddingCol) {
					size_t n = paddingCol - nColsFilter;
					iColImg += stridesCol * n;
					iColExp += n;
					pElemExp += bytesFilterColRowChannel * n;
				}
				for ( ; iColExp < nColsExp && iColImg < paddingCol; iColImg += stridesCol, iColExp++) {
					size_t nColsSkipPre = paddingCol - iColImg;
					size_t nColsFilterPart = nColsFilter - nColsSkipPre;
					size_t bytesSkipColPre = nColsSkipPre * bytesPerCol;
					size_t bytesFilterColPart = nColsFilterPart * bytesPerCol;
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemImg += bytesPerRow) {
							pElemExp += bytesSkipColPre;
							//::memcpy(pElemExp, pElemImg, bytesFilterColPart);
							funcAdd(pElemImg, pElemImg, pElemExp, nColsFilterPart);
							pElemExp += bytesFilterColPart;
						}
						pElemExp += bytesSkipRowPost;
					}
				}
				pElemKernelCol = pElemKernelColBase + (iColImg - paddingCol) * bytesPerCol;
				for ( ; iColExp < nColsExp && iColImg + nColsFilter <= paddingCol + nColsImg; iColImg += stridesCol, iColExp++) {
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemImg += bytesPerRow) {
							//::memcpy(pElemExp, pElemImg, bytesFilterCol);
							funcAdd(pElemImg, pElemImg, pElemExp, nColsFilter);
							pElemExp += bytesFilterCol;
						}
						pElemExp += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStridesCol;
				}
				for ( ; iColExp < nColsExp && iColImg < paddingCol + nColsImg; iColImg += stridesCol, iColExp++) {
					size_t nColsFilterPart = paddingCol + nColsImg - iColImg;
					size_t bytesFilterColPart = nColsFilterPart * bytesPerCol;
					size_t bytesSkipColPost = bytesFilterCol - bytesFilterColPart;
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemImg += bytesPerRow) {
							//::memcpy(pElemExp, pElemImg, bytesFilterColPart);
							funcAdd(pElemImg, pElemImg, pElemExp, nColsFilterPart);
							pElemExp += bytesFilterColPart;
							pElemExp += bytesSkipColPost;
						}
						pElemExp += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStridesCol;
				}
				if (iColExp < nColsExp) {
					size_t n = nColsExp - iColExp;
					pElemExp += bytesFilterColRowChannel * n;
				}
			} while (0);
		}
	}
	return true;
}

#if 0
bool ColToImg2d(RefPtr<Array>& pArrayImg, const DimSizes& dimSizesImg, const Array& arrayExp, size_t nRowsFilter, size_t nColsFilter, size_t stridesRow, size_t stridesCol, size_t paddingRow, size_t paddingCol)
{
	const Array::ElemTypeT& elemType = arrayExp.GetElemType();
	if (dimSizesImg.size() != 4) {
		Error::Issue(ErrorType::SizeError, "the array must have four dimensions");
		return false;
	}
	size_t nSamples = dimSizesImg[0];
	size_t nChannels = dimSizesImg[1];
	size_t nRowsImg = dimSizesImg[2];
	size_t nColsImg = dimSizesImg[3];
	size_t nRowsExp = (nRowsImg + 2 * paddingRow - nRowsFilter) / stridesRow + 1;
	size_t nColsExp = (nColsImg + 2 * paddingCol - nColsFilter) / stridesCol + 1;
	const DimSizes& dimSizesExp = arrayExp.GetDimSizes();
	if (!(dimSizesExp.size() == 2 && dimSizesExp[0] == nSamples * nRowsExp * nColsExp && dimSizesExp[1] == nChannels * nRowsFilter * nColsFilter)) {
		Error::Issue(ErrorType::SizeError, "invalid size of Array");
		return false;
	}
	auto func = Array::funcs.Add_ArrayArray[elemType.id][elemType.id];
	size_t bytesPerCol = elemType.bytes;
	size_t bytesPerRow = nColsImg * bytesPerCol;
	size_t bytesPerChannel = bytesPerRow * nRowsImg;
	size_t bytesPerSample = bytesPerChannel * nChannels;
	size_t bytesStridesCol = stridesCol * bytesPerCol;
	size_t bytesStridesRow = stridesRow * bytesPerRow;
	pArrayImg.reset(Array::Create(elemType, dimSizesImg));
	const UInt8* pElemExp = arrayExp.GetPointerC<UInt8>();
	size_t bytesFilterCol = nColsFilter * bytesPerCol;
	UInt8* pElemSample = pArrayImg->GetPointerC<UInt8>();
	for (size_t iSample = 0; iSample < nSamples; iSample++, pElemSample += bytesPerSample) {
		UInt8* pElemKernelRow = pElemSample;
		size_t iRowImg = 0, iRowExp = 0;
		for ( ; iRowExp < nRowsExp; iRowImg += stridesRow, iRowExp++) {
			size_t bytesSkipRowPre = 0;
			size_t bytesSkipRowPost = 0;
			size_t nRowsFilterPart = 0;
			UInt8* pElemKernelColBase = pElemKernelRow;
			if (iRowImg + nRowsFilter < paddingRow) {
				// nothing to do
			} else if (iRowImg < paddingRow) {
				size_t nRowsSkipPre = paddingRow - iRowImg;
				bytesSkipRowPre = bytesFilterCol * nRowsSkipPre;
				nRowsFilterPart = nRowsFilter - nRowsSkipPre;
				if (iRowImg + stridesRow >= paddingRow) {
					pElemKernelRow = pElemSample + (iRowImg + stridesRow - paddingRow) * bytesPerRow;
				}
			} else if (iRowImg + nRowsFilter <= paddingRow + nRowsImg) {
				nRowsFilterPart = nRowsFilter;
				pElemKernelRow += bytesStridesRow;
			} else if (iRowImg < paddingRow + nRowsImg) {
				nRowsFilterPart = paddingRow + nRowsImg - iRowImg;
				size_t nRowsSkipPost = nRowsFilter - nRowsFilterPart;
				bytesSkipRowPost = bytesFilterCol * nRowsSkipPost;
				pElemKernelRow += bytesStridesRow;
			} else {
				// nothing to do
			}
			do {
				size_t iColImg = 0, iColExp = 0;
				size_t bytesFilterColRowChannel = bytesFilterCol * nRowsFilterPart * nChannels;
				UInt8* pElemKernelCol = pElemKernelColBase;
				if (nColsFilter < paddingCol) {
					size_t n = paddingCol - nColsFilter;
					iColImg += stridesCol * n;
					iColExp += n;
					pElemExp += bytesFilterColRowChannel * n;
				}
				for ( ; iColExp < nColsExp && iColImg < paddingCol; iColImg += stridesCol, iColExp++) {
					size_t bytesSkipColPre = (paddingCol - iColImg) * bytesPerCol;
					size_t bytesFilterColPart = bytesFilterCol - bytesSkipColPre;
					size_t nColsSkipPre = paddingCol - iColImg;
					size_t nColsFilterColPart = nColsFilter - nColsSkipPre;
					UInt8* pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						UInt8* pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemImg += bytesPerRow) {
							pElemExp += bytesSkipColPre;
							//::memcpy(pElemExp, pElemImg, bytesFilterColPart);
							func(pElemImg, pElemImg, pElemExp, nColsFilterColPart);
							pElemExp += bytesFilterColPart;
						}
						pElemExp += bytesSkipRowPost;
					}
				}
				pElemKernelCol = pElemKernelColBase + (iColImg - paddingCol) * bytesPerCol;
				for ( ; iColExp < nColsExp && iColImg + nColsFilter <= paddingCol + nColsImg; iColImg += stridesCol, iColExp++) {
					const UInt8* pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						const UInt8* pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemImg += bytesPerRow) {
							//::memcpy(pElemExp, pElemImg, bytesFilterCol);
							pElemExp += bytesFilterCol;
						}
						pElemExp += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStridesCol;
				}
				for ( ; iColExp < nColsExp && iColImg < paddingCol + nColsImg; iColImg += stridesCol, iColExp++) {
					size_t bytesFilterColPart = (paddingCol + nColsImg - iColImg) * bytesPerCol;
					size_t bytesSkipColPost = bytesFilterCol - bytesFilterColPart;
					const UInt8* pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						const UInt8* pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsFilterPart; n++, pElemImg += bytesPerRow) {
							//::memcpy(pElemExp, pElemImg, bytesFilterColPart);
							pElemExp += bytesFilterColPart;
							pElemExp += bytesSkipColPost;
						}
						pElemExp += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStridesCol;
				}
				if (iColExp < nColsExp) {
					size_t n = nColsExp - iColExp;
					pElemExp += bytesFilterColRowChannel * n;
				}
			} while (0);
		}

	}
	return true;
}
#endif

Gurax_EndModuleScope(ml)
