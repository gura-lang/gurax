//==============================================================================
// Composer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Composer
//------------------------------------------------------------------------------
Composer::Composer(bool replFlag) :
	_replFlag(replFlag), _seqIdCur(0), _pPUnitFirst(nullptr), _pPUnitLast(nullptr)
{
}

void Composer::Add(PUnit* pPUnit)
{
	if (!_pPUnitFirst) _pPUnitFirst = pPUnit;
	_pPUnitLast = pPUnit;
	if (_replFlag) new PUnit_REPLEnd(); // automatically deleted when a new PUnit is allocated
}

PUnit* Composer::PeekPUnitCont() const
{
	MemoryPool::Global().SwitchChunkPUnit(_replFlag);
	return reinterpret_cast<PUnit*>(MemoryPool::Global().GetChunkPUnit().PeekPointer());
}

void Composer::SetFactory(PUnitFactory* pPUnitFactory)
{
	MemoryPool::Global().SwitchChunkPUnit(_replFlag);
	if (_pPUnitFactory) {
		Add(_pPUnitFactory->Create(false));
	}
	MemoryPool::Global().GetChunkPUnit().Reserve(pPUnitFactory->GetPUnitSize());
	_pPUnitFactory.reset(pPUnitFactory);
}

void Composer::_Flush(bool discardValueFlag)
{
	MemoryPool::Global().SwitchChunkPUnit(_replFlag);
	if (_pPUnitFactory) {
		Add(_pPUnitFactory->Create(discardValueFlag));
		_pPUnitFactory.reset(nullptr);
	}
}

void Composer::ComposeAsSequence(Expr& expr)
{
	expr.SetPUnitFirst(PeekPUnitCont());
	PUnit* pPUnitOfBeginSequence = PeekPUnitCont();
	Add_BeginSequence(expr);								// [Any]
	BeginRepeaterBlock(nullptr, nullptr, nullptr);
	expr.ComposeOrNil(*this);								// [Any]
	EndRepeaterBlock();
	pPUnitOfBeginSequence->SetPUnitSentinel(PeekPUnitCont());
	Add_EndSequence(expr);
}

void Composer::Add_Value(const Expr& exprSrc, Value* pValue)
{
	SetFactory(new PUnitFactory_Value(exprSrc.Reference(), NextSeqId(), pValue));
}

void Composer::Add_Lookup(const Expr& exprSrc, const Symbol* pSymbol)
{
	SetFactory(new PUnitFactory_Lookup(exprSrc.Reference(), NextSeqId(), pSymbol));
}

void Composer::Add_AssignToSymbol(const Expr& exprSrc, const Symbol* pSymbol)
{
	SetFactory(new PUnitFactory_AssignToSymbol(exprSrc.Reference(), NextSeqId(), pSymbol));
}

void Composer::Add_AssignToDeclArg(const Expr& exprSrc, DeclArg* pDeclArg)
{
	SetFactory(new PUnitFactory_AssignToDeclArg(exprSrc.Reference(), NextSeqId(), pDeclArg));
}

void Composer::Add_AssignFunction(const Expr& exprSrc, Function* pFunction)
{
	SetFactory(new PUnitFactory_AssignFunction(exprSrc.Reference(), NextSeqId(), pFunction));
}

void Composer::Add_Cast(const Expr& exprSrc, const VType& vtype, bool listVarFlag)
{
	SetFactory(new PUnitFactory_Cast(exprSrc.Reference(), NextSeqId(), vtype, listVarFlag));
}

void Composer::Add_GenIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenIterator(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_GenRangeIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenRangeIterator(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_GenCounterIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenCounterIterator(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_EvalIterator(const Expr& exprSrc, size_t offset, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_EvalIterator(exprSrc.Reference(), NextSeqId(), offset, pPUnitBranchDest));
}

void Composer::Add_ForEach(const Expr& exprSrc, size_t offset, DeclArgOwner* pDeclArgOwner,
							 const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_ForEach(exprSrc.Reference(), NextSeqId(), offset, pDeclArgOwner, pPUnitBranchDest));
}

void Composer::Add_UnaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	SetFactory(new PUnitFactory_UnaryOp(exprSrc.Reference(), NextSeqId(), pOperator));
}

void Composer::Add_BinaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	SetFactory(new PUnitFactory_BinaryOp(exprSrc.Reference(), NextSeqId(), pOperator));
}

void Composer::Add_Import(const Expr& exprSrc, DottedSymbol* pDottedSymbol, SymbolList* pSymbolList, bool mixInFlag)
{
	SetFactory(new PUnitFactory_Import(exprSrc.Reference(), NextSeqId(), pDottedSymbol, pSymbolList, mixInFlag));
}

void Composer::Add_CreateList(const Expr& exprSrc, size_t sizeReserve)
{
	SetFactory(new PUnitFactory_CreateList(exprSrc.Reference(), NextSeqId(), sizeReserve));
}

void Composer::Add_ListElem(const Expr& exprSrc, size_t offset, bool xlistFlag)
{
	SetFactory(new PUnitFactory_ListElem(exprSrc.Reference(), NextSeqId(), offset, xlistFlag));
}

