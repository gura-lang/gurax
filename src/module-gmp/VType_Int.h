//==============================================================================
// VType_Int.h
//==============================================================================
#ifndef GURAX_MODULE_GMP_VTYPE_MPZ_H
#define GURAX_MODULE_GMP_VTYPE_MPZ_H
#include "module-gmp.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// VType_Int
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Int : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Int VTYPE_Int;

//------------------------------------------------------------------------------
// Value_Int
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Int : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Int);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Int");
protected:
	mpz_class _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Int(mpz_class entity, VType& vtype = VTYPE_Int) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_Int(const Value_Int& src) = delete;
	Value_Int& operator=(const Value_Int& src) = delete;
	// Move constructor/operator
	Value_Int(Value_Int&& src) noexcept = delete;
	Value_Int& operator=(Value_Int&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Int() = default;
public:
	mpz_class& GetEntity() { return _entity; }
	const mpz_class& GetEntity() const { return _entity; }
	mpz_class* GetEntityPtr() { return &_entity; }
	const mpz_class* GetEntityPtr() const { return &_entity; }
public:
	static mpz_class& GetEntity(Value& value) {
		return dynamic_cast<Value_Int&>(value).GetEntity();
	}
	static const mpz_class& GetEntity(const Value& value) {
		return dynamic_cast<const Value_Int&>(value).GetEntity();
	}
	static mpz_class* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_Int&>(value).GetEntityPtr();
	}
	static const mpz_class* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_Int&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_Int::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_Int::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
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
