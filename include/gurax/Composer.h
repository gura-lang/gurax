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
	PUnitList _punitList;
	PUnitStack _punitStack;
	PUnit *_pPUnitLast;
public:
	// Constructor
	Composer() : _pPUnitLast(nullptr) {}
	// Copy constructor/operator
	Composer(const Composer& src) = delete;
	Composer& operator=(const Composer& src) = delete;
	// Move constructor/operator
	Composer(Composer&& src) = delete;
	Composer& operator=(Composer&& src) noexcept = delete;
	// Destructor
	virtual ~Composer() = default;
public:
	const PUnitList& GetPUnitList() const { return _punitList; }
	PUnitStack& GetPUnitStack() { return _punitStack; }
	const PUnit* GetPUnitTop() const { return _punitList.front(); }
	PUnit* GetPUnitLast() { return _pPUnitLast; }
	const PUnit* GetPUnitAt(size_t pos) const { return _punitList[pos]; }
	size_t MarkPUnit() const { return _punitList.size(); }
	static const PUnit* PeekPUnitNext() {
		return reinterpret_cast<const PUnit*>(MemoryPool::Global().chunkPUnit.PeekPointer());
	}
	void Begin() { _pPUnitLast = nullptr; }
	void Add(PUnit* pPUnit);
public:
	void Add_Value(const Expr* pExprSrc, const Value* pValue);
	PUnit_Value* AddF_Value(const Expr* pExprSrc, const Value* pValue);
	void Add_Lookup(const Expr* pExprSrc, const Symbol* pSymbol);
	void Add_AssignToSymbol(const Expr* pExprSrc, const Symbol* pSymbol);
	void Add_AssignToDeclArg(const Expr* pExprSrc, DeclArg* pDeclArg);
	void Add_AssignFunction(const Expr* pExprSrc, const Function* pFunction);
	void Add_PopToDiscard(const Expr* pExprSrc);
	PUnit_PopToDiscard* AddF_PopToDiscard(const Expr* pExprSrc);
	void Add_Cast(const Expr* pExprSrc, const VType& vtype);
	void Add_UnaryOp(const Expr* pExprSrc, const Operator* pOperator);
	void Add_BinaryOp(const Expr* pExprSrc, const Operator* pOperator);
	void Add_Add(const Expr* pExprSrc, int added);
	void Add_CreateList(const Expr* pExprSrc, size_t sizeReserve);
	void Add_AddList(const Expr* pExprSrc);
	void Add_Index(const Expr* pExprSrc, const Attribute& attr, size_t sizeReserve);
	void Add_FeedIndex(const Expr* pExprSrc);
	void Add_IndexGet(const Expr* pExprSrc);
	void Add_IndexSet(const Expr* pExprSrc);
	void Add_PropGet(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr);
	void Add_PropSet(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr);
	void Add_Member(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr);
	void Add_Argument(const Expr* pExprSrc, const Attribute& attr);
	PUnit_ArgSlot* AddF_ArgSlot(const Expr* pExprSrc, const PUnit* pPUnitSkipDest = nullptr);
	void Add_FeedArgSlot(const Expr* pExprSrc);
	PUnit_ArgSlotNamed* AddF_ArgSlotNamed(
		const Expr* pExprSrc, const Symbol* pSymbol,
		const Expr* pExprAssigned, const PUnit* pPUnitSkipDest = nullptr);
	void Add_FeedArgSlotNamed(const Expr* pExprSrc);
	void Add_Call(const Expr* pExprSrc);
	void Add_Jump(const Expr* pExprSrc, const PUnit* pPUnitDest);
	PUnit_Jump* AddF_Jump(const Expr* pExprSrc, const PUnit* pPUnitDest = nullptr);
	PUnit_JumpSub* AddF_JumpSub(const Expr* pExprSrc, const PUnit* pPUnitDest = nullptr);
	void Add_Return(const Expr* pExprSrc);
	PUnit_JumpIf* AddF_JumpIf(const Expr* pExprSrc, const PUnit* pPUnitJumpDest = nullptr);
	PUnit_JumpIfNot* AddF_JumpIfNot(const Expr* pExprSrc, const PUnit* pPUnitJumpDest = nullptr);
	PUnit_NilJumpIf* AddF_NilJumpIf(const Expr* pExprSrc, const PUnit* pPUnitJumpDest = nullptr);
	PUnit_NilJumpIfNot* AddF_NilJumpIfNot(const Expr* pExprSrc, const PUnit* pPUnitJumpDest = nullptr);
	void Print() const;
};

}

#endif
