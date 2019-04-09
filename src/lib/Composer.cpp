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

PUnit* Composer::PeekPUnitCont() const
{
	return _pPUnitFactory?
		_pPUnitFactory->CalcPUnitCont(MemoryPool::Global().chunkPUnit.PeekPointer()) :
		reinterpret_cast<PUnit*>(MemoryPool::Global().chunkPUnit.PeekPointer());
}

void Composer::SetFactory(PUnitFactory* pPUnitFactory)
{
	if (_pPUnitFactory) Add(_pPUnitFactory->Create(false));
	_pPUnitFactory.reset(pPUnitFactory);
}

void Composer::Flush(bool discardValueFlag)
{
	if (_pPUnitFactory) {
		Add(_pPUnitFactory->Create(discardValueFlag));
		_pPUnitFactory.reset(nullptr);
	}
}

RefPtr<PUnitFactory> Composer::Add_Value(const Expr& exprSrc, Value* pValue)
{
	SetFactory(new PUnitFactory_Value(exprSrc.Reference(), NextSeqId(), pValue));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_ValueAndJump(const Expr& exprSrc, Value* pValue)
{
	SetFactory(new PUnitFactory_ValueAndJump(exprSrc.Reference(), NextSeqId(), pValue));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Lookup(const Expr& exprSrc, const Symbol* pSymbol)
{
	SetFactory(new PUnitFactory_Lookup(exprSrc.Reference(), NextSeqId(), pSymbol));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_AssignToSymbol(const Expr& exprSrc, const Symbol* pSymbol)
{
	SetFactory(new PUnitFactory_AssignToSymbol(exprSrc.Reference(), NextSeqId(), pSymbol));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_AssignToDeclArg(const Expr& exprSrc, DeclArg* pDeclArg)
{
	SetFactory(new PUnitFactory_AssignToDeclArg(exprSrc.Reference(), NextSeqId(), pDeclArg));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_AssignFunction(const Expr& exprSrc, Function* pFunction)
{
	SetFactory(new PUnitFactory_AssignFunction(exprSrc.Reference(), NextSeqId(), pFunction));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Cast(const Expr& exprSrc, const VType& vtype)
{
	SetFactory(new PUnitFactory_Cast(exprSrc.Reference(), NextSeqId(), vtype));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_GenIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenIterator(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_GenRangeIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenRangeIterator(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_GenCounterIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenCounterIterator(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_EvalIterator(const Expr& exprSrc, size_t offset, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_EvalIterator(exprSrc.Reference(), NextSeqId(), offset, pPUnitBranchDest));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_ForEach(const Expr& exprSrc, size_t offset, DeclArgOwner* pDeclArgOwner,
							 const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_ForEach(exprSrc.Reference(), NextSeqId(), offset, pDeclArgOwner, pPUnitBranchDest));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_UnaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	SetFactory(new PUnitFactory_UnaryOp(exprSrc.Reference(), NextSeqId(), pOperator));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_BinaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	SetFactory(new PUnitFactory_BinaryOp(exprSrc.Reference(), NextSeqId(), pOperator));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_CreateList(const Expr& exprSrc, size_t sizeReserve)
{
	SetFactory(new PUnitFactory_CreateList(exprSrc.Reference(), NextSeqId(), sizeReserve));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_ListElem(const Expr& exprSrc, size_t offset)
{
	SetFactory(new PUnitFactory_ListElem(exprSrc.Reference(), NextSeqId(), offset));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_CreateDict(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_CreateDict(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_DictElem(const Expr& exprSrc, size_t offset)
{
	SetFactory(new PUnitFactory_DictElem(exprSrc.Reference(), NextSeqId(), offset));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Index(const Expr& exprSrc, Attribute* pAttr, size_t sizeReserve)
{
	SetFactory(new PUnitFactory_Index(exprSrc.Reference(), NextSeqId(), pAttr, sizeReserve));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_FeedIndex(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_FeedIndex(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_IndexGet(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_IndexGet(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_IndexSet(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_IndexSet(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_PropGet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_PropGet(exprSrc.Reference(), NextSeqId(), pSymbol, pAttr));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_PropSet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_PropSet(exprSrc.Reference(), NextSeqId(), pSymbol, pAttr));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Member(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_Member(exprSrc.Reference(), NextSeqId(), pSymbol, pAttr));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Argument(const Expr& exprSrc, Attribute* pAttr, Expr_Block* pExprOfBlock)
{
	SetFactory(new PUnitFactory_Argument(exprSrc.Reference(), NextSeqId(), pAttr, pExprOfBlock));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_ArgSlot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_ArgSlot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_FeedArgSlot(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_FeedArgSlot(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_ArgSlotNamed(
	const Expr& exprSrc, const Symbol* pSymbol, Expr* pExprAssigned, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_ArgSlotNamed(
				   exprSrc.Reference(), NextSeqId(), pSymbol, pExprAssigned, pPUnitBranchDest));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_FeedArgSlotNamed(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_FeedArgSlotNamed(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Call(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_Call(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Jump(const Expr& exprSrc, const PUnit* pPUnitCont)
{
	SetFactory(new PUnitFactory_Jump(exprSrc.Reference(), NextSeqId(), pPUnitCont));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_JumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_JumpIf(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_JumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_JumpIfNot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_NilJumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_NilJumpIf(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_NilJumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_NilJumpIfNot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_BeginSequence(const Expr& exprSrc, const PUnit* pPUnitSentinel)
{
	SetFactory(new PUnitFactory_BeginSequence(exprSrc.Reference(), NextSeqId(), pPUnitSentinel));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_BeginQuote(const Expr& exprSrc, const PUnit* pPUnitSentinel)
{
	SetFactory(new PUnitFactory_BeginQuote(exprSrc.Reference(), NextSeqId(), pPUnitSentinel));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_PopValue(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_PopValue(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_RemoveValue(const Expr& exprSrc, size_t offset)
{
	SetFactory(new PUnitFactory_RemoveValue(exprSrc.Reference(), NextSeqId(), offset));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_RemoveValues(const Expr& exprSrc, size_t offset, size_t cnt)
{
	SetFactory(new PUnitFactory_RemoveValues(exprSrc.Reference(), NextSeqId(), offset, cnt));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Break(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_Break(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Continue(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_Continue(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_Return(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_Return(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_PushFrame_Block(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_PushFrame_Block(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_PopFrame(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_PopFrame(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

RefPtr<PUnitFactory> Composer::Add_NoOperation(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_NoOperation(exprSrc.Reference(), NextSeqId()));
	return GetFactory().Reference();
}

void Composer::Add_Terminate(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_Terminate(exprSrc.Reference(), NextSeqId()));
	Flush(false);
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
	return new Iterator_EachPUnit(GetPUnitFirst(), nullptr);
}

}
