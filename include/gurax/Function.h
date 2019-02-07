//==============================================================================
// Function.h
//==============================================================================
#ifndef GURAX_FUNCTION_H
#define GURAX_FUNCTION_H
#include "DeclCaller.h"
#include "Help.h"
#include "Frame.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
class Function : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Function);
protected:
	RefPtr<Frame::WeakPtr> _pwFrame;
	RefPtr<DeclCaller> _pDeclCaller;
	RefPtr<HelpProvider> _pHelpProvider;
public:
	// Constructor
	Function() : Function(new DeclCaller(), new HelpProvider()) {}
	Function(DeclCaller* pDeclCaller) : Function(pDeclCaller, new HelpProvider()) {}
	Function(DeclCaller* pDeclCaller, HelpProvider* pHelpProvider) :
		_pDeclCaller(pDeclCaller), _pHelpProvider(pHelpProvider) {}
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
	void SetFrame(Frame* pFrame) { _pwFrame.reset(pFrame->GetWeakPtr()); }
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
