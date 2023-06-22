//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

Funcs funcs;

template<typename T_Elem> void MaxPool_T(void* pvPool, const void* pvSrc, size_t len, UInt32 scanPosIn, UInt32* pScanPosInSel)
{
	T_Elem* pPool = reinterpret_cast<T_Elem*>(pvPool);
	const T_Elem* pSrc = reinterpret_cast<const T_Elem*>(pvSrc);
	const T_Elem* pSrcEnd = pSrc + len;
	for ( ; pSrc != pSrcEnd; pSrc++, scanPosIn++) {
		if (*pPool < *pSrc) {
			*pPool = *pSrc;
			*pScanPosInSel = scanPosIn;
		}
	}
}

template<> void MaxPool_T<Complex>(void* pvPool, const void* pvSrc, size_t len, UInt32 scanPosIn, UInt32* pScanPosInSel) {}

template<typename T_Elem> void PoolBackward_T(void* pvBwdOut, UInt32 scanPos, const void* pvBwdIn)
{
	*(reinterpret_cast<T_Elem*>(pvBwdOut) + scanPos) += *reinterpret_cast<const T_Elem*>(pvBwdIn);
}

void InitializeUtil()
{
	Gurax_SetArrayFuncSingle(funcs.MaxPool, MaxPool_T);
	Gurax_SetArrayFuncSingle(funcs.PoolBackward, PoolBackward_T);
}

void PrintCol(const void* pv, size_t bytes)
{
	const Float* p = reinterpret_cast<const Float*>(pv);
	for (size_t i = 0; i < bytes / sizeof(Float); i++, p++) {
		::printf("  %g", *p);
	}
	::printf("\n");
}

bool Img2dToCol(RefPtr<Array>& pArrayExp, const Array& arrayImg, size_t nRowsKernel, size_t nColsKernel,
	size_t strideRow, size_t strideCol, size_t paddingRow, size_t paddingCol, size_t* pnRowsOut, size_t* pnColsOut)
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
	size_t nRowsOut = (nRowsImg + 2 * paddingRow - nRowsKernel) / strideRow + 1;
	size_t nColsOut = (nColsImg + 2 * paddingCol - nColsKernel) / strideCol + 1;
	if (pnRowsOut) *pnRowsOut = nRowsOut;
	if (pnColsOut) *pnColsOut = nColsOut;
	size_t bytesPerCol = elemType.bytes;
	size_t bytesPerRow = nColsImg * bytesPerCol;
	size_t bytesPerChannel = bytesPerRow * nRowsImg;
	size_t bytesPerSample = bytesPerChannel * nChannels;
	size_t bytesStrideCol = strideCol * bytesPerCol;
	size_t bytesStrideRow = strideRow * bytesPerRow;
	pArrayExp.reset(Array::Create(elemType, DimSizes(nSamples * nRowsOut * nColsOut, nChannels * nRowsKernel * nColsKernel)));
	auto pElemExp = pArrayExp->GetPointerC<UInt8>();
	size_t bytesKernelCol = nColsKernel * bytesPerCol;
	auto pElemSample = arrayImg.GetPointerC<UInt8>();
	for (size_t iSample = 0; iSample < nSamples; iSample++, pElemSample += bytesPerSample) {
		auto pElemKernelRow = pElemSample;
		size_t iRowImg = 0, iRowOut = 0;
		for ( ; iRowOut < nRowsOut; iRowImg += strideRow, iRowOut++) {
			size_t bytesSkipRowPre = 0;
			size_t bytesSkipRowPost = 0;
			size_t nRowsKernelPart = 0;
			auto pElemKernelColBase = pElemKernelRow;
			if (iRowImg + nRowsKernel < paddingRow) {
				// nothing to do
			} else if (iRowImg < paddingRow) {
				size_t nRowsSkipPre = paddingRow - iRowImg;
				bytesSkipRowPre = bytesKernelCol * nRowsSkipPre;
				nRowsKernelPart = nRowsKernel - nRowsSkipPre;
				if (iRowImg + strideRow >= paddingRow) {
					pElemKernelRow = pElemSample + (iRowImg + strideRow - paddingRow) * bytesPerRow;
				}
			} else if (iRowImg + nRowsKernel <= paddingRow + nRowsImg) {
				nRowsKernelPart = nRowsKernel;
				pElemKernelRow += bytesStrideRow;
			} else if (iRowImg < paddingRow + nRowsImg) {
				nRowsKernelPart = paddingRow + nRowsImg - iRowImg;
				size_t nRowsSkipPost = nRowsKernel - nRowsKernelPart;
				bytesSkipRowPost = bytesKernelCol * nRowsSkipPost;
				pElemKernelRow += bytesStrideRow;
			} else {
				// nothing to do
			}
			do {
				size_t iColImg = 0, iColOut = 0;
				size_t bytesKernelColRowChannel = bytesKernelCol * nRowsKernelPart * nChannels;
				auto pElemKernelCol = pElemKernelColBase;
				if (nColsKernel < paddingCol) {
					size_t n = paddingCol - nColsKernel;
					iColImg += strideCol * n;
					iColOut += n;
					pElemExp += bytesKernelColRowChannel * n;
				}
				for ( ; iColOut < nColsOut && iColImg < paddingCol; iColImg += strideCol, iColOut++) {
					size_t nColsSkipPre = paddingCol - iColImg;
					size_t nColsKernelPart = nColsKernel - nColsSkipPre;
					size_t bytesSkipColPre = nColsSkipPre * bytesPerCol;
					size_t bytesKernelColPart = nColsKernelPart * bytesPerCol;
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsKernelPart; n++, pElemImg += bytesPerRow) {
							pElemExp += bytesSkipColPre;
							::memcpy(pElemExp, pElemImg, bytesKernelColPart);
							pElemExp += bytesKernelColPart;
						}
						pElemExp += bytesSkipRowPost;
					}
				}
				pElemKernelCol = pElemKernelColBase + (iColImg - paddingCol) * bytesPerCol;
				for ( ; iColOut < nColsOut && iColImg + nColsKernel <= paddingCol + nColsImg; iColImg += strideCol, iColOut++) {
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsKernelPart; n++, pElemImg += bytesPerRow) {
							::memcpy(pElemExp, pElemImg, bytesKernelCol);
							pElemExp += bytesKernelCol;
						}
						pElemExp += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStrideCol;
				}
				for ( ; iColOut < nColsOut && iColImg < paddingCol + nColsImg; iColImg += strideCol, iColOut++) {
					size_t nColsKernelPart = paddingCol + nColsImg - iColImg;
					size_t bytesKernelColPart = nColsKernelPart * bytesPerCol;
					size_t bytesSkipColPost = bytesKernelCol - bytesKernelColPart;
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsKernelPart; n++, pElemImg += bytesPerRow) {
							::memcpy(pElemExp, pElemImg, bytesKernelColPart);
							pElemExp += bytesKernelColPart;
							pElemExp += bytesSkipColPost;
						}
						pElemExp += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStrideCol;
				}
				if (iColOut < nColsOut) {
					size_t n = nColsOut - iColOut;
					pElemExp += bytesKernelColRowChannel * n;
				}
			} while (0);
		}
	}
	// (nSamples * nRowsOut * nColsOut, nChannels * nRowsKernel * nColsKernel)
	return true;
}

