﻿//==============================================================================
// VType_wxFlexGridSizer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFLEXGRIDSIZER_H
#define GURAX_MODULE_WX_VTYPE_WXFLEXGRIDSIZER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxGridSizer.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFlexGridSizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFlexGridSizer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFlexGridSizer VTYPE_wxFlexGridSizer;

//------------------------------------------------------------------------------
// Value_wxFlexGridSizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFlexGridSizer : public Value_wxGridSizer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFlexGridSizer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFlexGridSizer");
protected:
	wxFlexGridSizer* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFlexGridSizer() = delete;
	explicit Value_wxFlexGridSizer(wxFlexGridSizer* pEntity, VType& vtype = VTYPE_wxFlexGridSizer) :
		Value_wxGridSizer(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxFlexGridSizer(const Value_wxFlexGridSizer& src) = delete;
	Value_wxFlexGridSizer& operator=(const Value_wxFlexGridSizer& src) = delete;
	// Move constructor/operator
	Value_wxFlexGridSizer(Value_wxFlexGridSizer&& src) noexcept = delete;
	Value_wxFlexGridSizer& operator=(Value_wxFlexGridSizer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFlexGridSizer() = default;
public:
	wxFlexGridSizer& GetEntity() { return *_pEntity; }
	const wxFlexGridSizer& GetEntity() const { return *_pEntity; }
	wxFlexGridSizer* GetEntityPtr() { return _pEntity; }
	const wxFlexGridSizer* GetEntityPtr() const { return _pEntity; }
public:
	static wxFlexGridSizer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFlexGridSizer&>(value).GetEntity();
	}
	static const wxFlexGridSizer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFlexGridSizer&>(value).GetEntity();
	}
	static wxFlexGridSizer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFlexGridSizer&>(value).GetEntityPtr();
	}
	static const wxFlexGridSizer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFlexGridSizer&>(value).GetEntityPtr();
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
