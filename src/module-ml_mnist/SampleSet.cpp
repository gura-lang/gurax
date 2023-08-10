//==============================================================================
// SampleSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// SampleSet
//------------------------------------------------------------------------------
SampleSet::SampleSet(ImageSet* pImageSet, LabelSet* pLabelSet) : _pImageSet(pImageSet), _pLabelSet(pLabelSet)
{
	_indices.reserve(pImageSet->GetNSamples());
	for (size_t i = 0; i < pImageSet->GetNSamples(); i++) _indices.push_back(i);
}

String SampleSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.SampleSet:%zusamples:%zurows:%zucols:%zuclasses",
		GetImageSet().GetNSamples(), GetImageSet().GetNRows(), GetImageSet().GetNCols(), GetLabelSet().GetNClasses());
}

//------------------------------------------------------------------------------
// SampleSetList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SampleSetOwner
//------------------------------------------------------------------------------
void SampleSetOwner::Clear()
{
	for (SampleSet* pSampleSet : *this) SampleSet::Delete(pSampleSet);
	clear();
}

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
Iterator_Each::Iterator_Each(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, Double numCeil) :
	_pSampleSet(pSampleSet),
	_pArrayImage(Array::Create(elemType, DimSizes(pSampleSet->GetImageSet().GetNRows(), pSampleSet->GetImageSet().GetNCols()))),
	_pArrayLabel(Array::Create(elemType, DimSizes(pSampleSet->GetLabelSet().GetNClasses()))),
	_numCeil(numCeil), _idx(0)
{
}

size_t Iterator_Each::GetLength() const
{
	return _pSampleSet->GetImageSet().GetNSamples();
}

Value* Iterator_Each::DoNextValue()
{
	if (_idx >= _pSampleSet->GetImageSet().GetNSamples()) return nullptr;
	void* pImageDst = _pArrayImage->GetPointerC<void>();
	size_t iSample = _pSampleSet->GetIndex(_idx);
	_idx++;
	//_pSampleSet->GetImageSet().Extract(_pArrayImage->GetElemType(), pImageDst, iSample, _numCeil);
	UInt32 label = _pSampleSet->GetLabelSet().GetLabel(iSample);
	_pArrayLabel->FillZero();
	_pArrayLabel->IndexSetDouble(label, 1.);
	return Value_Tuple::Create(new Value_Array(_pArrayImage->Reference()), new Value_Array(_pArrayLabel->Reference()));
}

String Iterator_Each::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.Each:%zu/%zu", _idx, _pSampleSet->GetImageSet().GetNSamples());
}

//------------------------------------------------------------------------------
// Iterator_EachBatch
//------------------------------------------------------------------------------
Iterator_EachBatch::Iterator_EachBatch(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, size_t batchSize, Double numCeil) :
	_pSampleSet(pSampleSet),
	_pArrayImage(Array::Create(elemType, DimSizes(batchSize, pSampleSet->GetImageSet().GetNRows(), pSampleSet->GetImageSet().GetNCols()))),
	_pArrayLabel(Array::Create(elemType, DimSizes(batchSize, pSampleSet->GetLabelSet().GetNClasses()))),
	_batchSize(batchSize), _numCeil(numCeil), _idx(0)
{
}

size_t Iterator_EachBatch::GetLength() const
{
	return _pSampleSet->GetImageSet().GetNSamples() / _batchSize;
}

Value* Iterator_EachBatch::DoNextValue()
{
	if (_idx + _batchSize > _pSampleSet->GetImageSet().GetNSamples()) return nullptr;
	void* pImageDst = _pArrayImage->GetPointerC<void>();
	_pArrayLabel->FillZero();
	size_t offset = 0;
	size_t nElems = _pSampleSet->GetImageSet().GetNRows() * _pSampleSet->GetImageSet().GetNCols();
	size_t nClasses = _pSampleSet->GetLabelSet().GetNClasses();
	for (size_t i = 0; i < _batchSize; i++, _idx++) {
		size_t iSample = _pSampleSet->GetIndex(_idx);
		//_pSampleSet->GetImageSet().Extract(_pArrayImage->GetElemType(), pImageDst, iSample, _numCeil);
		UInt32 label = _pSampleSet->GetLabelSet().GetLabel(iSample);
		_pArrayLabel->IndexSetDouble(offset + label, 1.);
		pImageDst = _pArrayImage->FwdPointer(pImageDst, nElems);
		offset += nClasses;
	}
	return Value_Tuple::Create(new Value_Array(_pArrayImage->Reference()), new Value_Array(_pArrayLabel->Reference()));
}

String Iterator_EachBatch::ToString(const StringStyle& ss) const
{
	return String().Format("ml.mnist.EachBatch:batchSize=%zu:%zu/%zu",
		_batchSize, _idx / _batchSize, _pSampleSet->GetImageSet().GetNSamples() / _batchSize);
}

Gurax_EndModuleScope(ml_mnist)
