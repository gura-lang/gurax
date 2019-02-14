//==============================================================================
// test-Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static DeclCaller* ComposeDeclCaller(const char* src)
{
	RefPtr<Expr_Root> pExprRoot = Parser::ParseString(String(src).append("={}").c_str());
	if (Error::IsIssued()) return nullptr;
	const Expr* pExpr = pExprRoot->GetExprElemHead();
	if (pExpr->IsType<Expr_Assign>()) {
		const Expr_Assign* pExprEx = dynamic_cast<const Expr_Assign*>(pExpr);
		const Expr* pExpr = pExprEx->GetExprLeft();
		if (pExpr->IsType<Expr_Caller>()) {
			const Expr_Caller* pExprEx = dynamic_cast<const Expr_Caller*>(pExpr);
			return pExprEx->GetDeclCaller().Reference();
		}
	}
	return nullptr;
}

static void PrintArgument(const Argument &argument)
{
	::printf("%s\n", argument.ToString().c_str());
}

Gurax_TesterEntry(Argument)
{
	do {
		RefPtr<Argument> pArgument(new Argument(ComposeDeclCaller("f()"), Attribute::Empty->Reference()));
		PrintArgument(*pArgument);
	} while (0);
	do {
		RefPtr<Argument> pArgument(new Argument(ComposeDeclCaller("f(a, b, c)"), Attribute::Empty->Reference()));
		PrintArgument(*pArgument);
		pArgument->FeedValue(new Value_Number(3));
		pArgument->FeedValue(new Value_Number(1));
		pArgument->FeedValue(new Value_Number(4));
		PrintArgument(*pArgument);
	} while (0);
	do {
		RefPtr<Argument> pArgument(new Argument(ComposeDeclCaller("f(a+)"), Attribute::Empty->Reference()));
		PrintArgument(*pArgument);
		pArgument->FeedValue(new Value_Number(3));
		pArgument->FeedValue(new Value_Number(1));
		pArgument->FeedValue(new Value_Number(4));
		PrintArgument(*pArgument);
	} while (0);
	do {
		RefPtr<Argument> pArgument(new Argument(ComposeDeclCaller("f(a, b, c+)"), Attribute::Empty->Reference()));
		PrintArgument(*pArgument);
		pArgument->FeedValue(new Value_Number(3));
		pArgument->FeedValue(new Value_Number(1));
		pArgument->FeedValue(new Value_Number(4));
		pArgument->FeedValue(new Value_Number(1));
		pArgument->FeedValue(new Value_Number(5));
		pArgument->FeedValue(new Value_Number(9));
		PrintArgument(*pArgument);
	} while (0);
}

}
