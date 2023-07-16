//==============================================================================
// Token.h
//==============================================================================
#ifndef GURAX_TOKEN_H
#define GURAX_TOKEN_H
#include "Referable.h"
#include "Operator.h"
#include "ListBase.h"

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
	static const TokenType As;
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
	static const TokenType BinarySuffixed;
	static const TokenType Template;
	static const TokenType TmplEmbedded;
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
private:
	static const TokenType* _opTypeToTokenTypeMap[static_cast<size_t>(OpType::max)];
public:
	TokenType(int category, const char* typeName, const char* symbol, OpType opType);
	bool IsIdentical(const TokenType &tokenType) const { return this == &tokenType; }
	bool HasSourceSymbol() const { return !(symbol[0] == '[' && symbol[1] != '\0'); }
	static const TokenType& OpTypeToTokenType(OpType opType) { return *_opTypeToTokenTypeMap[static_cast<size_t>(opType)]; }
};

//------------------------------------------------------------------------------
// Token
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Token : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Token);
private:
	const TokenType& _tokenType;
	int _lineNoTop;
	int _lineNoBtm;
	RefPtr<StringReferable> _pSegment;	// for Symbol, Space, Escape, Number, NumberSuffixed,
										//     Template, TmplEmbedded, CommentLine, CommentBlock,
										//     String, StringSuffixed and BinarySuffixed
	RefPtr<BinaryReferable> _pBinary;	// for Binary
	RefPtr<StringReferable> _pSuffix;	// for NumberSuffixed, StringSuffixed and BinarySuffixed
	RefPtr<StringReferable> _pSource;	// for NumberSuffixed, StringSuffixed and BinarySuffixed
	RefPtr<Expr> _pExpr;				// for Expr
	RefPtr<ExprLink> _pExprLink;		// for LBrace, LBlockParam, LBracket and LParenthesis
	RefPtr<ExprLink> _pExprLinkEx;		// for LBrace
	bool _tupleFlag;					// for LParenthesis
public:
	static const Precedence _precMatrix[][31];
public:
	// Constructor
	explicit Token(Expr* pExpr) :
		_tokenType(TokenType::Expr), _lineNoTop(pExpr->GetLineNoTop()), _lineNoBtm(pExpr->GetLineNoBtm()),
		_pExpr(pExpr), _tupleFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm) :
		_tokenType(tokenType), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm), _tupleFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm, ExprLink* pExprLink) :
		_tokenType(tokenType), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm),
		_pExprLink(pExprLink), _tupleFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm, StringReferable* pSegment) :
		_tokenType(tokenType), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm),
		_pSegment(pSegment), _tupleFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm, String segment) :
		Token(tokenType, lineNoTop, lineNoBtm, new StringReferable(std::move(segment))) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm,
		StringReferable* pSegment, StringReferable* pSuffix) :
		_tokenType(tokenType), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm),
		_pSegment(pSegment), _pSuffix(pSuffix), _tupleFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm, String segment, String suffix) :
		Token(tokenType, lineNoTop, lineNoBtm, new StringReferable(std::move(segment)),
		new StringReferable(std::move(suffix))) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm,
		StringReferable* pSegment, StringReferable* pSuffix, StringReferable* pSource) :
		_tokenType(tokenType), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm),
		_pSegment(pSegment), _pSuffix(pSuffix), _pSource(pSource), _tupleFlag(false) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm, String segment, String suffix, String source) :
		Token(tokenType, lineNoTop, lineNoBtm, new StringReferable(std::move(segment)),
		new StringReferable(std::move(suffix)), new StringReferable(std::move(source))) {}
	Token(const TokenType& tokenType, int lineNoTop, int lineNoBtm,  BinaryReferable* pBinary, String source) :
		_tokenType(tokenType), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm),
		_pBinary(pBinary), _pSource(new StringReferable(std::move(source))), _tupleFlag(false) {}
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
	const char* GetSegment() const { return _pSegment->GetString(); }
	const Binary& GetBinary() const { return _pBinary->GetBinary(); }
	const char* GetSuffix() const { return _pSuffix->GetString(); }
	const char* GetSource() const { return _pSource->GetString(); }
	const String& GetSegmentSTL() const { return _pSegment->GetStringSTL(); }
	const String& GetSuffixSTL() const { return _pSuffix->GetStringSTL(); }
	const String& GetSourceSTL() const { return _pSource->GetStringSTL(); }
	const StringReferable& GetSegmentReferable() const { return *_pSegment; }
	const BinaryReferable& GetBinaryReferable() const { return *_pBinary; }
	const StringReferable& GetSuffixReferable() const { return *_pSuffix; }
	const StringReferable& GetSourceReferable() const { return *_pSource; }
	void AppendSegment(const char* segment) { _pSegment->GetStringSTL().append(segment); }
	void AppendSegment(const String& segment) { _pSegment->GetStringSTL().append(segment); }
	void AppendBinary(const Binary& binary) { _pBinary->GetBinary().append(binary); }
	void SetExpr(Expr* pExpr) { _pExpr.reset(pExpr); }
	void SetExprLink(ExprLink* pExprLink) { _pExprLink.reset(pExprLink); }
	void SetExprLinkEx(ExprLink* pExprLinkEx) { _pExprLinkEx.reset(pExprLinkEx); }
	Expr* GetExpr() { return _pExpr.get(); }
	ExprLink& GetExprLink() { return *_pExprLink; }
	ExprLink& GetExprLinkEx() { return *_pExprLinkEx; }
	bool HasExpr() { return _pExpr.get() != nullptr; }
	bool HasExprLink() const { return _pExprLink.get() != nullptr; }
	bool HasExprLinkEx() const { return _pExprLinkEx.get() != nullptr; }
	void SetTupleFlag(bool tupleFlag) { _tupleFlag = tupleFlag; }
	bool GetTupleFlag() const { return _tupleFlag; }
public:
	static Precedence LookupPrec(const TokenType& tokenTypeLeft, const TokenType& tokenTypeRight) {
		return _precMatrix[tokenTypeLeft.category][tokenTypeRight.category];
	}
	static Precedence LookupPrec(const Token& tokenLeft, const Token& tokenRight) {
		return _precMatrix[tokenLeft.GetCategory()][tokenRight.GetCategory()];
	}
};

//------------------------------------------------------------------------------
// TokenList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TokenList : public ListBase<Token*> {
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
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
	bool IsEmpty() const { return size() <= 1; }
	Token* Peek(int offset) { return *(rbegin() + offset); }
	void Push(Token* pToken) { push_back(pToken); }
	Token* Pop() { Token* pToken = back(); pop_back(); return pToken; }
};

}

#endif
