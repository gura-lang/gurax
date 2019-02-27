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
	if (_pPUnitLast) _pPUnitLast->SetPUnitNext(pPUnit);
	_pPUnitLast = pPUnit;
}

void Composer::Add_Value(const Expr* pExprSrc, const Value* pValue)
{
	Add(new PUnit_Value(pExprSrc->Reference(), pValue->Clone()));
}

void Composer::Add_Lookup(const Expr* pExprSrc, const Symbol* pSymbol)
{
	Add(new PUnit_Lookup(pExprSrc->Reference(), pSymbol));
}

void Composer::Add_Assign(const Expr* pExprSrc, const Symbol* pSymbol)
{
	Add(new PUnit_Assign(pExprSrc->Reference(), pSymbol));
}

void Composer::Add_AssignFunction(const Expr* pExprSrc, const Function* pFunction)
{
	Add(new PUnit_AssignFunction(pExprSrc->Reference(), pFunction->Reference()));
}

void Composer::Add_Erase(const Expr* pExprSrc)
{
	Add(new PUnit_Erase(pExprSrc->Reference()));
}

void Composer::Add_UnaryOp(const Expr* pExprSrc, const Operator* pOperator)
{
	Add(new PUnit_UnaryOp(pExprSrc->Reference(), pOperator));
}

void Composer::Add_BinaryOp(const Expr* pExprSrc, const Operator* pOperator)
{
	Add(new PUnit_BinaryOp(pExprSrc->Reference(), pOperator));
}

void Composer::Add_CreateList(const Expr* pExprSrc, size_t sizeReserved)
{
	Add(new PUnit_CreateList(pExprSrc->Reference(), sizeReserved));
}

void Composer::Add_AddList(const Expr* pExprSrc)
{
	Add(new PUnit_AddList(pExprSrc->Reference()));
}

void Composer::Add_Index(const Expr* pExprSrc, const Attribute& attr)
{
	Add(new PUnit_Index(pExprSrc->Reference(), attr.Reference()));
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

PUnit_ArgSlot* Composer::Add_ArgSlot(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_ArgSlot(pExprSrc->Reference());
	Add(pPUnit);
	return pPUnit;
}

void Composer::Add_FeedArgSlot(const Expr* pExprSrc)
{
	Add(new PUnit_FeedArgSlot(pExprSrc->Reference()));
}

PUnit_ArgSlotNamed* Composer::Add_ArgSlotNamed(const Expr* pExprSrc, const Symbol* pSymbol, const Expr* pExprAssigned)
{
	auto pPUnit = new PUnit_ArgSlotNamed(pExprSrc->Reference(), pSymbol, pExprAssigned->Reference());
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
	Add(new PUnit_Jump(pExprSrc->Reference(), pPUnitDest));
}

PUnit_JumpSub* Composer::Add_JumpSub(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_JumpSub(pExprSrc->Reference());
	Add(pPUnit);
	return pPUnit;
}

void Composer::Add_Return(const Expr* pExprSrc)
{
	Add(new PUnit_Return(pExprSrc->Reference()));
}

PUnit_BranchIf* Composer::Add_BranchIf(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_BranchIf(pExprSrc->Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit_BranchIfNot* Composer::Add_BranchIfNot(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_BranchIfNot(pExprSrc->Reference());
	Add(pPUnit);
	return pPUnit;
}

}
