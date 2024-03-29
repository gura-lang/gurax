﻿//==============================================================================
// VType_wxFontMetrics.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFONTMETRICS_H
#define GURAX_MODULE_WX_VTYPE_WXFONTMETRICS_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dc.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFontMetrics
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFontMetrics : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFontMetrics VTYPE_wxFontMetrics;

//------------------------------------------------------------------------------
// Value_wxFontMetrics
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFontMetrics : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFontMetrics);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFontMetrics");
protected:
	wxFontMetrics _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFontMetrics() = delete;
	explicit Value_wxFontMetrics(const wxFontMetrics& entity, VType& vtype = VTYPE_wxFontMetrics) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxFontMetrics(const Value_wxFontMetrics& src) = delete;
	Value_wxFontMetrics& operator=(const Value_wxFontMetrics& src) = delete;
	// Move constructor/operator
	Value_wxFontMetrics(Value_wxFontMetrics&& src) noexcept = delete;
	Value_wxFontMetrics& operator=(Value_wxFontMetrics&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFontMetrics() = default;
public:
	wxFontMetrics& GetEntity() { return _entity; }
	const wxFontMetrics& GetEntity() const { return _entity; }
	wxFontMetrics* GetEntityPtr() { return &_entity; }
	const wxFontMetrics* GetEntityPtr() const { return &_entity; }
public:
	static wxFontMetrics& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFontMetrics&>(value).GetEntity();
	}
	static const wxFontMetrics& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFontMetrics&>(value).GetEntity();
	}
	static wxFontMetrics* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFontMetrics&>(value).GetEntityPtr();
	}
	static const wxFontMetrics* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFontMetrics&>(value).GetEntityPtr();
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
