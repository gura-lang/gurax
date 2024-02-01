//==============================================================================
// VType_ArgMapper.h
//==============================================================================
#ifndef GURAX_VTYPE_ARGMAPPER_H
#define GURAX_VTYPE_ARGMAPPER_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_ArgMapper
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ArgMapper : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ArgMapper VTYPE_ArgMapper;

//------------------------------------------------------------------------------
// Value_ArgMapper
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ArgMapper : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ArgMapper);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ArgMapper");
protected:
	RefPtr<Iterator> _pIterator;
	RefPtr<Value> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	Value_ArgMapper() = delete;
	explicit Value_ArgMapper(Iterator* pIterator, VType& vtype = VTYPE_Any) :
		Value_Object(vtype), _pIterator(pIterator) {}
	// Copy constructor/operator
	Value_ArgMapper(const Value_ArgMapper& src) = delete;
	Value_ArgMapper& operator=(const Value_ArgMapper& src) = delete;
	// Move constructor/operator
	Value_ArgMapper(Value_ArgMapper&& src) = delete;
	Value_ArgMapper& operator=(Value_ArgMapper&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ArgMapper() = default;
public:
	Iterator& GetIterator() { return *_pIterator; }
	const Iterator& GetIterator() const { return *_pIterator; }
public:
	static Iterator& GetIterator(Value& value) {
		return dynamic_cast<Value_ArgMapper&>(value).GetIterator();
	}
	static const Iterator& GetIterator(const Value& value) {
		return dynamic_cast<const Value_ArgMapper&>(value).GetIterator();
	}
public:
	// Virtual functions of Object
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetIterator().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetIterator().IsEqualTo(Value_ArgMapper::GetIterator(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetIterator().IsLessThan(Value_ArgMapper::GetIterator(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual Iterator* DoGenIterator() const override;
public:
	// Virtual functions for runtime process
	virtual bool ReadyToPickValue(Processor& processor, Frame& frame, DeclArg& declArg) override;
	virtual bool ReadyToPickValueWithoutCast() override;
	virtual Value* PickValue() override { return _pValue.Reference(); }
	virtual void UpdateIteratorInfo(Iterator::Flags& flags, size_t& len) const override;
};

}

#endif
