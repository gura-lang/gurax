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
	RefPtr<Expr> _pExprBody;
	const PUnit* _pPUnitBody;
public:
	FunctionCustom(Type type, const Symbol* pSymbol, DeclCallable* pDeclCallable, Expr* pExprBody);
public:
	// Virtual functions of Function
	virtual const Expr& GetExprBody() const override { return *_pExprBody; }
	virtual const PUnit* GetPUnitBody() const override { return _pPUnitBody; }
	virtual void DoExec(Processor& processor, Argument& argument) const override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
};

}

#endif
