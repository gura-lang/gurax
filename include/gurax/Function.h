//==============================================================================
// Function.h
//==============================================================================
#ifndef GURAX_FUNCTION_H
#define GURAX_FUNCTION_H
#include "Referable.h"
#include "Help.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
class Function : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Function);
protected:
	RefPtr<HelpProvider> _pHelpProvider;
public:
	// Constructor
	Function() : _pHelpProvider(new HelpProvider()) {}
	// Copy constructor/operator
	Function(const Function& src) = delete;
	Function& operator=(const Function& src) = delete;
	// Move constructor/operator
	Function(Function&& src) = delete;
	Function& operator=(Function&& src) noexcept = delete;
protected:
	// Destructor
	~Function() = default;
public:
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	String ToString() const { return "(func)"; }
};

}

#endif
