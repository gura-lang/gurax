//==============================================================================
// Composer.h
//==============================================================================
#ifndef GURAX_COMPOSER_H
#define GURAX_COMPOSER_H
#include "PUnit.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Composer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Composer {
private:
	PUnit::SeqId _seqIdCur;
	PUnit* _pPUnitFirst;
	PUnit* _pPUnitLast;
	PUnitStack _punitStack;
public:
	// Constructor
	Composer() : _seqIdCur(0), _pPUnitFirst(nullptr), _pPUnitLast(nullptr) {}
	// Copy constructor/operator
	Composer(const Composer& src) = delete;
	Composer& operator=(const Composer& src) = delete;
	// Move constructor/operator
	Composer(Composer&& src) = delete;
	Composer& operator=(Composer&& src) noexcept = delete;
	// Destructor
	virtual ~Composer() = default;
public:
	PUnit::SeqId NextSeqId() { return _seqIdCur++; }
	PUnitStack& GetPUnitStack() { return _punitStack; }
	const PUnit* GetPUnitFirst() const { return _pPUnitFirst; }
	PUnit* GetPUnitLast() { return _pPUnitLast; }
	void SetPUnitLast(PUnit* pPUnit) { _pPUnitLast = pPUnit; }
	static const PUnit* PeekPUnitCont() {
		return reinterpret_cast<const PUnit*>(MemoryPool::Global().chunkPUnit.PeekPointer());
	}
	void Begin() { _pPUnitLast = nullptr; }
	void Add(PUnit* pPUnit);
	void DoEval(Processor& processor) const;
public:
	PUnit_Value* Add_Value(const Expr& exprSrc, const Value* pValue);
	PUnit_ValueAndJump* Add_ValueAndJump(const Expr& exprSrc, const Value* pValue);
	PUnit_Lookup* Add_Lookup(const Expr& exprSrc, const Symbol* pSymbol);
	PUnit_AssignToSymbol* Add_AssignToSymbol(const Expr& exprSrc, const Symbol* pSymbol);
	PUnit_AssignToDeclArg* Add_AssignToDeclArg(const Expr& exprSrc, DeclArg* pDeclArg);
	PUnit_AssignFunction* Add_AssignFunction(const Expr& exprSrc, const Function* pFunction);
	PUnit_Cast* Add_Cast(const Expr& exprSrc, const VType& vtype);
	PUnit_GenIterator* Add_GenIterator(const Expr& exprSrc);
	PUnit_GenRangeIterator* Add_GenRangeIterator(const Expr& exprSrc);
	PUnit_GenCounterIterator* Add_GenCounterIterator(const Expr& exprSrc);
	PUnit_EvalIterator* Add_EvalIterator(const Expr& exprSrc, size_t offset, const PUnit* pPUnitBranchDest = nullptr);
	PUnit_ForEach* Add_ForEach(const Expr& exprSrc, size_t offset, DeclArgOwner* pDeclArgOwner,
							   const PUnit* pPUnitBranchDest = nullptr);
	PUnit_UnaryOp* Add_UnaryOp(const Expr& exprSrc, const Operator* pOperator);
	PUnit_BinaryOp* Add_BinaryOp(const Expr& exprSrc, const Operator* pOperator);
	PUnit_CreateList* Add_CreateList(const Expr& exprSrc, size_t sizeReserve);
	PUnit_ListElem* Add_ListElem(const Expr& exprSrc, size_t offset);
	PUnit_CreateDict* Add_CreateDict(const Expr& exprSrc);
	PUnit_DictElem* Add_DictElem(const Expr& exprSrc, size_t offset);
	PUnit_Index* Add_Index(const Expr& exprSrc, const Attribute& attr, size_t sizeReserve);
	PUnit_FeedIndex* Add_FeedIndex(const Expr& exprSrc);
	PUnit_IndexGet* Add_IndexGet(const Expr& exprSrc);
	PUnit_IndexSet* Add_IndexSet(const Expr& exprSrc);
	PUnit_PropGet* Add_PropGet(const Expr& exprSrc, const Symbol* pSymbol, const Attribute& attr);
	PUnit_PropSet* Add_PropSet(const Expr& exprSrc, const Symbol* pSymbol, const Attribute& attr);
	PUnit_Member* Add_Member(const Expr& exprSrc, const Symbol* pSymbol, const Attribute& attr);
	PUnit_Argument* Add_Argument(const Expr& exprSrc, const Attribute& attr, const Expr_Block* pExpBlock);
	PUnit_ArgSlot* Add_ArgSlot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	PUnit_FeedArgSlot* Add_FeedArgSlot(const Expr& exprSrc);
	PUnit_ArgSlotNamed* Add_ArgSlotNamed(
		const Expr& exprSrc, const Symbol* pSymbol,
		const Expr* pExprAssigned, const PUnit* pPUnitBranchDest = nullptr);
	PUnit_FeedArgSlotNamed* Add_FeedArgSlotNamed(const Expr& exprSrc);
	PUnit_Call* Add_Call(const Expr& exprSrc);
	PUnit_Jump* Add_Jump(const Expr& exprSrc, const PUnit* pPUnitCont);
	PUnit_Jump* Add_Jump(const Expr& exprSrc);
	PUnit_JumpIf* Add_JumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	PUnit_JumpIfNot* Add_JumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	PUnit_NilJumpIf* Add_NilJumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	PUnit_NilJumpIfNot* Add_NilJumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	PUnit_ExitPoint* Add_ExitPoint(const Expr& exprSrc, const PUnit* pPUnitExit = nullptr);
	PUnit_PopValue* Add_PopValue(const Expr& exprSrc);
	PUnit_RemoveValue* Add_RemoveValue(const Expr& exprSrc, size_t offset);
	PUnit_RemoveValues* Add_RemoveValues(const Expr& exprSrc, size_t offset, size_t cnt);
	PUnit_Return* Add_Return(const Expr& exprSrc);
	PUnit_PushFrame_Block* Add_PushFrame_Block(const Expr& exprSrc);
	PUnit_PopFrame* Add_PopFrame(const Expr& exprSrc);
	PUnit_Terminate* Add_Terminate(const Expr& exprSrc);
	void SetDiscardValueFlagAtLast() {
		if (_pPUnitLast) _pPUnitLast->SetDiscardValueFlag();
	}
	void Print() const;
	void PrintPUnit(const StringStyle& ss = StringStyle::Empty) const;
	Iterator* EachPUnit() const;
};

}

#endif
