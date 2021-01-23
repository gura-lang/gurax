//==============================================================================
// VType_mpq.h
//==============================================================================
#ifndef GURAX_MODULE_GMP_VTYPE_MPQ_H
#define GURAX_MODULE_GMP_VTYPE_MPQ_H
#include "module-gmp.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// VType_mpq
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_mpq : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_mpq VTYPE_mpq;

//------------------------------------------------------------------------------
// Value_mpq
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_mpq : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_mpq);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_mpq");
protected:
	mpq_class _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_mpq(const mpq_class& entity, VType& vtype = VTYPE_mpq) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_mpq(const Value_mpq& src) = delete;
	Value_mpq& operator=(const Value_mpq& src) = delete;
	// Move constructor/operator
	Value_mpq(Value_mpq&& src) noexcept = delete;
	Value_mpq& operator=(Value_mpq&& src) noexcept = delete;
protected:
	// Destructor
	~Value_mpq() = default;
public:
	mpq_class& GetEntity() { return _entity; }
	const mpq_class& GetEntity() const { return _entity; }
	mpq_class* GetEntityPtr() { return &_entity; }
	const mpq_class* GetEntityPtr() const { return &_entity; }
public:
	static mpq_class& GetEntity(Value& value) {
		return dynamic_cast<Value_mpq&>(value).GetEntity();
	}
	static const mpq_class& GetEntity(const Value& value) {
		return dynamic_cast<const Value_mpq&>(value).GetEntity();
	}
	static mpq_class* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_mpq&>(value).GetEntityPtr();
	}
	static const mpq_class* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_mpq&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_mpq::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_mpq::GetEntityPtr(value) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gmp)

#endif
