//==============================================================================
// Tokenizer.h
//==============================================================================
#ifndef GURAX_TOKENIZER_H
#define GURAX_TOKENIZER_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Tokenizer
//------------------------------------------------------------------------------
class Tokenizer : public Referable {
public:
	// Default constructor
	Tokenizer() {}
	// Copy constructor/operator
	Tokenizer(const Tokenizer& src) = delete;
	Tokenizer& operator=(const Tokenizer& src) = delete;
	// Move constructor/operator
	Tokenizer(Tokenizer&& src) = delete;
	Tokenizer& operator=(Tokenizer&& src) noexcept = delete;
protected:
	// Destructor
	~Tokenizer() = default;
public:
	Gurax_DeclareReferable(Tokenizer);
};

}

#endif
