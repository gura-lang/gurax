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
	PUnit::SeqId NextSeqId() { return ++_seqIdCur; }
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
	PUnit_Value* Add_Value(const Expr* pExprSrc, const Value* pValue);
	PUnit_Lookup* Add_Lookup(const Expr* pExprSrc, const Symbol* pSymbol);
	PUnit_AssignToSymbol* Add_AssignToSymbol(const Expr* pExprSrc, const Symbol* pSymbol);
	PUnit_AssignToDeclArg* Add_AssignToDeclArg(const Expr* pExprSrc, DeclArg* pDeclArg);
	PUnit_AssignFunction* Add_AssignFunction(const Expr* pExprSrc, const Function* pFunction);
	PUnit_Cast* Add_Cast(const Expr* pExprSrc, const VType& vtype);
	PUnit_UnaryOp* Add_UnaryOp(const Expr* pExprSrc, const Operator* pOperator);
	PUnit_BinaryOp* Add_BinaryOp(const Expr* pExprSrc, const Operator* pOperator);
	PUnit_Add* Add_Add(const Expr* pExprSrc, int added);
	PUnit_CreateList* Add_CreateList(const Expr* pExprSrc, size_t sizeReserve);
	PUnit_AddList* Add_AddList(const Expr* pExprSrc);
	PUnit_Index* Add_Index(const Expr* pExprSrc, const Attribute& attr, size_t sizeReserve);
	PUnit_FeedIndex* Add_FeedIndex(const Expr* pExprSrc);
	PUnit_IndexGet* Add_IndexGet(const Expr* pExprSrc);
	PUnit_IndexSet* Add_IndexSet(const Expr* pExprSrc);
	PUnit_PropGet* Add_PropGet(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr);
	PUnit_PropSet* Add_PropSet(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr);
	PUnit_Member* Add_Member(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr);
	PUnit_Argument* Add_Argument(const Expr* pExprSrc, const Attribute& attr, const Expr_Block* pExpBlock);
	PUnit_ArgSlot* Add_ArgSlot(const Expr* pExprSrc, const PUnit* pPUnitSkipDest = nullptr);
	PUnit_FeedArgSlot* Add_FeedArgSlot(const Expr* pExprSrc);
	PUnit_ArgSlotNamed* Add_ArgSlotNamed(
		const Expr* pExprSrc, const Symbol* pSymbol,
		const Expr* pExprAssigned, const PUnit* pPUnitSkipDest = nullptr);
	PUnit_FeedArgSlotNamed* Add_FeedArgSlotNamed(const Expr* pExprSrc);
	PUnit_Call* Add_Call(const Expr* pExprSrc);
	void AddOpt_Jump(const Expr* pExprSrc, const PUnit* pPUnitCont);
	PUnit_Jump* Add_Jump(const Expr* pExprSrc, const PUnit* pPUnitCont = nullptr);
	PUnit_JumpIf* Add_JumpIf(const Expr* pExprSrc, const PUnit* pPUnitBranch = nullptr);
	PUnit_JumpIfNot* Add_JumpIfNot(const Expr* pExprSrc, const PUnit* pPUnitBranch = nullptr);
	PUnit_NilJumpIf* Add_NilJumpIf(const Expr* pExprSrc, const PUnit* pPUnitBranch = nullptr);
	PUnit_NilJumpIfNot* Add_NilJumpIfNot(const Expr* pExprSrc, const PUnit* pPUnitBranch = nullptr);
	PUnit_ExitPoint* Add_ExitPoint(const Expr* pExprSrc, const PUnit* pPUnitExit = nullptr);
	void AddOpt_PopValueToDiscard(const Expr* pExprSrc);
	PUnit_PopValueToDiscard* Add_PopValueToDiscard(const Expr* pExprSrc);
	PUnit_RemoveValue* Add_RemoveValue(const Expr* pExprSrc, size_t offset);
	PUnit_Return* Add_Return(const Expr* pExprSrc);
	PUnit_PushFrame_Block* Add_PushFrame_Block(const Expr* pExprSrc);
	PUnit_PopFrame* Add_PopFrame(const Expr* pExprSrc);
	PUnit_Terminate* Add_Terminate(const Expr* pExprSrc);
	void Print() const;
	void PrintPUnit() const;
};

}

#endif
