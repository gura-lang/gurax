﻿//==============================================================================
// VType_wxGraphicsPath.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRAPHICSPATH_H
#define GURAX_MODULE_WX_VTYPE_WXGRAPHICSPATH_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/graphics.h>
#include "Util.h"
#include "VType_wxGraphicsObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGraphicsPath
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGraphicsPath : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGraphicsPath VTYPE_wxGraphicsPath;

//------------------------------------------------------------------------------
// Value_wxGraphicsPath
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGraphicsPath : public Value_wxGraphicsObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGraphicsPath);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGraphicsPath");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGraphicsPath() = delete;
	explicit Value_wxGraphicsPath(const wxGraphicsPath& entity, VType& vtype = VTYPE_wxGraphicsPath) :
		Value_wxGraphicsObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxGraphicsPath(const Value_wxGraphicsPath& src) = delete;
	Value_wxGraphicsPath& operator=(const Value_wxGraphicsPath& src) = delete;
	// Move constructor/operator
	Value_wxGraphicsPath(Value_wxGraphicsPath&& src) noexcept = delete;
	Value_wxGraphicsPath& operator=(Value_wxGraphicsPath&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGraphicsPath() = default;
public:
	wxGraphicsPath& GetEntity() { return reinterpret_cast<wxGraphicsPath&>(Value_wxGraphicsObject::GetEntity()); }
	const wxGraphicsPath& GetEntity() const { return reinterpret_cast<const wxGraphicsPath&>(Value_wxGraphicsObject::GetEntity()); }
	wxGraphicsPath* GetEntityPtr() { return reinterpret_cast<wxGraphicsPath*>(Value_wxGraphicsObject::GetEntityPtr()); }\
	const wxGraphicsPath* GetEntityPtr() const { return reinterpret_cast<const wxGraphicsPath*>(Value_wxGraphicsObject::GetEntityPtr()); }
public:
	static wxGraphicsPath& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGraphicsPath&>(value).GetEntity();
	}
	static const wxGraphicsPath& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGraphicsPath&>(value).GetEntity();
	}
	static wxGraphicsPath* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGraphicsPath&>(value).GetEntityPtr();
	}
	static const wxGraphicsPath* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGraphicsPath&>(value).GetEntityPtr();
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
