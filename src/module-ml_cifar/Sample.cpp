//==============================================================================
// Sample.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Sample
//------------------------------------------------------------------------------
Sample::Sample(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, Double numCeil, const Image::Format& format, size_t iSample) :
		_pSampleSet(pSampleSet), _elemType(elemType), _numCeil(numCeil), _format(format), _iSample(iSample)
{
}

const Array& Sample::GetArrayInput()
{
	_pSampleSet->GetImageSet().ExtractAsArray(_pArrayInput, _elemType, _numCeil, _iSample);
	return *_pArrayInput;
}

const Array& Sample::GetArrayResult()
{
	if (!_pArrayResult) {
		_pArrayResult.reset(Array::Create(_elemType, DimSizes(_pSampleSet->GetLabelSet().GetNClasses())));
		_pArrayResult->IndexSetDouble(GetLabel(), 1.);
	}
	return *_pArrayResult;
}

const Image& Sample::GetImage()
{
	_pSampleSet->GetImageSet().ExtractAsImage(_pImage, _format, _iSample);
	return *_pImage;
}

UInt8 Sample::GetLabel() const
{
	return _pSampleSet->GetLabelSet().GetLabel(_iSample);
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
