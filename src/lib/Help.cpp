//==============================================================================
// Help.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
String Help::ToString(const StringStyle& ss) const
{
	String str;
	str += "Help";
	return str;
}

//------------------------------------------------------------------------------
// HelpList
//------------------------------------------------------------------------------
const Help* HelpList::Lookup(const Symbol* pLangCode) const
{
	for (const Help* pHelp : *this) {
		if (pHelp->GetLangCode()->IsIdentical(pLangCode)) return pHelp;
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// HelpOwner
//------------------------------------------------------------------------------
void HelpOwner::Clear()
{
	for (Help* pHelp : *this) Help::Delete(pHelp);
	clear();
}

//------------------------------------------------------------------------------
// HelpHolder
//------------------------------------------------------------------------------
void HelpHolder::AddHelp(Help* pHelp)
{
	pHelp->SetHelpHolder(GetWeakPtr());
	for (auto ppHelpIter = _helpOwner.begin(); ppHelpIter != _helpOwner.end(); ppHelpIter++) {
		Help* pHelpIter = *ppHelpIter;
		if (pHelpIter->GetLangCode()->IsIdentical(pHelp->GetLangCode())) {
			Help::Delete(pHelpIter);
			*ppHelpIter = pHelp;
			return;
 		}
	}
	_helpOwner.push_back(pHelp);
}

void HelpHolder::AddHelp(const Symbol* pLangCode, StringReferable* pDoc)
{
	AddHelp(new Help(pLangCode, pDoc));
}

}
