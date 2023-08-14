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

void ImageSet::ExtractAsArray(RefPtr<Array>& pArray, const SampleSet& sampleSet, const Array::ElemTypeT& elemType, size_t batchSize, Double numCeil, size_t idx) const
{
	auto func = CopyElems[elemType.id];
	size_t nElems = _nRows * _nCols;
	if (batchSize == 0) {
		if (!pArray) pArray.reset(Array::Create(elemType, DimSizes(_nRows, _nCols)));
		UInt8* pElemDst = pArray->GetPointerC<UInt8>();
		const UInt8* pElemSrc = _pMemory->GetPointerC<UInt8>() + nElems * sampleSet.GetIndex(idx);
		func(pElemDst, pElemSrc, nElems, numCeil);
	} else {
		if (!pArray) pArray.reset(Array::Create(elemType, DimSizes(batchSize, _nRows, _nCols)));
		UInt8* pElemDst = pArray->GetPointerC<UInt8>();
		size_t bytesForward = nElems * elemType.bytes;
		for (size_t i = 0; i < batchSize; i++, idx++) {
			const UInt8* pElemSrc = _pMemory->GetPointerC<UInt8>() + nElems * sampleSet.GetIndex(idx);
			func(pElemDst, pElemSrc, nElems, numCeil);
			pElemDst += bytesForward;
		}
	}
}

void ImageSet::ExtractAsImage(RefPtr<Image>& pImage, const SampleSet& sampleSet, const Image::Format& format, size_t batchSize, size_t idx) const
{
	size_t nItems = (batchSize == 0)? 1 : batchSize;
	if (!pImage) {
		pImage.reset(new Image(format));
		pImage->Allocate(_nCols, _nRows * nItems);
	}
	UInt8* pDst = pImage->GetPointerC();
	size_t nPixels = _nRows * _nCols;
	if (format.IsIdentical(Image::Format::RGB)) {
		for (size_t iItem = 0; iItem < nItems; iItem++, idx++) {
			const UInt8* pElemSrc = _pMemory->GetPointerC<UInt8>() + nPixels * sampleSet.GetIndex(idx);
			for (size_t iPixel = 0; iPixel < nPixels; iPixel++) {
				*pDst++ = *pElemSrc;
				*pDst++ = *pElemSrc;
				*pDst++ = *pElemSrc++;
			}
		}
	} else { // Image::Format::RGBA
		for (size_t iItem = 0; iItem < nItems; iItem++, idx++) {
			const UInt8* pElemSrc = _pMemory->GetPointerC<UInt8>() + nPixels * sampleSet.GetIndex(idx);
			for (size_t iPixel = 0; iPixel < nPixels; iPixel++) {
				*pDst++ = *pElemSrc;
				*pDst++ = *pElemSrc;
				*pDst++ = *pElemSrc++;
				*pDst++ = 0xff;
			}
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
