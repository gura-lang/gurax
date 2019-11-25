//==============================================================================
// Help.h
//==============================================================================
#ifndef GURAX_HELP_H
#define GURAX_HELP_H
#include "Referable.h"
#include "DottedSymbol.h"

namespace Gurax {

class Help;

//------------------------------------------------------------------------------
// HelpList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE HelpList : public std::vector<Help*> {
public:
	const Help* Lookup(const Symbol* pLangCode) const;
};

//------------------------------------------------------------------------------
// HelpOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE HelpOwner : public HelpList {
public:
	~HelpOwner() { Clear(); }
	void Clear();
};

//------------------------------------------------------------------------------
// HelpHolder
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE HelpHolder : public Referable {
public:
	Gurax_DeclareReferable(HelpHolder);
protected:
	HelpOwner _helpOwner;
public:
	// Constructor
	HelpHolder() {}
	// Copy constructor/operator
	HelpHolder(const HelpHolder& src) = delete;
	HelpHolder& operator=(const HelpHolder& src) = delete;
	// Move constructor/operator
	HelpHolder(HelpHolder&& src) = delete;
	HelpHolder& operator=(HelpHolder&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~HelpHolder() = default;
public:
	void AddHelp(Help* pHelp);
	void AddHelp(const Symbol* pLangCode, StringReferable* pDoc);
	void AddHelp(const Symbol* pLangCode, const char* doc) {
		AddHelp(pLangCode, new StringReferable(doc));
	}
	const Help* GetDefault() const { return _helpOwner.empty()? nullptr : _helpOwner.front(); }
	const Help* Lookup(const Symbol* pLangCode) const { return _helpOwner.Lookup(pLangCode); }
	const HelpOwner& GetHelpOwner() const { return _helpOwner; }
};

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Help : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Help);
private:
	RefPtr<HelpHolder::WeakPtr> _pwHelpHolder;
	const Symbol* _pLangCode;
	RefPtr<StringReferable> _pDoc;
public:
	// Constructor
	Help(const Symbol* pLangCode, StringReferable* pDoc) :
		_pwHelpHolder(nullptr), _pLangCode(pLangCode), _pDoc(pDoc) {}
	// Copy constructor/operator
	Help(const Help& src) :
		_pwHelpHolder(src._pwHelpHolder.Reference()), _pLangCode(src._pLangCode), _pDoc(src._pDoc.Reference()) {}
	Help& operator=(const Help& src) = delete;
	// Move constructor/operator
	Help(Help&& src) = delete;
	Help& operator=(Help&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Help() = default;
public:
	void SetHelpHolder(HelpHolder::WeakPtr* pwHelpHolder) { _pwHelpHolder = pwHelpHolder; }
	const Symbol* GetLangCode() const { return _pLangCode; }
	const char* GetDoc() const { return _pDoc->GetString(); }
	const String& GetDocSTL() const { return _pDoc->GetStringSTL(); }
	const StringReferable& GetDocReferable() const { return *_pDoc; }
	Help* Clone() const { return new Help(*this); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Help& help) const { return this == &help; }
	virtual bool IsEqualTo(const Help& help) const { return IsIdentical(help); }
	bool IsLessThan(const Help& help) const { return this < &help; }
	virtual String ToString(const StringStyle& ss) const;
};

}

#endif
