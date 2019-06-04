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
	Add_BeginSequence(&expr);								// [Any]
	BeginRepeaterBlock(nullptr, nullptr, nullptr);
	expr.ComposeOrNil(*this);								// [Any]
	EndRepeaterBlock();
	pPUnitOfBeginSequence->SetPUnitSentinel(PeekPUnitCont());
	Add_Return(&expr);
}

void Composer::Add_Value(Value* pValue, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Value(pValue, Expr::Reference(pExprSrc)));
}

void Composer::Add_Lookup(const Symbol* pSymbol, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Lookup(pSymbol, Expr::Reference(pExprSrc)));
}

void Composer::Add_AssignToSymbol(const Symbol* pSymbol, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_AssignToSymbol(pSymbol, Expr::Reference(pExprSrc)));
}

void Composer::Add_AssignToDeclArg(DeclArg* pDeclArg, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_AssignToDeclArg(pDeclArg, Expr::Reference(pExprSrc)));
}

void Composer::Add_AssignFunction(Function* pFunction, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_AssignFunction(pFunction, Expr::Reference(pExprSrc)));
}

void Composer::Add_Cast(const VType& vtype, bool listVarFlag, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Cast(vtype, listVarFlag, Expr::Reference(pExprSrc)));
}

void Composer::Add_GenIterator(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_GenIterator(Expr::Reference(pExprSrc)));
}

void Composer::Add_GenRangeIterator(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_GenRangeIterator(Expr::Reference(pExprSrc)));
}

void Composer::Add_GenCounterIterator(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_GenCounterIterator(Expr::Reference(pExprSrc)));
}

void Composer::Add_EvalIterator(size_t offset, const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_EvalIterator(offset, pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_ForEach(size_t offset, DeclArgOwner* pDeclArgOwner, const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_ForEach(offset, pDeclArgOwner, pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_UnaryOp(const Operator* pOperator, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_UnaryOp(pOperator, Expr::Reference(pExprSrc)));
}

void Composer::Add_BinaryOp(const Operator* pOperator, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_BinaryOp(pOperator, Expr::Reference(pExprSrc)));
}

void Composer::Add_Import(DottedSymbol* pDottedSymbol, SymbolList* pSymbolList, bool mixInFlag, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Import(pDottedSymbol, pSymbolList, mixInFlag, Expr::Reference(pExprSrc)));
}

void Composer::Add_CreateVType(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_CreateVType(Expr::Reference(pExprSrc)));
}

void Composer::Add_CreateList(size_t sizeReserve, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_CreateList(sizeReserve, Expr::Reference(pExprSrc)));
}

void Composer::Add_ListElem(size_t offset, bool xlistFlag, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_ListElem(offset, xlistFlag, Expr::Reference(pExprSrc)));
}

void Composer::Add_CreateDict(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_CreateDict(Expr::Reference(pExprSrc)));
}

void Composer::Add_DictElem(size_t offset, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_DictElem(offset, Expr::Reference(pExprSrc)));
}

void Composer::Add_Index(Attribute* pAttr, size_t sizeReserve, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Index(pAttr, sizeReserve, Expr::Reference(pExprSrc)));
}

void Composer::Add_FeedIndex(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_FeedIndex(Expr::Reference(pExprSrc)));
}

void Composer::Add_IndexGet(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_IndexGet(Expr::Reference(pExprSrc)));
}

void Composer::Add_IndexSet(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_IndexSet(Expr::Reference(pExprSrc)));
}

void Composer::Add_PropGet(const Symbol* pSymbol, Attribute* pAttr, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_PropGet(pSymbol, pAttr, Expr::Reference(pExprSrc)));
}

void Composer::Add_PropSet(const Symbol* pSymbol, Attribute* pAttr, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_PropSet(pSymbol, pAttr, Expr::Reference(pExprSrc)));
}

void Composer::Add_Member(const Symbol* pSymbol, Attribute* pAttr, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Member(pSymbol, pAttr, Expr::Reference(pExprSrc)));
}

