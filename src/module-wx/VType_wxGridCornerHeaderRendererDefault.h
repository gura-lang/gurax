﻿//==============================================================================
// VType_wxGridCornerHeaderRendererDefault.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCORNERHEADERRENDERERDEFAULT_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCORNERHEADERRENDERERDEFAULT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxGridCornerHeaderRenderer.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCornerHeaderRendererDefault
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCornerHeaderRendererDefault : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCornerHeaderRendererDefault VTYPE_wxGridCornerHeaderRendererDefault;

//------------------------------------------------------------------------------
// Value_wxGridCornerHeaderRendererDefault
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCornerHeaderRendererDefault : public Value_wxGridCornerHeaderRenderer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCornerHeaderRendererDefault);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCornerHeaderRendererDefault");
protected:
	wxGridCornerHeaderRendererDefault* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCornerHeaderRendererDefault() = delete;
	explicit Value_wxGridCornerHeaderRendererDefault(wxGridCornerHeaderRendererDefault* pEntity, VType& vtype = VTYPE_wxGridCornerHeaderRendererDefault) :
		Value_wxGridCornerHeaderRenderer(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxGridCornerHeaderRendererDefault(const Value_wxGridCornerHeaderRendererDefault& src) = delete;
	Value_wxGridCornerHeaderRendererDefault& operator=(const Value_wxGridCornerHeaderRendererDefault& src) = delete;
	// Move constructor/operator
	Value_wxGridCornerHeaderRendererDefault(Value_wxGridCornerHeaderRendererDefault&& src) noexcept = delete;
	Value_wxGridCornerHeaderRendererDefault& operator=(Value_wxGridCornerHeaderRendererDefault&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCornerHeaderRendererDefault() = default;
public:
	wxGridCornerHeaderRendererDefault& GetEntity() { return *_pEntity; }
	const wxGridCornerHeaderRendererDefault& GetEntity() const { return *_pEntity; }
	wxGridCornerHeaderRendererDefault* GetEntityPtr() { return _pEntity; }
	const wxGridCornerHeaderRendererDefault* GetEntityPtr() const { return _pEntity; }
public:
	static wxGridCornerHeaderRendererDefault& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCornerHeaderRendererDefault&>(value).GetEntity();
	}
	static const wxGridCornerHeaderRendererDefault& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCornerHeaderRendererDefault&>(value).GetEntity();
	}
	static wxGridCornerHeaderRendererDefault* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCornerHeaderRendererDefault&>(value).GetEntityPtr();
	}
	static const wxGridCornerHeaderRendererDefault* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCornerHeaderRendererDefault&>(value).GetEntityPtr();
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
