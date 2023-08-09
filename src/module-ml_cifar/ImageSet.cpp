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

void ImageSet::ExtractAsArray(RefPtr<Array>& pArray, const Array::ElemTypeT& elemType, Double numCeil, size_t iSample) const
{
	if (!pArray) pArray.reset(Array::Create(elemType, DimSizes(nChannels, nRowsImage, nColsImage)));
	auto func = CopyElems[elemType.id];
	size_t nElems = nChannels * nRowsImage * nColsImage;
	const UInt8* pElemSrc = _buff.data() + nElems * iSample;
	func(pArray->GetPointerC<void>(), pElemSrc, nElems, numCeil);
}

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
	const UInt8* pElemSrcB = pElemSrcR + nElemsPlate;
	for (size_t i = 0; i < nElemsPlate; i++) {
		*pDst++ = *pElemSrcR++;
		*pDst++ = *pElemSrcG++;
		*pDst++ = *pElemSrcB++;
	}
}

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
