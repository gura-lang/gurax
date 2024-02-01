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
class GURAX_DLLDECLARE VType_Iterator : public VType {
public:
	using VType::VType;
	virtual bool IsIterator() const override { return true; }
	virtual bool IsListOrIterator() const override { return true; }
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const override;
public:
	static Value* Method_Align(
		Processor& processor, Argument& argument, Iterator& iteratorSrc);
	static Value* Method_ArgMax(Argument& argument, Iterator& iteratorThis);
	static Value* Method_ArgMin(Argument& argument, Iterator& iteratorThis);
	static Value* Method_Combination(
		Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner);
	static Value* Method_Cycle_List(
		Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner);
	static Value* Method_Filter(Processor& processor, Argument& argument, Iterator& iteratorSrc);
	static Value* Method_Find(Processor& processor, Argument& argument, Iterator& iteratorSrc);
	static Value* Method_Flatten(
		Processor& processor, Argument& argument, Iterator& iteratorSrc);
	static Value* Method_Fold(
		Processor& processor, Argument& argument, Iterator& iteratorSrc);
	static Value* Method_Permutation(
		Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner);
	static Value* Method_PingPong(
		Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner);
	static Value* Method_Reverse(
		Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner);
	static Value* Method_Since(Processor& processor, Argument& argument,
							Iterator& iteratorSrc, bool includeFirstFlag);
	static Value* Method_Sort(
		Processor& processor, Argument& argument, const ValueTypedOwner& valueTypedOwner);
	static Value* Method_Until(Processor& processor, Argument& argument,
							Iterator& iteratorSrc, bool includeLastFlag);
	static Value* Method_While(Processor& processor, Argument& argument, Iterator& iteratorSrc);
};

extern GURAX_DLLDECLARE VType_Iterator VTYPE_Iterator;

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
	static VType& vtype;
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
	Iterator& GetIterator() const { return *_pIterator; }
public:
	static Iterator& GetIterator(Value& value) {
		return dynamic_cast<Value_Iterator&>(value).GetIterator();
	}
	static Iterator& GetIterator(const Value& value) {
		return dynamic_cast<const Value_Iterator&>(value).GetIterator();
	}
public:
	// Virtual functions of Object
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetIterator().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetIterator().IsEqualTo(dynamic_cast<const Value_Iterator&>(value).GetIterator());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetIterator().IsLessThan(dynamic_cast<const Value_Iterator&>(value).GetIterator()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	// Virtual functions for runtime process
	virtual bool IsIterable() const override { return true; }
	virtual bool IsIterableOrTuple() const override { return true; }
	virtual bool IsIterator() const override { return true; }
	virtual bool IsMappable(const DeclArg& declArg, DeclCallable::Flags flags) const override;
	virtual void UpdateMapMode(Argument& argument) const override;
	virtual bool FeedExpandToArgument(Processor& processor, Frame& frame, Argument& argument) override;
	virtual const DeclCallable* GetDeclCallable() override;
	virtual void DoCall(Processor& processor, Argument& argument) override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
	virtual bool DoEmptyIndexGet(Value** ppValue) const override;
	virtual bool DoEmptyIndexSet(RefPtr<Value> pValue) override;
	virtual bool DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const override;
	virtual bool DoSingleIndexSet(Processor& processor, const Value& valueIndex, RefPtr<Value> pValue) override;
	virtual Iterator* DoGenIterator() const override;
};

}

#endif
