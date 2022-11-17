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
class GURAX_DLLDECLARE FunctionCustom : public Function {
protected:
	RefPtr<Expr> _pExprBody;
	const PUnit* _pPUnitBody;
	RefPtr<Frame> _pFrameHolder;	// this may be nullptr
public:
	FunctionCustom(Type type, const Symbol* pSymbol, DeclCallable* pDeclCallable,
				   Expr* pExprBody, HelpHolder* pHelpHolder = nullptr);
public:
	void SetFrameHolder(Frame* pFrameHolder) { _pFrameHolder.reset(pFrameHolder); }
public:
	// Virtual functions of Function
	virtual bool IsCustom() const override { return true; }
	virtual const Expr& GetExprBody() const override { return *_pExprBody; }
	virtual const PUnit* GetPUnitBody() const override { return _pPUnitBody; }
	virtual void DoExec(Processor& processor, Argument& argument) const override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
};

}

#endif
