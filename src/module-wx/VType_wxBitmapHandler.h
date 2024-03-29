﻿//==============================================================================
// VType_wxBitmapHandler.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXBITMAPHANDLER_H
#define GURAX_MODULE_WX_VTYPE_WXBITMAPHANDLER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/bitmap.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxBitmapHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxBitmapHandler : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxBitmapHandler VTYPE_wxBitmapHandler;

//------------------------------------------------------------------------------
// Value_wxBitmapHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxBitmapHandler : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxBitmapHandler);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxBitmapHandler");
protected:
	wxBitmapHandler* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxBitmapHandler() = delete;
	explicit Value_wxBitmapHandler(wxBitmapHandler* pEntity, VType& vtype = VTYPE_wxBitmapHandler) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxBitmapHandler(const wxBitmapHandler& entity, VType& vtype = VTYPE_wxBitmapHandler) :
		Value_Object(vtype), _pEntity(const_cast<wxBitmapHandler*>(&entity)) {}
	// Copy constructor/operator
	Value_wxBitmapHandler(const Value_wxBitmapHandler& src) = delete;
	Value_wxBitmapHandler& operator=(const Value_wxBitmapHandler& src) = delete;
	// Move constructor/operator
	Value_wxBitmapHandler(Value_wxBitmapHandler&& src) noexcept = delete;
	Value_wxBitmapHandler& operator=(Value_wxBitmapHandler&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxBitmapHandler() = default;
public:
	wxBitmapHandler& GetEntity() { return *_pEntity; }
	const wxBitmapHandler& GetEntity() const { return *_pEntity; }
	wxBitmapHandler* GetEntityPtr() { return _pEntity; }
	const wxBitmapHandler* GetEntityPtr() const { return _pEntity; }
public:
	static wxBitmapHandler& GetEntity(Value& value) {
		return dynamic_cast<Value_wxBitmapHandler&>(value).GetEntity();
	}
	static const wxBitmapHandler& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxBitmapHandler&>(value).GetEntity();
	}
	static wxBitmapHandler* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxBitmapHandler&>(value).GetEntityPtr();
	}
	static const wxBitmapHandler* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxBitmapHandler&>(value).GetEntityPtr();
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
