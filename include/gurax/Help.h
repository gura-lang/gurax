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
	void AddHelp(const Symbol* pLangCode, String doc);
	void AddHelp(const Symbol* pLangCode, String formatName, String doc);
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
	String _formatName;
	String _doc;
public:
	// Constructor
	Help(HelpHolder::WeakPtr *pwHelpHolder, const Symbol* pLangCode, String doc) :
		_pwHelpHolder(pwHelpHolder), _pLangCode(pLangCode), _doc(std::move(doc)) {}
	Help(HelpHolder::WeakPtr *pwHelpHolder, const Symbol* pLangCode, String formatName, String doc) :
		_pwHelpHolder(pwHelpHolder), _pLangCode(pLangCode),
		_formatName(std::move(formatName)), _doc(std::move(doc)) {}
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
	const char* GetFormatName() const { return _formatName.c_str(); }
	const char* GetDoc() const { return _doc.c_str(); }
};


}

#endif
