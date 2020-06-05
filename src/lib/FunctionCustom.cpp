//==============================================================================
// FunctionCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// FunctionCustom
//------------------------------------------------------------------------------
FunctionCustom::FunctionCustom(Type type, const Symbol* pSymbol, DeclCallable* pDeclCallable,
							   Expr* pExprBody, HelpHolder* pHelpHolder) :
	Function(type, pSymbol, pDeclCallable, pHelpHolder),
	_pExprBody(pExprBody), _pPUnitBody(pExprBody->GetPUnitFirst())
{
	if (_pPUnitBody && _pPUnitBody->IsSequenceBegin()) _pPUnitBody = _pPUnitBody->GetPUnitCont();
}

void FunctionCustom::DoExec(Processor& processor, Argument& argument) const
{
	bool dynamicScopeFlag = argument.IsSet(DeclCallable::Flag::DynamicScope);
	argument.AssignToFrame(processor.PushFrameForFunction(*this, dynamicScopeFlag));
	processor.PushPUnit(processor.GetPUnitCur());
	processor.SetPUnitCur(GetPUnitBody());
	// PUnit_Return will do PopFrame().
}

Value* FunctionCustom::DoEval(Processor& processor, Argument& argument) const
{
	bool dynamicScopeFlag = argument.IsSet(DeclCallable::Flag::DynamicScope);
	argument.AssignToFrame(processor.PushFrameForFunction(*this, dynamicScopeFlag));
	RefPtr<Value> pValue(processor.ProcessPUnit(GetPUnitBody()));
	processor.PopFrame();
	processor.ClearEvent();
	return pValue.release();
}

String FunctionCustom::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

}
