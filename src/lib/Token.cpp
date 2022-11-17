//==============================================================================
// Token.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TokenType
//------------------------------------------------------------------------------
const TokenType *TokenType::_opTypeToTokenTypeMap[static_cast<size_t>(OpType::max)] {};

const TokenType TokenType::Begin			{  1, "Begin",			"[Bgn]",	OpType::None	};
const TokenType TokenType::Assign			{  2, "Assign",			"=",		OpType::None	};	// =
const TokenType TokenType::AssignAdd		{  2, "AssignAdd",		"+=",		OpType::None	};
const TokenType TokenType::AssignSub		{  2, "AssignSub",		"-=",		OpType::None	};
const TokenType TokenType::AssignMul		{  2, "AssignMul",		"*=",		OpType::None	};
const TokenType TokenType::AssignDiv		{  2, "AssignDiv",		"/=",		OpType::None	};
const TokenType TokenType::AssignMod		{  2, "AssignMod",		"%=",		OpType::None	};
const TokenType TokenType::AssignPow		{  2, "AssignPow",		"**=",		OpType::None	};
const TokenType TokenType::AssignOr			{  2, "AssignOr",		"|=",		OpType::None	};
const TokenType TokenType::AssignAnd		{  2, "AssignAnd",		"&=",		OpType::None	};
const TokenType TokenType::AssignXor		{  2, "AssignXor",		"^=",		OpType::None	};
const TokenType TokenType::AssignShl		{  2, "AssignShl",		"<<=",		OpType::None	};
const TokenType TokenType::AssignShr		{  2, "AssignShr",		">>=",		OpType::None	};
const TokenType TokenType::Pair				{  2, "Pair",			"=>",		OpType::Pair	};
const TokenType TokenType::OrOr				{  4, "OrOr",			"||",		OpType::OrOr	};	// ||
const TokenType TokenType::AndAnd			{  5, "AndAnd",			"&&",		OpType::AndAnd	};	// &&
const TokenType TokenType::Not				{  6, "Not",			"!",		OpType::Not		};	// !
const TokenType TokenType::As				{  7, "As",				"as",		OpType::As		};	// as
const TokenType TokenType::Contains			{  7, "Contains",		"in",		OpType::Contains };	// in
const TokenType TokenType::Lt				{  8, "Lt",				"<",		OpType::Lt		};	// <
const TokenType TokenType::Gt				{  8, "Gt",				">",		OpType::Gt		};
const TokenType TokenType::Le				{  8, "Le",				"<=",		OpType::Le		};
const TokenType TokenType::Ge				{  8, "Ge",				">=",		OpType::Ge		};
const TokenType TokenType::Cmp				{  8, "Cmp",			"<=>",		OpType::Cmp		};
const TokenType TokenType::Eq				{  8, "Eq",				"==",		OpType::Eq		};
const TokenType TokenType::Ne				{  8, "Ne",				"!=",		OpType::Ne		};
const TokenType TokenType::Seq				{  9, "Seq",			"..",		OpType::Seq		};	// ..
const TokenType TokenType::Or				{ 10, "Or",				"|",		OpType::Or		};	// |
const TokenType TokenType::Xor				{ 11, "Xor",			"^",		OpType::Xor		};	// ^
const TokenType TokenType::And				{ 12, "And",			"&",		OpType::And		};	// &
const TokenType TokenType::Shl				{ 13, "Shl",			"<<",		OpType::Shl		};	// <<
const TokenType TokenType::Shr				{ 13, "Shr",			">>",		OpType::Shr		};
const TokenType TokenType::Add				{ 14, "Add",			"+",		OpType::Add		};	// +
const TokenType TokenType::Sub				{ 14, "Sub",			"-",		OpType::Sub		};
const TokenType TokenType::Mul				{ 15, "Mul",			"*",		OpType::Mul		};	// *
const TokenType TokenType::Div				{ 15, "Div",			"/",		OpType::Div		};
const TokenType TokenType::Mod				{ 15, "Mod",			"%",		OpType::Mod		};
const TokenType TokenType::ModMod			{ 15, "ModMod",			"%%",		OpType::ModMod	};
const TokenType TokenType::Dot				{ 15, "Dot",			"|.|",		OpType::Dot		};
const TokenType TokenType::Cross			{ 15, "Cross",			"|^|",		OpType::Cross	};
const TokenType TokenType::Gear				{ 15, "Gear",			"|*|",		OpType::Gear	};
const TokenType TokenType::Concat			{  3, "Concat",			"|+|",		OpType::Concat	};
const TokenType TokenType::Difference		{  3, "Difference",		"|-|",		OpType::Difference };
const TokenType TokenType::Intersection		{  3, "Intersection",	"|&|",		OpType::Intersection };
const TokenType TokenType::Union			{  3, "Union",			"|||",		OpType::Union	};
const TokenType TokenType::Question			{ 15, "Question",		"?",		OpType::None	};
const TokenType TokenType::Inv				{ 16, "Inv",			"~",		OpType::Inv		};	// ~
const TokenType TokenType::Pow				{ 17, "Pow",			"**",		OpType::Pow		};	// **
const TokenType TokenType::Quote			{ 18, "Quote",			"`",		OpType::None	};	// `
const TokenType TokenType::Colon			{ 19, "Colon",			":",		OpType::None	};	// :
const TokenType TokenType::ColonAfterSuffix	{ 20, "ColonAfterSuffix",":",		OpType::None	};	// *:
const TokenType TokenType::Period			{ 21, "Period",			".",		OpType::None	};	// .
const TokenType TokenType::ColonColon		{ 21, "ColonColon",		"::",		OpType::None	};
const TokenType TokenType::ColonAsterisk	{ 21, "ColonAsterisk",	":*",		OpType::None	};
const TokenType TokenType::ColonAnd			{ 21, "ColonAnd",		":&",		OpType::None	};
const TokenType TokenType::LParenthesis		{ 22, "LParenthesis",	"(",		OpType::None	};	// (
const TokenType TokenType::RParenthesis		{ 23, "RParenthesis",	")",		OpType::None	};	// )
const TokenType TokenType::LBrace			{ 22, "LBrace",			"{",		OpType::None	};
const TokenType TokenType::RBrace			{ 23, "RBrace",			"}",		OpType::None	};
const TokenType TokenType::LBlockParam		{ 22, "LBlockParam",	"|",		OpType::None	};
const TokenType TokenType::RBlockParam		{ 23, "RBlockParam",	"|",		OpType::None	};
const TokenType TokenType::LBracket			{ 24, "LBracket",		"[",		OpType::None	};	// [
const TokenType TokenType::RBracket			{ 25, "RBracket",		"]",		OpType::None	};	// ]
const TokenType TokenType::Comma			{ 26, "Comma",			",",		OpType::None	};	// ,
const TokenType TokenType::Semicolon		{ 26, "Semicolon",		";",		OpType::None	};
const TokenType TokenType::EndOfLine		{ 27, "EndOfLine",		"[EOL]",	OpType::None	};	// \n
const TokenType TokenType::Number			{ 28, "Number",			"[Num]",	OpType::None	};	// V
const TokenType TokenType::NumberSuffixed	{ 28, "NumberSuffixed",	"[NmS]",	OpType::None	};
const TokenType TokenType::String			{ 28, "String",			"[Str]",	OpType::None	};
const TokenType TokenType::StringSuffixed	{ 28, "StringSuffixed",	"[StS]",	OpType::None	};
const TokenType TokenType::Binary			{ 28, "Binary",			"[Bin]",	OpType::None	};
const TokenType TokenType::BinarySuffixed	{ 28, "BinarySuffixed",	"[BiS]",	OpType::None	};
const TokenType TokenType::Template			{ 28, "Template",		"[TpS]",	OpType::None	};
const TokenType TokenType::TmplEmbedded		{ 28, "TmplEmbedded",	"[EmS]",	OpType::None	};
const TokenType TokenType::Symbol			{ 29, "Symbol",			"[Sym]",	OpType::None	};	// S
const TokenType TokenType::EndOfFile		{ 30, "EndOfFile",		"[EOF]",	OpType::None	};	// E
const TokenType TokenType::Expr				{  0, "Expr",			"[Exp]",	OpType::None	};
const TokenType TokenType::Space			{  0, "Space",			"[Spc]",	OpType::None	};
const TokenType TokenType::Escape			{  0, "Escape",			"[Esc]",	OpType::None	};
const TokenType TokenType::CommentLine		{  0, "CommentLine",	"[CmL]",	OpType::None	};
const TokenType TokenType::CommentBlock		{  0, "CommentBlock",	"[CmB]",	OpType::None	};
const TokenType TokenType::DoubleChars		{  0, "DoubleChars",	"[DbC]",	OpType::None	};
const TokenType TokenType::TripleChars		{  0, "TripleChars",	"[TrC]",	OpType::None	};
const TokenType TokenType::Unknown			{  0, "Unknown",		"[unk]",	OpType::None	};

