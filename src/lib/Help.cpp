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
void HelpHolder::AddHelp(const Symbol* pLangCode, StringReferable* pDoc)
{
	RefPtr<Help> pHelpNew(new Help(GetWeakPtr(), pLangCode, pDoc));
	for (auto ppHelp = _helpOwner.begin(); ppHelp != _helpOwner.end(); ppHelp++) {
		Help* pHelp = *ppHelp;
		if (pHelp->GetLangCode()->IsIdentical(pLangCode)) {
			Help::Delete(pHelp);
			*ppHelp = pHelpNew.release();
			return;
 		}
	}
	_helpOwner.push_back(pHelpNew.release());
}

}
