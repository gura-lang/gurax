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
	RefPtr<PUnitFactory> _pPUnitFactory;
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
	static const PUnit* PeekPUnitCont() {
		return reinterpret_cast<const PUnit*>(MemoryPool::Global().chunkPUnit.PeekPointer());
	}
	void Begin() { _pPUnitLast = nullptr; }
	void Add(PUnit* pPUnit);
	void SetFactory(PUnitFactory* pPUnitFactory);
	PUnitFactory& GetFactory() { return *_pPUnitFactory; }
	void DoEval(Processor& processor) const;
public:
	RefPtr<PUnitFactory> Add_Value(const Expr& exprSrc, Value* pValue);
	PUnit* Add_ValueAndJump(const Expr& exprSrc, Value* pValue);
	PUnit* Add_Lookup(const Expr& exprSrc, const Symbol* pSymbol);
	PUnit* Add_AssignToSymbol(const Expr& exprSrc, const Symbol* pSymbol);
	PUnit* Add_AssignToDeclArg(const Expr& exprSrc, DeclArg* pDeclArg);
	PUnit* Add_AssignFunction(const Expr& exprSrc, Function* pFunction);
	PUnit* Add_Cast(const Expr& exprSrc, const VType& vtype);
	PUnit* Add_GenIterator(const Expr& exprSrc);
	PUnit* Add_GenRangeIterator(const Expr& exprSrc);
	PUnit* Add_GenCounterIterator(const Expr& exprSrc);
	PUnit* Add_EvalIterator(const Expr& exprSrc, size_t offset, const PUnit* pPUnitBranchDest = nullptr);
	PUnit* Add_ForEach(const Expr& exprSrc, size_t offset, DeclArgOwner* pDeclArgOwner,
					   const PUnit* pPUnitBranchDest = nullptr);
	PUnit* Add_UnaryOp(const Expr& exprSrc, const Operator* pOperator);
	PUnit* Add_BinaryOp(const Expr& exprSrc, const Operator* pOperator);
	PUnit* Add_CreateList(const Expr& exprSrc, size_t sizeReserve);
	PUnit* Add_ListElem(const Expr& exprSrc, size_t offset);
	PUnit* Add_CreateDict(const Expr& exprSrc);
	PUnit* Add_DictElem(const Expr& exprSrc, size_t offset);
	PUnit* Add_Index(const Expr& exprSrc, Attribute* pAttr, size_t sizeReserve);
	PUnit* Add_FeedIndex(const Expr& exprSrc);
	PUnit* Add_IndexGet(const Expr& exprSrc);
	PUnit* Add_IndexSet(const Expr& exprSrc);
	PUnit* Add_PropGet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr);
	PUnit* Add_PropSet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr);
	PUnit* Add_Member(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr);
	PUnit* Add_Argument(const Expr& exprSrc, Attribute* pAttr, Expr_Block* pExprOfBlock);
	PUnit* Add_ArgSlot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	PUnit* Add_FeedArgSlot(const Expr& exprSrc);
	PUnit* Add_ArgSlotNamed(
		const Expr& exprSrc, const Symbol* pSymbol,
		Expr* pExprAssigned, const PUnit* pPUnitBranchDest = nullptr);
	PUnit* Add_FeedArgSlotNamed(const Expr& exprSrc);
	PUnit* Add_Call(const Expr& exprSrc);
	PUnit* Add_Jump(const Expr& exprSrc, const PUnit* pPUnitCont);
	PUnit* Add_Jump(const Expr& exprSrc);
	PUnit* Add_JumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	PUnit* Add_JumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	PUnit* Add_NilJumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	PUnit* Add_NilJumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	PUnit* Add_ExitPoint(const Expr& exprSrc, const PUnit* pPUnitExit = nullptr);
	PUnit* Add_PopValue(const Expr& exprSrc);
	PUnit* Add_RemoveValue(const Expr& exprSrc, size_t offset);
	PUnit* Add_RemoveValues(const Expr& exprSrc, size_t offset, size_t cnt);
	PUnit* Add_Return(const Expr& exprSrc);
	PUnit* Add_PushFrame_Block(const Expr& exprSrc);
	PUnit* Add_PopFrame(const Expr& exprSrc);
	PUnit* Add_NoOperation(const Expr& exprSrc);
	PUnit* Add_Terminate(const Expr& exprSrc);
	void SetDiscardValueFlagAtLast() {
		if (_pPUnitLast) _pPUnitLast->_SetDiscardValueFlag();
	}
	void Print() const;
	void PrintPUnit(const StringStyle& ss = StringStyle::Empty) const;
	Iterator* EachPUnit() const;
};

}

#endif
