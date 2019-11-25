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
	_helpOwner.push_back(new Help(GetWeakPtr(), pLangCode, pDoc));
}

void HelpHolder::AddHelp(const Symbol* pLangCode, String formatName, StringReferable* pDoc)
{
	_helpOwner.push_back(new Help(GetWeakPtr(), pLangCode, std::move(formatName), pDoc));
}

}
