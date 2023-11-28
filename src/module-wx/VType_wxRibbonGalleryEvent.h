﻿//==============================================================================
// VType_wxRibbonGalleryEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRIBBONGALLERYEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXRIBBONGALLERYEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/ribbon/gallery.h>
#include "Util.h"
#include "VType_wxCommandEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRibbonGalleryEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRibbonGalleryEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRibbonGalleryEvent VTYPE_wxRibbonGalleryEvent;

//------------------------------------------------------------------------------
// Value_wxRibbonGalleryEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRibbonGalleryEvent : public Value_wxCommandEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRibbonGalleryEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRibbonGalleryEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxRibbonGalleryEvent> eventValueFactory;
public:
	// Constructor
	Value_wxRibbonGalleryEvent() = delete;
	Value_wxRibbonGalleryEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxRibbonGalleryEvent) :
		Value_wxCommandEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxRibbonGalleryEvent(const Value_wxRibbonGalleryEvent& src) = delete;
	Value_wxRibbonGalleryEvent& operator=(const Value_wxRibbonGalleryEvent& src) = delete;
	// Move constructor/operator
	Value_wxRibbonGalleryEvent(Value_wxRibbonGalleryEvent&& src) noexcept = delete;
	Value_wxRibbonGalleryEvent& operator=(Value_wxRibbonGalleryEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRibbonGalleryEvent() = default;
public:
	wxRibbonGalleryEvent& GetEntity() { return reinterpret_cast<wxRibbonGalleryEvent&>(Value_wxCommandEvent::GetEntity()); }
	const wxRibbonGalleryEvent& GetEntity() const { return reinterpret_cast<const wxRibbonGalleryEvent&>(Value_wxCommandEvent::GetEntity()); }
	wxRibbonGalleryEvent* GetEntityPtr() { return reinterpret_cast<wxRibbonGalleryEvent*>(Value_wxCommandEvent::GetEntityPtr()); }\
	const wxRibbonGalleryEvent* GetEntityPtr() const { return reinterpret_cast<const wxRibbonGalleryEvent*>(Value_wxCommandEvent::GetEntityPtr()); }
public:
	static wxRibbonGalleryEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRibbonGalleryEvent&>(value).GetEntity();
	}
	static const wxRibbonGalleryEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRibbonGalleryEvent&>(value).GetEntity();
	}
	static wxRibbonGalleryEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRibbonGalleryEvent&>(value).GetEntityPtr();
	}
	static const wxRibbonGalleryEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRibbonGalleryEvent&>(value).GetEntityPtr();
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