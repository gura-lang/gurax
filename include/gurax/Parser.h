//==============================================================================
// Parser.h
//==============================================================================
#ifndef GURAX_PARSER_H
#define GURAX_PARSER_H
#include "Tokenizer.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Parser : public Referable, public Tokenizer::TokenWatcher {
private:
	UniquePtr<Tokenizer> _pTokenizer;
public:
	// Constructor
	Parser() = delete;
	Parser(String pathNameSrc);
	// Copy constructor/operator
	Parser(const Parser& src) = delete;
	Parser& operator=(const Parser& src) = delete;
	// Move constructor/operator
	Parser(Parser&& src) = delete;
	Parser& operator=(Parser&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Parser() = default;
public:
	// Referable accessor
	Gurax_DeclareReferable(Parser);
public:
	virtual void FeedToken(UniquePtr<Token> pToken) override;
};

}

#endif
