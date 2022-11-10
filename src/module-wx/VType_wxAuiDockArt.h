﻿//==============================================================================
// VType_wxAuiDockArt.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXAUIDOCKART_H
#define GURAX_MODULE_WX_VTYPE_WXAUIDOCKART_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/aui/framemanager.h>
#include <wx/aui/dockart.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAuiDockArt
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAuiDockArt : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAuiDockArt VTYPE_wxAuiDockArt;

//------------------------------------------------------------------------------
// Value_wxAuiDockArt
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAuiDockArt : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAuiDockArt);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAuiDockArt");
protected:
	wxAuiDockArt* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAuiDockArt() = delete;
	explicit Value_wxAuiDockArt(wxAuiDockArt* pEntity, VType& vtype = VTYPE_wxAuiDockArt) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxAuiDockArt(const wxAuiDockArt& entity, VType& vtype = VTYPE_wxAuiDockArt) :
		Value_Object(vtype), _pEntity(const_cast<wxAuiDockArt*>(&entity)) {}
	// Copy constructor/operator
	Value_wxAuiDockArt(const Value_wxAuiDockArt& src) = delete;
	Value_wxAuiDockArt& operator=(const Value_wxAuiDockArt& src) = delete;
	// Move constructor/operator
	Value_wxAuiDockArt(Value_wxAuiDockArt&& src) noexcept = delete;
	Value_wxAuiDockArt& operator=(Value_wxAuiDockArt&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAuiDockArt() = default;
public:
	wxAuiDockArt& GetEntity() { return *_pEntity; }
	const wxAuiDockArt& GetEntity() const { return *_pEntity; }
	wxAuiDockArt* GetEntityPtr() { return _pEntity; }
	const wxAuiDockArt* GetEntityPtr() const { return _pEntity; }
public:
	static wxAuiDockArt& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAuiDockArt&>(value).GetEntity();
	}
	static const wxAuiDockArt& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAuiDockArt&>(value).GetEntity();
	}
	static wxAuiDockArt* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAuiDockArt&>(value).GetEntityPtr();
	}
	static const wxAuiDockArt* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAuiDockArt&>(value).GetEntityPtr();
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
