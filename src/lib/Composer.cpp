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
	if (_pPUnitLast && !_pPUnitLast->GetPUnitCont()) {
		_pPUnitLast->SetPUnitCont(pPUnit);
	}
	_pPUnitLast = pPUnit;
}

void Composer::DoEval(Processor& processor) const
{
	processor.RunLoop(GetPUnitFirst());
}

PUnit_Value* Composer::Add_Value(const Expr* pExprSrc, const Value* pValue)
{
	auto pPUnit = new PUnit_Value(pExprSrc->Reference(), NextSeqId(), pValue->Clone());
	Add(pPUnit);
	return pPUnit;
}

PUnit_ValueAndJump* Composer::Add_ValueAndJump(const Expr* pExprSrc, const Value* pValue)
{
	auto pPUnit = new PUnit_ValueAndJump(pExprSrc->Reference(), NextSeqId(), pValue->Clone());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Lookup* Composer::Add_Lookup(const Expr* pExprSrc, const Symbol* pSymbol)
{
	auto pPUnit = new PUnit_Lookup(pExprSrc->Reference(), NextSeqId(), pSymbol);
	Add(pPUnit);
	return pPUnit;
}

PUnit_AssignToSymbol* Composer::Add_AssignToSymbol(const Expr* pExprSrc, const Symbol* pSymbol)
{
	auto pPUnit = new PUnit_AssignToSymbol(pExprSrc->Reference(), NextSeqId(), pSymbol);
	Add(pPUnit);
	return pPUnit;
}

PUnit_AssignToDeclArg* Composer::Add_AssignToDeclArg(const Expr* pExprSrc, DeclArg* pDeclArg)
{
	auto pPUnit = new PUnit_AssignToDeclArg(pExprSrc->Reference(), NextSeqId(), pDeclArg);
	Add(pPUnit);
	return pPUnit;
}

PUnit_AssignFunction* Composer::Add_AssignFunction(const Expr* pExprSrc, const Function* pFunction)
{
	auto pPUnit = new PUnit_AssignFunction(pExprSrc->Reference(), NextSeqId(), pFunction->Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Cast* Composer::Add_Cast(const Expr* pExprSrc, const VType& vtype)
{
	auto pPUnit = new PUnit_Cast(pExprSrc->Reference(), NextSeqId(), vtype);
	Add(pPUnit);
	return pPUnit;
}

PUnit_UnaryOp* Composer::Add_UnaryOp(const Expr* pExprSrc, const Operator* pOperator)
{
	auto pPUnit = new PUnit_UnaryOp(pExprSrc->Reference(), NextSeqId(), pOperator);
	Add(pPUnit);
	return pPUnit;
}

PUnit_BinaryOp* Composer::Add_BinaryOp(const Expr* pExprSrc, const Operator* pOperator)
{
	auto pPUnit = new PUnit_BinaryOp(pExprSrc->Reference(), NextSeqId(), pOperator);
	Add(pPUnit);
	return pPUnit;
}

PUnit_Add* Composer::Add_Add(const Expr* pExprSrc, int added)
{
	auto pPUnit = new PUnit_Add(pExprSrc->Reference(), NextSeqId(), added);
	Add(pPUnit);
	return pPUnit;
}

PUnit_CreateList* Composer::Add_CreateList(const Expr* pExprSrc, size_t sizeReserve)
{
	auto pPUnit = new PUnit_CreateList(pExprSrc->Reference(), NextSeqId(), sizeReserve);
	Add(pPUnit);
	return pPUnit;
}

PUnit_AddList* Composer::Add_AddList(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_AddList(pExprSrc->Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Index* Composer::Add_Index(const Expr* pExprSrc, const Attribute& attr, size_t sizeReserve)
{
	auto pPUnit = new PUnit_Index(pExprSrc->Reference(), NextSeqId(), attr.Reference(), sizeReserve);
	Add(pPUnit);
	return pPUnit;
}

PUnit_FeedIndex* Composer::Add_FeedIndex(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_FeedIndex(pExprSrc->Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_IndexGet* Composer::Add_IndexGet(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_IndexGet(pExprSrc->Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_IndexSet* Composer::Add_IndexSet(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_IndexSet(pExprSrc->Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_PropGet* Composer::Add_PropGet(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	auto pPUnit = new PUnit_PropGet(pExprSrc->Reference(), NextSeqId(), pSymbol, attr.Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit_PropSet* Composer::Add_PropSet(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	auto pPUnit = new PUnit_PropSet(pExprSrc->Reference(), NextSeqId(), pSymbol, attr.Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Member* Composer::Add_Member(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr)
{
	auto pPUnit = new PUnit_Member(pExprSrc->Reference(), NextSeqId(), pSymbol, attr.Reference());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Argument* Composer::Add_Argument(const Expr* pExprSrc, const Attribute& attr, const Expr_Block* pExprOfBlock)
{
	auto pPUnit = new PUnit_Argument(pExprSrc->Reference(), NextSeqId(), attr.Reference(), Expr_Block::Reference(pExprOfBlock));
	Add(pPUnit);
	return pPUnit;
}

PUnit_ArgSlot* Composer::Add_ArgSlot(const Expr* pExprSrc, const PUnit* pPUnitSkipDest)
{
	auto pPUnit = new PUnit_ArgSlot(pExprSrc->Reference(), NextSeqId(), pPUnitSkipDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_FeedArgSlot* Composer::Add_FeedArgSlot(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_FeedArgSlot(pExprSrc->Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_ArgSlotNamed* Composer::Add_ArgSlotNamed(
	const Expr* pExprSrc, const Symbol* pSymbol, const Expr* pExprAssigned, const PUnit* pPUnitSkipDest)
{
	auto pPUnit = new PUnit_ArgSlotNamed(
		pExprSrc->Reference(), NextSeqId(), pSymbol, pExprAssigned->Reference(), pPUnitSkipDest);
	Add(pPUnit);
	return pPUnit;
}

PUnit_FeedArgSlotNamed* Composer::Add_FeedArgSlotNamed(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_FeedArgSlotNamed(pExprSrc->Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Call* Composer::Add_Call(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_Call(pExprSrc->Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

void Composer::AddOpt_Jump(const Expr* pExprSrc, const PUnit* pPUnitDest)
{
	if (_pPUnitLast && !_pPUnitLast->GetPUnitCont()) {
		_pPUnitLast->SetPUnitCont(pPUnitDest);
	} else {
		Add_Jump(pExprSrc, pPUnitDest);
	}
}

PUnit_Jump* Composer::Add_Jump(const Expr* pExprSrc, const PUnit* pPUnitCont)
{
	auto pPUnit = new PUnit_Jump(pExprSrc->Reference(), NextSeqId(), pPUnitCont);
	Add(pPUnit);
	return pPUnit;
}

PUnit_JumpIf* Composer::Add_JumpIf(const Expr* pExprSrc, const PUnit* pPUnitBranch)
{
	auto pPUnit = new PUnit_JumpIf(pExprSrc->Reference(), NextSeqId(), pPUnitBranch);
	Add(pPUnit);
	return pPUnit;
}

PUnit_JumpIfNot* Composer::Add_JumpIfNot(const Expr* pExprSrc, const PUnit* pPUnitBranch)
{
	auto pPUnit = new PUnit_JumpIfNot(pExprSrc->Reference(), NextSeqId(), pPUnitBranch);
	Add(pPUnit);
	return pPUnit;
}

PUnit_NilJumpIf* Composer::Add_NilJumpIf(const Expr* pExprSrc, const PUnit* pPUnitBranch)
{
	auto pPUnit = new PUnit_NilJumpIf(pExprSrc->Reference(), NextSeqId(), pPUnitBranch);
	Add(pPUnit);
	return pPUnit;
}

PUnit_NilJumpIfNot* Composer::Add_NilJumpIfNot(const Expr* pExprSrc, const PUnit* pPUnitBranch)
{
	auto pPUnit = new PUnit_NilJumpIfNot(pExprSrc->Reference(), NextSeqId(), pPUnitBranch);
	Add(pPUnit);
	return pPUnit;
}

PUnit_ExitPoint* Composer::Add_ExitPoint(const Expr* pExprSrc, const PUnit* pPUnitExit)
{
	auto pPUnit = new PUnit_ExitPoint(pExprSrc->Reference(), NextSeqId(), pPUnitExit);
	Add(pPUnit);
	return pPUnit;
}

void Composer::AddOpt_PopValueToDiscard(const Expr* pExprSrc)
{
	if (_pPUnitLast) {
		_pPUnitLast->SetPopValueToDiscardFlag();
	} else {
		Add_PopValueToDiscard(pExprSrc);
	}
}

PUnit_PopValueToDiscard* Composer::Add_PopValueToDiscard(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_PopValueToDiscard(pExprSrc->Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_RemoveValue* Composer::Add_RemoveValue(const Expr* pExprSrc, size_t offset)
{
	auto pPUnit = new PUnit_RemoveValue(pExprSrc->Reference(), NextSeqId(), offset);
	Add(pPUnit);
	return pPUnit;
}

PUnit_Return* Composer::Add_Return(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_Return(pExprSrc->Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_PushFrame_Block* Composer::Add_PushFrame_Block(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_PushFrame_Block(pExprSrc->Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_PopFrame* Composer::Add_PopFrame(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_PopFrame(pExprSrc->Reference(), NextSeqId());
	Add(pPUnit);
	return pPUnit;
}

PUnit_Terminate* Composer::Add_Terminate(const Expr* pExprSrc)
{
	auto pPUnit = new PUnit_Terminate(pExprSrc->Reference(), NextSeqId());
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
