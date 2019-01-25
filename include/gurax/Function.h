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
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Function& function) const { return this == &function; }
	bool IsEqualTo(const Function& function) const { return IsIdentical(function); }
	bool IsLessThan(const Function& function) const { return this < &function; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(function)"; }
};

}

#endif
