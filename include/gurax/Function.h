//==============================================================================
// Function.h
//==============================================================================
#ifndef GURAX_FUNCTION_H
#define GURAX_FUNCTION_H
#include "DeclCaller.h"
#include "Help.h"
#include "Frame.h"
#include "Argument.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
class Function : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Function);
protected:
	const Symbol* _pSymbol;
	RefPtr<DeclCaller> _pDeclCaller;
	RefPtr<HelpProvider> _pHelpProvider;
	RefPtr<Frame::WeakPtr> _pwFrameParent;
public:
	// Constructor
	Function() : Function(Symbol::Empty, new DeclCaller(), new HelpProvider()) {}
	Function(const Symbol* pSymbol, DeclCaller* pDeclCaller) : Function(pSymbol, pDeclCaller, new HelpProvider()) {}
	Function(const Symbol* pSymbol, DeclCaller* pDeclCaller, HelpProvider* pHelpProvider) :
		_pSymbol(pSymbol), _pDeclCaller(pDeclCaller), _pHelpProvider(pHelpProvider) {}
	// Copy constructor/operator
	Function(const Function& src) = delete;
	Function& operator=(const Function& src) = delete;
	// Move constructor/operator
	Function(Function&& src) = delete;
	Function& operator=(Function&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Function() = default;
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const DeclCaller& GetDeclCaller() const { return *_pDeclCaller; }
	void SetFrameParent(Frame* pFrameParent) { _pwFrameParent.reset(pFrameParent->GetWeakPtr()); }
	Frame* LockFrameParent() { return _pwFrameParent? _pwFrameParent->Lock() : nullptr; }
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Function& function) const { return this == &function; }
	bool IsEqualTo(const Function& function) const { return IsIdentical(function); }
	bool IsLessThan(const Function& function) const { return this < &function; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(function)"; }
public:
	// Virtual functions
	virtual Value* Eval(const Argument& argument) const = 0;
};

}

#endif