bool ColToImg2d(RefPtr<Array>& pArrayImg, const DimSizes& dimSizesImg, const Array& arrayExp, size_t nRowsKernel, size_t nColsKernel,
				size_t strideRow, size_t strideCol, size_t paddingRow, size_t paddingCol)
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
	size_t nRowsOut = (nRowsImg + 2 * paddingRow - nRowsKernel) / strideRow + 1;
	size_t nColsOut = (nColsImg + 2 * paddingCol - nColsKernel) / strideCol + 1;
	if (!(dimSizesExp.size() == 2 && dimSizesExp[0] == nSamples * nRowsOut * nColsOut && dimSizesExp[1] == nChannels * nRowsKernel * nColsKernel)) {
		Error::Issue(ErrorType::SizeError, "invalid size of Array");
		return false;
	}
	auto funcAdd = Array::funcs.Add_ArrayArray[elemType.id][elemType.id];
	size_t bytesPerCol = elemType.bytes;
	size_t bytesPerRow = nColsImg * bytesPerCol;
	size_t bytesPerChannel = bytesPerRow * nRowsImg;
	size_t bytesPerSample = bytesPerChannel * nChannels;
	size_t bytesStrideCol = strideCol * bytesPerCol;
	size_t bytesStrideRow = strideRow * bytesPerRow;
	pArrayImg.reset(Array::Create(elemType, dimSizesImg));
	auto pElemExp = arrayExp.GetPointerC<UInt8>();
	size_t bytesKernelCol = nColsKernel * bytesPerCol;
	auto pElemSample = pArrayImg->GetPointerC<UInt8>();
	for (size_t iSample = 0; iSample < nSamples; iSample++, pElemSample += bytesPerSample) {
		auto pElemKernelRow = pElemSample;
		size_t iRowImg = 0, iRowOut = 0;
		for ( ; iRowOut < nRowsOut; iRowImg += strideRow, iRowOut++) {
			size_t bytesSkipRowPre = 0;
			size_t bytesSkipRowPost = 0;
			size_t nRowsKernelPart = 0;
			auto pElemKernelColBase = pElemKernelRow;
			if (iRowImg + nRowsKernel < paddingRow) {
				// nothing to do
			} else if (iRowImg < paddingRow) {
				size_t nRowsSkipPre = paddingRow - iRowImg;
				bytesSkipRowPre = bytesKernelCol * nRowsSkipPre;
				nRowsKernelPart = nRowsKernel - nRowsSkipPre;
				if (iRowImg + strideRow >= paddingRow) {
					pElemKernelRow = pElemSample + (iRowImg + strideRow - paddingRow) * bytesPerRow;
				}
			} else if (iRowImg + nRowsKernel <= paddingRow + nRowsImg) {
				nRowsKernelPart = nRowsKernel;
				pElemKernelRow += bytesStrideRow;
			} else if (iRowImg < paddingRow + nRowsImg) {
				nRowsKernelPart = paddingRow + nRowsImg - iRowImg;
				size_t nRowsSkipPost = nRowsKernel - nRowsKernelPart;
				bytesSkipRowPost = bytesKernelCol * nRowsSkipPost;
				pElemKernelRow += bytesStrideRow;
			} else {
				// nothing to do
			}
			do {
				size_t iColImg = 0, iColOut = 0;
				size_t bytesKernelColRowChannel = bytesKernelCol * nRowsKernelPart * nChannels;
				auto pElemKernelCol = pElemKernelColBase;
				if (nColsKernel < paddingCol) {
					size_t n = paddingCol - nColsKernel;
					iColImg += strideCol * n;
					iColOut += n;
					pElemExp += bytesKernelColRowChannel * n;
				}
				for ( ; iColOut < nColsOut && iColImg < paddingCol; iColImg += strideCol, iColOut++) {
					size_t nColsSkipPre = paddingCol - iColImg;
					size_t nColsKernelPart = nColsKernel - nColsSkipPre;
					size_t bytesSkipColPre = nColsSkipPre * bytesPerCol;
					size_t bytesKernelColPart = nColsKernelPart * bytesPerCol;
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsKernelPart; n++, pElemImg += bytesPerRow) {
							pElemExp += bytesSkipColPre;
							//::memcpy(pElemExp, pElemImg, bytesKernelColPart);
							funcAdd(pElemImg, pElemImg, pElemExp, nColsKernelPart);
							pElemExp += bytesKernelColPart;
						}
						pElemExp += bytesSkipRowPost;
					}
				}
				pElemKernelCol = pElemKernelColBase + (iColImg - paddingCol) * bytesPerCol;
				for ( ; iColOut < nColsOut && iColImg + nColsKernel <= paddingCol + nColsImg; iColImg += strideCol, iColOut++) {
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsKernelPart; n++, pElemImg += bytesPerRow) {
							//::memcpy(pElemExp, pElemImg, bytesKernelCol);
							funcAdd(pElemImg, pElemImg, pElemExp, nColsKernel);
							pElemExp += bytesKernelCol;
						}
						pElemExp += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStrideCol;
				}
				for ( ; iColOut < nColsOut && iColImg < paddingCol + nColsImg; iColImg += strideCol, iColOut++) {
					size_t nColsKernelPart = paddingCol + nColsImg - iColImg;
					size_t bytesKernelColPart = nColsKernelPart * bytesPerCol;
					size_t bytesSkipColPost = bytesKernelCol - bytesKernelColPart;
					auto pElemChannel = pElemKernelCol;
					for (size_t iChannel = 0; iChannel < nChannels; iChannel++, pElemChannel += bytesPerChannel) {
						auto pElemImg = pElemChannel;
						pElemExp += bytesSkipRowPre;
						for (size_t n = 0; n < nRowsKernelPart; n++, pElemImg += bytesPerRow) {
							//::memcpy(pElemExp, pElemImg, bytesKernelColPart);
							funcAdd(pElemImg, pElemImg, pElemExp, nColsKernelPart);
							pElemExp += bytesKernelColPart;
							pElemExp += bytesSkipColPost;
						}
						pElemExp += bytesSkipRowPost;
					}
					pElemKernelCol += bytesStrideCol;
				}
				if (iColOut < nColsOut) {
					size_t n = nColsOut - iColOut;
					pElemExp += bytesKernelColRowChannel * n;
				}
			} while (0);
		}
	}
	return true;
}

Gurax_EndModuleScope(ml)
