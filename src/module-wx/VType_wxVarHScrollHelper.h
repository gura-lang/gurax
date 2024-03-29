﻿//==============================================================================
// VType_wxVarHScrollHelper.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXVARHSCROLLHELPER_H
#define GURAX_MODULE_WX_VTYPE_WXVARHSCROLLHELPER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/vscroll.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxVarHScrollHelper
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxVarHScrollHelper : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxVarHScrollHelper VTYPE_wxVarHScrollHelper;

//------------------------------------------------------------------------------
// Value_wxVarHScrollHelper
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxVarHScrollHelper : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxVarHScrollHelper);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxVarHScrollHelper");
protected:
	wxVarHScrollHelper* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxVarHScrollHelper() = delete;
	explicit Value_wxVarHScrollHelper(wxVarHScrollHelper* pEntity, VType& vtype = VTYPE_wxVarHScrollHelper) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxVarHScrollHelper(const wxVarHScrollHelper& entity, VType& vtype = VTYPE_wxVarHScrollHelper) :
		Value_Object(vtype), _pEntity(const_cast<wxVarHScrollHelper*>(&entity)) {}
	// Copy constructor/operator
	Value_wxVarHScrollHelper(const Value_wxVarHScrollHelper& src) = delete;
	Value_wxVarHScrollHelper& operator=(const Value_wxVarHScrollHelper& src) = delete;
	// Move constructor/operator
	Value_wxVarHScrollHelper(Value_wxVarHScrollHelper&& src) noexcept = delete;
	Value_wxVarHScrollHelper& operator=(Value_wxVarHScrollHelper&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxVarHScrollHelper() = default;
public:
	wxVarHScrollHelper& GetEntity() { return *_pEntity; }
	const wxVarHScrollHelper& GetEntity() const { return *_pEntity; }
	wxVarHScrollHelper* GetEntityPtr() { return _pEntity; }
	const wxVarHScrollHelper* GetEntityPtr() const { return _pEntity; }
public:
	static wxVarHScrollHelper& GetEntity(Value& value) {
		return dynamic_cast<Value_wxVarHScrollHelper&>(value).GetEntity();
	}
	static const wxVarHScrollHelper& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxVarHScrollHelper&>(value).GetEntity();
	}
	static wxVarHScrollHelper* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxVarHScrollHelper&>(value).GetEntityPtr();
	}
	static const wxVarHScrollHelper* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxVarHScrollHelper&>(value).GetEntityPtr();
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