void Composer::Add_CreateDict(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_CreateDict(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_DictElem(const Expr& exprSrc, size_t offset)
{
	SetFactory(new PUnitFactory_DictElem(exprSrc.Reference(), NextSeqId(), offset));
}

void Composer::Add_Index(const Expr& exprSrc, Attribute* pAttr, size_t sizeReserve)
{
	SetFactory(new PUnitFactory_Index(exprSrc.Reference(), NextSeqId(), pAttr, sizeReserve));
}

void Composer::Add_FeedIndex(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_FeedIndex(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_IndexGet(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_IndexGet(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_IndexSet(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_IndexSet(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_PropGet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_PropGet(exprSrc.Reference(), NextSeqId(), pSymbol, pAttr));
}

void Composer::Add_PropSet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_PropSet(exprSrc.Reference(), NextSeqId(), pSymbol, pAttr));
}

void Composer::Add_Member(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_Member(exprSrc.Reference(), NextSeqId(), pSymbol, pAttr));
}

void Composer::Add_Argument(const Expr& exprSrc, Attribute* pAttr, Expr_Block* pExprOfBlock)
{
	SetFactory(new PUnitFactory_Argument(exprSrc.Reference(), NextSeqId(), pAttr, pExprOfBlock));
}

void Composer::Add_ArgSlot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_ArgSlot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_FeedArgSlot(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_FeedArgSlot(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_ArgSlotNamed(
	const Expr& exprSrc, const Symbol* pSymbol, Expr* pExprAssigned, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_ArgSlotNamed(
				   exprSrc.Reference(), NextSeqId(), pSymbol, pExprAssigned, pPUnitBranchDest));
}

void Composer::Add_FeedArgSlotNamed(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_FeedArgSlotNamed(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_Call(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_Call(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_Jump(const Expr& exprSrc, const PUnit* pPUnitCont)
{
	SetFactory(new PUnitFactory_Jump(exprSrc.Reference(), NextSeqId(), pPUnitCont));
}

void Composer::Add_JumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_JumpIf(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_JumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_JumpIfNot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_NilJumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_NilJumpIf(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_NilJumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_NilJumpIfNot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_KeepJumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_KeepJumpIf(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_KeepJumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_KeepJumpIfNot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_PushExceptionInfo(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_PushExceptionInfo(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_PopExceptionInfo(const Expr& exprSrc, const PUnit* pPUnitCont)
{
	SetFactory(new PUnitFactory_PopExceptionInfo(exprSrc.Reference(), NextSeqId(), pPUnitCont));
}

void Composer::Add_JumpIfNoCatch(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_JumpIfNoCatch(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_JumpIfNoCatchAny(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_JumpIfNoCatchAny(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_NilJumpIfNoCatch(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_NilJumpIfNoCatch(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_NilJumpIfNoCatchAny(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	SetFactory(new PUnitFactory_NilJumpIfNoCatchAny(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest));
}

void Composer::Add_BeginSequence(const Expr& exprSrc, const PUnit* pPUnitSentinel)
{
	SetFactory(new PUnitFactory_BeginSequence(exprSrc.Reference(), NextSeqId(), pPUnitSentinel));
}

void Composer::Add_EndSequence(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_EndSequence(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_DiscardValue(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_DiscardValue(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_RemoveValue(const Expr& exprSrc, size_t offset)
{
	SetFactory(new PUnitFactory_RemoveValue(exprSrc.Reference(), NextSeqId(), offset));
}

void Composer::Add_RemoveValues(const Expr& exprSrc, size_t offset, size_t cnt)
{
	SetFactory(new PUnitFactory_RemoveValues(exprSrc.Reference(), NextSeqId(), offset, cnt));
}

void Composer::Add_Break(const Expr& exprSrc, const PUnit* pPUnitMarked, bool branchDestFlag)
{
	SetFactory(new PUnitFactory_Break(exprSrc.Reference(), NextSeqId(), pPUnitMarked, branchDestFlag));
}

void Composer::Add_Continue(const Expr& exprSrc, const PUnit* pPUnitOfLoop)
{
	SetFactory(new PUnitFactory_Continue(exprSrc.Reference(), NextSeqId(), pPUnitOfLoop));
}

void Composer::Add_Miscatch(const Expr& exprSrc, Value* pValue)
{
	SetFactory(new PUnitFactory_Miscatch(exprSrc.Reference(), NextSeqId(), pValue));
}

void Composer::Add_Return(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_Return(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_PushFrameFromStack(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_PushFrameFromStack(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_PopFrame(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_PopFrame(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_NoOperation(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_NoOperation(exprSrc.Reference(), NextSeqId()));
}

void Composer::Add_Terminate(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_Terminate(exprSrc.Reference(), NextSeqId()));
	Flush();
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
	return new Iterator_PUnit(GetPUnitFirst(), nullptr);
}

//------------------------------------------------------------------------------
// Composer::RepeaterInfoOwner
//------------------------------------------------------------------------------
void Composer::RepeaterInfoOwner::Clear()
{
	for (RepeaterInfo* pRepeaterInfo : *this) delete pRepeaterInfo;
	clear();
}

}
