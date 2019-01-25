//==============================================================================
// Token.h
//==============================================================================
#ifndef GURAX_TOKEN_H
#define GURAX_TOKEN_H
#include "Referable.h"
#include "Operator.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TokenType
//------------------------------------------------------------------------------
struct GURAX_DLLDECLARE TokenType {
public:
	int category;
	const char* typeName;
	const char* symbol;
	OpType opType;
public:
	static const TokenType Begin;
	static const TokenType Assign;
	static const TokenType AssignAdd;
	static const TokenType AssignSub;
	static const TokenType AssignMul;
	static const TokenType AssignDiv;
	static const TokenType AssignMod;
	static const TokenType AssignPow;
	static const TokenType AssignOr;
	static const TokenType AssignAnd;
	static const TokenType AssignXor;
	static const TokenType AssignShl;
	static const TokenType AssignShr;
	static const TokenType Pair;
	static const TokenType OrOr;
	static const TokenType AndAnd;
	static const TokenType Not;
	static const TokenType Contains;
	static const TokenType Lt;
	static const TokenType Gt;
	static const TokenType Le;
	static const TokenType Ge;
	static const TokenType Cmp;
	static const TokenType Eq;
	static const TokenType Ne;
	static const TokenType Seq;
	static const TokenType Or;
	static const TokenType Xor;
	static const TokenType And;
	static const TokenType Shl;
	static const TokenType Shr;
	static const TokenType Add;
	static const TokenType Sub;
	static const TokenType Mul;
	static const TokenType Div;
	static const TokenType Mod;
	static const TokenType ModMod;
	static const TokenType Dot;
	static const TokenType Cross;
	static const TokenType Gear;
	static const TokenType Concat;
	static const TokenType Difference;
	static const TokenType Intersection;
	static const TokenType Union;
	static const TokenType Question;
	static const TokenType Inv;
	static const TokenType Pow;
	static const TokenType Quote;
	static const TokenType Colon;
	static const TokenType ColonAfterSuffix;
	static const TokenType Period;
	static const TokenType ColonColon;
	static const TokenType ColonAsterisk;
	static const TokenType ColonAnd;
	static const TokenType LParenthesis;
	static const TokenType RParenthesis;
	static const TokenType LBrace;
	static const TokenType RBrace;
	static const TokenType LBlockParam;
	static const TokenType RBlockParam;
	static const TokenType LBracket;
	static const TokenType RBracket;
	static const TokenType Comma;
	static const TokenType Semicolon;
	static const TokenType EndOfLine;
	static const TokenType Number;
	static const TokenType NumberSuffixed;
	static const TokenType String;
	static const TokenType StringSuffixed;
	static const TokenType Binary;
	static const TokenType EmbedString;
	static const TokenType Symbol;
	static const TokenType EndOfFile;
	static const TokenType Expr;
	static const TokenType Space;
	static const TokenType Escape;
	static const TokenType CommentLine;
	static const TokenType CommentBlock;
	static const TokenType DoubleChars;
	static const TokenType TripleChars;
	static const TokenType Unknown;
	static const TokenType *opTypeToTokenTypeMap[static_cast<size_t>(OpType::max)];
public:
	TokenType(int category, const char* typeName, const char* symbol, OpType opType);
	bool IsIdentical(const TokenType &tokenType) const { return this == &tokenType; }
	bool HasSourceSymbol() const { return !(symbol[0] == '[' && symbol[1] != '\0'); }
};

//------------------------------------------------------------------------------
// Token
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Token : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Token);
public:
	enum class Precedence { LT, EQ, GT, Error, };
private:
	const TokenType& _tokenType;
	int _lineNoTop;
	int _lineNoBtm;
	RefPtr<StringReferable> _pValue;	// for Symbol, Space, Escape, Number, NumberSuffixed,
										//     CommentLine, CommentBlock, String, StringSuffixed
										//     Binary and EmbedString
	RefPtr<StringReferable> _pSuffix;	// for NumberSuffixed, StringSuffixed
	RefPtr<StringReferable> _pSource;	// for NumberSuffixed, StringSuffixed
	RefPtr<Expr> _pExpr;				// for Expr
	RefPtr<ExprOwner> _pExprOwner;		// for LBrace, LBlockParam, LBracket and LParenthesis
	RefPtr<ExprOwner> _pExprOwnerEx;	// for LBrace
	bool _itererFlag;					// for LParenthesis
public:
	static const Precedence _precMatrix[][31];
