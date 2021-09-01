//==============================================================================
// VType_wxRect2DDouble.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRECT2DDOUBLE_H
#define GURAX_MODULE_WX_VTYPE_WXRECT2DDOUBLE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/graphics.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRect2DDouble
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRect2DDouble : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRect2DDouble VTYPE_wxRect2DDouble;

//------------------------------------------------------------------------------
// Value_wxRect2DDouble
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRect2DDouble : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRect2DDouble);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRect2DDouble");
protected:
	wxRect2DDouble _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRect2DDouble() = delete;
	explicit Value_wxRect2DDouble(const wxRect2DDouble& entity, VType& vtype = VTYPE_wxRect2DDouble) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxRect2DDouble(const Value_wxRect2DDouble& src) = delete;
	Value_wxRect2DDouble& operator=(const Value_wxRect2DDouble& src) = delete;
	// Move constructor/operator
	Value_wxRect2DDouble(Value_wxRect2DDouble&& src) noexcept = delete;
	Value_wxRect2DDouble& operator=(Value_wxRect2DDouble&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRect2DDouble() = default;
public:
	wxRect2DDouble& GetEntity() { return _entity; }
	const wxRect2DDouble& GetEntity() const { return _entity; }
	wxRect2DDouble* GetEntityPtr() { return &_entity; }
	const wxRect2DDouble* GetEntityPtr() const { return &_entity; }
public:
	static wxRect2DDouble& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRect2DDouble&>(value).GetEntity();
	}
	static const wxRect2DDouble& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRect2DDouble&>(value).GetEntity();
	}
	static wxRect2DDouble* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRect2DDouble&>(value).GetEntityPtr();
	}
	static const wxRect2DDouble* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRect2DDouble&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntityPtr(*this) == GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(GetEntityPtr(*this) < GetEntityPtr(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif