//==============================================================================
// VType_Rational.h
//==============================================================================
#ifndef GURAX_MODULE_GMP_VTYPE_MPQ_H
#define GURAX_MODULE_GMP_VTYPE_MPQ_H
#include "module-gmp.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// VType_Rational
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Rational : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Rational VTYPE_Rational;

//------------------------------------------------------------------------------
// Value_Rational
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Rational : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Rational);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Rational");
protected:
	mpq_class _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Rational(mpq_class entity, VType& vtype = VTYPE_Rational) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_Rational(const Value_Rational& src) = delete;
	Value_Rational& operator=(const Value_Rational& src) = delete;
	// Move constructor/operator
	Value_Rational(Value_Rational&& src) noexcept = delete;
	Value_Rational& operator=(Value_Rational&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Rational() = default;
public:
	mpq_class& GetEntity() { return _entity; }
	const mpq_class& GetEntity() const { return _entity; }
	mpq_class* GetEntityPtr() { return &_entity; }
	const mpq_class* GetEntityPtr() const { return &_entity; }
public:
	static mpq_class& GetEntity(Value& value) {
		return dynamic_cast<Value_Rational&>(value).GetEntity();
	}
	static const mpq_class& GetEntity(const Value& value) {
		return dynamic_cast<const Value_Rational&>(value).GetEntity();
	}
	static mpq_class* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_Rational&>(value).GetEntityPtr();
	}
	static const mpq_class* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_Rational&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_Rational::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_Rational::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gmp)

#endif
