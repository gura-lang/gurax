//==============================================================================
// PUnit.h
//==============================================================================
#ifndef GURAX_PUNIT_H
#define GURAX_PUNIT_H
#include "Expr.h"

namespace Gurax {

class Processor;

//------------------------------------------------------------------------------
// PUnit
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit {
protected:
	RefPtr<Expr> _pExprSrc;
	const PUnit* _pPUnitNext;
public:
	// Constructor
	explicit PUnit(Expr* pExprSrc);
	// Copy constructor/operator
	PUnit(const PUnit& src) = delete;
	PUnit& operator=(const PUnit& src) = delete;
	// Move constructor/operator
	PUnit(PUnit&& src) = delete;
	PUnit& operator=(PUnit&& src) noexcept = delete;
	// Destructor
	virtual ~PUnit() = default;
public:
	const Expr* GetExprSrc() const { return _pExprSrc.get(); }
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const PUnit* pPUnit) const { return this == pPUnit; }
	bool IsEqualTo(const PUnit* pPUnit) const { return IsIdentical(pPUnit); }
	bool IsLessThan(const PUnit* pPUnit) const { return this < pPUnit; }
	String ToString() const { return ToString(StringStyle::Empty); }
public:
	size_t GetIndex() const { return MemoryPool::Global().chunkPUnit.GetIndex(this); }
	void SetPUnitNext(const PUnit* pPUnit) { _pPUnitNext = pPUnit; }
	const PUnit* GetPUnitNext() const { return _pPUnitNext; }
	void AppendJumpInfo(String& str) const;
public:
	// Virtual functions
	virtual void Exec(Processor& processor) const = 0;
	virtual String ToString(const StringStyle& ss) const = 0;
};

//------------------------------------------------------------------------------
// PUnitList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnitList : public std::vector<const PUnit*> {
};

//------------------------------------------------------------------------------
// PUnitStack
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnitStack : public PUnitList {
public:
	const PUnit* Peek(int offset) { return *(rbegin() + offset); }
	void Push(const PUnit* pPUnit) { push_back(pPUnit); }
	const PUnit* Pop() { const PUnit* pPUnit = back(); pop_back(); return pPUnit; }
};


//------------------------------------------------------------------------------
// PUnit_Value
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Value : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Value> _pValue;
public:
	// Constructor
	PUnit_Value(Expr* pExprSrc, Value* pValue) : PUnit(pExprSrc), _pValue(pValue) {}
public:
	const Value* GetValue() const { return _pValue.get(); }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Lookup
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Lookup : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	PUnit_Lookup(Expr* pExprSrc, const Symbol* pSymbol) : PUnit(pExprSrc), _pSymbol(pSymbol) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Assign
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Assign : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	PUnit_Assign(Expr* pExprSrc, const Symbol* pSymbol) : PUnit(pExprSrc), _pSymbol(pSymbol) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_AssignFunction
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_AssignFunction : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Function> _pFunction;
public:
	// Constructor
	PUnit_AssignFunction(Expr* pExprSrc, Function* pFunction) : PUnit(pExprSrc), _pFunction(pFunction) {}
