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
	// Default constructor
	Tokenizer() : _cntRef(1) {}
	// Copy constructor/operator
	Tokenizer(const Tokenizer& obj) = delete;
	Tokenizer& operator=(const Tokenizer& obj) = delete;
	// Move constructor/operator
	Tokenizer(Tokenizer&& obj) = delete;
	Tokenizer& operator=(Tokenizer&& obj) noexcept = delete;
protected:
	// Destructor
	~Tokenizer() = default;
public:
	Gurax_DeclareReferenceAccessor(Tokenizer)
};

}

#endif
