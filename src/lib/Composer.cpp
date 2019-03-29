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
	if (!_pPUnitFirst) _pPUnitFirst = pPUnit;
	_pPUnitLast = pPUnit;
}

void Composer::SetFactory(PUnitFactory* pPUnitFactory)
{
	_pPUnitFactory.reset(pPUnitFactory);
}

void Composer::DoEval(Processor& processor) const
{
	processor.RunLoop(GetPUnitFirst());
}

RefPtr<PUnitFactory> Composer::Add_Value(const Expr& exprSrc, const Value* pValue)
{
	SetFactory(new PUnitFactory_Value(exprSrc.Reference(), NextSeqId(), pValue->Clone()));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

PUnit* Composer::Add_ValueAndJump(const Expr& exprSrc, const Value* pValue)
{
	auto pPUnit = new PUnit_ValueAndJump(exprSrc.Reference(), NextSeqId(), pValue->Clone());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_Lookup(const Expr& exprSrc, const Symbol* pSymbol)
{
	auto pPUnit = new PUnit_Lookup(exprSrc.Reference(), NextSeqId(), pSymbol);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_AssignToSymbol(const Expr& exprSrc, const Symbol* pSymbol)
{
	auto pPUnit = new PUnit_AssignToSymbol(exprSrc.Reference(), NextSeqId(), pSymbol);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_AssignToDeclArg(const Expr& exprSrc, DeclArg* pDeclArg)
{
	auto pPUnit = new PUnit_AssignToDeclArg(exprSrc.Reference(), NextSeqId(), pDeclArg);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_AssignFunction(const Expr& exprSrc, const Function* pFunction)
{
	auto pPUnit = new PUnit_AssignFunction(exprSrc.Reference(), NextSeqId(), pFunction->Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_Cast(const Expr& exprSrc, const VType& vtype)
{
	auto pPUnit = new PUnit_Cast(exprSrc.Reference(), NextSeqId(), vtype);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_GenIterator(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_GenIterator(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_GenRangeIterator(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_GenRangeIterator(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_GenCounterIterator(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_GenCounterIterator(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_EvalIterator(const Expr& exprSrc, size_t offset, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_EvalIterator(exprSrc.Reference(), NextSeqId(), offset, pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_ForEach(const Expr& exprSrc, size_t offset, DeclArgOwner* pDeclArgOwner,
									 const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_ForEach(exprSrc.Reference(), NextSeqId(), offset, pDeclArgOwner, pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_UnaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	auto pPUnit = new PUnit_UnaryOp(exprSrc.Reference(), NextSeqId(), pOperator);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_BinaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	auto pPUnit = new PUnit_BinaryOp(exprSrc.Reference(), NextSeqId(), pOperator);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_CreateList(const Expr& exprSrc, size_t sizeReserve)
{
	auto pPUnit = new PUnit_CreateList(exprSrc.Reference(), NextSeqId(), sizeReserve);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_ListElem(const Expr& exprSrc, size_t offset)
{
	auto pPUnit = new PUnit_ListElem(exprSrc.Reference(), NextSeqId(), offset);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_CreateDict(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_CreateDict(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_DictElem(const Expr& exprSrc, size_t offset)
{
	auto pPUnit = new PUnit_DictElem(exprSrc.Reference(), NextSeqId(), offset);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_Index(const Expr& exprSrc, const Attribute& attr, size_t sizeReserve)
{
	auto pPUnit = new PUnit_Index(exprSrc.Reference(), NextSeqId(), attr.Reference(), sizeReserve);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_FeedIndex(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_FeedIndex(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_IndexGet(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_IndexGet(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_IndexSet(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_IndexSet(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_PropGet(const Expr& exprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	auto pPUnit = new PUnit_PropGet(exprSrc.Reference(), NextSeqId(), pSymbol, attr.Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_PropSet(const Expr& exprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	auto pPUnit = new PUnit_PropSet(exprSrc.Reference(), NextSeqId(), pSymbol, attr.Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_Member(const Expr& exprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	auto pPUnit = new PUnit_Member(exprSrc.Reference(), NextSeqId(), pSymbol, attr.Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_Argument(const Expr& exprSrc, const Attribute& attr, const Expr_Block* pExprOfBlock)
{
	auto pPUnit = new PUnit_Argument(exprSrc.Reference(), NextSeqId(), attr.Reference(), Expr_Block::Reference(pExprOfBlock));
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_ArgSlot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_ArgSlot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_FeedArgSlot(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_FeedArgSlot(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_ArgSlotNamed(
	const Expr& exprSrc, const Symbol* pSymbol, const Expr* pExprAssigned, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_ArgSlotNamed(
		exprSrc.Reference(), NextSeqId(), pSymbol, pExprAssigned->Reference(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_FeedArgSlotNamed(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_FeedArgSlotNamed(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_Call(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_Call(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_Jump(const Expr& exprSrc, const PUnit* pPUnitCont)
{
	auto pPUnit = new PUnit_Jump(exprSrc.Reference(), NextSeqId(), pPUnitCont);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_Jump(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_Jump(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_JumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_JumpIf(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_JumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_JumpIfNot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_NilJumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_NilJumpIf(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_NilJumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_NilJumpIfNot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_ExitPoint(const Expr& exprSrc, const PUnit* pPUnitExit)
{
	auto pPUnit = new PUnit_ExitPoint(exprSrc.Reference(), NextSeqId(), pPUnitExit);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_PopValue(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_PopValue(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_RemoveValue(const Expr& exprSrc, size_t offset)
{
	auto pPUnit = new PUnit_RemoveValue(exprSrc.Reference(), NextSeqId(), offset);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_RemoveValues(const Expr& exprSrc, size_t offset, size_t cnt)
{
	auto pPUnit = new PUnit_RemoveValues(exprSrc.Reference(), NextSeqId(), offset, cnt);
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_Return(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_Return(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_PushFrame_Block(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_PushFrame_Block(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_PopFrame(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_PopFrame(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_NoOperation(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_NoOperation(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit* Composer::Add_Terminate(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_Terminate(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

void Composer::Print() const
{
}

void Composer::PrintPUnit(const StringStyle& ss) const
{
	for (const PUnit* pPUnit = GetPUnitFirst(); pPUnit; pPUnit = pPUnit->GetPUnitNext()) {
		if (!pPUnit->IsBridge()) pPUnit->Print(ss);
	}
}

Iterator* Composer::EachPUnit() const
{
	return new Iterator_EachPUnit(GetPUnitFirst(), nullptr, false);
}

}
