//==============================================================================
// IteratorIF.h
//==============================================================================
#ifndef GURAX_ITERATORIF_H
#define GURAX_ITERATORIF_H
#include "DeclCallable.h"

namespace Gurax {

class Value;
class Processor;
class Expr_Block;

//------------------------------------------------------------------------------
// IteratorIF
//------------------------------------------------------------------------------
class IteratorIF {
public:
	Value* Each(Processor& processor, const Expr_Block& exprOfBlock, DeclCallable::Flags flags);
public:
	virtual Value* NextValue() = 0;
};

}

#endif
