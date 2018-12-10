//==============================================================================
// Token.h
//==============================================================================
#ifndef GURAX_TOKEN_H
#define GURAX_TOKEN_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TokenType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TokenType {
public:
	static const TokenType Begin;
public:
	int category;
	const char *typeName;
	const char *symbol;
	OpType opType;
public:
	// Constructor
	TokenType() = default;
	// Copy constructor/operator
	TokenType(const TokenType& src) = default;
	TokenType& operator=(const TokenType& src) = default;
	// Move constructor/operator
	TokenType(TokenType&& src) = default;
	TokenType& operator=(TokenType&& src) noexcept = default;
	// Destructor
	~TokenType() = default;
public:
	bool IsIdentical(const TokenType &tokenType) const { return this == &tokenType; }
};

//------------------------------------------------------------------------------
// Token
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Token : public Referable {
public:
	// Constructor
	Token() {}
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
		for (auto pToken : *this) Token::Delete(pToken);
		clear();
	}
};

}

#endif
