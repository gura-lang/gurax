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
	return true;
}

String PairSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.cifar.PairSet:%zusamples:%zuchannels:%zurows:%zucols:%zuclasses:%zusuper-classes",
		_nSamples, ImageSet::nChannels, ImageSet::nRowsImage, ImageSet::nColsImage, GetLabelSet().GetNClasses(), GetLabelSet().GetNClassesSuper());
}

//------------------------------------------------------------------------------
// CifarList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CifarOwner
//------------------------------------------------------------------------------
void CifarOwner::Clear()
{
	for (PairSet* pCifar : *this) PairSet::Delete(pCifar);
	clear();
}

Gurax_EndModuleScope(ml_cifar)