public:
	// Constructor
	explicit Token(Expr* pExpr) :
		_tokenType(TokenType::Expr), _lineNoTop(pExpr->GetLineNoTop()), _lineNoBtm(pExpr->GetLineNoBtm()),
		_pExpr(pExpr), _itererFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm) :
		_tokenType(tokenType), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm), _itererFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm, ExprOwner* pExprOwner) :
		_tokenType(tokenType), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm),
		_pExprOwner(pExprOwner), _itererFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm, StringReferable* pValue) :
		_tokenType(tokenType), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm),
		_pValue(pValue), _itererFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm, String value) :
		Token(tokenType, lineNoTop, lineNoBtm, new StringReferable(std::move(value))) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm,
		  StringReferable* pValue, StringReferable* pSuffix) :
		_tokenType(tokenType), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm),
		_pValue(pValue), _pSuffix(pSuffix), _itererFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm, String value, String suffix) :
		Token(tokenType, lineNoTop, lineNoBtm, new StringReferable(std::move(value)),
			  new StringReferable(std::move(suffix))) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm,
		  StringReferable* pValue, StringReferable* pSuffix, StringReferable* pSource) :
		_tokenType(tokenType), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm),
		_pValue(pValue), _pSuffix(pSuffix), _pSource(pSource), _itererFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm, String value, String suffix, String source) :
		Token(tokenType, lineNoTop, lineNoBtm, new StringReferable(std::move(value)),
			  new StringReferable(std::move(suffix)), new StringReferable(std::move(source))) {}
	// Copy constructor/operator
	Token(const Token& src) = delete;
	Token& operator=(const Token& src) = delete;
	// Move constructor/operator
	Token(Token&& src) = delete;
	Token& operator=(Token&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Token() = default;
public:
	static void Bootup();
	bool IsType(const TokenType& tokenType) const { return _tokenType.IsIdentical(tokenType); }
	bool IsOpenToken() const {
		return IsType(TokenType::LParenthesis) || IsType(TokenType::LBrace) ||
			IsType(TokenType::LBracket) || IsType(TokenType::LBlockParam);
	}
	bool IsCloseToken() const {
		return IsType(TokenType::RParenthesis) || IsType(TokenType::RBrace) ||
			IsType(TokenType::RBracket) || IsType(TokenType::RBlockParam);
	}
	bool IsSeparatorToken() const {
		return IsType(TokenType::EndOfLine) || IsType(TokenType::EndOfFile) ||
			IsType(TokenType::Comma) || IsType(TokenType::Semicolon);
	}
	bool IsSuffixToken() const {
		return IsType(TokenType::Add) ||
			IsType(TokenType::Mul) || IsType(TokenType::Question);
	}
public:
	int GetLineNoTop() const { return _lineNoTop; }
	int GetLineNoBtm() const { return _lineNoBtm; }
	int GetCategory() const { return _tokenType.category; }
	const char *GetTypeName() const { return _tokenType.typeName; }
	const char *GetSymbol() const { return _tokenType.symbol; }
	OpType GetOpType() const { return _tokenType.opType; }
	const char* GetValue() const { return _pValue->GetString(); }
	const char* GetSuffix() const { return _pSuffix->GetString(); }
	const char* GetSource() const { return _pSource->GetString(); }
	const String& GetValueSTL() const { return _pValue->GetStringSTL(); }
	const String& GetSuffixSTL() const { return _pSuffix->GetStringSTL(); }
	const String& GetSourceSTL() const { return _pSource->GetStringSTL(); }
	const StringReferable* GetValueReferable() const { return _pValue.get(); }
	const StringReferable* GetSuffixReferable() const { return _pSuffix.get(); }
	const StringReferable* GetSourceReferable() const { return _pSource.get(); }
	void AppendValue(const char* value) { _pValue->GetStringSTL().append(value); }
	void AppendValue(const String& value) { _pValue->GetStringSTL().append(value); }
	void SetExpr(Expr* pExpr) { _pExpr.reset(pExpr); }
	void SetExprOwner(ExprOwner* pExprOwner) { _pExprOwner.reset(pExprOwner); }
	void SetExprOwnerEx(ExprOwner* pExprOwnerEx) { _pExprOwnerEx.reset(pExprOwnerEx); }
	Expr* GetExpr() { return _pExpr.get(); }
	ExprOwner& GetExprOwner() { return *_pExprOwner; }
	ExprOwner& GetExprOwnerEx() { return *_pExprOwnerEx; }
	bool HasExpr() { return _pExpr.get() != nullptr; }
	bool HasExprOwner() const { return _pExprOwner.get() != nullptr; }
	bool HasExprOwnerEx() const { return _pExprOwnerEx.get() != nullptr; }
	void SetItererFlag(bool itererFlag) { _itererFlag = itererFlag; }
	bool GetItererFlag() const { return _itererFlag; }
public:
	static Precedence LookupPrec(const Token& tokenLeft, const Token& tokenRight) {
		return _precMatrix[tokenLeft.GetCategory()][tokenRight.GetCategory()];
	}
};

//------------------------------------------------------------------------------
// TokenList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TokenList : public std::vector<Token*> {
};

//------------------------------------------------------------------------------
// TokenOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TokenOwner : public TokenList, public Referable {
protected:
	~TokenOwner() { Clear(); }
public:
	// Referable accessor
	Gurax_DeclareReferable(TokenOwner);
public:
	void Clear() {
		for (Token* pToken : *this) Token::Delete(pToken);
		clear();
	}
};

//------------------------------------------------------------------------------
// TokenStack
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TokenStack : public TokenOwner {
public:
	void Initialize();
	reverse_iterator SeekTerminal(reverse_iterator ppToken);
	bool CheckBlockParamEnd() const;
	String ToString(const StringStyle& ss) const;
	bool IsEmpty() const { return size() <= 1; }
	Token* Peek(int offset) { return *(rbegin() + offset); }
	void Push(Token* pToken) { push_back(pToken); }
	Token* Pop() { Token* pToken = back(); pop_back(); return pToken; }
};

}

#endif
