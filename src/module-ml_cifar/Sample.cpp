//==============================================================================
// Sample.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Sample
//------------------------------------------------------------------------------
Sample::Sample(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, const Image::Format& format, size_t batchSize, Double numCeil, size_t idx) :
		_pSampleSet(pSampleSet), _elemType(elemType), _format(format), _batchSize(batchSize), _numCeil(numCeil), _idx(idx)
{
}

const Array& Sample::GetArrayInput()
{
	_pSampleSet->GetImageSet().ExtractAsArray(_pArrayInput, *_pSampleSet, _elemType, _batchSize, _numCeil, _idx);
	return *_pArrayInput;
}

const Array& Sample::GetArrayResult()
{
	size_t nClasses = _pSampleSet->GetLabelSet().GetNClasses();
	if (_pArrayResult) {
		// nothing to do
	} else if (_batchSize == 0) {
		_pArrayResult.reset(Array::Create(_elemType, DimSizes(nClasses)));
		_pArrayResult->IndexSetDouble(GetLabel(_idx), 1.);
	} else {
		_pArrayResult.reset(Array::Create(_elemType, DimSizes(_batchSize, nClasses)));
		for (size_t i = 0; i < _batchSize; i++) {
			_pArrayResult->IndexSetDouble(i * nClasses + GetLabel(_idx + i), 1.);
		}
	}
	return *_pArrayResult;
}

const Image& Sample::GetImage()
{
	_pSampleSet->GetImageSet().ExtractAsImage(_pImage, *_pSampleSet, _format, _batchSize, _idx);
	return *_pImage;
}

UInt8 Sample::GetLabel(size_t idx) const
{
	return _pSampleSet->GetLabelSet().GetLabel(_pSampleSet->GetIndex(idx));
}

UInt8 Sample::GetLabelSuper(size_t idx) const
{
	return _pSampleSet->GetLabelSet().GetLabelSuper(_pSampleSet->GetIndex(idx));
}

String Sample::GetLabelName(size_t idx) const
{
	return _pSampleSet->GetLabelSet().GetLabelName(_pSampleSet->GetIndex(idx));
}

String Sample::GetLabelNameSuper(size_t idx) const
{
	return _pSampleSet->GetLabelSet().GetLabelNameSuper(_pSampleSet->GetIndex(idx));
}

const ValueOwner& Sample::GetValuesLabel()
{
	if (!_pValuesLabel) {
		size_t idx = _idx;
		size_t nItems = (_batchSize == 0)? 1 : _batchSize;
		_pValuesLabel.reset(new ValueOwner());
		_pValuesLabel->reserve(nItems);
		for (size_t iItem = 0; iItem < nItems; iItem++, idx++) {
			_pValuesLabel->push_back(new Value_Number(GetLabel(idx)));
		}
	}
	return *_pValuesLabel;
}

const ValueOwner& Sample::GetValuesLabelSuper()
{
	if (!_pValuesLabelSuper) {
		size_t idx = _idx;
		size_t nItems = (_batchSize == 0)? 1 : _batchSize;
		_pValuesLabelSuper.reset(new ValueOwner());
		_pValuesLabelSuper->reserve(nItems);
		for (size_t iItem = 0; iItem < nItems; iItem++, idx++) {
			_pValuesLabelSuper->push_back(new Value_Number(GetLabelSuper(idx)));
		}
	}
	return *_pValuesLabelSuper;
}

const ValueOwner& Sample::GetValuesLabelName()
{
	if (!_pValuesLabelName) {
		size_t idx = _idx;
		size_t nItems = (_batchSize == 0)? 1 : _batchSize;
		_pValuesLabelName.reset(new ValueOwner());
		_pValuesLabelName->reserve(nItems);
		for (size_t iItem = 0; iItem < nItems; iItem++, idx++) {
			_pValuesLabelName->push_back(new Value_String(GetLabelName(idx)));
		}
	}
	return *_pValuesLabelName;
}

const ValueOwner& Sample::GetValuesLabelNameSuper()
{
	if (!_pValuesLabelSuperName) {
		size_t idx = _idx;
		size_t nItems = (_batchSize == 0)? 1 : _batchSize;
		_pValuesLabelSuperName.reset(new ValueOwner());
		_pValuesLabelSuperName->reserve(nItems);
		for (size_t iItem = 0; iItem < nItems; iItem++, idx++) {
			_pValuesLabelSuperName->push_back(new Value_String(GetLabelNameSuper(idx)));
		}
	}
	return *_pValuesLabelSuperName;
}

String Sample::ToString(const StringStyle& ss) const
{
	return String().Format("ml.cifar.Sample");
}

//------------------------------------------------------------------------------
// SampleList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SampleOwner
//------------------------------------------------------------------------------
void SampleOwner::Clear()
{
	for (Sample* pSample : *this) Sample::Delete(pSample);
	clear();
}

Gurax_EndModuleScope(ml_cifar)
