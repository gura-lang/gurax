//==============================================================================
// test-Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//static DeclCallable* ComposeDeclCallable(const char* src)
//{
//	RefPtr<Expr_Collector> pExprRoot(Parser::ParseString(String(src).append("={}").c_str()));
//	if (!pExprRoot) return nullptr;
//	const Expr* pExpr = pExprRoot->GetExprElemFirst();
//	if (pExpr->IsType<Expr_Assign>()) {
//		const Expr_Assign* pExprEx = dynamic_cast<const Expr_Assign*>(pExpr);
//		const Expr* pExpr = &pExprEx->GetExprLeft();
//		if (pExpr->IsType<Expr_Caller>()) {
//			const Expr_Caller* pExprEx = dynamic_cast<const Expr_Caller*>(pExpr);
//			return pExprEx->GetDeclCallable().Reference();
//		}
//	}
//	return nullptr;
//}

//static Argument* ComposeArgument(Processor& processor, const char* src)
//{
//	return new Argument(processor, Value::nil(), ComposeDeclCallable(src), Attribute::Empty->Reference(),
//						DeclCallable::Flag::None, Value::nil(), nullptr);
//}

//static void PrintArgument(const Argument &argument)
//{
//	::printf("%s\n", argument.ToString().c_str());
//}

Gurax_TesterEntry(Argument)
{
#if 0
	Frame& frame = Basement::Inst.GetFrame();
	do {
		RefPtr<Argument> pArgument(ComposeArgument(processor, "f()"));
		PrintArgument(*pArgument);
	} while (0);
	do {
		RefPtr<Argument> pArgument(ComposeArgument(processor, "f(a, b, c)"));
		PrintArgument(*pArgument);
		pArgument->FeedValue(frame, new Value_Number(3));
		pArgument->FeedValue(frame, new Value_Number(1));
		pArgument->FeedValue(frame, new Value_Number(4));
		PrintArgument(*pArgument);
	} while (0);
	do {
		RefPtr<Argument> pArgument(ComposeArgument(processor, "f(a+)"));
		PrintArgument(*pArgument);
		pArgument->FeedValue(frame, new Value_Number(3));
		pArgument->FeedValue(frame, new Value_Number(1));
		pArgument->FeedValue(frame, new Value_Number(4));
		PrintArgument(*pArgument);
	} while (0);
	do {
		RefPtr<Argument> pArgument(ComposeArgument(processor, "f(a, b, c+)"));
		PrintArgument(*pArgument);
		pArgument->FeedValue(frame, new Value_Number(3));
		pArgument->FeedValue(frame, new Value_Number(1));
		pArgument->FeedValue(frame, new Value_Number(4));
		pArgument->FeedValue(frame, new Value_Number(1));
		pArgument->FeedValue(frame, new Value_Number(5));
		pArgument->FeedValue(frame, new Value_Number(9));
		PrintArgument(*pArgument);
	} while (0);
#endif
}

}
