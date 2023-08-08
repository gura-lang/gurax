//==============================================================================
// PairSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// PairSet
//------------------------------------------------------------------------------
PairSet::PairSet(bool superClassFlag) : _superClassFlag(superClassFlag), _nSamples(0),
							_pLabelSet(new LabelSet()), _pImageSet(new ImageSet())
{
}

bool PairSet::Read(Stream& stream)
{
	struct Pack {
		UInt8 labelSuper;
		UInt8 label;
	};
	UInt8 buffImage[ImageSet::nChannels * ImageSet::nRowsImage * ImageSet::nColsImage];
	for (;;) {
		if (_superClassFlag) {
			Pack pack;
			size_t bytesRead = stream.Read(&pack, sizeof(pack));
			if (bytesRead == 0) break;
			if (bytesRead != sizeof(pack)) return false;
			_pLabelSet->Add(pack.labelSuper, pack.label);
		} else {
			UInt8 label;
			size_t bytesRead = stream.Read(&label, sizeof(label));
			if (bytesRead == 0) break;
			_pLabelSet->Add(label);
		}
		if (stream.Read(buffImage, sizeof(buffImage)) < sizeof(buffImage)) return false;
		_pImageSet->Add(buffImage);
		_nSamples++;
	}
	_indices.reserve(_nSamples);
	for (size_t i = 0; i < _nSamples; i++) _indices.push_back(i);
	return true;
}

String PairSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.cifar.PairSet:%zusamples:%zuchannels:%zurows:%zucols:%zuclasses:%zusuper-classes",
		_nSamples, ImageSet::nChannels, ImageSet::nRowsImage, ImageSet::nColsImage, GetLabelSet().GetNClasses(), GetLabelSet().GetNClassesSuper());
}

//------------------------------------------------------------------------------
// PairSetList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PairSetOwner
//------------------------------------------------------------------------------
void PairSetOwner::Clear()
{
	for (PairSet* pPairSet : *this) PairSet::Delete(pPairSet);
	clear();
}

#if 0
//------------------------------------------------------------------------------
// Iterator_EachBatch
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_EachBatch : public Iterator {
private:
	RefPtr<PairSet> _pPairSet;
	RefPtr<Array> _pArrayImage;
	RefPtr<Array> _pArrayLabel;
	size_t _batchSize;
	Double _numCeil;
	size_t _idx;
public:
	Iterator_EachBatch(PairSet* pPairSet, const Array::ElemTypeT& elemType, size_t batchSize, Double numCeil);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override;
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};
#endif

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
Iterator_Each::Iterator_Each(PairSet* pPairSet, const Array::ElemTypeT& elemType, Double numCeil) :
	_pPairSet(pPairSet),
	_pArrayImage(Array::Create(elemType, DimSizes(ImageSet::nChannels, ImageSet::nRowsImage, ImageSet::nColsImage))),
	_pArrayLabel(Array::Create(elemType, DimSizes(pPairSet->GetLabelSet().GetNClasses()))),
	_numCeil(numCeil), _idx(0)
{
}

size_t Iterator_Each::GetLength() const
{
	return _pPairSet->GetNSamples();
}

Value* Iterator_Each::DoNextValue()
{
	if (_idx >= _pPairSet->GetNSamples()) return nullptr;
	void* pImageDst = _pArrayImage->GetPointerC<void>();
	size_t iSample = _pPairSet->GetIndex(_idx);
	_idx++;
	_pPairSet->GetImageSet().Extract(_pArrayImage->GetElemType(), pImageDst, iSample, _numCeil);
	UInt8 label = _pPairSet->GetLabelSet().GetLabel(iSample);
	_pArrayLabel->FillZero();
	_pArrayLabel->IndexSetDouble(label, 1.);
	return Value_Tuple::Create(new Value_Array(_pArrayImage->Reference()), new Value_Array(_pArrayLabel->Reference()));
}

String Iterator_Each::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.EachBatch:%zu/%zu", _idx, _pPairSet->GetNSamples());
}

#if 0
//------------------------------------------------------------------------------
// Iterator_EachBatch
//------------------------------------------------------------------------------
Iterator_EachBatch::Iterator_EachBatch(PairSet* pPairSet, const Array::ElemTypeT& elemType, size_t batchSize, Double numCeil) :
	_pPairSet(pPairSet),
	_pArrayImage(Array::Create(elemType, DimSizes(batchSize, pPairSet->GetImageSet().GetNRows(), pPairSet->GetImageSet().GetNCols()))),
	_pArrayLabel(Array::Create(elemType, DimSizes(batchSize, pPairSet->GetLabelSet().GetNClasses()))),
	_batchSize(batchSize), _numCeil(numCeil), _idx(0)
{
}

size_t Iterator_EachBatch::GetLength() const
{
	return _pPairSet->GetImageSet().GetNSamples() / _batchSize;
}

Value* Iterator_EachBatch::DoNextValue()
{
	if (_idx + _batchSize > _pPairSet->GetImageSet().GetNSamples()) return nullptr;
	void* pImageDst = _pArrayImage->GetPointerC<void>();
	_pArrayLabel->FillZero();
	size_t offset = 0;
	size_t nElems = _pPairSet->GetImageSet().GetNRows() * _pPairSet->GetImageSet().GetNCols();
	size_t nClasses = _pPairSet->GetLabelSet().GetNClasses();
	for (size_t i = 0; i < _batchSize; i++, _idx++) {
		size_t iSample = _pPairSet->GetIndex(_idx);
		_pPairSet->GetImageSet().Extract(_pArrayImage->GetElemType(), pImageDst, iSample, _numCeil);
		UInt32 label = _pPairSet->GetLabelSet().GetLabel(iSample);
		_pArrayLabel->IndexSetDouble(offset + label, 1.);
		pImageDst = _pArrayImage->FwdPointer(pImageDst, nElems);
		offset += nClasses;
	}
	return Value_Tuple::Create(new Value_Array(_pArrayImage->Reference()), new Value_Array(_pArrayLabel->Reference()));
}

String Iterator_EachBatch::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.EachBatch:batchSize=%zu:%zu/%zu",
		_batchSize, _idx / _batchSize, _pPairSet->GetImageSet().GetNSamples() / _batchSize);
}
#endif

Gurax_EndModuleScope(ml_cifar)