TokenType::TokenType(int category_, const char* typeName_, const char* symbol_, OpType opType_) :
	category(category_), typeName(typeName_), symbol(symbol_), opType(opType_)
{
	_opTypeToTokenTypeMap[static_cast<size_t>(opType)] = this;
}

//------------------------------------------------------------------------------
// Token
//------------------------------------------------------------------------------
static const Token::Precedence
	LT = Token::Precedence::LT,
	EQ = Token::Precedence::EQ,
	GT = Token::Precedence::GT,
	xx = Token::Precedence::Error;

const Token::Precedence Token::_precMatrix[][31] = {
	/*         e   B   =  |+| ||  &&   !  in   <  ..   |   ^   &  <<   +   *   ~  **   `   :  *:   .   (   )   [   ]   ,  \n   V   S   E */
	/* e */ { xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
	/* B */ { xx, xx, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, xx, LT, xx, EQ, EQ, LT, LT, EQ },
	/* = */ { xx, xx, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* |+|*/{ xx, xx, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* ||*/ { xx, xx, GT, GT, GT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* &&*/ { xx, xx, GT, GT, GT, GT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* ! */ { xx, xx, GT, GT, GT, GT, GT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* in*/ { xx, xx, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* < */ { xx, xx, LT, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* ..*/ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* | */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* ^ */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* & */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* <<*/ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* + */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, LT, GT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* * */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, GT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* ~ */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* ***/ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* ` */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, LT, LT, LT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* : */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* *:*/ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, GT, GT, GT, LT, LT, GT },
	/* . */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, GT, GT, GT, GT, GT, GT, GT, GT, LT, LT, GT },
	/* ( */ { xx, xx, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, EQ, LT, EQ, EQ, EQ, LT, LT, xx },
	/* ) */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT },
	/* [ */ { xx, xx, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, LT, EQ, LT, EQ, EQ, EQ, LT, LT, xx },
	/* ] */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT },
	/* , */ { xx, xx, LT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, xx, GT, GT, GT, GT },
	/* \n*/ { xx, xx, LT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT },
	/* V */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, LT, xx, GT },
	/* S */ { xx, xx, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, GT, xx, xx, GT },
};

void Token::Bootup()
{
}

//------------------------------------------------------------------------------
// TokenList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TokenOwner
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TokenStack
//------------------------------------------------------------------------------
void TokenStack::Initialize()
{
	Clear();
	push_back(new Token(TokenType::Begin, 0, 0));
}

TokenStack::reverse_iterator TokenStack::SeekTerminal(reverse_iterator ppToken)
{
	for ( ; (*ppToken)->IsType(TokenType::Expr); ppToken++) ;
	return ppToken;
}

bool TokenStack::CheckBlockParamEnd() const
{
	int parLevel = 0;
	for (auto ppToken = rbegin(); ppToken != rend(); ppToken++) {
		const Token* pToken = *ppToken;
		if (pToken->IsType(TokenType::LBlockParam)) break;
		if (pToken->IsCloseToken()) parLevel++;
		if (pToken->IsOpenToken()) {
			parLevel--;
			if (parLevel < 0) return false;
		}
	}
	return true;
}

String TokenStack::ToString(const StringStyle&) const
{
	String str;
	for (auto ppToken = begin(); ppToken != end(); ppToken++) {
		if (ppToken != begin()) str.append(" ");
		str.append((*ppToken)->GetSymbol());
	}
	return str;
}

}
