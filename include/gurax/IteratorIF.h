//==============================================================================
// IteratorIF.h
//==============================================================================
#ifndef GURAX_ITERATORIF_H
#define GURAX_ITERATORIF_H
#include "Referable.h"

namespace Gurax {

class Value;
class Processor;
class Expr_Block;

//------------------------------------------------------------------------------
// IteratorIF
//------------------------------------------------------------------------------
class IteratorIF {
public:
	Value* Each(Processor& processor, const Expr_Block& exprOfBlock);
public:
	virtual Value* NextValue() = 0;
};

}

#endif
