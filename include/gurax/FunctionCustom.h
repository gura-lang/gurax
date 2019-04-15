//==============================================================================
// FunctionCustom.h
//==============================================================================
#ifndef GURAX_FUNCTIONCUSTOM_H
#define GURAX_FUNCTIONCUSTOM_H
#include "Function.h"

namespace Gurax {

//------------------------------------------------------------------------------
// FunctionCustom
//------------------------------------------------------------------------------
class FunctionCustom : public Function {
protected:
	const PUnit* _pPUnitBody;
public:
	FunctionCustom(Type type, const Symbol* pSymbol, DeclCallable* pDeclCallable,
				   const PUnit* pPUnitBody = nullptr) :
		Function(type, pSymbol, pDeclCallable), _pPUnitBody(pPUnitBody) {}
public:
	void SetPUnitBody(const PUnit* pPUnit) { _pPUnitBody = pPUnit; }
	const PUnit* GetPUnitBody() const { return _pPUnitBody; }
public:
	// Virtual functions of Function
	virtual void DoCall(Processor& processor, Argument& argument) const override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
};

}

#endif
