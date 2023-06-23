//==============================================================================
// ImageSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// ImageSet
//------------------------------------------------------------------------------
bool ImageSet::Read(Stream& stream)
{
	size_t bytesRead = 0;
	Header header;
	bytesRead = stream.Read(&header, sizeof(header));
	if (bytesRead < sizeof(header)) {
		Error::Issue(ErrorType::FormatError, "invalid format of MNIST image file");
		return false;
	}
	UInt32 magicNumber = Gurax_UnpackUInt32(header.magicNumber);
	if (magicNumber != 0x00000803) {
		Error::Issue(ErrorType::FormatError, "invalid magic number of MNIST image file: %08x", magicNumber);
		return false;
	}
	_nImages = Gurax_UnpackUInt32(header.nImages);
	_nRows = Gurax_UnpackUInt32(header.nRows);
	_nCols = Gurax_UnpackUInt32(header.nCols);
	size_t bytesImage = _nImages * _nRows * _nCols;
	_pMemory.reset(new MemoryHeap(bytesImage));
	bytesRead = stream.Read(_pMemory->GetPointerC<void>(), bytesImage);
	if (bytesRead < bytesImage) {
		Error::Issue(ErrorType::FormatError, "invalid format of MNIST image file");
		return false;
	}
	return true;
}

template<typename T_Elem>
Array* CreateArrayOfImages(const Array::ElemTypeT& elemType, DimSizes& dimSizes, const UInt8* pElemSrc, Float numMax)
{
	RefPtr<Array> pArray(Array::Create(elemType, dimSizes));
	size_t nElems = pArray->GetDimSizes().CalcLength();
	T_Elem* pElemDst = pArray->GetPointerC<T_Elem>();
	if (numMax > 0) {
		for (size_t i = 0; i < nElems; i++, pElemSrc++, pElemDst++) {
			*pElemDst = static_cast<T_Elem>(numMax * *pElemSrc / 255);
		}
	} else {
		for (size_t i = 0; i < nElems; i++, pElemSrc++, pElemDst++) {
			*pElemDst = static_cast<T_Elem>(*pElemSrc);
		}
	}
	return pArray.release();
}

Array* ImageSet::ToArray(const Array::ElemTypeT& elemType, bool flattenFlag, Float numMax) const
{
	RefPtr<Array> pArray;
	DimSizes dimSizes;
	dimSizes.push_back(_nImages);
	if (flattenFlag) {
		dimSizes.push_back(_nRows * _nCols);
	} else {
		dimSizes.push_back(_nRows);
		dimSizes.push_back(_nCols);
	}
	if (elemType.IsIdentical(Array::ElemType::UInt8)) {
		pArray.reset(CreateArrayOfImages<UInt8>(elemType, dimSizes, _pMemory->GetPointerC<UInt8>(), numMax));
	} else if (elemType.IsIdentical(Array::ElemType::Half)) {
		pArray.reset(CreateArrayOfImages<Half>(elemType, dimSizes, _pMemory->GetPointerC<UInt8>(), numMax));
	} else if (elemType.IsIdentical(Array::ElemType::Float)) {
		pArray.reset(CreateArrayOfImages<Float>(elemType, dimSizes, _pMemory->GetPointerC<UInt8>(), numMax));
	} else if (elemType.IsIdentical(Array::ElemType::Double)) {
		pArray.reset(CreateArrayOfImages<Double>(elemType, dimSizes, _pMemory->GetPointerC<UInt8>(), numMax));
	} else {
		Error::Issue(ErrorType::ValueError, "can't create an array of %s", elemType.GetName());
		return nullptr;
	}
	return pArray.release();
}

String ImageSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.ImageSet:%zusamples:%zurows:%zucols", CountImages(), CountRows(), CountCols());
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

Gurax_EndModuleScope(ml_mnist)
