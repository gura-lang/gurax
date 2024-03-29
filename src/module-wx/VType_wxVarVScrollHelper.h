﻿//==============================================================================
// VType_wxVarVScrollHelper.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXVARVSCROLLHELPER_H
#define GURAX_MODULE_WX_VTYPE_WXVARVSCROLLHELPER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/vscroll.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxVarVScrollHelper
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxVarVScrollHelper : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxVarVScrollHelper VTYPE_wxVarVScrollHelper;

//------------------------------------------------------------------------------
// Value_wxVarVScrollHelper
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxVarVScrollHelper : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxVarVScrollHelper);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxVarVScrollHelper");
protected:
	wxVarVScrollHelper* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxVarVScrollHelper() = delete;
	explicit Value_wxVarVScrollHelper(wxVarVScrollHelper* pEntity, VType& vtype = VTYPE_wxVarVScrollHelper) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxVarVScrollHelper(const wxVarVScrollHelper& entity, VType& vtype = VTYPE_wxVarVScrollHelper) :
		Value_Object(vtype), _pEntity(const_cast<wxVarVScrollHelper*>(&entity)) {}
	// Copy constructor/operator
	Value_wxVarVScrollHelper(const Value_wxVarVScrollHelper& src) = delete;
	Value_wxVarVScrollHelper& operator=(const Value_wxVarVScrollHelper& src) = delete;
	// Move constructor/operator
	Value_wxVarVScrollHelper(Value_wxVarVScrollHelper&& src) noexcept = delete;
	Value_wxVarVScrollHelper& operator=(Value_wxVarVScrollHelper&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxVarVScrollHelper() = default;
public:
	wxVarVScrollHelper& GetEntity() { return *_pEntity; }
	const wxVarVScrollHelper& GetEntity() const { return *_pEntity; }
	wxVarVScrollHelper* GetEntityPtr() { return _pEntity; }
	const wxVarVScrollHelper* GetEntityPtr() const { return _pEntity; }
public:
	static wxVarVScrollHelper& GetEntity(Value& value) {
		return dynamic_cast<Value_wxVarVScrollHelper&>(value).GetEntity();
	}
	static const wxVarVScrollHelper& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxVarVScrollHelper&>(value).GetEntity();
	}
	static wxVarVScrollHelper* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxVarVScrollHelper&>(value).GetEntityPtr();
	}
	static const wxVarVScrollHelper* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxVarVScrollHelper&>(value).GetEntityPtr();
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
