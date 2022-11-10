﻿//==============================================================================
// VType_wxPaintDC.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPAINTDC_H
#define GURAX_MODULE_WX_VTYPE_WXPAINTDC_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dcclient.h>
#include "Util.h"
#include "VType_wxClientDC.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPaintDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPaintDC : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPaintDC VTYPE_wxPaintDC;

//------------------------------------------------------------------------------
// Value_wxPaintDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPaintDC : public Value_wxClientDC {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPaintDC);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPaintDC");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPaintDC() = delete;
	Value_wxPaintDC(wxDC* pEntity, VType& vtype = VTYPE_wxPaintDC) :
		Value_wxClientDC(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxPaintDC(const Value_wxPaintDC& src) = delete;
	Value_wxPaintDC& operator=(const Value_wxPaintDC& src) = delete;
	// Move constructor/operator
	Value_wxPaintDC(Value_wxPaintDC&& src) noexcept = delete;
	Value_wxPaintDC& operator=(Value_wxPaintDC&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPaintDC() = default;
public:
	wxPaintDC& GetEntity() { return reinterpret_cast<wxPaintDC&>(Value_wxClientDC::GetEntity()); }
	const wxPaintDC& GetEntity() const { return reinterpret_cast<const wxPaintDC&>(Value_wxClientDC::GetEntity()); }
	wxPaintDC* GetEntityPtr() { return reinterpret_cast<wxPaintDC*>(Value_wxClientDC::GetEntityPtr()); }\
	const wxPaintDC* GetEntityPtr() const { return reinterpret_cast<const wxPaintDC*>(Value_wxClientDC::GetEntityPtr()); }
public:
	static wxPaintDC& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPaintDC&>(value).GetEntity();
	}
	static const wxPaintDC& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPaintDC&>(value).GetEntity();
	}
	static wxPaintDC* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPaintDC&>(value).GetEntityPtr();
	}
	static const wxPaintDC* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPaintDC&>(value).GetEntityPtr();
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
