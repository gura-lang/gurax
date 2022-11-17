//==============================================================================
// DottedSymbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DottedSymbol
//------------------------------------------------------------------------------
const DottedSymbol DottedSymbol::Empty;

// Append symbols from a list of Exprs.
bool DottedSymbol::AppendFromExprList(const ExprList& exprList)
{
	_symbolList.reserve(exprList.size());
	for (const Expr* pExpr : exprList) {
		if (!pExpr->IsType<Expr_Identifier>()) return false;
		Append(dynamic_cast<const Expr_Identifier*>(pExpr)->GetSymbol());
	}
	return true;
}

// Append symbols from a string.
bool DottedSymbol::AppendFromString(const char* str, char separator)
{
	enum class Stat {
		SymbolFirst,
		SymbolFollower,
	} stat = Stat::SymbolFirst;
	String field;
	for (const char* p = str; *p != '\0'; p++) {
		char ch = *p;
		switch (stat) {
		case Stat::SymbolFirst: {
			if (String::IsSymbolFirst(ch)) {
				field.clear();
				field += ch;
				stat = Stat::SymbolFollower;
			} else {
				return false;
			}
			break;
		}
		case Stat::SymbolFollower: {
			if (ch == separator) {
				Append(Symbol::Add(field));
				stat = Stat::SymbolFirst;
			} else if (String::IsSymbolFollower(ch)) {
				field += ch;
			} else {
				return false;
			}
			break;
		}
		}
	}
	if (!field.empty()) {
		Append(Symbol::Add(field));
	}
	return true;
}

// Append symbols from Exprs that are chained by member operator ".".
bool DottedSymbol::AppendFromExpr(const Expr& expr)
{
	const Expr* pExpr = &expr;
	for (;;) {
		if (pExpr->IsType<Expr_Member>()) {
			const Expr_Member* pExprMember = dynamic_cast<const Expr_Member*>(pExpr);
			_symbolList.insert(_symbolList.begin(), pExprMember->GetSymbol());
			pExpr = &pExprMember->GetExprTarget();
		} else if (pExpr->IsType<Expr_Identifier>()) {
			const Expr_Identifier* pExprIdentifier = dynamic_cast<const Expr_Identifier*>(pExpr);
			_symbolList.insert(_symbolList.begin(), pExprIdentifier->GetSymbol());
			break;
		} else {
			return false;
		}
	}
	return true;
}

Expr* DottedSymbol::ToExpr() const
{
	SymbolList::const_iterator ppSymbol = _symbolList.begin();
	if (ppSymbol == _symbolList.end()) return nullptr;
	const Symbol* pSymbol = *ppSymbol++;
	RefPtr<Expr> pExpr(new Expr_Identifier(pSymbol));
	for ( ; ppSymbol != _symbolList.end(); ppSymbol++) {
		const Symbol* pSymbol = *ppSymbol;
		pExpr.reset(new Expr_Member(pExpr.release(), pSymbol,
						Attribute::Empty->Reference(), MemberMode::Normal));
	}
	return pExpr.release();
}

String DottedSymbol::ToString(char separator, const StringStyle& ss) const
{
	String str;
	for (const Symbol* pSymbol : _symbolList) {
		if (!str.empty()) str += separator;
		str += pSymbol->ToString();
	}
	return str;
}

}
