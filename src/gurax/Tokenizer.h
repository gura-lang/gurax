//==============================================================================
// Tokenizer.h
//==============================================================================
#ifndef GURAX_TOKENIZER_H
#define GURAX_TOKENIZER_H
#include "Common.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Tokenizer
//------------------------------------------------------------------------------
class Tokenizer {
protected:
	int _cntRef;
public:
	Tokenizer() : _cntRef(1) {}
public:
	Tokenizer *Reference() const { const_cast<Tokenizer *>(this)->_cntRef++; return const_cast<Tokenizer *>(this); }
	static void Delete(Tokenizer *p) { if (--p->_cntRef) delete p; }
protected:
	~Tokenizer() {}
};

}

#endif
