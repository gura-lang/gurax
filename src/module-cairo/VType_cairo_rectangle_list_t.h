﻿//==============================================================================
// VType_cairo_rectangle_list_t.h
//==============================================================================
#ifndef GURAX_MODULE_CAIRO_VTYPE_CAIRO_RECTANGLE_LIST_T_H
#define GURAX_MODULE_CAIRO_VTYPE_CAIRO_RECTANGLE_LIST_T_H
#include "module-cairo.h"

Gurax_BeginModuleScope(cairo)

//------------------------------------------------------------------------------
// VType_cairo_rectangle_list_t
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_cairo_rectangle_list_t : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_cairo_rectangle_list_t VTYPE_cairo_rectangle_list_t;

//------------------------------------------------------------------------------
// Value_cairo_rectangle_list_t
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_cairo_rectangle_list_t : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_cairo_rectangle_list_t);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_cairo_rectangle_list_t");
protected:
	cairo_rectangle_list_t* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_cairo_rectangle_list_t(VType& vtype = VTYPE_cairo_rectangle_list_t) : Value_Object(vtype) {}
	explicit Value_cairo_rectangle_list_t(cairo_rectangle_list_t* entity, VType& vtype = VTYPE_cairo_rectangle_list_t) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_cairo_rectangle_list_t(const Value_cairo_rectangle_list_t& src) = delete;
	Value_cairo_rectangle_list_t& operator=(const Value_cairo_rectangle_list_t& src) = delete;
	// Move constructor/operator
	Value_cairo_rectangle_list_t(Value_cairo_rectangle_list_t&& src) noexcept = delete;
	Value_cairo_rectangle_list_t& operator=(Value_cairo_rectangle_list_t&& src) noexcept = delete;
protected:
	// Destructor
	~Value_cairo_rectangle_list_t() = default;
public:
	cairo_rectangle_list_t& GetEntity() { return *_entity; }
	const cairo_rectangle_list_t& GetEntity() const { return *_entity; }
	cairo_rectangle_list_t* GetEntityPtr() { return _entity; }
	const cairo_rectangle_list_t* GetEntityPtr() const { return _entity; }
public:
	static cairo_rectangle_list_t& GetEntity(Value& value) {
		return dynamic_cast<Value_cairo_rectangle_list_t&>(value).GetEntity();
	}
	static const cairo_rectangle_list_t& GetEntity(const Value& value) {
		return dynamic_cast<const Value_cairo_rectangle_list_t&>(value).GetEntity();
	}
	static cairo_rectangle_list_t* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_cairo_rectangle_list_t&>(value).GetEntityPtr();
	}
	static const cairo_rectangle_list_t* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_cairo_rectangle_list_t&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_cairo_rectangle_list_t::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_cairo_rectangle_list_t::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_cairo_rectangle_list
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_cairo_rectangle_list : public Iterator {
private:
	RefPtr<Value_cairo_rectangle_list_t> _pValue;
	int _idx;
public:
	Iterator_cairo_rectangle_list(Value_cairo_rectangle_list_t* pValue) : _pValue(pValue), _idx(0) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenDetermined;
	}
	virtual size_t GetLength() const override { return _pValue->GetEntity().num_rectangles; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(cairo)

#endif
