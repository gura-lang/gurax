﻿//==============================================================================
// VType_wxFontData.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFONTDATA_H
#define GURAX_MODULE_WX_VTYPE_WXFONTDATA_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/fontdata.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFontData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFontData : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFontData VTYPE_wxFontData;

//------------------------------------------------------------------------------
// Value_wxFontData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFontData : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFontData);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFontData");
protected:
	wxFontData _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFontData() = delete;
	explicit Value_wxFontData(const wxFontData& entity, VType& vtype = VTYPE_wxFontData) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxFontData(const Value_wxFontData& src) = delete;
	Value_wxFontData& operator=(const Value_wxFontData& src) = delete;
	// Move constructor/operator
	Value_wxFontData(Value_wxFontData&& src) noexcept = delete;
	Value_wxFontData& operator=(Value_wxFontData&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFontData() = default;
public:
	wxFontData& GetEntity() { return _entity; }
	const wxFontData& GetEntity() const { return _entity; }
	wxFontData* GetEntityPtr() { return &_entity; }
	const wxFontData* GetEntityPtr() const { return &_entity; }
public:
	static wxFontData& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFontData&>(value).GetEntity();
	}
	static const wxFontData& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFontData&>(value).GetEntity();
	}
	static wxFontData* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFontData&>(value).GetEntityPtr();
	}
	static const wxFontData* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFontData&>(value).GetEntityPtr();
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
