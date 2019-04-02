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
	const PUnit* PeekPUnitCont() const;
	void Begin() { _pPUnitLast = nullptr; }
	void Add(PUnit* pPUnit);
	void SetFactory(PUnitFactory* pPUnitFactory);
	void Flush(bool discardValueFlag);
	PUnitFactory& GetFactory() { return *_pPUnitFactory; }
	void DoEval(Processor& processor) const;
public:
	RefPtr<PUnitFactory> Add_Value(const Expr& exprSrc, Value* pValue);
	RefPtr<PUnitFactory> Add_ValueAndJump(const Expr& exprSrc, Value* pValue);
	RefPtr<PUnitFactory> Add_Lookup(const Expr& exprSrc, const Symbol* pSymbol);
	RefPtr<PUnitFactory> Add_AssignToSymbol(const Expr& exprSrc, const Symbol* pSymbol);
	RefPtr<PUnitFactory> Add_AssignToDeclArg(const Expr& exprSrc, DeclArg* pDeclArg);
	RefPtr<PUnitFactory> Add_AssignFunction(const Expr& exprSrc, Function* pFunction);
	RefPtr<PUnitFactory> Add_Cast(const Expr& exprSrc, const VType& vtype);
	RefPtr<PUnitFactory> Add_GenIterator(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_GenRangeIterator(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_GenCounterIterator(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_EvalIterator(const Expr& exprSrc, size_t offset, const PUnit* pPUnitBranchDest = nullptr);

	RefPtr<PUnitFactory> Add_ForEach(const Expr& exprSrc, size_t offset, DeclArgOwner* pDeclArgOwner,
					   const PUnit* pPUnitBranchDest = nullptr);
	RefPtr<PUnitFactory> Add_UnaryOp(const Expr& exprSrc, const Operator* pOperator);
	RefPtr<PUnitFactory> Add_BinaryOp(const Expr& exprSrc, const Operator* pOperator);
	RefPtr<PUnitFactory> Add_CreateList(const Expr& exprSrc, size_t sizeReserve);
	RefPtr<PUnitFactory> Add_ListElem(const Expr& exprSrc, size_t offset);
	RefPtr<PUnitFactory> Add_CreateDict(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_DictElem(const Expr& exprSrc, size_t offset);
	RefPtr<PUnitFactory> Add_Index(const Expr& exprSrc, Attribute* pAttr, size_t sizeReserve);
	RefPtr<PUnitFactory> Add_FeedIndex(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_IndexGet(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_IndexSet(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_PropGet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr);
	RefPtr<PUnitFactory> Add_PropSet(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr);
	RefPtr<PUnitFactory> Add_Member(const Expr& exprSrc, const Symbol* pSymbol, Attribute* pAttr);
	RefPtr<PUnitFactory> Add_Argument(const Expr& exprSrc, Attribute* pAttr, Expr_Block* pExprOfBlock);
	RefPtr<PUnitFactory> Add_ArgSlot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	RefPtr<PUnitFactory> Add_FeedArgSlot(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_ArgSlotNamed(
		const Expr& exprSrc, const Symbol* pSymbol,
		Expr* pExprAssigned, const PUnit* pPUnitBranchDest = nullptr);
	RefPtr<PUnitFactory> Add_FeedArgSlotNamed(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_Call(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_Jump(const Expr& exprSrc, const PUnit* pPUnitCont = nullptr);
	RefPtr<PUnitFactory> Add_JumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	RefPtr<PUnitFactory> Add_JumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	RefPtr<PUnitFactory> Add_NilJumpIf(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	RefPtr<PUnitFactory> Add_NilJumpIfNot(const Expr& exprSrc, const PUnit* pPUnitBranchDest = nullptr);
	RefPtr<PUnitFactory> Add_BeginSequence(const Expr& exprSrc, const PUnit* pPUnitSentinel = nullptr);
	RefPtr<PUnitFactory> Add_BeginQuote(const Expr& exprSrc, const PUnit* pPUnitSentinel = nullptr);
	RefPtr<PUnitFactory> Add_PopValue(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_RemoveValue(const Expr& exprSrc, size_t offset);
	RefPtr<PUnitFactory> Add_RemoveValues(const Expr& exprSrc, size_t offset, size_t cnt);
	RefPtr<PUnitFactory> Add_Break(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_Continue(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_Return(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_PushFrame_Block(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_PopFrame(const Expr& exprSrc);
	RefPtr<PUnitFactory> Add_NoOperation(const Expr& exprSrc);
	void Add_Terminate(const Expr& exprSrc);
	//void SetDiscardValueFlagAtLast() {
	//	if (_pPUnitLast) _pPUnitLast->_SetDiscardValueFlag();
	//}
	void Print() const;
	void PrintPUnit(const StringStyle& ss = StringStyle::Empty) const;
	Iterator* EachPUnit() const;
};

}

#endif
