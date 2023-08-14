//==============================================================================
// ImageSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Template Function
//------------------------------------------------------------------------------
template<typename T_Elem> void CopyElems_T(void* pDst, const UInt8* pElemSrc, size_t nElems, Double numCeil)
{
	T_Elem* pElemDst = reinterpret_cast<T_Elem*>(pDst);
	if (numCeil > 0) {
		for (size_t i = 0; i < nElems; i++, pElemSrc++, pElemDst++) {
			*pElemDst = static_cast<T_Elem>(numCeil * *pElemSrc / 255);
		}
	} else {
		for (size_t i = 0; i < nElems; i++, pElemSrc++, pElemDst++) {
			*pElemDst = static_cast<T_Elem>(*pElemSrc);
		}
	}
}

std::function<void (void* pDst, const UInt8* pElemSrc, size_t nElems, Double numCeil)> CopyElems[Array::ElemTypeIdMax];

//------------------------------------------------------------------------------
// ImageSet
//------------------------------------------------------------------------------
void ImageSet::Bootup()
{
	Gurax_SetArrayFuncSingle(CopyElems, CopyElems_T);
}

ImageSet::ImageSet()
{
}

void ImageSet::ExtractAsArray(RefPtr<Array>& pArray, const SampleSet& sampleSet, const Array::ElemTypeT& elemType, Double numCeil, size_t idx, size_t batchSize) const
{
	auto func = CopyElems[elemType.id];
	size_t nElems = nChannels * nRowsImage * nColsImage;
	if (batchSize == 0) {
		if (!pArray) pArray.reset(Array::Create(elemType, DimSizes(nRowsImage, nColsImage)));
		UInt8* pElemDst = pArray->GetPointerC<UInt8>();
		const UInt8* pElemSrc = _buff.data() + nElems * sampleSet.GetIndex(idx);
		func(pElemDst, pElemSrc, nElems, numCeil);
	} else {
		if (!pArray) pArray.reset(Array::Create(elemType, DimSizes(batchSize, nRowsImage, nColsImage)));
		UInt8* pElemDst = pArray->GetPointerC<UInt8>();
		size_t bytesForward = nElems * elemType.bytes;
		for (size_t i = 0; i < batchSize; i++, idx++) {
			const UInt8* pElemSrc = _buff.data() + nElems * sampleSet.GetIndex(idx);
			func(pElemDst, pElemSrc, nElems, numCeil);
			pElemDst += bytesForward;
		}
	}
}

#if 0
void ImageSet::ExtractAsArray(RefPtr<Array>& pArray, const Array::ElemTypeT& elemType, Double numCeil, size_t iSample) const
{
	if (!pArray) pArray.reset(Array::Create(elemType, DimSizes(nChannels, nRowsImage, nColsImage)));
	auto func = CopyElems[elemType.id];
	size_t nElems = nChannels * nRowsImage * nColsImage;
	const UInt8* pElemSrc = _buff.data() + nElems * iSample;
	func(pArray->GetPointerC<void>(), pElemSrc, nElems, numCeil);
}
#endif

void ImageSet::ExtractAsImage(RefPtr<Image>& pImage, const SampleSet& sampleSet, const Image::Format& format, size_t idx, size_t batchSize) const
{
	size_t nItems = (batchSize == 0)? 1 : batchSize;
	if (!pImage) {
		pImage.reset(new Image(format));
		pImage->Allocate(nColsImage, nRowsImage * nItems);
	}
	UInt8* pDst = pImage->GetPointerC();
	size_t nPixels = nRowsImage * nColsImage;
	if (format.IsIdentical(Image::Format::RGB)) {
		for (size_t iItem = 0; iItem < nItems; iItem++, idx++) {
			const UInt8* pElemSrcR = _buff.data() + nPixels * nChannels * sampleSet.GetIndex(idx);
			const UInt8* pElemSrcG = pElemSrcR + nPixels;
			const UInt8* pElemSrcB = pElemSrcG + nPixels;
			for (size_t iPixel = 0; iPixel < nPixels; iPixel++) {
				*pDst++ = *pElemSrcB++;
				*pDst++ = *pElemSrcG++;
				*pDst++ = *pElemSrcR++;
			}
		}
	} else { // Image::Format::RGBA
		for (size_t iItem = 0; iItem < nItems; iItem++, idx++) {
			const UInt8* pElemSrcR = _buff.data() + nPixels * nChannels * sampleSet.GetIndex(idx);
			const UInt8* pElemSrcG = pElemSrcR + nPixels;
			const UInt8* pElemSrcB = pElemSrcG + nPixels;
			for (size_t iPixel = 0; iPixel < nPixels; iPixel++) {
				*pDst++ = *pElemSrcB++;
				*pDst++ = *pElemSrcG++;
				*pDst++ = *pElemSrcR++;
				*pDst++ = 0xff;
			}
		}
	}
}

#if 0
void ImageSet::ExtractAsImage(RefPtr<Image>& pImage, const Image::Format& format, size_t iSample) const
{
	if (!pImage) {
		pImage.reset(new Image(format));
		pImage->Allocate(nColsImage, nRowsImage);
	}
	UInt8* pDst = pImage->GetPointerC();
	size_t nElemsPlate = nRowsImage * nColsImage;
	const UInt8* pElemSrcR = _buff.data() + nElemsPlate * nChannels * iSample;
	const UInt8* pElemSrcG = pElemSrcR + nElemsPlate;
	const UInt8* pElemSrcB = pElemSrcG + nElemsPlate;
	if (format.IsIdentical(Image::Format::RGB)) {
		for (size_t i = 0; i < nElemsPlate; i++) {
			*pDst++ = *pElemSrcB++;
			*pDst++ = *pElemSrcG++;
			*pDst++ = *pElemSrcR++;
		}
	} else { // Image::Format::RGBA
		for (size_t i = 0; i < nElemsPlate; i++) {
			*pDst++ = *pElemSrcB++;
			*pDst++ = *pElemSrcG++;
			*pDst++ = *pElemSrcR++;
			*pDst++ = 0xff;
		}
	}
}
#endif

String ImageSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.cifar.ImageSet");
}

//------------------------------------------------------------------------------
// ImageSetList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ImageSetOwner
//------------------------------------------------------------------------------
void ImageSetOwner::Clear()
{
	for (ImageSet* pImageSet : *this) ImageSet::Delete(pImageSet);
	clear();
}

Gurax_EndModuleScope(ml_cifar)
