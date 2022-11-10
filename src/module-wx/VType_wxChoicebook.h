﻿//==============================================================================
// VType_wxChoicebook.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCHOICEBOOK_H
#define GURAX_MODULE_WX_VTYPE_WXCHOICEBOOK_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/choicebk.h>
#include "Util.h"
#include "VType_wxBookCtrlBase.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxChoicebook
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxChoicebook : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxChoicebook VTYPE_wxChoicebook;

//------------------------------------------------------------------------------
// Value_wxChoicebook
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxChoicebook : public Value_wxBookCtrlBase {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxChoicebook);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxChoicebook");
protected:
	wxWeakRef<wxChoicebook> _pEntity;
public:
	class EntityT : public wxChoicebook {
	public:
		using wxChoicebook::wxChoicebook;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxChoicebook() = delete;
	explicit Value_wxChoicebook(wxChoicebook* pEntity, VType& vtype = VTYPE_wxChoicebook) :
		Value_wxBookCtrlBase(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxChoicebook(const Value_wxChoicebook& src) = delete;
	Value_wxChoicebook& operator=(const Value_wxChoicebook& src) = delete;
	// Move constructor/operator
	Value_wxChoicebook(Value_wxChoicebook&& src) noexcept = delete;
	Value_wxChoicebook& operator=(Value_wxChoicebook&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxChoicebook() = default;
public:
	wxChoicebook& GetEntity() { return *_pEntity; }
	const wxChoicebook& GetEntity() const { return *_pEntity; }
	wxChoicebook* GetEntityPtr() { return _pEntity.get(); }
	const wxChoicebook* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxChoicebook& GetEntity(Value& value) {
		return dynamic_cast<Value_wxChoicebook&>(value).GetEntity();
	}
	static const wxChoicebook& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxChoicebook&>(value).GetEntity();
	}
	static wxChoicebook* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxChoicebook&>(value).GetEntityPtr();
	}
	static const wxChoicebook* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxChoicebook&>(value).GetEntityPtr();
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
