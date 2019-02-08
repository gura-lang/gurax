//==============================================================================
// Module.h
//==============================================================================
#ifndef GURAX_MODULE_H
#define GURAX_MODULE_H
#include "Referable.h"
#include "Help.h"
#include "Frame.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Module
//------------------------------------------------------------------------------
class Module : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Module);
protected:
	RefPtr<DottedSymbol> _pDottedSymbol;
	RefPtr<HelpProvider> _pHelpProvider;
	RefPtr<Frame> _pFrame;
public:
	// Constructor
	Module() : Module(DottedSymbol::Empty.Reference()) {}
	Module(DottedSymbol* pDottedSymbol) :
		_pDottedSymbol(pDottedSymbol), _pHelpProvider(new HelpProvider()), _pFrame(Frame::CreateSource()) {}
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
	const DottedSymbol& GetDottedSymbol() const { return *_pDottedSymbol; }
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	Frame& GetFrame() { return *_pFrame; }
	const Frame& GetFrame() const { return *_pFrame; }
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Module& module) const { return this == &module; }
	bool IsEqualTo(const Module& module) const { return IsIdentical(module); }
	bool IsLessThan(const Module& module) const { return this < &module; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
