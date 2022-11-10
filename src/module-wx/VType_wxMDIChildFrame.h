﻿//==============================================================================
// VType_wxMDIChildFrame.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMDICHILDFRAME_H
#define GURAX_MODULE_WX_VTYPE_WXMDICHILDFRAME_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/mdi.h>
#include "Util.h"
#include "VType_wxFrame.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMDIChildFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMDIChildFrame : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMDIChildFrame VTYPE_wxMDIChildFrame;

//------------------------------------------------------------------------------
// Value_wxMDIChildFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMDIChildFrame : public Value_wxFrame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMDIChildFrame);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMDIChildFrame");
protected:
	wxWeakRef<wxMDIChildFrame> _pEntity;
public:
	class EntityT : public wxMDIChildFrame {
	public:
		using wxMDIChildFrame::wxMDIChildFrame;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxMDIChildFrame() = delete;
	explicit Value_wxMDIChildFrame(wxMDIChildFrame* pEntity, VType& vtype = VTYPE_wxMDIChildFrame) :
		Value_wxFrame(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxMDIChildFrame(const Value_wxMDIChildFrame& src) = delete;
	Value_wxMDIChildFrame& operator=(const Value_wxMDIChildFrame& src) = delete;
	// Move constructor/operator
	Value_wxMDIChildFrame(Value_wxMDIChildFrame&& src) noexcept = delete;
	Value_wxMDIChildFrame& operator=(Value_wxMDIChildFrame&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMDIChildFrame() = default;
public:
	wxMDIChildFrame& GetEntity() { return *_pEntity; }
	const wxMDIChildFrame& GetEntity() const { return *_pEntity; }
	wxMDIChildFrame* GetEntityPtr() { return _pEntity.get(); }
	const wxMDIChildFrame* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxMDIChildFrame& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMDIChildFrame&>(value).GetEntity();
	}
	static const wxMDIChildFrame& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMDIChildFrame&>(value).GetEntity();
	}
	static wxMDIChildFrame* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMDIChildFrame&>(value).GetEntityPtr();
	}
	static const wxMDIChildFrame* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMDIChildFrame&>(value).GetEntityPtr();
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
