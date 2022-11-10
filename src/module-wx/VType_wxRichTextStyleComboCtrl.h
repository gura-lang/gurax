﻿//==============================================================================
// VType_wxRichTextStyleComboCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRICHTEXTSTYLECOMBOCTRL_H
#define GURAX_MODULE_WX_VTYPE_WXRICHTEXTSTYLECOMBOCTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/richtext/richtextstyles.h>
#include "Util.h"
#include "VType_wxComboCtrl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRichTextStyleComboCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRichTextStyleComboCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRichTextStyleComboCtrl VTYPE_wxRichTextStyleComboCtrl;

//------------------------------------------------------------------------------
// Value_wxRichTextStyleComboCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRichTextStyleComboCtrl : public Value_wxComboCtrl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRichTextStyleComboCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRichTextStyleComboCtrl");
protected:
	wxWeakRef<wxRichTextStyleComboCtrl> _pEntity;
public:
	class EntityT : public wxRichTextStyleComboCtrl {
	public:
		using wxRichTextStyleComboCtrl::wxRichTextStyleComboCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRichTextStyleComboCtrl() = delete;
	explicit Value_wxRichTextStyleComboCtrl(wxRichTextStyleComboCtrl* pEntity, VType& vtype = VTYPE_wxRichTextStyleComboCtrl) :
		Value_wxComboCtrl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRichTextStyleComboCtrl(const Value_wxRichTextStyleComboCtrl& src) = delete;
	Value_wxRichTextStyleComboCtrl& operator=(const Value_wxRichTextStyleComboCtrl& src) = delete;
	// Move constructor/operator
	Value_wxRichTextStyleComboCtrl(Value_wxRichTextStyleComboCtrl&& src) noexcept = delete;
	Value_wxRichTextStyleComboCtrl& operator=(Value_wxRichTextStyleComboCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRichTextStyleComboCtrl() = default;
public:
	wxRichTextStyleComboCtrl& GetEntity() { return *_pEntity; }
	const wxRichTextStyleComboCtrl& GetEntity() const { return *_pEntity; }
	wxRichTextStyleComboCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxRichTextStyleComboCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxRichTextStyleComboCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRichTextStyleComboCtrl&>(value).GetEntity();
	}
	static const wxRichTextStyleComboCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRichTextStyleComboCtrl&>(value).GetEntity();
	}
	static wxRichTextStyleComboCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRichTextStyleComboCtrl&>(value).GetEntityPtr();
	}
	static const wxRichTextStyleComboCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRichTextStyleComboCtrl&>(value).GetEntityPtr();
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
