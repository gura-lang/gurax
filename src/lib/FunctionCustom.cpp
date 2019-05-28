//==============================================================================
// FunctionCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// FunctionCustom
//------------------------------------------------------------------------------
FunctionCustom::FunctionCustom(Type type, const Symbol* pSymbol, DeclCallable* pDeclCallable, Expr* pExprBody) :
	Function(type, pSymbol, pDeclCallable), _pExprBody(pExprBody), _pPUnitBody(pExprBody->GetPUnitFirst())
{
	if (_pPUnitBody && _pPUnitBody->IsBeginSequence()) _pPUnitBody = _pPUnitBody->GetPUnitCont();
}

void FunctionCustom::DoExec(Processor& processor, Argument& argument) const
{
	bool dynamicScopeFlag = argument.IsSet(DeclCallable::Flag::DynamicScope);
	argument.AssignToFrame(processor.PushFrameForFunction(*this, dynamicScopeFlag));
	processor.PushPUnit(processor.GetPUnitNext());
	processor.SetPUnitNext(GetPUnitBody());
	// PUnit_Return will do PopFrame().
}

Value* FunctionCustom::DoEval(Processor& processor, Argument& argument) const
{
	bool dynamicScopeFlag = argument.IsSet(DeclCallable::Flag::DynamicScope);
	argument.AssignToFrame(processor.PushFrameForFunction(*this, dynamicScopeFlag));
	processor.ProcessPUnit(GetPUnitBody());
	processor.PopFrame();
	processor.ClearEvent();
	if (Error::IsIssued()) return Value::nil();
	return processor.PopValue();
}

String FunctionCustom::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
#if 0
	str += ss.IsCram()? "=" : " = ";
	if (GetPUnitBody()) {
		str.Printf("#%zu", GetPUnitBody()->GetSeqId());
	} else {
		str += "null";
	}
#endif
	return str;
}

}
