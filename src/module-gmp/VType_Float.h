//==============================================================================
// VType_Float.h
//==============================================================================
#ifndef GURAX_MODULE_GMP_VTYPE_MPF_H
#define GURAX_MODULE_GMP_VTYPE_MPF_H
#include "module-gmp.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// VType_Float
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Float : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Float VTYPE_Float;

//------------------------------------------------------------------------------
// Value_Float
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Float : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Float);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Float");
protected:
	mpf_class _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Float(mpf_class entity, VType& vtype = VTYPE_Float) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_Float(const Value_Float& src) = delete;
	Value_Float& operator=(const Value_Float& src) = delete;
	// Move constructor/operator
	Value_Float(Value_Float&& src) noexcept = delete;
	Value_Float& operator=(Value_Float&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Float() = default;
public:
	mpf_class& GetEntity() { return _entity; }
	const mpf_class& GetEntity() const { return _entity; }
	mpf_class* GetEntityPtr() { return &_entity; }
	const mpf_class* GetEntityPtr() const { return &_entity; }
public:
	static mpf_class& GetEntity(Value& value) {
		return dynamic_cast<Value_Float&>(value).GetEntity();
	}
	static const mpf_class& GetEntity(const Value& value) {
		return dynamic_cast<const Value_Float&>(value).GetEntity();
	}
	static mpf_class* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_Float&>(value).GetEntityPtr();
	}
	static const mpf_class* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_Float&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_Float::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_Float::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
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
