//==============================================================================
// Composer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Composer
//------------------------------------------------------------------------------
Composer::Composer(bool replFlag) :
	_replFlag(replFlag), _pPUnitFirst(nullptr), _pPUnitLast(nullptr)
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
	Add_Return(expr);
}

void Composer::Add_Value(const Expr& exprSrc, Value* pValue)
{
	SetFactory(new PUnitFactory_Value(pValue, exprSrc.Reference()));
}

void Composer::Add_Lookup(const Expr& exprSrc, const Symbol* pSymbol)
{
	SetFactory(new PUnitFactory_Lookup(pSymbol, exprSrc.Reference()));
}

void Composer::Add_AssignToSymbol(const Expr& exprSrc, const Symbol* pSymbol)
{
	SetFactory(new PUnitFactory_AssignToSymbol(pSymbol, exprSrc.Reference()));
}

void Composer::Add_AssignToDeclArg(const Expr& exprSrc, DeclArg* pDeclArg)
{
	SetFactory(new PUnitFactory_AssignToDeclArg(pDeclArg, exprSrc.Reference()));
}

void Composer::Add_AssignFunction(const Expr& exprSrc, Function* pFunction)
{
	SetFactory(new PUnitFactory_AssignFunction(pFunction, exprSrc.Reference()));
}

void Composer::Add_Cast(const Expr& exprSrc, const VType& vtype, bool listVarFlag)
{
	SetFactory(new PUnitFactory_Cast(vtype, listVarFlag, exprSrc.Reference()));
}

void Composer::Add_GenIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenIterator(exprSrc.Reference()));
}

void Composer::Add_GenRangeIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenRangeIterator(exprSrc.Reference()));
}

void Composer::Add_GenCounterIterator(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_GenCounterIterator(exprSrc.Reference()));
}

void Composer::Add_EvalIterator(const Expr& exprSrc, size_t offset)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_EvalIterator(offset, pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_ForEach(const Expr& exprSrc, size_t offset, DeclArgOwner* pDeclArgOwner)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_ForEach(offset, pDeclArgOwner, pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_UnaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	SetFactory(new PUnitFactory_UnaryOp(pOperator, exprSrc.Reference()));
}

void Composer::Add_BinaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	SetFactory(new PUnitFactory_BinaryOp(pOperator, exprSrc.Reference()));
}

void Composer::Add_Import(const Expr& exprSrc, DottedSymbol* pDottedSymbol, SymbolList* pSymbolList, bool mixInFlag)
{
	SetFactory(new PUnitFactory_Import(pDottedSymbol, pSymbolList, mixInFlag, exprSrc.Reference()));
}

void Composer::Add_CreateVType(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_CreateVType(exprSrc.Reference()));
}

void Composer::Add_CreateList(const Expr& exprSrc, size_t sizeReserve)
{
	SetFactory(new PUnitFactory_CreateList(sizeReserve, exprSrc.Reference()));
}

void Composer::Add_ListElem(const Expr& exprSrc, size_t offset, bool xlistFlag)
{
	SetFactory(new PUnitFactory_ListElem(offset, xlistFlag, exprSrc.Reference()));
}

void Composer::Add_CreateDict(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_CreateDict(exprSrc.Reference()));
}

void Composer::Add_DictElem(const Expr& exprSrc, size_t offset)
{
	SetFactory(new PUnitFactory_DictElem(offset, exprSrc.Reference()));
}

void Composer::Add_Index(const Expr& exprSrc, Attribute* pAttr, size_t sizeReserve)
{
	SetFactory(new PUnitFactory_Index(pAttr, sizeReserve, exprSrc.Reference()));
}

void Composer::Add_FeedIndex(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_FeedIndex(exprSrc.Reference()));
}

void Composer::Add_IndexGet(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_IndexGet(exprSrc.Reference()));
}

void Composer::Add_IndexSet(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_IndexSet(exprSrc.Reference()));
}

void Composer::Add_PropGet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_PropGet(pSymbol, pAttr, exprSrc.Reference()));
}

void Composer::Add_PropSet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_PropSet(pSymbol, pAttr, exprSrc.Reference()));
}

void Composer::Add_Member(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr)
{
	SetFactory(new PUnitFactory_Member(pSymbol, pAttr, exprSrc.Reference()));
}

