//==============================================================================
// VType_Iterator.h
//==============================================================================
#ifndef GURAX_VTYPE_ITERATOR_H
#define GURAX_VTYPE_ITERATOR_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Iterator
//------------------------------------------------------------------------------
class VType_Iterator : public VType {
public:
	using VType::VType;
	virtual bool IsIterator() const override { return true; }
	virtual bool IsListOrIterator() const override { return true; }
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern VType_Iterator VTYPE_Iterator;

//------------------------------------------------------------------------------
// Value_Iterator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Iterator : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Iterator);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Iterator");
protected:
	RefPtr<Iterator> _pIterator;
public:
	// Constructor
	Value_Iterator() = delete;
	explicit Value_Iterator(Iterator *pIterator, VType& vtype = VTYPE_Iterator) :
		Value_Object(vtype), _pIterator(pIterator) {}
	// Copy constructor/operator
	Value_Iterator(const Value_Iterator& src) :
		Value_Object(src), _pIterator(src._pIterator->Reference()) {}
	Value_Iterator& operator=(const Value_Iterator& src) = delete;
	// Move constructor/operator
	Value_Iterator(Value_Iterator&& src) = delete;
	Value_Iterator& operator=(Value_Iterator&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Iterator() = default;
public:
	Iterator& GetIterator() { return *_pIterator; }
	const Iterator& GetIterator() const { return *_pIterator; }
public:
	static Iterator& GetIterator(Value& value) {
		return dynamic_cast<Value_Iterator&>(value).GetIterator();
	}
	static const Iterator& GetIterator(const Value& value) {
		return dynamic_cast<const Value_Iterator&>(value).GetIterator();
	}
public:
	// Virtual functions of Object
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetIterator().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetIterator().IsEqualTo(dynamic_cast<const Value_Iterator*>(pValue)->GetIterator());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetIterator().IsLessThan(dynamic_cast<const Value_Iterator*>(pValue)->GetIterator()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDigest(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
	// Virtual functions for runtime process
	virtual bool IsIterable() const override { return true; }
	virtual bool IsIterator() const override { return true; }
	virtual bool IsMappable(const DeclArg& declArg, DeclCallable::Flags flags) const override;
	virtual void UpdateMapMode(Argument& argument) const override;
	virtual const DeclCallable* GetDeclCallable() override;
	virtual void DoCall(Processor& processor, Argument& argument) override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual Iterator* DoGenIterator() const override;
};

}

#endif
