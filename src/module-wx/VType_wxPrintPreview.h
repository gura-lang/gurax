﻿//==============================================================================
// VType_wxPrintPreview.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPRINTPREVIEW_H
#define GURAX_MODULE_WX_VTYPE_WXPRINTPREVIEW_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/print.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPrintPreview
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPrintPreview : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPrintPreview VTYPE_wxPrintPreview;

//------------------------------------------------------------------------------
// Value_wxPrintPreview
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPrintPreview : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPrintPreview);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPrintPreview");
protected:
	wxPrintPreview* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPrintPreview() = delete;
	explicit Value_wxPrintPreview(wxPrintPreview* pEntity, VType& vtype = VTYPE_wxPrintPreview) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxPrintPreview(const wxPrintPreview& entity, VType& vtype = VTYPE_wxPrintPreview) :
		Value_Object(vtype), _pEntity(const_cast<wxPrintPreview*>(&entity)) {}
	// Copy constructor/operator
	Value_wxPrintPreview(const Value_wxPrintPreview& src) = delete;
	Value_wxPrintPreview& operator=(const Value_wxPrintPreview& src) = delete;
	// Move constructor/operator
	Value_wxPrintPreview(Value_wxPrintPreview&& src) noexcept = delete;
	Value_wxPrintPreview& operator=(Value_wxPrintPreview&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPrintPreview() = default;
public:
	wxPrintPreview& GetEntity() { return *_pEntity; }
	const wxPrintPreview& GetEntity() const { return *_pEntity; }
	wxPrintPreview* GetEntityPtr() { return _pEntity; }
	const wxPrintPreview* GetEntityPtr() const { return _pEntity; }
public:
	static wxPrintPreview& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPrintPreview&>(value).GetEntity();
	}
	static const wxPrintPreview& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPrintPreview&>(value).GetEntity();
	}
	static wxPrintPreview* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPrintPreview&>(value).GetEntityPtr();
	}
	static const wxPrintPreview* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPrintPreview&>(value).GetEntityPtr();
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
