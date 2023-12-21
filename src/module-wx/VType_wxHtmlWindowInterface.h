﻿//==============================================================================
// VType_wxHtmlWindowInterface.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXHTMLWINDOWINTERFACE_H
#define GURAX_MODULE_WX_VTYPE_WXHTMLWINDOWINTERFACE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/html/htmlwin.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxHtmlWindowInterface
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxHtmlWindowInterface : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxHtmlWindowInterface VTYPE_wxHtmlWindowInterface;

//------------------------------------------------------------------------------
// Value_wxHtmlWindowInterface
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxHtmlWindowInterface : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxHtmlWindowInterface);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxHtmlWindowInterface");
protected:
	wxHtmlWindowInterface* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxHtmlWindowInterface() = delete;
	explicit Value_wxHtmlWindowInterface(wxHtmlWindowInterface* pEntity, VType& vtype = VTYPE_wxHtmlWindowInterface) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxHtmlWindowInterface(const wxHtmlWindowInterface& entity, VType& vtype = VTYPE_wxHtmlWindowInterface) :
		Value_Object(vtype), _pEntity(const_cast<wxHtmlWindowInterface*>(&entity)) {}
	// Copy constructor/operator
	Value_wxHtmlWindowInterface(const Value_wxHtmlWindowInterface& src) = delete;
	Value_wxHtmlWindowInterface& operator=(const Value_wxHtmlWindowInterface& src) = delete;
	// Move constructor/operator
	Value_wxHtmlWindowInterface(Value_wxHtmlWindowInterface&& src) noexcept = delete;
	Value_wxHtmlWindowInterface& operator=(Value_wxHtmlWindowInterface&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxHtmlWindowInterface() = default;
public:
	wxHtmlWindowInterface& GetEntity() { return *_pEntity; }
	const wxHtmlWindowInterface& GetEntity() const { return *_pEntity; }
	wxHtmlWindowInterface* GetEntityPtr() { return _pEntity; }
	const wxHtmlWindowInterface* GetEntityPtr() const { return _pEntity; }
public:
	static wxHtmlWindowInterface& GetEntity(Value& value) {
		return dynamic_cast<Value_wxHtmlWindowInterface&>(value).GetEntity();
	}
	static const wxHtmlWindowInterface& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxHtmlWindowInterface&>(value).GetEntity();
	}
	static wxHtmlWindowInterface* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxHtmlWindowInterface&>(value).GetEntityPtr();
	}
	static const wxHtmlWindowInterface* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxHtmlWindowInterface&>(value).GetEntityPtr();
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