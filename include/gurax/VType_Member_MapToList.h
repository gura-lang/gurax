//==============================================================================
// VType_Member_MapToList.h
//==============================================================================
#ifndef GURAX_VTYPE_MEMBER_MAPTOLIST_H
#define GURAX_VTYPE_MEMBER_MAPTOLIST_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member_MapToList
//------------------------------------------------------------------------------
class VType_Member_MapToList : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Member_MapToList VTYPE_Member_MapToList;

//------------------------------------------------------------------------------
// Value_Member_MapToList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Member_MapToList : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Member_MapToList);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Member_MapToList");
protected:
	RefPtr<Iterator> _pIteratorTarget;
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	Value_Member_MapToList(Iterator* pIteratorTarget, const Symbol* pSymbol, Attribute* pAttr, VType& vtype = VTYPE_Member_MapToList) :
		Value_Object(vtype), _pIteratorTarget(pIteratorTarget), _pSymbol(pSymbol), _pAttr(pAttr) {}
	// Copy constructor/operator
	Value_Member_MapToList(const Value_Member_MapToList& src) = delete;
	Value_Member_MapToList& operator=(const Value_Member_MapToList& src) = delete;
	// Move constructor/operator
	Value_Member_MapToList(Value_Member_MapToList&& src) = delete;
	Value_Member_MapToList& operator=(Value_Member_MapToList&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Member_MapToList() = default;
public:
	Iterator& GetIteratorTarget() { return *_pIteratorTarget; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return reinterpret_cast<size_t>(this); }
	virtual bool IsEqualTo(const Value* pValue) const override { return this == pValue; }
	virtual bool IsLessThan(const Value* pValue) const override { return this < pValue; }
	virtual String ToStringDetail(const StringStyle& ss) const override;
	virtual const DeclCallable* GetDeclCallable() const override;
	virtual void DoCall(Processor& processor, Argument& argument) override;
	virtual Value* DoIndexGet(const Index& index) const override;
	virtual void DoIndexSet(const Index& index, Value* pValue) override;
	virtual Value* DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag) override;
	virtual bool DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr) override;
};

}

#endif
