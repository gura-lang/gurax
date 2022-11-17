//==============================================================================
// VType_cairo_font_extents_t.h
//==============================================================================
#ifndef GURAX_MODULE_CAIRO_VTYPE_CAIRO_FONT_EXTENTS_T_H
#define GURAX_MODULE_CAIRO_VTYPE_CAIRO_FONT_EXTENTS_T_H
#include "module-cairo.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// VType_cairo_font_extents_t
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_cairo_font_extents_t : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_cairo_font_extents_t VTYPE_cairo_font_extents_t;

//------------------------------------------------------------------------------
// Value_cairo_font_extents_t
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_cairo_font_extents_t : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_cairo_font_extents_t);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_cairo_font_extents_t");
protected:
	cairo_font_extents_t _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_cairo_font_extents_t(VType& vtype = VTYPE_cairo_font_extents_t) : Value_Object(vtype) {}
	explicit Value_cairo_font_extents_t(const cairo_font_extents_t& entity, VType& vtype = VTYPE_cairo_font_extents_t) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_cairo_font_extents_t(const Value_cairo_font_extents_t& src) = delete;
	Value_cairo_font_extents_t& operator=(const Value_cairo_font_extents_t& src) = delete;
	// Move constructor/operator
	Value_cairo_font_extents_t(Value_cairo_font_extents_t&& src) noexcept = delete;
	Value_cairo_font_extents_t& operator=(Value_cairo_font_extents_t&& src) noexcept = delete;
protected:
	// Destructor
	~Value_cairo_font_extents_t() = default;
public:
	cairo_font_extents_t& GetEntity() { return _entity; }
	const cairo_font_extents_t& GetEntity() const { return _entity; }
	cairo_font_extents_t* GetEntityPtr() { return &_entity; }
	const cairo_font_extents_t* GetEntityPtr() const { return &_entity; }
public:
	static cairo_font_extents_t& GetEntity(Value& value) {
		return dynamic_cast<Value_cairo_font_extents_t&>(value).GetEntity();
	}
	static const cairo_font_extents_t& GetEntity(const Value& value) {
		return dynamic_cast<const Value_cairo_font_extents_t&>(value).GetEntity();
	}
	static cairo_font_extents_t* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_cairo_font_extents_t&>(value).GetEntityPtr();
	}
	static const cairo_font_extents_t* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_cairo_font_extents_t&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_cairo_font_extents_t::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_cairo_font_extents_t::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(cairo)

#endif
