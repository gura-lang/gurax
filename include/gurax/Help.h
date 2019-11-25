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
	void AddHelp(const Symbol* pLangCode, StringReferable* pDoc);
	void AddHelp(const Symbol* pLangCode, const char* doc) {
		AddHelp(pLangCode, new StringReferable(doc));
	}
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
	Help(HelpHolder::WeakPtr *pwHelpHolder, const Symbol* pLangCode, StringReferable* pDoc) :
		_pwHelpHolder(pwHelpHolder), _pLangCode(pLangCode), _pDoc(pDoc) {}
	// Copy constructor/operator
	Help(const Help& src) = delete;
	Help& operator=(const Help& src) = delete;
	// Move constructor/operator
	Help(Help&& src) = delete;
	Help& operator=(Help&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Help() = default;
public:
	const Symbol* GetLangCode() const { return _pLangCode; }
	const char* GetDoc() const { return _pDoc->GetString(); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Help& help) const { return this == &help; }
	virtual bool IsEqualTo(const Help& help) const { return IsIdentical(help); }
	bool IsLessThan(const Help& help) const { return this < &help; }
	virtual String ToString(const StringStyle& ss) const;
};

}

#endif
