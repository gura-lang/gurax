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

void ImageSet::Extract(const Array::ElemTypeT& elemType, void* pDst, size_t iSample, Double numCeil) const
{
	auto func = CopyElems[elemType.id];
	size_t nElems = nChannels * nRowsImage * nColsImage;
	const UInt8* pElemSrc = _buff.data() + nElems * iSample;
	func(pDst, pElemSrc, nElems, numCeil);
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
