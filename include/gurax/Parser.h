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
	RefPtr<Expr_Root> _pExprRoot;
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
	Expr_Root& GetExprRoot() { return *_pExprRoot; }
	const Expr_Root& GetExprRoot() const { return *_pExprRoot; }
	static Expr_Root* ParseStream(Stream& stream);
	static Expr_Root* ParseString(const char* text);
	void ParseChar(char ch) { _pTokenizer->FeedChar(ch); }
private:
	bool ReduceOneToken();
	bool ReduceTwoTokens();
	bool ReduceThreeTokens();
	bool ReduceFourTokens();
	bool ReduceFiveTokens();
	bool EmitExpr(ExprLink& exprLink, Expr* pExpr);
	Expr_Block* CreateExprBlock(RefPtr<Token>& pToken);
	template<typename T_TokenP, typename... Args>
	void IssueError(const ErrorType& errorType, T_TokenP& pToken, const char* format, const Args&... args) {
		Error::IssueAt(errorType, _pTokenizer->GetPathNameSrcReferable()->Reference(),
					   pToken->GetLineNoTop(), pToken->GetLineNoBtm(), format, args...);
	}
	template<typename T_TokenP, typename... Args>
	void IssueError(const ErrorType& errorType, T_TokenP& pTokenTop, T_TokenP& pTokenBtm,
					const char* format, const Args&... args) {
		Error::IssueAt(errorType, _pTokenizer->GetPathNameSrcReferable()->Reference(),
					   pTokenTop->GetLineNoTop(), pTokenBtm->GetLineNoBtm(), format, args...);
	}
public:
	virtual void FeedToken(RefPtr<Token> pToken) override;
private:
	void SetSourceInfo(Expr* pExpr, int lineNoTop, int lineNoBtm) const {
		pExpr->SetSourceInfo(_pTokenizer->GetPathNameSrcReferable()->Reference(), lineNoTop, lineNoBtm);
	}
	void SetSourceInfo(RefPtr<Expr>& pExpr, int lineNoTop, int lineNoBtm) const {
		SetSourceInfo(pExpr.get(), lineNoTop, lineNoBtm);
	}
};

}

#endif
