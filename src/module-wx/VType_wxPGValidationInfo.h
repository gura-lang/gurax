﻿//==============================================================================
// VType_wxPGValidationInfo.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPGVALIDATIONINFO_H
#define GURAX_MODULE_WX_VTYPE_WXPGVALIDATIONINFO_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPGValidationInfo
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPGValidationInfo : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPGValidationInfo VTYPE_wxPGValidationInfo;

//------------------------------------------------------------------------------
// Value_wxPGValidationInfo
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPGValidationInfo : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPGValidationInfo);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPGValidationInfo");
protected:
	wxPGValidationInfo _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPGValidationInfo() = delete;
	explicit Value_wxPGValidationInfo(const wxPGValidationInfo& entity, VType& vtype = VTYPE_wxPGValidationInfo) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxPGValidationInfo(const Value_wxPGValidationInfo& src) = delete;
	Value_wxPGValidationInfo& operator=(const Value_wxPGValidationInfo& src) = delete;
	// Move constructor/operator
	Value_wxPGValidationInfo(Value_wxPGValidationInfo&& src) noexcept = delete;
	Value_wxPGValidationInfo& operator=(Value_wxPGValidationInfo&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPGValidationInfo() = default;
public:
	wxPGValidationInfo& GetEntity() { return _entity; }
	const wxPGValidationInfo& GetEntity() const { return _entity; }
	wxPGValidationInfo* GetEntityPtr() { return &_entity; }
	const wxPGValidationInfo* GetEntityPtr() const { return &_entity; }
public:
	static wxPGValidationInfo& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPGValidationInfo&>(value).GetEntity();
	}
	static const wxPGValidationInfo& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPGValidationInfo&>(value).GetEntity();
	}
	static wxPGValidationInfo* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPGValidationInfo&>(value).GetEntityPtr();
	}
	static const wxPGValidationInfo* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPGValidationInfo&>(value).GetEntityPtr();
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
