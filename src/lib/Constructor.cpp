//==============================================================================
// Constructor.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Constructor::Constructor(VTypeCustom& vtypeCustom, Function* pFuncInitializer) :
	Function(Type::Function, Symbol::Empty, pFuncInitializer->GetDeclCallable().Reference()),
	_vtypeCustom(vtypeCustom), _pFuncInitializer(pFuncInitializer)
{
}

Value* Constructor::DoEval(Processor& processor, Argument& argument) const
{
	RefPtr<Value> pValueThis(new ValueCustom(GetVTypeCustom()));
	argument.SetValueThis(pValueThis.Reference());
	RefPtr<Value> pValue(GetFuncInitializer().DoEval(processor, argument));
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	if (!pExprOfBlock) return pValueThis.release();
	Frame& frame = processor.GetFrameCur();
	RefPtr<Argument> pArgumentSub(Argument::CreateForBlockCall(*pExprOfBlock));
	ArgFeeder args(*pArgumentSub);
	if (!args.FeedValue(frame, pValueThis.release())) return Value::nil();
	return pExprOfBlock->DoEval(processor, *pArgumentSub);
}

String Constructor::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

}
