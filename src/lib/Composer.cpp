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

RefPtr<PUnitFactory> Composer::Add_Value(const Expr& exprSrc, Value* pValue)
{
	SetFactory(new PUnitFactory_Value(exprSrc.Reference(), NextSeqId(), pValue));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_ValueAndJump(const Expr& exprSrc, Value* pValue)
{
	SetFactory(new PUnitFactory_ValueAndJump(exprSrc.Reference(), NextSeqId(), pValue));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Lookup(const Expr& exprSrc, const Symbol* pSymbol)
{
	SetFactory(new PUnitFactory_Lookup(exprSrc.Reference(), NextSeqId(), pSymbol));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_AssignToSymbol(const Expr& exprSrc, const Symbol* pSymbol)
{
	SetFactory(new PUnitFactory_AssignToSymbol(exprSrc.Reference(), NextSeqId(), pSymbol));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_AssignToDeclArg(const Expr& exprSrc, DeclArg* pDeclArg)
{
	SetFactory(new PUnitFactory_AssignToDeclArg(exprSrc.Reference(), NextSeqId(), pDeclArg));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_AssignFunction(const Expr& exprSrc, Function* pFunction)
{
	SetFactory(new PUnitFactory_AssignFunction(exprSrc.Reference(), NextSeqId(), pFunction));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Cast(const Expr& exprSrc, const VType& vtype)
{
	SetFactory(new PUnitFactory_Cast(exprSrc.Reference(), NextSeqId(), vtype));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_GenIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenIterator(exprSrc.Reference(), NextSeqId()));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_GenRangeIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenRangeIterator(exprSrc.Reference(), NextSeqId()));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_GenCounterIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenCounterIterator(exprSrc.Reference(), NextSeqId()));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_EvalIterator(const Expr& exprSrc, size_t offset, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_EvalIterator(exprSrc.Reference(), NextSeqId(), offset, pPUnitBranchDest));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_ForEach(const Expr& exprSrc, size_t offset, DeclArgOwner* pDeclArgOwner,
							 const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_ForEach(exprSrc.Reference(), NextSeqId(), offset, pDeclArgOwner, pPUnitBranchDest));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_UnaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	SetFactory(new PUnitFactory_UnaryOp(exprSrc.Reference(), NextSeqId(), pOperator));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_BinaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	SetFactory(new PUnitFactory_BinaryOp(exprSrc.Reference(), NextSeqId(), pOperator));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_CreateList(const Expr& exprSrc, size_t sizeReserve)
{
	SetFactory(new PUnitFactory_CreateList(exprSrc.Reference(), NextSeqId(), sizeReserve));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_ListElem(const Expr& exprSrc, size_t offset)
{
	SetFactory(new PUnitFactory_ListElem(exprSrc.Reference(), NextSeqId(), offset));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_CreateDict(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_CreateDict(exprSrc.Reference(), NextSeqId()));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_DictElem(const Expr& exprSrc, size_t offset)
{
	SetFactory(new PUnitFactory_DictElem(exprSrc.Reference(), NextSeqId(), offset));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Index(const Expr& exprSrc, Attribute* pAttr, size_t sizeReserve)
{
	SetFactory(new PUnitFactory_Index(exprSrc.Reference(), NextSeqId(), pAttr, sizeReserve));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_FeedIndex(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_FeedIndex(exprSrc.Reference(), NextSeqId()));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_IndexGet(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_IndexGet(exprSrc.Reference(), NextSeqId()));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_IndexSet(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_IndexSet(exprSrc.Reference(), NextSeqId()));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_PropGet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_PropGet(exprSrc.Reference(), NextSeqId(), pSymbol, pAttr));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_PropSet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_PropSet(exprSrc.Reference(), NextSeqId(), pSymbol, pAttr));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Member(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_Member(exprSrc.Reference(), NextSeqId(), pSymbol, pAttr));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Argument(const Expr& exprSrc, Attribute* pAttr, Expr_Block* pExprOfBlock)
{
	SetFactory(new PUnitFactory_Argument(exprSrc.Reference(), NextSeqId(), pAttr, pExprOfBlock));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_ArgSlot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_ArgSlot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_FeedArgSlot(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_FeedArgSlot(exprSrc.Reference(), NextSeqId()));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_ArgSlotNamed(
	const Expr& exprSrc, const Symbol* pSymbol, Expr* pExprAssigned, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_ArgSlotNamed(
				   exprSrc.Reference(), NextSeqId(), pSymbol, pExprAssigned, pPUnitBranchDest));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_FeedArgSlotNamed(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_FeedArgSlotNamed(exprSrc.Reference(), NextSeqId()));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Call(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_Call(exprSrc.Reference(), NextSeqId()));
	Add(GetFactory().Create(false));
	return GetFactory().Reference();
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
