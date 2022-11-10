﻿//==============================================================================
// VType_wxCheckListBox.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCHECKLISTBOX_H
#define GURAX_MODULE_WX_VTYPE_WXCHECKLISTBOX_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/checklst.h>
#include "Util.h"
#include "VType_wxListBox.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxCheckListBox
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxCheckListBox : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxCheckListBox VTYPE_wxCheckListBox;

//------------------------------------------------------------------------------
// Value_wxCheckListBox
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxCheckListBox : public Value_wxListBox {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxCheckListBox);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxCheckListBox");
protected:
	wxWeakRef<wxCheckListBox> _pEntity;
public:
	class EntityT : public wxCheckListBox {
	public:
		using wxCheckListBox::wxCheckListBox;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxCheckListBox() = delete;
	explicit Value_wxCheckListBox(wxCheckListBox* pEntity, VType& vtype = VTYPE_wxCheckListBox) :
		Value_wxListBox(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxCheckListBox(const Value_wxCheckListBox& src) = delete;
	Value_wxCheckListBox& operator=(const Value_wxCheckListBox& src) = delete;
	// Move constructor/operator
	Value_wxCheckListBox(Value_wxCheckListBox&& src) noexcept = delete;
	Value_wxCheckListBox& operator=(Value_wxCheckListBox&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxCheckListBox() = default;
public:
	wxCheckListBox& GetEntity() { return *_pEntity; }
	const wxCheckListBox& GetEntity() const { return *_pEntity; }
	wxCheckListBox* GetEntityPtr() { return _pEntity.get(); }
	const wxCheckListBox* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxCheckListBox& GetEntity(Value& value) {
		return dynamic_cast<Value_wxCheckListBox&>(value).GetEntity();
	}
	static const wxCheckListBox& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxCheckListBox&>(value).GetEntity();
	}
	static wxCheckListBox* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxCheckListBox&>(value).GetEntityPtr();
	}
	static const wxCheckListBox* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxCheckListBox&>(value).GetEntityPtr();
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
