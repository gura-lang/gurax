//==============================================================================
// VType_mpz.h
//==============================================================================
#ifndef GURAX_MODULE_GMP_VTYPE_MPZ_H
#define GURAX_MODULE_GMP_VTYPE_MPZ_H
#include "module-gmp.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// VType_mpz
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_mpz : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_mpz VTYPE_mpz;

//------------------------------------------------------------------------------
// Value_mpz
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_mpz : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_mpz);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_mpz");
protected:
	mpz_class _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_mpz(mpz_class entity, VType& vtype = VTYPE_mpz) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_mpz(const Value_mpz& src) = delete;
	Value_mpz& operator=(const Value_mpz& src) = delete;
	// Move constructor/operator
	Value_mpz(Value_mpz&& src) noexcept = delete;
	Value_mpz& operator=(Value_mpz&& src) noexcept = delete;
protected:
	// Destructor
	~Value_mpz() = default;
public:
	mpz_class& GetEntity() { return _entity; }
	const mpz_class& GetEntity() const { return _entity; }
	mpz_class* GetEntityPtr() { return &_entity; }
	const mpz_class* GetEntityPtr() const { return &_entity; }
public:
	static mpz_class& GetEntity(Value& value) {
		return dynamic_cast<Value_mpz&>(value).GetEntity();
	}
	static const mpz_class& GetEntity(const Value& value) {
		return dynamic_cast<const Value_mpz&>(value).GetEntity();
	}
	static mpz_class* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_mpz&>(value).GetEntityPtr();
	}
	static const mpz_class* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_mpz&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_mpz::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_mpz::GetEntityPtr(value) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	virtual bool Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	virtual bool Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	virtual bool Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const override;
};

Gurax_EndModuleScope(gmp)

#endif
