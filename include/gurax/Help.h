//==============================================================================
// Help.h
//==============================================================================
#ifndef GURAX_HELP_H
#define GURAX_HELP_H
#include "Referable.h"
#include "Symbol.h"

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
// HelpProvider
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE HelpProvider : public Referable {
public:
	Gurax_DeclareReferable(HelpProvider);
protected:
	HelpOwner _helpOwner;
public:
	// Constructor
	HelpProvider() {}
	// Copy constructor/operator
	HelpProvider(const HelpProvider& src) = delete;
	HelpProvider& operator=(const HelpProvider& src) = delete;
	// Move constructor/operator
	HelpProvider(HelpProvider&& src) = delete;
	HelpProvider& operator=(HelpProvider&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~HelpProvider() = default;
public:
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
	RefPtr<HelpProvider::WeakPtr> _pwHelpProvider;
	const Symbol* _pLangCode;
	String _formatName;
	String _doc;
public:
	// Constructor
	Help(HelpProvider::WeakPtr *pwHelpProvider, const Symbol* pLangCode, String formatName, String doc) :
		_pwHelpProvider(pwHelpProvider), _pLangCode(pLangCode),
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
