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
	int category;
	const char* typeName;
	const char* symbol;
	OpType opType;
public:
	using MapByOpType = std::map<OpType, const TokenType *>;
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
	static const TokenType *mapByOpType[static_cast<size_t>(OpType::max)];
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
	enum class Precedence { LT, EQ, GT, Error, };
private:
	const TokenType &_tokenType;
	int _lineNo;
	String _value;
	String _suffix;
	String _strSource;
	UniquePtr<Expr> _pExpr;
public:
	static const Precedence _precMatrix[][31];
public:
	// Constructor
	Token(const TokenType &tokenType, int lineNo) : _tokenType(tokenType), _lineNo(lineNo) {}
	Token(const TokenType &tokenType, int lineNo, String value) :
		_tokenType(tokenType), _lineNo(lineNo), _value(std::move(value)) {}
	Token(const TokenType &tokenType, int lineNo, String value, String suffix) :
		_tokenType(tokenType), _lineNo(lineNo), _value(std::move(value)), _suffix(std::move(suffix)) {}
	Token(const TokenType &tokenType, int lineNo, String value, String suffix, String strSource) :
		_tokenType(tokenType), _lineNo(lineNo),
		_value(std::move(value)), _suffix(std::move(suffix)), _strSource(std::move(strSource)) {}
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
	// Referable accessor
	Gurax_DeclareReferable(Token);
public:
	static void Bootup();
	bool IsType(const TokenType &tokenType) const { return _tokenType.IsIdentical(tokenType); }
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
	int GetLineNo() const { return _lineNo; }
	int GetCategory() const { return _tokenType.category; }
	const char *GetTypeName() const { return _tokenType.typeName; }
	const char *GetSymbol() const { return _tokenType.symbol; }
	OpType GetOpType() const { return _tokenType.opType; }
	const char* GetValue() const { return _value.c_str(); }
	const String& GetValueSTL() const { return _value; }
	void AppendValue(const char* value) { _value.append(value); }
	void AppendValue(const String& value) { _value.append(value); }
	Expr* GetExpr() { return _pExpr.get(); }
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
		for (auto& pToken : *this) Token::Delete(pToken);
		clear();
	}
};

//------------------------------------------------------------------------------
// TokenStack
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TokenStack : public TokenList {
public:
	~TokenStack() { Clear(); }
	void Clear() {
		for (auto pToken : *this) Token::Delete(pToken);
		clear();
	}
	void Initialize();
	reverse_iterator SeekTerminal(reverse_iterator ppToken);
	Token* Peek(int offset) { return *(rbegin() + offset); }
	bool CheckBlockParamEnd() const;
	String ToString() const;
	bool IsEmpty() const { return size() <= 1; }
	void Push(Token* pToken) { push_back(pToken); }
	UniquePtr<Token> Pop() { Token* pToken = back(); pop_back(); return pToken; }
};

}

#endif