void Composer::Add_Argument(const Expr& exprSrc, Attribute* pAttr, Expr_Block* pExprOfBlock)
{
	SetFactory(new PUnitFactory_Argument(pAttr, pExprOfBlock, exprSrc.Reference()));
}

void Composer::Add_BeginArgSlot(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_BeginArgSlot(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_EndArgSlot(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_EndArgSlot(exprSrc.Reference()));
}

void Composer::Add_BeginArgSlotNamed(const Expr& exprSrc, const Symbol* pSymbol, Expr* pExprAssigned)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_BeginArgSlotNamed(
				   pSymbol, pExprAssigned, pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_EndArgSlotNamed(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_EndArgSlotNamed(exprSrc.Reference()));
}

void Composer::Add_Call(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_Call(exprSrc.Reference()));
}

void Composer::Add_Jump(const Expr& exprSrc)
{
	const PUnit* pPUnitCont = nullptr;
	SetFactory(new PUnitFactory_Jump(pPUnitCont, exprSrc.Reference()));
}

void Composer::Add_Jump(const Expr& exprSrc, const PUnit* pPUnitCont)
{
	SetFactory(new PUnitFactory_Jump(pPUnitCont, exprSrc.Reference()));
}

void Composer::Add_JumpIf(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_JumpIf(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_JumpIfNot(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_JumpIfNot(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_NilJumpIf(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_NilJumpIf(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_NilJumpIfNot(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_NilJumpIfNot(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_KeepJumpIf(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_KeepJumpIf(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_KeepJumpIfNot(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_KeepJumpIfNot(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_BeginTryBlock(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_BeginTryBlock(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_EndTryBlock(const Expr& exprSrc)
{
	const PUnit* pPUnitCont = nullptr;
	SetFactory(new PUnitFactory_EndTryBlock(pPUnitCont, exprSrc.Reference()));
}

void Composer::Add_JumpIfNoCatch(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_JumpIfNoCatch(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_JumpIfNoCatchAny(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_JumpIfNoCatchAny(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_NilJumpIfNoCatch(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_NilJumpIfNoCatch(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_NilJumpIfNoCatchAny(const Expr& exprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_NilJumpIfNoCatchAny(pPUnitBranchDest, exprSrc.Reference()));
}

void Composer::Add_BeginSequence(const Expr& exprSrc)
{
	const PUnit* pPUnitSentinel = nullptr;
	SetFactory(new PUnitFactory_BeginSequence(pPUnitSentinel, exprSrc.Reference()));
}

void Composer::Add_EndSequence(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_EndSequence(exprSrc.Reference()));
}

void Composer::Add_DiscardValue(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_DiscardValue(exprSrc.Reference()));
}

void Composer::Add_RemoveValue(const Expr& exprSrc, size_t offset)
{
	SetFactory(new PUnitFactory_RemoveValue(offset, exprSrc.Reference()));
}

void Composer::Add_RemoveValues(const Expr& exprSrc, size_t offset, size_t cnt)
{
	SetFactory(new PUnitFactory_RemoveValues(offset, cnt, exprSrc.Reference()));
}

void Composer::Add_Break(const Expr& exprSrc, const PUnit* pPUnitMarked, bool branchDestFlag)
{
	SetFactory(new PUnitFactory_Break(pPUnitMarked, branchDestFlag, exprSrc.Reference()));
}

void Composer::Add_Continue(const Expr& exprSrc, const PUnit* pPUnitOfLoop)
{
	SetFactory(new PUnitFactory_Continue(pPUnitOfLoop, exprSrc.Reference()));
}

void Composer::Add_Miscatch(const Expr& exprSrc, Value* pValue)
{
	SetFactory(new PUnitFactory_Miscatch(pValue, exprSrc.Reference()));
}

void Composer::Add_Return(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_Return(exprSrc.Reference()));
}

void Composer::Add_PushFrameFromStack(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_PushFrameFromStack(exprSrc.Reference()));
}

void Composer::Add_PopFrame(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_PopFrame(exprSrc.Reference()));
}

void Composer::Add_NoOperation(const Expr& exprSrc)
{
	SetFactory(new PUnitFactory_NoOperation(exprSrc.Reference()));
}

void Composer::Add_Terminate()
{
	SetFactory(new PUnitFactory_Terminate());
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
