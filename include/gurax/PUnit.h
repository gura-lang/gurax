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
	const PUnit* _pPUnitNext;
public:
	// Constructor
	PUnit() : _pPUnitNext(nullptr) {}
	// Copy constructor/operator
	PUnit(const PUnit& src) = delete;
	PUnit& operator=(const PUnit& src) = delete;
	// Move constructor/operator
	PUnit(PUnit&& src) = delete;
	PUnit& operator=(PUnit&& src) noexcept = delete;
	// Destructor
	virtual ~PUnit() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const PUnit* pPUnit) const { return this == pPUnit; }
	bool IsEqualTo(const PUnit* pPUnit) const { return IsIdentical(pPUnit); }
	bool IsLessThan(const PUnit* pPUnit) const { return this < pPUnit; }
	String ToString() const { return ToString(StringStyle::Empty); }
public:
	void SetPUnitNext(const PUnit* pPUnit) { _pPUnitNext = pPUnit; }
	const PUnit* GetPUnitNext() const { return _pPUnitNext; }
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
// PUnitComposer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnitComposer {
private:
	PUnitStack _punitStack;
	PUnit *_pPUnitCont;
public:
	// Constructor
	PUnitComposer() : _pPUnitCont(nullptr) {}
	// Copy constructor/operator
	PUnitComposer(const PUnitComposer& src) = delete;
	PUnitComposer& operator=(const PUnitComposer& src) = delete;
	// Move constructor/operator
	PUnitComposer(PUnitComposer&& src) = delete;
	PUnitComposer& operator=(PUnitComposer&& src) noexcept = delete;
	// Destructor
	virtual ~PUnitComposer() = default;
public:
	PUnitStack& GetPUnitStack() { return _punitStack; }
	PUnit* GetPUnitCont() { return _pPUnitCont; }
	void Begin() { _pPUnitCont = nullptr; }
	void Add(PUnit* pPUnit);
};

//------------------------------------------------------------------------------
// PUnit_Value
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PUnit_Value : public PUnit {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator_PUnit("Value");
private:
	RefPtr<Value> _pValue;
public:
	// Constructor
	PUnit_Value(Value* pValue) : _pValue(pValue) {}
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
	Gurax_MemoryPoolAllocator_PUnit("Lookup");
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	PUnit_Lookup(const Symbol* pSymbol) : _pSymbol(pSymbol) {}
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
	Gurax_MemoryPoolAllocator_PUnit("Assign");
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	PUnit_Assign(const Symbol* pSymbol) : _pSymbol(pSymbol) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
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
	Gurax_MemoryPoolAllocator_PUnit("Erase");
public:
	// Constructor
	PUnit_Erase() {}
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
	Gurax_MemoryPoolAllocator_PUnit("UnaryOp");
private:
	const Operator* _pOperator;
public:
	// Constructor
	PUnit_UnaryOp(const Operator* pOperator) : _pOperator(pOperator) {}
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
	Gurax_MemoryPoolAllocator_PUnit("BinaryOp");
private:
	const Operator* _pOperator;
public:
	// Constructor
	PUnit_BinaryOp(const Operator* pOperator) : _pOperator(pOperator) {}
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
	Gurax_MemoryPoolAllocator_PUnit("List");
private:
	size_t _sizeReserve;
public:
	// Constructor
	PUnit_CreateList(size_t sizeReserve = 0) : _sizeReserve(sizeReserve) {}
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
	Gurax_MemoryPoolAllocator_PUnit("AddList");
public:
	// Constructor
	PUnit_AddList() {}
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
	Gurax_MemoryPoolAllocator_PUnit("CreateIndex");
private:
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_Index(Attribute* pAttr) : _pAttr(pAttr) {}
public:
	const Attribute& GetAttr() const { return *_pAttr; }
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
	Gurax_MemoryPoolAllocator_PUnit("FeedIndex");
public:
	// Constructor
	PUnit_FeedIndex() {}
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
	Gurax_MemoryPoolAllocator_PUnit("IndexGet");
public:
	// Constructor
	PUnit_IndexGet() {}
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
	Gurax_MemoryPoolAllocator_PUnit("IndexSet");
public:
	// Constructor
	PUnit_IndexSet() {}
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
	Gurax_MemoryPoolAllocator_PUnit("PropGet");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_PropGet(const Symbol* pSymbol, Attribute* pAttr) :
		_pSymbol(pSymbol), _pAttr(pAttr) {}
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
	Gurax_MemoryPoolAllocator_PUnit("PropSet");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_PropSet(const Symbol* pSymbol, Attribute* pAttr) : _pSymbol(pSymbol), _pAttr(pAttr) {}
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
	Gurax_MemoryPoolAllocator_PUnit("Member");
private:
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_Member(const Symbol* pSymbol, Attribute* pAttr) : _pSymbol(pSymbol), _pAttr(pAttr) {}
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
	Gurax_MemoryPoolAllocator_PUnit("CreateArgument");
private:
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	PUnit_Argument(Attribute* pAttr) : _pAttr(pAttr) {}
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
	Gurax_MemoryPoolAllocator_PUnit("ArgSlot");
private:
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	explicit PUnit_ArgSlot(Expr* pExpr) : _pExpr(pExpr) {}
public:
	const Expr* GetExpr() const { return _pExpr.get(); }
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
	Gurax_MemoryPoolAllocator_PUnit("FeedArgSlot");
public:
	// Constructor
	PUnit_FeedArgSlot() {}
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
	Gurax_MemoryPoolAllocator_PUnit("ArgSlotNamed");
private:
	const Symbol* _pSymbol;
	RefPtr<Expr> _pExpr;
public:
	// Constructor
	explicit PUnit_ArgSlotNamed(const Symbol* pSymbol, Expr* pExpr) :
		_pSymbol(pSymbol), _pExpr(pExpr) {}
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Expr* GetExpr() const { return _pExpr.get(); }
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
	Gurax_MemoryPoolAllocator_PUnit("FeedArgSlotNamed");
public:
	// Constructor
	PUnit_FeedArgSlotNamed() {}
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
	Gurax_MemoryPoolAllocator_PUnit("Call");
public:
	// Constructor
	PUnit_Call() {}
public:
	// Virtual functions of PUnit
	virtual void Exec(Processor& processor) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