void Composer::Add_Argument(Attribute* pAttr, Expr_Block* pExprOfBlock, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Argument(pAttr, pExprOfBlock, Expr::Reference(pExprSrc)));
}

void Composer::Add_BeginArgSlot(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_BeginArgSlot(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_EndArgSlot(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_EndArgSlot(Expr::Reference(pExprSrc)));
}

void Composer::Add_BeginArgSlotNamed(const Symbol* pSymbol, Expr* pExprAssigned, const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_BeginArgSlotNamed(
				   pSymbol, pExprAssigned, pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_EndArgSlotNamed(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_EndArgSlotNamed(Expr::Reference(pExprSrc)));
}

void Composer::Add_Call(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Call(Expr::Reference(pExprSrc)));
}

void Composer::Add_Jump(const Expr* pExprSrc)
{
	const PUnit* pPUnitCont = nullptr;
	SetFactory(new PUnitFactory_Jump(pPUnitCont, Expr::Reference(pExprSrc)));
}

void Composer::Add_Jump(const PUnit* pPUnitCont, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Jump(pPUnitCont, Expr::Reference(pExprSrc)));
}

void Composer::Add_JumpIf(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_JumpIf(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_JumpIfNot(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_JumpIfNot(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_NilJumpIf(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_NilJumpIf(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_NilJumpIfNot(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_NilJumpIfNot(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_KeepJumpIf(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_KeepJumpIf(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_KeepJumpIfNot(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_KeepJumpIfNot(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_BeginTryBlock(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_BeginTryBlock(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_EndTryBlock(const Expr* pExprSrc)
{
	const PUnit* pPUnitCont = nullptr;
	SetFactory(new PUnitFactory_EndTryBlock(pPUnitCont, Expr::Reference(pExprSrc)));
}

void Composer::Add_JumpIfNoCatch(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_JumpIfNoCatch(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_JumpIfNoCatchAny(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_JumpIfNoCatchAny(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_NilJumpIfNoCatch(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_NilJumpIfNoCatch(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_NilJumpIfNoCatchAny(const Expr* pExprSrc)
{
	const PUnit* pPUnitBranchDest = nullptr;
	SetFactory(new PUnitFactory_NilJumpIfNoCatchAny(pPUnitBranchDest, Expr::Reference(pExprSrc)));
}

void Composer::Add_BeginSequence(const Expr* pExprSrc)
{
	const PUnit* pPUnitSentinel = nullptr;
	SetFactory(new PUnitFactory_BeginSequence(pPUnitSentinel, Expr::Reference(pExprSrc)));
}

void Composer::Add_EndSequence(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_EndSequence(Expr::Reference(pExprSrc)));
}

void Composer::Add_DiscardValue(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_DiscardValue(Expr::Reference(pExprSrc)));
}

void Composer::Add_RemoveValue(size_t offset, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_RemoveValue(offset, Expr::Reference(pExprSrc)));
}

void Composer::Add_RemoveValues(size_t offset, size_t cnt, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_RemoveValues(offset, cnt, Expr::Reference(pExprSrc)));
}

void Composer::Add_Break(const PUnit* pPUnitMarked, bool branchDestFlag, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Break(pPUnitMarked, branchDestFlag, Expr::Reference(pExprSrc)));
}

void Composer::Add_Continue(const PUnit* pPUnitOfLoop, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Continue(pPUnitOfLoop, Expr::Reference(pExprSrc)));
}

void Composer::Add_Miscatch(Value* pValue, const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Miscatch(pValue, Expr::Reference(pExprSrc)));
}

void Composer::Add_Return(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_Return(Expr::Reference(pExprSrc)));
}

void Composer::Add_PushFrameFromStack(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_PushFrameFromStack(Expr::Reference(pExprSrc)));
}

void Composer::Add_PopFrame(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_PopFrame(Expr::Reference(pExprSrc)));
}

void Composer::Add_NoOperation(const Expr* pExprSrc)
{
	SetFactory(new PUnitFactory_NoOperation(Expr::Reference(pExprSrc)));
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
