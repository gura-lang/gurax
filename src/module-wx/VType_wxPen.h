﻿//==============================================================================
// VType_wxPen.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPEN_H
#define GURAX_MODULE_WX_VTYPE_WXPEN_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxGDIObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPen
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPen : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPen VTYPE_wxPen;

//------------------------------------------------------------------------------
// Value_wxPen
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPen : public Value_wxGDIObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPen);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPen");
protected:
	wxPen _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPen() = delete;
	explicit Value_wxPen(const wxPen& entity, VType& vtype = VTYPE_wxPen) :
		Value_wxGDIObject(entity, vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxPen(const Value_wxPen& src) = delete;
	Value_wxPen& operator=(const Value_wxPen& src) = delete;
	// Move constructor/operator
	Value_wxPen(Value_wxPen&& src) noexcept = delete;
	Value_wxPen& operator=(Value_wxPen&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPen() = default;
public:
	wxPen& GetEntity() { return _entity; }
	const wxPen& GetEntity() const { return _entity; }
	wxPen* GetEntityPtr() { return &_entity; }
	const wxPen* GetEntityPtr() const { return &_entity; }
public:
	static wxPen& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPen&>(value).GetEntity();
	}
	static const wxPen& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPen&>(value).GetEntity();
	}
	static wxPen* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPen&>(value).GetEntityPtr();
	}
	static const wxPen* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPen&>(value).GetEntityPtr();
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
