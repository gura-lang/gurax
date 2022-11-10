﻿//==============================================================================
// VType_wxMirrorDC.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMIRRORDC_H
#define GURAX_MODULE_WX_VTYPE_WXMIRRORDC_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dcmirror.h>
#include "Util.h"
#include "VType_wxDC.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMirrorDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMirrorDC : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMirrorDC VTYPE_wxMirrorDC;

//------------------------------------------------------------------------------
// Value_wxMirrorDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMirrorDC : public Value_wxDC {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMirrorDC);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMirrorDC");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxMirrorDC() = delete;
	Value_wxMirrorDC(wxDC* pEntity, VType& vtype = VTYPE_wxMirrorDC) :
		Value_wxDC(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxMirrorDC(const Value_wxMirrorDC& src) = delete;
	Value_wxMirrorDC& operator=(const Value_wxMirrorDC& src) = delete;
	// Move constructor/operator
	Value_wxMirrorDC(Value_wxMirrorDC&& src) noexcept = delete;
	Value_wxMirrorDC& operator=(Value_wxMirrorDC&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMirrorDC() = default;
public:
	wxMirrorDC& GetEntity() { return reinterpret_cast<wxMirrorDC&>(Value_wxDC::GetEntity()); }
	const wxMirrorDC& GetEntity() const { return reinterpret_cast<const wxMirrorDC&>(Value_wxDC::GetEntity()); }
	wxMirrorDC* GetEntityPtr() { return reinterpret_cast<wxMirrorDC*>(Value_wxDC::GetEntityPtr()); }\
	const wxMirrorDC* GetEntityPtr() const { return reinterpret_cast<const wxMirrorDC*>(Value_wxDC::GetEntityPtr()); }
public:
	static wxMirrorDC& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMirrorDC&>(value).GetEntity();
	}
	static const wxMirrorDC& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMirrorDC&>(value).GetEntity();
	}
	static wxMirrorDC* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMirrorDC&>(value).GetEntityPtr();
	}
	static const wxMirrorDC* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMirrorDC&>(value).GetEntityPtr();
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
