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
	_pwHelpHolder(nullptr), _pLangCode(pLangCode), _pDoc(nullptr), _pTmplDoc(pTmplDoc)
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

String Help::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Help:%s", GetLangCode()->GetName());
	return str;
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

void HelpHolder::AddHelpTmpl(const Symbol* pLangCode, const char* doc)
{
	RefPtr<Template> pTmpl(new Template());
	bool autoIndentFlag = true;
	bool appendLastEOLFlag = true;
	if (pTmpl->ParseString_(doc, autoIndentFlag, appendLastEOLFlag)) {
		AddHelp(new Help(pLangCode, pTmpl.release()));
		return;
	}
	String str;
	for (Error* pError : Error::GetErrorOwner()) {
		str += pError->MakeMessage();
		str += "\n";
	}
	Error::Clear();
	AddHelp(pLangCode, str.c_str());
}

}
