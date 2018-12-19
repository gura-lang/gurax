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
	RefPtr<Tokenizer> _pTokenizer;
	ExprOwner* _pExprOwner = nullptr;
	Expr* _pExprParent = nullptr;
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
	void ParseChar(char ch) { _pTokenizer->FeedChar(ch); }
private:
	bool EmitExpr(ExprOwner& exprOwner, const Expr* pExprParent, Expr* pExpr);
	bool ReduceOneToken();
	bool ReduceTwoTokens();
	bool ReduceThreeTokens();
	bool ReduceFourTokens();
	bool ReduceFiveTokens();
	void IssueError(const ErrorType& errorType, const char* format, ...);
public:
	virtual void FeedToken(RefPtr<Token> pToken) override;
};

}

#endif
