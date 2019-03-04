//==============================================================================
// Composer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Composer
//------------------------------------------------------------------------------
void Composer::Add(PUnit* pPUnit)
{
	_punitList.push_back(pPUnit);
	if (_pPUnitLast && !_pPUnitLast->GetPUnitNext()) {
		_pPUnitLast->SetPUnitNext(pPUnit);
	}
	_pPUnitLast = pPUnit;
}

void Composer::Add_Value(const Expr* pExprSrc, const Value* pValue)
{
	AddF_Value(pExprSrc, pValue);
}

PUnit_Value* Composer::AddF_Value(const Expr* pExprSrc, const Value* pValue)
{
	auto pPUnit = new PUnit_Value(pExprSrc->Reference(), pValue->Clone());
	Add(pPUnit);
	return pPUnit;
}

void Composer::Add_Lookup(const Expr* pExprSrc, const Symbol* pSymbol)
{
	Add(new PUnit_Lookup(pExprSrc->Reference(), pSymbol));
}

void Composer::Add_AssignToSymbol(const Expr* pExprSrc, const Symbol* pSymbol)
{
	Add(new PUnit_AssignToSymbol(pExprSrc->Reference(), pSymbol));
}

void Composer::Add_AssignToDeclArg(const Expr* pExprSrc, DeclArg* pDeclArg)
{
	Add(new PUnit_AssignToDeclArg(pExprSrc->Reference(), pDeclArg));
}

void Composer::Add_AssignFunction(const Expr* pExprSrc, const Function* pFunction)
{
	Add(new PUnit_AssignFunction(pExprSrc->Reference(), pFunction->Reference()));
}

void Composer::Add_Cast(const Expr* pExprSrc, const VType& vtype)
{
	Add(new PUnit_Cast(pExprSrc->Reference(), vtype));
}

void Composer::Add_UnaryOp(const Expr* pExprSrc, const Operator* pOperator)
{
	Add(new PUnit_UnaryOp(pExprSrc->Reference(), pOperator));
}

void Composer::Add_BinaryOp(const Expr* pExprSrc, const Operator* pOperator)
{
	Add(new PUnit_BinaryOp(pExprSrc->Reference(), pOperator));
}

void Composer::Add_Add(const Expr* pExprSrc, int added)
{
	Add(new PUnit_Add(pExprSrc->Reference(), added));
}

void Composer::Add_CreateList(const Expr* pExprSrc, size_t sizeReserve)
{
	Add(new PUnit_CreateList(pExprSrc->Reference(), sizeReserve));
}

void Composer::Add_AddList(const Expr* pExprSrc)
{
	Add(new PUnit_AddList(pExprSrc->Reference()));
}

void Composer::Add_Index(const Expr* pExprSrc, const Attribute& attr, size_t sizeReserve)
{
	Add(new PUnit_Index(pExprSrc->Reference(), attr.Reference(), sizeReserve));
}

void Composer::Add_FeedIndex(const Expr* pExprSrc)
{
	Add(new PUnit_FeedIndex(pExprSrc->Reference()));
}

void Composer::Add_IndexGet(const Expr* pExprSrc)
{
	Add(new PUnit_IndexGet(pExprSrc->Reference()));
}

void Composer::Add_IndexSet(const Expr* pExprSrc)
{
	Add(new PUnit_IndexSet(pExprSrc->Reference()));
}

void Composer::Add_PropGet(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	Add(new PUnit_PropGet(pExprSrc->Reference(), pSymbol, attr.Reference()));
}

void Composer::Add_PropSet(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	Add(new PUnit_PropSet(pExprSrc->Reference(), pSymbol, attr.Reference()));
}

void Composer::Add_Member(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	Add(new PUnit_Member(pExprSrc->Reference(), pSymbol, attr.Reference()));
}

void Composer::Add_Argument(const Expr* pExprSrc, const Attribute& attr)
{
	Add(new PUnit_Argument(pExprSrc->Reference(), attr.Reference()));
}

