//==============================================================================
// Cifar.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Cifar
//------------------------------------------------------------------------------
Cifar::Cifar(bool superClassFlag) : _superClassFlag(superClassFlag), _nImages(0),
							_pLabelSet(new LabelSet()), _pImageSet(new ImageSet())
{
}

bool Cifar::Read(Stream& stream)
{
	_nImages = 0;
	using Pack = struct {
		UInt8 labelSuper;
		UInt8 label;
	};
	UInt8 buffImage[ImageSet::nRowsImage * ImageSet::nColsImage];
	for (;;) {
		if (_superClassFlag) {
			Pack pack;
			if (stream.Read(&pack, sizeof(pack)) < sizeof(pack)) return false;
			_pLabelSet->Add(pack.labelSuper, pack.label);
		} else {
			UInt8 label;
			if (stream.Read(&label, sizeof(label)) < sizeof(label)) return false;
			_pLabelSet->Add(label);
		}
		if (stream.Read(buffImage, sizeof(buffImage)) < sizeof(buffImage)) return false;
		_pImageSet->Add(buffImage);
		_nImages++;
	}
	return false;
}

String Cifar::ToString(const StringStyle& ss) const
{
	return String().Format("ml.cifar.Cifar");
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
