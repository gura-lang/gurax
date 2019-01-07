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
public:
	// Referable declaration
	Gurax_DeclareReferable(Parser);
private:
	RefPtr<Tokenizer> _pTokenizer;
	ExprOwner* _pExprOwner = nullptr;
	Expr* _pExprParent = nullptr;
public:
	// Constructor
	Parser() = delete;
	explicit Parser(String pathNameSrc);
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
	void ParseChar(char ch) { _pTokenizer->FeedChar(ch); }
private:
	bool EmitExpr(ExprOwner& exprOwner, const Expr* pExprParent, Expr* pExpr);
	bool ReduceOneToken();
	bool ReduceTwoTokens();
	bool ReduceThreeTokens();
	bool ReduceFourTokens();
	bool ReduceFiveTokens();
	void IssueError(const ErrorType& errorType, const Token* pToken, const char* format, ...);
	void IssueError(const ErrorType& errorType, RefPtr<Token>& pToken, const char* format, ...);
public:
	virtual void FeedToken(RefPtr<Token> pToken) override;
};

}

#endif
