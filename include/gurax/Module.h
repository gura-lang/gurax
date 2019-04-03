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
	Module() = delete;
	Module(Frame* pFrameOuter) : Module(DottedSymbol::Empty.Reference(), pFrameOuter) {}
	Module(DottedSymbol* pDottedSymbol, Frame* pFrameOuter) :
		_pDottedSymbol(pDottedSymbol), _pHelpProvider(new HelpProvider()), _pFrame(new Frame_Module(pFrameOuter)) {}
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
	void Assign(const Symbol* pSymbol, Value* pValue) { GetFrame().Assign(pSymbol, pValue); }
	void Assign(const char* name, Value* pValue) { GetFrame().Assign(name, pValue); }
	void Assign(VType& vtype) { GetFrame().Assign(vtype); }
	void Assign(Function* pFunction) { GetFrame().Assign(pFunction); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Module& module) const { return this == &module; }
	bool IsEqualTo(const Module& module) const { return IsIdentical(module); }
	bool IsLessThan(const Module& module) const { return this < &module; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
