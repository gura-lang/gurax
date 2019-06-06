//==============================================================================
// Constructor.h
//==============================================================================
#ifndef GURAX_CONSTRUCTOR_H
#define GURAX_CONSTRUCTOR_H
#include "Function.h"

namespace Gurax {

class VTypeCustom;

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
class Constructor : public Function {
protected:
	VTypeCustom& _vtypeCustom;
	RefPtr<Function> _pFuncInitializer;
public:
	Constructor(VTypeCustom& vtypeCustom, Function* pFuncInitializer);
public:
	VTypeCustom& GetVTypeCustom() const { return _vtypeCustom; }
	const Function& GetFuncInitializer() const { return *_pFuncInitializer; }
public:
	// Virtual functions of Function
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
};

}

#endif
