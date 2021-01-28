//==============================================================================
// VType_mpf.h
//==============================================================================
#ifndef GURAX_MODULE_GMP_VTYPE_MPF_H
#define GURAX_MODULE_GMP_VTYPE_MPF_H
#include "module-gmp.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// VType_mpf
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_mpf : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_mpf VTYPE_mpf;

//------------------------------------------------------------------------------
// Value_mpf
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_mpf : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_mpf);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_mpf");
protected:
	mpf_class _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_mpf(mpf_class entity, VType& vtype = VTYPE_mpf) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_mpf(const Value_mpf& src) = delete;
	Value_mpf& operator=(const Value_mpf& src) = delete;
	// Move constructor/operator
	Value_mpf(Value_mpf&& src) noexcept = delete;
	Value_mpf& operator=(Value_mpf&& src) noexcept = delete;
protected:
	// Destructor
	~Value_mpf() = default;
public:
	mpf_class& GetEntity() { return _entity; }
	const mpf_class& GetEntity() const { return _entity; }
	mpf_class* GetEntityPtr() { return &_entity; }
	const mpf_class* GetEntityPtr() const { return &_entity; }
public:
	static mpf_class& GetEntity(Value& value) {
		return dynamic_cast<Value_mpf&>(value).GetEntity();
	}
	static const mpf_class& GetEntity(const Value& value) {
		return dynamic_cast<const Value_mpf&>(value).GetEntity();
	}
	static mpf_class* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_mpf&>(value).GetEntityPtr();
	}
	static const mpf_class* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_mpf&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_mpf::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_mpf::GetEntityPtr(value) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
	//virtual bool Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	virtual bool Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	virtual bool Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	virtual bool Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const override;
	//virtual bool Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const override;
};

Gurax_EndModuleScope(gmp)

#endif
