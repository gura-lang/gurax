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

void Composer::DoEval(Processor& processor) const
{
	processor.RunLoop(GetPUnitFirst());
}

PUnit_Value* Composer::Add_Value(const Expr& exprSrc, const Value* pValue)
{
	auto pPUnit = new PUnit_Value(exprSrc.Reference(), NextSeqId(), pValue->Clone());
	Add(pPUnit);
	return pPUnit;
}

PUnit_ValueAndJump* Composer::Add_ValueAndJump(const Expr& exprSrc, const Value* pValue)
{
	auto pPUnit = new PUnit_ValueAndJump(exprSrc.Reference(), NextSeqId(), pValue->Clone());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Lookup* Composer::Add_Lookup(const Expr& exprSrc, const Symbol* pSymbol)
{
	auto pPUnit = new PUnit_Lookup(exprSrc.Reference(), NextSeqId(), pSymbol);
	Add(pPUnit);
	return pPUnit;
}

PUnit_AssignToSymbol* Composer::Add_AssignToSymbol(const Expr& exprSrc, const Symbol* pSymbol)
{
	auto pPUnit = new PUnit_AssignToSymbol(exprSrc.Reference(), NextSeqId(), pSymbol);
	Add(pPUnit);
	return pPUnit;
}

PUnit_AssignToDeclArg* Composer::Add_AssignToDeclArg(const Expr& exprSrc, DeclArg* pDeclArg)
{
	auto pPUnit = new PUnit_AssignToDeclArg(exprSrc.Reference(), NextSeqId(), pDeclArg);
	Add(pPUnit);
	return pPUnit;
}

PUnit_AssignFunction* Composer::Add_AssignFunction(const Expr& exprSrc, const Function* pFunction)
{
	auto pPUnit = new PUnit_AssignFunction(exprSrc.Reference(), NextSeqId(), pFunction->Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Cast* Composer::Add_Cast(const Expr& exprSrc, const VType& vtype)
{
	auto pPUnit = new PUnit_Cast(exprSrc.Reference(), NextSeqId(), vtype);
	Add(pPUnit);
	return pPUnit;
}

PUnit_GenIterator* Composer::Add_GenIterator(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_GenIterator(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_GenRangeIterator* Composer::Add_GenRangeIterator(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_GenRangeIterator(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_GenInfiniteIterator* Composer::Add_GenInfiniteIterator(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_GenInfiniteIterator(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_EvalIterator* Composer::Add_EvalIterator(const Expr& exprSrc, size_t offset, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_EvalIterator(exprSrc.Reference(), NextSeqId(), offset, pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_EvalIterators* Composer::Add_EvalIterators(const Expr& exprSrc, size_t offset, DeclArgOwner* pDeclArgOwner,
												 const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_EvalIterators(exprSrc.Reference(), NextSeqId(), offset, pDeclArgOwner, pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_UnaryOp* Composer::Add_UnaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	auto pPUnit = new PUnit_UnaryOp(exprSrc.Reference(), NextSeqId(), pOperator);
	Add(pPUnit);
	return pPUnit;
}

PUnit_BinaryOp* Composer::Add_BinaryOp(const Expr& exprSrc, const Operator* pOperator)
{
	auto pPUnit = new PUnit_BinaryOp(exprSrc.Reference(), NextSeqId(), pOperator);
	Add(pPUnit);
	return pPUnit;
}

PUnit_CreateList* Composer::Add_CreateList(const Expr& exprSrc, size_t sizeReserve)
{
	auto pPUnit = new PUnit_CreateList(exprSrc.Reference(), NextSeqId(), sizeReserve);
	Add(pPUnit);
	return pPUnit;
}

PUnit_AddList* Composer::Add_AddList(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_AddList(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_CreateDict* Composer::Add_CreateDict(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_CreateDict(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_AddDict* Composer::Add_AddDict(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_AddDict(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Index* Composer::Add_Index(const Expr& exprSrc, const Attribute& attr, size_t sizeReserve)
{
	auto pPUnit = new PUnit_Index(exprSrc.Reference(), NextSeqId(), attr.Reference(), sizeReserve);
	Add(pPUnit);
	return pPUnit;
}

PUnit_FeedIndex* Composer::Add_FeedIndex(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_FeedIndex(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_IndexGet* Composer::Add_IndexGet(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_IndexGet(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_IndexSet* Composer::Add_IndexSet(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_IndexSet(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_PropGet* Composer::Add_PropGet(const Expr& exprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	auto pPUnit = new PUnit_PropGet(exprSrc.Reference(), NextSeqId(), pSymbol, attr.Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit_PropSet* Composer::Add_PropSet(const Expr& exprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	auto pPUnit = new PUnit_PropSet(exprSrc.Reference(), NextSeqId(), pSymbol, attr.Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Member* Composer::Add_Member(const Expr& exprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	auto pPUnit = new PUnit_Member(exprSrc.Reference(), NextSeqId(), pSymbol, attr.Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Argument* Composer::Add_Argument(const Expr& exprSrc, const Attribute& attr, const Expr_Block* pExprOfBlock)
{
	auto pPUnit = new PUnit_Argument(exprSrc.Reference(), NextSeqId(), attr.Reference(), Expr_Block::Reference(pExprOfBlock));
	Add(pPUnit);
	return pPUnit;
}

PUnit_ArgSlot* Composer::Add_ArgSlot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_ArgSlot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_FeedArgSlot* Composer::Add_FeedArgSlot(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_FeedArgSlot(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_ArgSlotNamed* Composer::Add_ArgSlotNamed(
	const Expr& exprSrc, const Symbol* pSymbol, const Expr* pExprAssigned, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_ArgSlotNamed(
		exprSrc.Reference(), NextSeqId(), pSymbol, pExprAssigned->Reference(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_FeedArgSlotNamed* Composer::Add_FeedArgSlotNamed(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_FeedArgSlotNamed(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Call* Composer::Add_Call(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_Call(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Jump* Composer::Add_Jump(const Expr& exprSrc, const PUnit* pPUnitCont)
{
	auto pPUnit = new PUnit_Jump(exprSrc.Reference(), NextSeqId(), pPUnitCont);
	Add(pPUnit);
	return pPUnit;
}

PUnit_Jump* Composer::Add_Jump(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_Jump(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_JumpIf* Composer::Add_JumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_JumpIf(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_JumpIfNot* Composer::Add_JumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_JumpIfNot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_NilJumpIf* Composer::Add_NilJumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_NilJumpIf(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_NilJumpIfNot* Composer::Add_NilJumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest)
{
	auto pPUnit = new PUnit_NilJumpIfNot(exprSrc.Reference(), NextSeqId(), pPUnitBranchDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_ExitPoint* Composer::Add_ExitPoint(const Expr& exprSrc, const PUnit* pPUnitExit)
{
	auto pPUnit = new PUnit_ExitPoint(exprSrc.Reference(), NextSeqId(), pPUnitExit);
	Add(pPUnit);
	return pPUnit;
}

PUnit_PopValue* Composer::Add_PopValue(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_PopValue(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_RemoveValue* Composer::Add_RemoveValue(const Expr& exprSrc, size_t offset)
{
	auto pPUnit = new PUnit_RemoveValue(exprSrc.Reference(), NextSeqId(), offset);
	Add(pPUnit);
	return pPUnit;
}

PUnit_RemoveValues* Composer::Add_RemoveValues(const Expr& exprSrc, size_t offset, size_t cnt)
{
	auto pPUnit = new PUnit_RemoveValues(exprSrc.Reference(), NextSeqId(), offset, cnt);
	Add(pPUnit);
	return pPUnit;
}

PUnit_Return* Composer::Add_Return(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_Return(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_PushFrame_Block* Composer::Add_PushFrame_Block(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_PushFrame_Block(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_PopFrame* Composer::Add_PopFrame(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_PopFrame(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Terminate* Composer::Add_Terminate(const Expr& exprSrc)
{
	auto pPUnit = new PUnit_Terminate(exprSrc.Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

void Composer::Print() const
{
}

void Composer::PrintPUnit() const
{
	PUnit::PrintSequence(GetPUnitFirst());
}

}
