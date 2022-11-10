﻿//==============================================================================
// VType_wxPGPaintData.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPGPAINTDATA_H
#define GURAX_MODULE_WX_VTYPE_WXPGPAINTDATA_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/property.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPGPaintData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPGPaintData : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPGPaintData VTYPE_wxPGPaintData;

//------------------------------------------------------------------------------
// Value_wxPGPaintData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPGPaintData : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPGPaintData);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPGPaintData");
protected:
	wxPGPaintData _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPGPaintData() = delete;
	explicit Value_wxPGPaintData(const wxPGPaintData& entity, VType& vtype = VTYPE_wxPGPaintData) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxPGPaintData(const Value_wxPGPaintData& src) = delete;
	Value_wxPGPaintData& operator=(const Value_wxPGPaintData& src) = delete;
	// Move constructor/operator
	Value_wxPGPaintData(Value_wxPGPaintData&& src) noexcept = delete;
	Value_wxPGPaintData& operator=(Value_wxPGPaintData&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPGPaintData() = default;
public:
	wxPGPaintData& GetEntity() { return _entity; }
	const wxPGPaintData& GetEntity() const { return _entity; }
	wxPGPaintData* GetEntityPtr() { return &_entity; }
	const wxPGPaintData* GetEntityPtr() const { return &_entity; }
public:
	static wxPGPaintData& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPGPaintData&>(value).GetEntity();
	}
	static const wxPGPaintData& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPGPaintData&>(value).GetEntity();
	}
	static wxPGPaintData* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPGPaintData&>(value).GetEntityPtr();
	}
	static const wxPGPaintData* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPGPaintData&>(value).GetEntityPtr();
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
