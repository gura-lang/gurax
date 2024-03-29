﻿//==============================================================================
// VType_wxPostScriptDC.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPOSTSCRIPTDC_H
#define GURAX_MODULE_WX_VTYPE_WXPOSTSCRIPTDC_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dcps.h>
#include "Util.h"
#include "VType_wxDC.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPostScriptDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPostScriptDC : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPostScriptDC VTYPE_wxPostScriptDC;

//------------------------------------------------------------------------------
// Value_wxPostScriptDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPostScriptDC : public Value_wxDC {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPostScriptDC);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPostScriptDC");
protected:
	wxPostScriptDC& _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPostScriptDC() = delete;
	explicit Value_wxPostScriptDC(const wxPostScriptDC& entity, VType& vtype = VTYPE_wxPostScriptDC) :
		Value_wxDC(entity, vtype), _entity(const_cast<wxPostScriptDC&>(entity)) {}
	// Copy constructor/operator
	Value_wxPostScriptDC(const Value_wxPostScriptDC& src) = delete;
	Value_wxPostScriptDC& operator=(const Value_wxPostScriptDC& src) = delete;
	// Move constructor/operator
	Value_wxPostScriptDC(Value_wxPostScriptDC&& src) noexcept = delete;
	Value_wxPostScriptDC& operator=(Value_wxPostScriptDC&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPostScriptDC() = default;
public:
	wxPostScriptDC& GetEntity() { return _entity; }
	const wxPostScriptDC& GetEntity() const { return _entity; }
	wxPostScriptDC* GetEntityPtr() { return &_entity; }
	const wxPostScriptDC* GetEntityPtr() const { return &_entity; }
public:
	static wxPostScriptDC& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPostScriptDC&>(value).GetEntity();
	}
	static const wxPostScriptDC& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPostScriptDC&>(value).GetEntity();
	}
	static wxPostScriptDC* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPostScriptDC&>(value).GetEntityPtr();
	}
	static const wxPostScriptDC* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPostScriptDC&>(value).GetEntityPtr();
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
