//==============================================================================
// Module.h
//==============================================================================
#ifndef GURAX_MODULE_H
#define GURAX_MODULE_H
#include "Referable.h"
#include "Help.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Module
//------------------------------------------------------------------------------
class Module : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Module);
protected:
	RefPtr<HelpProvider> _pHelpProvider;
public:
	// Constructor
	Module() : _pHelpProvider(new HelpProvider()) {}
	// Copy constructor/operator
	Module(const Module& src) = delete;
	Module& operator=(const Module& src) = delete;
	// Move constructor/operator
	Module(Module&& src) = delete;
	Module& operator=(Module&& src) noexcept = delete;
protected:
	// Destructor
	~Module() = default;
public:
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Module* pModule) const { return this == pModule; }
	bool IsEqualTo(const Module* pModule) const { return IsIdentical(pModule); }
	bool IsLessThan(const Module* pModule) const { return this < pModule; }
	String ToString() const { return "(module)"; }
};

}

#endif
