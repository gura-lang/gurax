﻿//==============================================================================
// VType_wxDataObject.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXDATAOBJECT_H
#define GURAX_MODULE_WX_VTYPE_WXDATAOBJECT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxDataObject
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxDataObject : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxDataObject VTYPE_wxDataObject;

//------------------------------------------------------------------------------
// Value_wxDataObject
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxDataObject : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxDataObject);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxDataObject");
protected:
	wxDataObject* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxDataObject() = delete;
	explicit Value_wxDataObject(wxDataObject* pEntity, VType& vtype = VTYPE_wxDataObject) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxDataObject(const wxDataObject& entity, VType& vtype = VTYPE_wxDataObject) :
		Value_Object(vtype), _pEntity(const_cast<wxDataObject*>(&entity)) {}
	// Copy constructor/operator
	Value_wxDataObject(const Value_wxDataObject& src) = delete;
	Value_wxDataObject& operator=(const Value_wxDataObject& src) = delete;
	// Move constructor/operator
	Value_wxDataObject(Value_wxDataObject&& src) noexcept = delete;
	Value_wxDataObject& operator=(Value_wxDataObject&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxDataObject() = default;
public:
	wxDataObject& GetEntity() { return *_pEntity; }
	const wxDataObject& GetEntity() const { return *_pEntity; }
	wxDataObject* GetEntityPtr() { return _pEntity; }
	const wxDataObject* GetEntityPtr() const { return _pEntity; }
public:
	static wxDataObject& GetEntity(Value& value) {
		return dynamic_cast<Value_wxDataObject&>(value).GetEntity();
	}
	static const wxDataObject& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxDataObject&>(value).GetEntity();
	}
	static wxDataObject* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxDataObject&>(value).GetEntityPtr();
	}
	static const wxDataObject* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxDataObject&>(value).GetEntityPtr();
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
