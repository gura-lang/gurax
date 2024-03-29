﻿//==============================================================================
// VType_wxAuiPanelInfo.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXAUIPANELINFO_H
#define GURAX_MODULE_WX_VTYPE_WXAUIPANELINFO_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/aui/framemanager.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAuiPanelInfo
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAuiPanelInfo : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAuiPanelInfo VTYPE_wxAuiPanelInfo;

//------------------------------------------------------------------------------
// Value_wxAuiPanelInfo
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAuiPanelInfo : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAuiPanelInfo);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAuiPanelInfo");
protected:
	wxAuiPanelInfo _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAuiPanelInfo() = delete;
	explicit Value_wxAuiPanelInfo(const wxAuiPanelInfo& entity, VType& vtype = VTYPE_wxAuiPanelInfo) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxAuiPanelInfo(const Value_wxAuiPanelInfo& src) = delete;
	Value_wxAuiPanelInfo& operator=(const Value_wxAuiPanelInfo& src) = delete;
	// Move constructor/operator
	Value_wxAuiPanelInfo(Value_wxAuiPanelInfo&& src) noexcept = delete;
	Value_wxAuiPanelInfo& operator=(Value_wxAuiPanelInfo&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAuiPanelInfo() = default;
public:
	wxAuiPanelInfo& GetEntity() { return _entity; }
	const wxAuiPanelInfo& GetEntity() const { return _entity; }
	wxAuiPanelInfo* GetEntityPtr() { return &_entity; }
	const wxAuiPanelInfo* GetEntityPtr() const { return &_entity; }
public:
	static wxAuiPanelInfo& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAuiPanelInfo&>(value).GetEntity();
	}
	static const wxAuiPanelInfo& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAuiPanelInfo&>(value).GetEntity();
	}
	static wxAuiPanelInfo* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAuiPanelInfo&>(value).GetEntityPtr();
	}
	static const wxAuiPanelInfo* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAuiPanelInfo&>(value).GetEntityPtr();
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
