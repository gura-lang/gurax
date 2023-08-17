//==============================================================================
// LabelSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// LabelSet
//------------------------------------------------------------------------------
void LabelSet::Add(UInt8 label)
{
	_labels += label;
	if (_nClasses <= label) _nClasses = label + 1;
}

void LabelSet::Add(UInt8 labelSuper, UInt8 label)
{
	_labelsSuper += labelSuper;
	_labels += label;
	if (_nClasses <= label) _nClasses = label + 1;
	if (_nClassesSuper <= labelSuper) _nClassesSuper = labelSuper + 1;
}

String LabelSet::GetLabelName(size_t iSample) const
{
	UInt8 label = GetLabel(iSample);
	return (label < _labelNames.size())? _labelNames[label] : String().Format("%d", label);
}

String LabelSet::GetLabelNameSuper(size_t iSample) const
{
	UInt8 labelSuper = GetLabelSuper(iSample);
	return (labelSuper < _labelNamesSuper.size())? _labelNamesSuper[labelSuper] : String().Format("%d", labelSuper);
}

String LabelSet::ToString(const StringStyle& ss) const
{
	return String().Format("ml.cifar.LabelSet");
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

Gurax_EndModuleScope(ml_cifar)
