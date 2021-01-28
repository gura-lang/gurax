//==============================================================================
// VType_Random.h
//==============================================================================
#ifndef GURAX_MODULE_GMP_VTYPE_RANDOM_H
#define GURAX_MODULE_GMP_VTYPE_RANDOM_H
#include "module-gmp.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// VType_Random
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Random : public VType {
private:
	static gmp_randstate_t _stateGlobal;
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	static gmp_randstate_t& GetStateGlobal() { return _stateGlobal; }
};

extern GURAX_DLLDECLARE VType_Random VTYPE_Random;

//------------------------------------------------------------------------------
// Value_Random
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Random : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Random);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Random");
protected:
	gmp_randstate_t _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Random(VType& vtype = VTYPE_Random) : Value_Object(vtype) {}
	// Copy constructor/operator
	Value_Random(const Value_Random& src) = delete;
	Value_Random& operator=(const Value_Random& src) = delete;
	// Move constructor/operator
	Value_Random(Value_Random&& src) noexcept = delete;
	Value_Random& operator=(Value_Random&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Random() = default;
public:
	gmp_randstate_t& GetEntity() { return _entity; }
	const gmp_randstate_t& GetEntity() const { return _entity; }
	gmp_randstate_t* GetEntityPtr() { return &_entity; }
	const gmp_randstate_t* GetEntityPtr() const { return &_entity; }
public:
	static gmp_randstate_t& GetEntity(Value& value) {
		return dynamic_cast<Value_Random&>(value).GetEntity();
	}
	static const gmp_randstate_t& GetEntity(const Value& value) {
		return dynamic_cast<const Value_Random&>(value).GetEntity();
	}
	static gmp_randstate_t* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_Random&>(value).GetEntityPtr();
	}
	static const gmp_randstate_t* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_Random&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_Random::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_Random::GetEntityPtr(value) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gmp)

#endif
