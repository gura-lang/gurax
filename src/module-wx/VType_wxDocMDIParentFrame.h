﻿//==============================================================================
// VType_wxDocMDIParentFrame.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXDOCMDIPARENTFRAME_H
#define GURAX_MODULE_WX_VTYPE_WXDOCMDIPARENTFRAME_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/docmdi.h>
#include "Util.h"
#include "VType_wxMDIParentFrame.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxDocMDIParentFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxDocMDIParentFrame : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxDocMDIParentFrame VTYPE_wxDocMDIParentFrame;

//------------------------------------------------------------------------------
// Value_wxDocMDIParentFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxDocMDIParentFrame : public Value_wxMDIParentFrame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxDocMDIParentFrame);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxDocMDIParentFrame");
protected:
	wxWeakRef<wxDocMDIParentFrame> _pEntity;
public:
	class EntityT : public wxDocMDIParentFrame {
	public:
		using wxDocMDIParentFrame::wxDocMDIParentFrame;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxDocMDIParentFrame() = delete;
	explicit Value_wxDocMDIParentFrame(wxDocMDIParentFrame* pEntity, VType& vtype = VTYPE_wxDocMDIParentFrame) :
		Value_wxMDIParentFrame(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxDocMDIParentFrame(const Value_wxDocMDIParentFrame& src) = delete;
	Value_wxDocMDIParentFrame& operator=(const Value_wxDocMDIParentFrame& src) = delete;
	// Move constructor/operator
	Value_wxDocMDIParentFrame(Value_wxDocMDIParentFrame&& src) noexcept = delete;
	Value_wxDocMDIParentFrame& operator=(Value_wxDocMDIParentFrame&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxDocMDIParentFrame() = default;
public:
	wxDocMDIParentFrame& GetEntity() { return *_pEntity; }
	const wxDocMDIParentFrame& GetEntity() const { return *_pEntity; }
	wxDocMDIParentFrame* GetEntityPtr() { return _pEntity.get(); }
	const wxDocMDIParentFrame* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxDocMDIParentFrame& GetEntity(Value& value) {
		return dynamic_cast<Value_wxDocMDIParentFrame&>(value).GetEntity();
	}
	static const wxDocMDIParentFrame& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxDocMDIParentFrame&>(value).GetEntity();
	}
	static wxDocMDIParentFrame* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxDocMDIParentFrame&>(value).GetEntityPtr();
	}
	static const wxDocMDIParentFrame* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxDocMDIParentFrame&>(value).GetEntityPtr();
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
