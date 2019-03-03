//==============================================================================
// test-Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

static DeclCallable* ComposeDeclCallable(const char* src)
{
	RefPtr<Expr_Root> pExprRoot = Parser::ParseString(String(src).append("={}").c_str());
	if (Error::IsIssued()) return nullptr;
	const Expr* pExpr = pExprRoot->GetExprElemHead();
	if (pExpr->IsType<Expr_Assign>()) {
		const Expr_Assign* pExprEx = dynamic_cast<const Expr_Assign*>(pExpr);
		const Expr* pExpr = pExprEx->GetExprLeft();
		if (pExpr->IsType<Expr_Caller>()) {
			const Expr_Caller* pExprEx = dynamic_cast<const Expr_Caller*>(pExpr);
			return pExprEx->GetDeclCallable().Reference();
		}
	}
	return nullptr;
}

static Argument* ComposeArgument(const char* src)
{
	return new Argument(Value::nil(), ComposeDeclCallable(src), Attribute::Empty->Reference(), Value::nil());
}

static void PrintArgument(const Argument &argument)
{
	::printf("%s\n", argument.ToString().c_str());
}

Gurax_TesterEntry(Argument)
{
	do {
		RefPtr<Argument> pArgument(ComposeArgument("f()"));
		PrintArgument(*pArgument);
	} while (0);
	do {
		RefPtr<Argument> pArgument(ComposeArgument("f(a, b, c)"));
		PrintArgument(*pArgument);
		pArgument->FeedValue(new Value_Number(3));
		pArgument->FeedValue(new Value_Number(1));
		pArgument->FeedValue(new Value_Number(4));
		PrintArgument(*pArgument);
	} while (0);
	do {
		RefPtr<Argument> pArgument(ComposeArgument("f(a+)"));
		PrintArgument(*pArgument);
		pArgument->FeedValue(new Value_Number(3));
		pArgument->FeedValue(new Value_Number(1));
		pArgument->FeedValue(new Value_Number(4));
		PrintArgument(*pArgument);
	} while (0);
	do {
		RefPtr<Argument> pArgument(ComposeArgument("f(a, b, c+)"));
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
