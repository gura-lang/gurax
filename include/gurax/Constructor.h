//==============================================================================
// Constructor.h
//==============================================================================
#ifndef GURAX_CONSTRUCTOR_H
#define GURAX_CONSTRUCTOR_H
#include "Function.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
class Constructor : public Function {
protected:
	VType& _vtype;
	RefPtr<Function> _pFuncInitializer;
public:
	Constructor(VType& vtype, Function* pFuncInitializer);
public:
	VType& GetVType() const { return _vtype; }
	const Function& GetFuncInitializer() const { return *_pFuncInitializer; }
public:
	// Virtual functions of Function
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
};

}

#endif
