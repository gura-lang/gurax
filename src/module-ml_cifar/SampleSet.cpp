//==============================================================================
// SampleSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// SampleSet
//------------------------------------------------------------------------------
SampleSet::SampleSet(bool superClassFlag) : _hasSuperClassFlag(superClassFlag), _nSamples(0),
							_pLabelSet(new LabelSet()), _pImageSet(new ImageSet())
{
}

bool SampleSet::Read(Stream& stream)
{
	struct Pack {
		UInt8 labelSuper;
		UInt8 label;
	};
	UInt8 buffImage[ImageSet::nChannels * ImageSet::nRows * ImageSet::nCols];
	for (;;) {
		if (_hasSuperClassFlag) {
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
		_pImageSet->Add(buffImage, sizeof(buffImage));
		_nSamples++;
	}
	_indices.reserve(_nSamples);
	for (size_t i = 0; i < _nSamples; i++) _indices.push_back(i);
	return true;
}

String SampleSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.cifar.SampleSet:%zusamples:%zuchannels:%zurows:%zucols:%zuclasses:%zusuper-classes",
		_nSamples, ImageSet::nChannels, ImageSet::nRows, ImageSet::nCols, GetLabelSet().GetNClasses(), GetLabelSet().GetNClassesSuper());
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
Iterator_Each::Iterator_Each(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, const Image::Format& format,
								size_t batchSize, Double numCeil, bool defaultSuperClassFlag) :
	_pSampleSet(pSampleSet), _elemType(elemType), _format(format),
	_batchSize(batchSize), _numCeil(numCeil), _idx(0), _defaultSuperClassFlag(defaultSuperClassFlag)
{
}

size_t Iterator_Each::GetLength() const
{
	size_t nChars = (_batchSize == 0)? 1 : _batchSize;
	return _pSampleSet->GetNSamples() / nChars;
}

Value* Iterator_Each::DoNextValue()
{
	size_t nChars = (_batchSize == 0)? 1 : _batchSize;
	if (_idx + nChars > _pSampleSet->GetNSamples()) return nullptr;
	RefPtr<Sample> pSample(new Sample(_pSampleSet->Reference(), _elemType, _format, _batchSize, _numCeil, _idx, _defaultSuperClassFlag));
	_idx += nChars;
	return new Value_Sample(pSample.release());
}

String Iterator_Each::ToString(const StringStyle& ss) const
{
	return String().Format("ml.cifar.Each:%zu/%zu", _idx, _pSampleSet->GetNSamples());
}

Gurax_EndModuleScope(ml_cifar)
