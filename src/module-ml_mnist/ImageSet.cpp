//==============================================================================
// ImageSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

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
	_nSamples = Gurax_UnpackUInt32(header.nSamples);
	_nRows = Gurax_UnpackUInt32(header.nRows);
	_nCols = Gurax_UnpackUInt32(header.nCols);
	size_t bytesImage = _nSamples * _nRows * _nCols;
	_pMemory.reset(new MemoryHeap(bytesImage));
	bytesRead = stream.Read(_pMemory->GetPointerC<void>(), bytesImage);
	if (bytesRead < bytesImage) {
		Error::Issue(ErrorType::FormatError, "invalid format of MNIST image file");
		return false;
	}
	return true;
}

void ImageSet::ExtractAsArray(RefPtr<Array>& pArray, const Array::ElemTypeT& elemType, Double numCeil, size_t iSample) const
{
	if (!pArray) pArray.reset(Array::Create(elemType, DimSizes(_nRows, _nCols)));
	auto func = CopyElems[elemType.id];
	size_t nElems = _nRows * _nCols;
	const UInt8* pElemSrc = _pMemory->GetPointerC<UInt8>() + nElems * iSample;
	func(pArray->GetPointerC<void>(), pElemSrc, nElems, numCeil);
}

void ImageSet::ExtractAsImage(RefPtr<Image>& pImage, const Image::Format& format, size_t iSample) const
{
	if (!pImage) {
		pImage.reset(new Image(format));
		pImage->Allocate(_nCols, _nRows);
	}
	UInt8* pDst = pImage->GetPointerC();
	size_t nElems = _nRows * _nCols;
	const UInt8* pElemSrc = _pMemory->GetPointerC<UInt8>() + nElems * iSample;
	if (format.IsIdentical(Image::Format::RGB)) {
		for (size_t i = 0; i < nElems; i++) {
			*pDst++ = *pElemSrc;
			*pDst++ = *pElemSrc;
			*pDst++ = *pElemSrc++;
		}
	} else { // Image::Format::RGBA
		for (size_t i = 0; i < nElems; i++) {
			*pDst++ = *pElemSrc;
			*pDst++ = *pElemSrc;
			*pDst++ = *pElemSrc++;
			*pDst++ = 0xff;
		}
	}
}

String ImageSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.ImageSet:%zusamples:%zurows:%zucols", GetNSamples(), GetNRows(), GetNCols());
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
