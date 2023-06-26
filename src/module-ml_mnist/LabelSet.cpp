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
	struct Header {
		Gurax_PackedUInt32_BE(magicNumber);
		Gurax_PackedUInt32_BE(nSamples);
	};
	struct HeaderExtra {
		Gurax_PackedUInt32_BE(nFields);
	};
	struct ElemRaw {
		Gurax_PackedUInt32_BE(num);
	};
	size_t bytesRead = 0;
	Header header;
	bytesRead = stream.Read(&header, sizeof(header));
	if (bytesRead < sizeof(header)) {
		Error::Issue(ErrorType::FormatError, "invalid format of MNIST label file");
		return false;
	}
	UInt32 magicNumber = Gurax_UnpackUInt32(header.magicNumber);
	_nSamples = Gurax_UnpackUInt32(header.nSamples);
	if (magicNumber == 0x00000801) {
		size_t bytesLabel = _nSamples * sizeof(UInt8);
		_pMemory.reset(new MemoryHeap(bytesLabel));
		bytesRead = stream.Read(_pMemory->GetPointerC<void>(), bytesLabel);
		if (bytesRead < bytesLabel) {
			Error::Issue(ErrorType::FormatError, "invalid format of MNIST label file");
			return false;
		}
		size_t iClassMax = 0;
		const UInt8* pElemSrc = _pMemory->GetPointerC<UInt8>();
		for (size_t i = 0; i < _nSamples; i++, pElemSrc++) {
			UInt8 iClass = *pElemSrc;
			if (iClassMax < iClass) iClassMax = iClass;
		}
		_nClasses = iClassMax + 1;
	} else if (magicNumber == 0x00000c02) {
		_qmnistFlag = true;
		HeaderExtra headerExtra;
		bytesRead = stream.Read(&headerExtra, sizeof(headerExtra));
		if (bytesRead < sizeof(headerExtra)) {
			Error::Issue(ErrorType::FormatError, "invalid format of QMNIST label file");
			return false;
		}
		_nFields = Gurax_UnpackUInt32(headerExtra.nFields);
		size_t nElemRaws = _nSamples * _nFields;
		size_t bytesLabel = nElemRaws * sizeof(UInt32);
		_pMemory.reset(new MemoryHeap(bytesLabel));
		ElemRaw elemRaw;
		UInt32* pElem = _pMemory->GetPointerC<UInt32>();
		for (size_t i = 0; i < nElemRaws; i++) {
			bytesRead = stream.Read(&elemRaw, sizeof(elemRaw));
			if (bytesRead < sizeof(elemRaw)) {
				Error::Issue(ErrorType::FormatError, "invalid format of QMNIST label file");
				return false;
			}
			*pElem++ = Gurax_UnpackUInt32(elemRaw.num);
		}
		size_t iClassMax = 0;
		const UInt32* pElemSrc = _pMemory->GetPointerC<UInt32>();
		for (size_t i = 0; i < _nSamples; i++, pElemSrc += _nFields) {
			UInt32 iClass = *pElemSrc;
			if (iClassMax < iClass) iClassMax = iClass;
		}
		_nClasses = iClassMax + 1;
	} else {
		Error::Issue(ErrorType::FormatError, "invalid magic number of MNIST label file: %08x", magicNumber);
		return false;
	}
	return true;
}

template<typename T_Elem>
Array* CreateArrayOfLabels(const Array::ElemTypeT& elemType, const Memory& memory, size_t nSamples, size_t nClases, bool oneHotFlag)
{
	const UInt8* pElemSrc = memory.GetPointerC<UInt8>();
	RefPtr<Array> pArray;
	if (oneHotFlag) {
		pArray.reset(Array::Create(elemType, DimSizes(nSamples, nClases)));
		T_Elem* pElemDst = pArray->GetPointerC<T_Elem>();
		for (size_t i = 0; i < nSamples; i++, pElemSrc++, pElemDst += nClases) {
			UInt8 iClass = *pElemSrc;
			*(pElemDst + iClass) = 1;
		}
	} else {
		pArray.reset(Array::Create(elemType, DimSizes(nSamples)));
		T_Elem* pElemDst = pArray->GetPointerC<T_Elem>();
		for (size_t i = 0; i < nSamples; i++, pElemSrc++, pElemDst++) {
			*pElemDst = static_cast<T_Elem>(*pElemSrc);
		}
	}
	return pArray.release();
}

template<typename T_Elem>
Array* CreateArrayOfLabelsQMNIST(const Array::ElemTypeT& elemType, const Memory& memory, size_t nSamples, size_t nFields, size_t nClases, bool oneHotFlag)
{
	const UInt32* pElemSrc = memory.GetPointerC<UInt32>();
	RefPtr<Array> pArray;
	if (oneHotFlag) {
		pArray.reset(Array::Create(elemType, DimSizes(nSamples, nClases)));
		T_Elem* pElemDst = pArray->GetPointerC<T_Elem>();
		for (size_t i = 0; i < nSamples; i++, pElemSrc += nFields, pElemDst += nClases) {
			UInt32 iClass = *pElemSrc;
			*(pElemDst + iClass) = 1;
		}
	} else {
		pArray.reset(Array::Create(elemType, DimSizes(nSamples)));
		T_Elem* pElemDst = pArray->GetPointerC<T_Elem>();
		for (size_t i = 0; i < nSamples; i++, pElemSrc += nFields, pElemDst++) {
			*pElemDst = static_cast<T_Elem>(*pElemSrc);
		}
	}
	return pArray.release();
}

Array* LabelSet::ToArray(const Array::ElemTypeT& elemType, bool oneHotFlag) const
{
	RefPtr<Array> pArray;
	if (elemType.IsIdentical(Array::ElemType::UInt8)) {
		pArray.reset(_qmnistFlag?
			CreateArrayOfLabelsQMNIST<UInt8>(elemType, *_pMemory, _nSamples, _nFields, _nClasses, oneHotFlag) :
			CreateArrayOfLabels<UInt8>(elemType, *_pMemory, _nSamples, _nClasses, oneHotFlag));
	} else if (elemType.IsIdentical(Array::ElemType::Half)) {
		pArray.reset(_qmnistFlag?
			CreateArrayOfLabelsQMNIST<Half>(elemType, *_pMemory, _nSamples, _nFields, _nClasses, oneHotFlag) :
			CreateArrayOfLabels<Half>(elemType, *_pMemory, _nSamples, _nClasses, oneHotFlag));
	} else if (elemType.IsIdentical(Array::ElemType::Float)) {
		pArray.reset(_qmnistFlag?
			CreateArrayOfLabelsQMNIST<Float>(elemType, *_pMemory, _nSamples, _nFields, _nClasses, oneHotFlag) :
			CreateArrayOfLabels<Float>(elemType, *_pMemory, _nSamples, _nClasses, oneHotFlag));
	} else if (elemType.IsIdentical(Array::ElemType::Double)) {
		pArray.reset(_qmnistFlag?
			CreateArrayOfLabelsQMNIST<Double>(elemType, *_pMemory, _nSamples, _nFields, _nClasses, oneHotFlag) :
			CreateArrayOfLabels<Double>(elemType, *_pMemory, _nSamples, _nClasses, oneHotFlag));
	} else {
		Error::Issue(ErrorType::ValueError, "can't create an array of %s", elemType.GetName());
		return nullptr;
	}
	return Error::IsIssued()? nullptr : pArray.release();
}

String LabelSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.LabelSet:%zusamples", CountSamples());
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
