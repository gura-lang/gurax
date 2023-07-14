//==============================================================================
// Cifar.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Cifar
//------------------------------------------------------------------------------
Cifar::Cifar(bool superClassFlag) : _superClassFlag(superClassFlag), _nSamples(0),
							_pLabelSet(new LabelSet()), _pImageSet(new ImageSet())
{
}

bool Cifar::Read(Stream& stream)
{
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

String Cifar::ToString(const StringStyle& ss) const
{
	return String().Format("ml.cifar.Cifar:%zusamples", _nSamples);
}

//------------------------------------------------------------------------------
// CifarList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CifarOwner
//------------------------------------------------------------------------------
void CifarOwner::Clear()
{
	for (Cifar* pCifar : *this) Cifar::Delete(pCifar);
	clear();
}

Gurax_EndModuleScope(ml_cifar)
