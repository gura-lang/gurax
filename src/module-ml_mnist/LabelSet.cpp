//==============================================================================
// LabelSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// LabelSet
//------------------------------------------------------------------------------
bool LabelSet::Read(Stream& stream)
{
	size_t bytesRead = 0;
	Header header;
	bytesRead = stream.Read(&header, sizeof(header));
	if (bytesRead < sizeof(header)) {
		Error::Issue(ErrorType::FormatError, "invalid format of MNIST image file");
		return false;
	}
	UInt32 magicNumber = Gurax_UnpackUInt32(header.magicNumber);
	if (magicNumber != 0x00000801) {
		Error::Issue(ErrorType::FormatError, "invalid magic number of MNIST label file: %08x", magicNumber);
		return false;
	}
	_nLabels = Gurax_UnpackUInt32(header.nLabels);
	size_t bytesLabel = _nLabels;
	_pMemory.reset(new MemoryHeap(bytesLabel));
	bytesRead = stream.Read(_pMemory->GetPointerC<void>(), bytesLabel);
	if (bytesRead < bytesLabel) {
		Error::Issue(ErrorType::FormatError, "invalid format of MNIST label file");
		return false;
	}
	return true;
}

template<typename T_Elem>
Array *CreateArrayOfLabels(const Array::ElemTypeT& elemType, const UInt8* pElemSrc, size_t nLabels, bool oneHotFlag)
{
	RefPtr<Array> pArray;
	if (oneHotFlag) {
		size_t labelMax = 0;
		for (size_t i = 0; i < nLabels; i++) {
			UInt8 label = *(pElemSrc + i);
			if (labelMax < label) labelMax = label;
		}
		size_t nCols = labelMax + 1;
		pArray.reset(Array::Create2d(elemType, nLabels, nCols));
		//pArray->FillZero();
		T_Elem *pElemDst = pArray->GetPointerC<T_Elem>();
		for (size_t i = 0; i < nLabels; i++, pElemDst += nCols) {
			UInt8 label = *(pElemSrc + i);
			*(pElemDst + label) = 1;
		}
	} else {
		pArray.reset(Array::Create1d(elemType, nLabels));
		T_Elem *pElemDst = pArray->GetPointerC<T_Elem>();
		for (size_t i = 0; i < nLabels; i++, pElemSrc++, pElemDst++) {
			*pElemDst = static_cast<T_Elem>(*pElemSrc);
		}
	}
	return pArray.release();
}

Array* LabelSet::ToArray(bool oneHotFlag, const Array::ElemTypeT& elemType) const
{
	RefPtr<Array> pArray;
	const UInt8 *pElemSrc = _pMemory->GetPointerC<UInt8>();
	if (elemType.IsIdentical(Array::ElemType::UInt8)) {
		if (oneHotFlag) {
			pArray.reset(CreateArrayOfLabels<UInt8>(elemType, pElemSrc, _nLabels, oneHotFlag));
		} else {
			pArray.reset(Array::Create(elemType, _pMemory.Reference(), DimSizes(_nLabels)));
		}
	} else if (elemType.IsIdentical(Array::ElemType::Half)) {
		pArray.reset(CreateArrayOfLabels<Half>(elemType, pElemSrc, _nLabels, oneHotFlag));
	} else if (elemType.IsIdentical(Array::ElemType::Float)) {
		pArray.reset(CreateArrayOfLabels<Float>(elemType, pElemSrc, _nLabels, oneHotFlag));
	} else if (elemType.IsIdentical(Array::ElemType::Double)) {
		pArray.reset(CreateArrayOfLabels<Double>(elemType, pElemSrc, _nLabels, oneHotFlag));
	} else {
		Error::Issue(ErrorType::ValueError, "can't create an array of %s", elemType.GetName());
		return nullptr;
	}
	return Error::IsIssued()? nullptr : pArray.release();
}

String LabelSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.LabelSet");
}

//------------------------------------------------------------------------------
// LabelSetList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// LabelSetOwner
//------------------------------------------------------------------------------
void LabelSetOwner::Clear()
{
	for (LabelSet* pLabelSet : *this) LabelSet::Delete(pLabelSet);
	clear();
}

Gurax_EndModuleScope(ml_mnist)