public:
	const Function& GetFunction() const { return *_pFunction; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Erase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Erase : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_Erase(Expr* pExprSrc) : PUnit(pExprSrc) {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_UnaryOp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_UnaryOp : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Operator* _pOperator;
public:
	// Constructor
	PUnit_UnaryOp(Expr* pExprSrc, const Operator* pOperator) : PUnit(pExprSrc), _pOperator(pOperator) {}
public:
	const Operator* GetOperator() const { return _pOperator; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_BinaryOp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_BinaryOp : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Operator* _pOperator;
public:
	// Constructor
	PUnit_BinaryOp(Expr* pExprSrc, const Operator* pOperator) : PUnit(pExprSrc), _pOperator(pOperator) {}
public:
	const Operator* GetOperator() const { return _pOperator; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_CreateList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_CreateList : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	size_t _sizeReserve;
public:
	// Constructor
	explicit PUnit_CreateList(Expr* pExprSrc, size_t sizeReserve) : PUnit(pExprSrc), _sizeReserve(sizeReserve) {}
public:
	size_t GetSizeReserve() const { return _sizeReserve; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_AddList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_AddList : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_AddList(Expr* pExprSrc) : PUnit(pExprSrc) {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Index
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Index : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Attribute> _pAttr;
	size_t _sizeReserve;
public:
	// Constructor
	PUnit_Index(Expr* pExprSrc, Attribute* pAttr, size_t sizeReserve) :
		PUnit(pExprSrc), _pAttr(pAttr), _sizeReserve(sizeReserve) {}
public:
	const Attribute& GetAttr() const { return *_pAttr; }
	size_t GetSizeReserve() const { return _sizeReserve; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_FeedIndex
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_FeedIndex : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_FeedIndex(Expr* pExprSrc) : PUnit(pExprSrc) {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_IndexGet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_IndexGet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_IndexGet(Expr* pExprSrc) : PUnit(pExprSrc) {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_IndexSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_IndexSet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_IndexSet(Expr* pExprSrc) : PUnit(pExprSrc) {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_PropGet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_PropGet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_PropGet(Expr* pExprSrc, const Symbol* pSymbol, Attribute* pAttr) :
		PUnit(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_PropSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_PropSet : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_PropSet(Expr* pExprSrc, const Symbol* pSymbol, Attribute* pAttr) :
		PUnit(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Member
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Member : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_Member(Expr* pExprSrc, const Symbol* pSymbol, Attribute* pAttr) :
		PUnit(pExprSrc), _pSymbol(pSymbol), _pAttr(pAttr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Argument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Argument : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_Argument(Expr* pExprSrc, Attribute* pAttr) : PUnit(pExprSrc), _pAttr(pAttr) {}
public:
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_ArgSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_ArgSlot : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitAtMerging;
public:
	// Constructor
	PUnit_ArgSlot(Expr* pExprSrc) : PUnit(pExprSrc), _pPUnitAtMerging(nullptr) {}
public:
	void SetPUnitAtMerging(const PUnit* pPUnit) { _pPUnitAtMerging = pPUnit; }
	const PUnit* GetPUnitAtMerging() const { return _pPUnitAtMerging; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_FeedArgSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_FeedArgSlot : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_FeedArgSlot(Expr* pExprSrc) : PUnit(pExprSrc) {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_ArgSlotNamed
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_ArgSlotNamed : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const Symbol* _pSymbol;
	RefPtr<Expr> _pExprAssigned;
	const PUnit* _pPUnitAtMerging;
public:
	// Constructor
	PUnit_ArgSlotNamed(Expr* pExprSrc, const Symbol* pSymbol, Expr* pExprAssigned) :
		PUnit(pExprSrc), _pSymbol(pSymbol), _pExprAssigned(pExprAssigned), _pPUnitAtMerging(nullptr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Expr* GetExprAssigned() const { return _pExprAssigned.get(); }
	void SetPUnitAtMerging(const PUnit* pPUnit) { _pPUnitAtMerging = pPUnit; }
	const PUnit* GetPUnitAtMerging() const { return _pPUnitAtMerging; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_FeedArgSlotNamed
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_FeedArgSlotNamed : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_FeedArgSlotNamed(Expr* pExprSrc) : PUnit(pExprSrc) {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Call
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Call : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
public:
	// Constructor
	explicit PUnit_Call(Expr* pExprSrc) : PUnit(pExprSrc) {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_Jump
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Jump : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitDest;
public:
	// Constructor
	explicit PUnit_Jump(Expr* pExprSrc, const PUnit* pPUnitDest = nullptr) :
		PUnit(pExprSrc), _pPUnitDest(pPUnitDest) {}
public:
	void SetPUnitDest(const PUnit* pPUnit) { _pPUnitDest = pPUnit; }
	const PUnit* GetPUnitDest() const { return _pPUnitDest; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_JumpSub
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_JumpSub : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitDest;
public:
	// Constructor
	explicit PUnit_JumpSub(Expr* pExprSrc, const PUnit* pPUnitDest = nullptr) :
		PUnit(pExprSrc), _pPUnitDest(pPUnitDest) {}
public:
	void SetPUnitDest(const PUnit* pPUnit) { _pPUnitDest = pPUnit; }
	const PUnit* GetPUnitDest() const { return _pPUnitDest; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_BranchIf
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_BranchIf : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitAtMerging;
public:
	// Constructor
	explicit PUnit_BranchIf(Expr* pExprSrc, const PUnit* pPUnitAtMerging = nullptr) :
		PUnit(pExprSrc), _pPUnitAtMerging(pPUnitAtMerging) {}
public:
	void SetPUnitAtMerging(const PUnit* pPUnit) { _pPUnitAtMerging = pPUnit; }
	const PUnit* GetPUnitAtMerging() const { return _pPUnitAtMerging; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// PUnit_BranchIfNot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_BranchIfNot : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit();
private:
	const PUnit* _pPUnitAtMerging;
public:
	// Constructor
	explicit PUnit_BranchIfNot(Expr* pExprSrc, const PUnit* pPUnitAtMerging = nullptr) :
		PUnit(pExprSrc), _pPUnitAtMerging(pPUnitAtMerging) {}
public:
	void SetPUnitAtMerging(const PUnit* pPUnit) { _pPUnitAtMerging = pPUnit; }
	const PUnit* GetPUnitAtMerging() const { return _pPUnitAtMerging; }
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
