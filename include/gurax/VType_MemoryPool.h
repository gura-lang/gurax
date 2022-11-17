//==============================================================================
// VType_MemoryPool.h
//==============================================================================
#ifndef GURAX_VTYPE_MEMORYPOOL_H
#define GURAX_VTYPE_MEMORYPOOL_H
#include "VType_Object.h"
#include "MemoryPool.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_MemoryPool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_MemoryPool : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_MemoryPool VTYPE_MemoryPool;

//------------------------------------------------------------------------------
// Value_MemoryPool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_MemoryPool : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_MemoryPool);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_MemoryPool");
protected:
	MemoryPool& _memoryPool;
public:
	static VType& vtype;
public:
	// Constructor
	Value_MemoryPool() = delete;
	explicit Value_MemoryPool(MemoryPool& memoryPool, VType& vtype = VTYPE_MemoryPool) :
		Value_Object(vtype), _memoryPool(memoryPool) {}
	// Copy constructor/operator
	Value_MemoryPool(const Value_MemoryPool& src) :
		Value_Object(src), _memoryPool(src._memoryPool) {}
	Value_MemoryPool& operator=(const Value_MemoryPool& src) = delete;
	// Move constructor/operator
	Value_MemoryPool(Value_MemoryPool&& src) noexcept = delete;
	Value_MemoryPool& operator=(Value_MemoryPool&& src) noexcept = delete;
protected:
	// Destructor
	~Value_MemoryPool() = default;
public:
	MemoryPool& GetMemoryPool() { return _memoryPool; }
	const MemoryPool& GetMemoryPool() const { return _memoryPool; }
public:
	static MemoryPool& GetMemoryPool(Value& value) {
		return dynamic_cast<Value_MemoryPool&>(value).GetMemoryPool();
	}
	static const MemoryPool& GetMemoryPool(const Value& value) {
		return dynamic_cast<const Value_MemoryPool&>(value).GetMemoryPool();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetMemoryPool().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetMemoryPool().IsEqualTo(Value_MemoryPool::GetMemoryPool(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetMemoryPool().IsLessThan(Value_MemoryPool::GetMemoryPool(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
