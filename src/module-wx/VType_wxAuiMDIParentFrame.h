﻿//==============================================================================
// VType_wxAuiMDIParentFrame.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXAUIMDIPARENTFRAME_H
#define GURAX_MODULE_WX_VTYPE_WXAUIMDIPARENTFRAME_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/aui/tabmdi.h>
#include "Util.h"
#include "VType_wxFrame.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAuiMDIParentFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAuiMDIParentFrame : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAuiMDIParentFrame VTYPE_wxAuiMDIParentFrame;

//------------------------------------------------------------------------------
// Value_wxAuiMDIParentFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAuiMDIParentFrame : public Value_wxFrame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAuiMDIParentFrame);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAuiMDIParentFrame");
protected:
	wxWeakRef<wxAuiMDIParentFrame> _pEntity;
public:
	class EntityT : public wxAuiMDIParentFrame {
	public:
		using wxAuiMDIParentFrame::wxAuiMDIParentFrame;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAuiMDIParentFrame() = delete;
	explicit Value_wxAuiMDIParentFrame(wxAuiMDIParentFrame* pEntity, VType& vtype = VTYPE_wxAuiMDIParentFrame) :
		Value_wxFrame(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxAuiMDIParentFrame(const Value_wxAuiMDIParentFrame& src) = delete;
	Value_wxAuiMDIParentFrame& operator=(const Value_wxAuiMDIParentFrame& src) = delete;
	// Move constructor/operator
	Value_wxAuiMDIParentFrame(Value_wxAuiMDIParentFrame&& src) noexcept = delete;
	Value_wxAuiMDIParentFrame& operator=(Value_wxAuiMDIParentFrame&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAuiMDIParentFrame() = default;
public:
	wxAuiMDIParentFrame& GetEntity() { return *_pEntity; }
	const wxAuiMDIParentFrame& GetEntity() const { return *_pEntity; }
	wxAuiMDIParentFrame* GetEntityPtr() { return _pEntity.get(); }
	const wxAuiMDIParentFrame* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxAuiMDIParentFrame& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAuiMDIParentFrame&>(value).GetEntity();
	}
	static const wxAuiMDIParentFrame& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAuiMDIParentFrame&>(value).GetEntity();
	}
	static wxAuiMDIParentFrame* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAuiMDIParentFrame&>(value).GetEntityPtr();
	}
	static const wxAuiMDIParentFrame* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAuiMDIParentFrame&>(value).GetEntityPtr();
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
