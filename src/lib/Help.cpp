//==============================================================================
// Help.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
Help::Help(const Symbol* pLangCode, StringReferable* pDoc) :
	_pwHelpHolder(nullptr), _pLangCode(pLangCode), _pDoc(pDoc), _pTmplDoc(nullptr)
{
}

Help::Help(const Symbol* pLangCode, Template* pTmplDoc) :
	_pwHelpHolder(nullptr), _pLangCode(pLangCode), _pDoc(StringReferable::Empty.Reference()),
	_pTmplDoc(pTmplDoc)
{
}

Help::Help(const Help& src) :
	_pwHelpHolder(src._pwHelpHolder.Reference()), _pLangCode(src._pLangCode),
	_pDoc(src._pDoc.Reference()), _pTmplDoc(Template::Reference(src._pTmplDoc))
{
}

Help::~Help()
{
	Template::Delete(_pTmplDoc);
}

const Template* Help::GetTmplDoc()
{
	if (!_pTmplDoc) {
		_pTmplDoc = new Template();
		bool autoIndentFlag = true;
		bool appendLastEOLFlag = true;
		if (!_pTmplDoc->ParseString(GetDoc(), autoIndentFlag, appendLastEOLFlag) ||
			!_pTmplDoc->PrepareAndCompose()) return nullptr;
	}
	return _pTmplDoc;
}

String Help::ToString(const StringStyle& ss) const
{
	return String().Format("Help:%s", GetLangCode()->GetName());
}

//------------------------------------------------------------------------------
// HelpList
//------------------------------------------------------------------------------
const Help* HelpList::Lookup(const Symbol* pLangCode) const
{
	if (!pLangCode) return empty()? nullptr : front();
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

void HelpHolder::AddHelp(const Symbol* pLangCode, const char* doc)
{
	while (String::IsSpace(*doc)) doc++;
	AddHelp(pLangCode, new StringReferable(doc));
}

const Help* HelpHolder::LookupLoose(const Symbol* pLangCode) const
{
	const Help* pHelp = _helpOwner.Lookup(pLangCode);
	if (pHelp) return pHelp;
	return GetDefault();
}

}
