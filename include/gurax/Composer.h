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
	PUnit *_pPUnitCont;
public:
	// Constructor
	Composer() : _pPUnitCont(nullptr) {}
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
	PUnit* GetPUnitCont() { return _pPUnitCont; }
	void Begin() { _pPUnitCont = nullptr; }
	void Add(PUnit* pPUnit);
public:
	void Add_Value(const Expr* pExprSrc, const Value* pValue);
	void Add_Lookup(const Expr* pExprSrc, const Symbol* pSymbol);
	void Add_Assign(const Expr* pExprSrc, const Symbol* pSymbol);
	void Add_AssignFunction(const Expr* pExprSrc, const Function* pFunction);
	void Add_Erase(const Expr* pExprSrc);
	void Add_UnaryOp(const Expr* pExprSrc, const Operator* pOperator);
	void Add_BinaryOp(const Expr* pExprSrc, const Operator* pOperator);
	void Add_CreateList(const Expr* pExprSrc, size_t sizeReserved = 0);
	void Add_AddList(const Expr* pExprSrc);
	void Add_Index(const Expr* pExprSrc, const Attribute& attr);
	void Add_FeedIndex(const Expr* pExprSrc);
	void Add_IndexGet(const Expr* pExprSrc);
	void Add_IndexSet(const Expr* pExprSrc);
	void Add_PropGet(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr);
	void Add_PropSet(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr);
	void Add_Member(const Expr* pExprSrc, const Symbol* pSymbol, const Attribute& attr);
	void Add_Argument(const Expr* pExprSrc, const Attribute& attr);
	void Add_ArgSlot(const Expr* pExprSrc);
	void Add_FeedArgSlot(const Expr* pExprSrc);
	void Add_ArgSlotNamed(const Expr* pExprSrc, const Symbol* pSymbol, const Expr* pExprAssigned);
	void Add_FeedArgSlotNamed(const Expr* pExprSrc);
	void Add_Call(const Expr* pExprSrc);
	void Add_Jump(const Expr* pExprSrc);
	void Add_JumpSub(const Expr* pExprSrc);
	void Add_Return(const Expr* pExprSrc);
	void Add_JumpIf(const Expr* pExprSrc);
	void Add_JumpIfNot(const Expr* pExprSrc);
	
};

}

#endif