PUnit_ArgSlot* Composer::AddF_ArgSlot(const Expr* pExprSrc, const PUnit* pPUnitSkipDest)
{
	auto pPUnit = new PUnit_ArgSlot(pExprSrc->Reference(), pPUnitSkipDest);
	Add(pPUnit);
	return pPUnit;
}

void Composer::Add_FeedArgSlot(const Expr* pExprSrc)
{
	Add(new PUnit_FeedArgSlot(pExprSrc->Reference()));
}

PUnit_ArgSlotNamed* Composer::AddF_ArgSlotNamed(
	const Expr* pExprSrc, const Symbol* pSymbol, const Expr* pExprAssigned, const PUnit* pPUnitSkipDest)
{
	auto pPUnit = new PUnit_ArgSlotNamed(
		pExprSrc->Reference(), pSymbol, pExprAssigned->Reference(), pPUnitSkipDest);
	Add(pPUnit);
	return pPUnit;
}

void Composer::Add_FeedArgSlotNamed(const Expr* pExprSrc)
{
	Add(new PUnit_FeedArgSlotNamed(pExprSrc->Reference()));
}

void Composer::Add_Call(const Expr* pExprSrc)
{
	Add(new PUnit_Call(pExprSrc->Reference()));
}

void Composer::Add_Jump(const Expr* pExprSrc, const PUnit* pPUnitDest)
{
	if (_pPUnitLast && !_pPUnitLast->GetPUnitNext()) {
		_pPUnitLast->SetPUnitNext(pPUnitDest);
	} else {
		AddF_Jump(pExprSrc->Reference(), pPUnitDest);
	}
}

PUnit_Jump* Composer::AddF_Jump(const Expr* pExprSrc, const PUnit* pPUnitDest)
{
	auto pPUnit = new PUnit_Jump(pExprSrc->Reference(), pPUnitDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_JumpSub* Composer::AddF_JumpSub(const Expr* pExprSrc, const PUnit* pPUnitDest)
{
	auto pPUnit = new PUnit_JumpSub(pExprSrc->Reference(), pPUnitDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_JumpIf* Composer::AddF_JumpIf(const Expr* pExprSrc, const PUnit* pPUnitJumpDest)
{
	auto pPUnit = new PUnit_JumpIf(pExprSrc->Reference(), pPUnitJumpDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_JumpIfNot* Composer::AddF_JumpIfNot(const Expr* pExprSrc, const PUnit* pPUnitJumpDest)
{
	auto pPUnit = new PUnit_JumpIfNot(pExprSrc->Reference(), pPUnitJumpDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_NilJumpIf* Composer::AddF_NilJumpIf(const Expr* pExprSrc, const PUnit* pPUnitJumpDest)
{
	auto pPUnit = new PUnit_NilJumpIf(pExprSrc->Reference(), pPUnitJumpDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_NilJumpIfNot* Composer::AddF_NilJumpIfNot(const Expr* pExprSrc, const PUnit* pPUnitJumpDest)
{
	auto pPUnit = new PUnit_NilJumpIfNot(pExprSrc->Reference(), pPUnitJumpDest);
	Add(pPUnit);
	return pPUnit;
}

void Composer::Add_PopToDiscard(const Expr* pExprSrc)
{
	if (_pPUnitLast) {
		_pPUnitLast->SetPopToDiscardFlag();
	} else {
		AddF_PopToDiscard(pExprSrc);
	}
}

PUnit_PopToDiscard* Composer::AddF_PopToDiscard(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_PopToDiscard(pExprSrc->Reference());
	Add(pPUnit);
	return pPUnit;
}

void Composer::Add_Return(const Expr* pExprSrc)
{
	Add(new PUnit_Return(pExprSrc->Reference()));
}

void Composer::Add_Terminate(const Expr* pExprSrc)
{
	Add(new PUnit_Terminate(pExprSrc->Reference()));
}

}
