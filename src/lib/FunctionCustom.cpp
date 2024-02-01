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
	Frame& frameOuter = processor.GetFrameCur();
	argument.AssignToFrame(processor, processor.BeginFunction(*this, dynamicScopeFlag), frameOuter);
	processor.PushPUnit(processor.GetPUnitCur());
	processor.SetPUnitCur(GetPUnitBody());
	// PUnit_Return will do EndFunction().
}

Value* FunctionCustom::DoEval(Processor& processor, Argument& argument) const
{
	bool dynamicScopeFlag = argument.IsSet(DeclCallable::Flag::DynamicScope);
	Frame& frameOuter = processor.GetFrameCur();
	argument.AssignToFrame(processor, processor.BeginFunction(*this, dynamicScopeFlag), frameOuter);
	RefPtr<Value> pValue(processor.ProcessPUnit(GetPUnitBody()));
	processor.EndFunction(true);
	processor.ClearEvent();
	return pValue.release();
}

String FunctionCustom::ToString(const StringStyle& ss) const
{
	return String().Format("%s%s", MakeFullName().c_str(), GetDeclCallable().ToString(ss).c_str());
}

}
