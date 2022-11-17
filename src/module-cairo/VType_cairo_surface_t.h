//==============================================================================
// VType_cairo_surface_t.h
//==============================================================================
#ifndef GURAX_MODULE_CAIRO_VTYPE_CAIRO_SURFACE_T_H
#define GURAX_MODULE_CAIRO_VTYPE_CAIRO_SURFACE_T_H
#include "module-cairo.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// VType_cairo_surface_t
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_cairo_surface_t : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_cairo_surface_t VTYPE_cairo_surface_t;

//------------------------------------------------------------------------------
// Value_cairo_surface_t
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_cairo_surface_t : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_cairo_surface_t);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_cairo_surface_t");
protected:
	cairo_surface_t* _entity;
	RefPtr<Stream> _pStream;	// maybe nullptr
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_cairo_surface_t(VType& vtype = VTYPE_cairo_surface_t) : Value_Object(vtype) {}
	explicit Value_cairo_surface_t(cairo_surface_t* entity, Stream* pStream = nullptr, VType& vtype = VTYPE_cairo_surface_t) :
		Value_Object(vtype), _entity(entity), _pStream(pStream) {}
	// Copy constructor/operator
	Value_cairo_surface_t(const Value_cairo_surface_t& src) = delete;
	Value_cairo_surface_t& operator=(const Value_cairo_surface_t& src) = delete;
	// Move constructor/operator
	Value_cairo_surface_t(Value_cairo_surface_t&& src) noexcept = delete;
	Value_cairo_surface_t& operator=(Value_cairo_surface_t&& src) noexcept = delete;
protected:
	// Destructor
	~Value_cairo_surface_t() = default;
public:
	cairo_surface_t& GetEntity() { return *_entity; }
	const cairo_surface_t& GetEntity() const { return *_entity; }
	cairo_surface_t* GetEntityPtr() { return _entity; }
	const cairo_surface_t* GetEntityPtr() const { return _entity; }
public:
	static cairo_surface_t& GetEntity(Value& value) {
		return dynamic_cast<Value_cairo_surface_t&>(value).GetEntity();
	}
	static const cairo_surface_t& GetEntity(const Value& value) {
		return dynamic_cast<const Value_cairo_surface_t&>(value).GetEntity();
	}
	static cairo_surface_t* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_cairo_surface_t&>(value).GetEntityPtr();
	}
	static const cairo_surface_t* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_cairo_surface_t&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_cairo_surface_t::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_cairo_surface_t::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(cairo)

#endif
