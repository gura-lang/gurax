﻿//==============================================================================
// VType_wxRegConfig.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXREGCONFIG_H
#define GURAX_MODULE_WX_VTYPE_WXREGCONFIG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/msw/regconf.h>
#include "Util.h"
#include "VType_wxConfigBase.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRegConfig
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRegConfig : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRegConfig VTYPE_wxRegConfig;

//------------------------------------------------------------------------------
// Value_wxRegConfig
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRegConfig : public Value_wxConfigBase {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRegConfig);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRegConfig");
protected:
	wxRegConfig* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRegConfig() = delete;
	explicit Value_wxRegConfig(wxRegConfig* pEntity, VType& vtype = VTYPE_wxRegConfig) :
		Value_wxConfigBase(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRegConfig(const Value_wxRegConfig& src) = delete;
	Value_wxRegConfig& operator=(const Value_wxRegConfig& src) = delete;
	// Move constructor/operator
	Value_wxRegConfig(Value_wxRegConfig&& src) noexcept = delete;
	Value_wxRegConfig& operator=(Value_wxRegConfig&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRegConfig() = default;
public:
	wxRegConfig& GetEntity() { return *_pEntity; }
	const wxRegConfig& GetEntity() const { return *_pEntity; }
	wxRegConfig* GetEntityPtr() { return _pEntity; }
	const wxRegConfig* GetEntityPtr() const { return _pEntity; }
public:
	static wxRegConfig& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRegConfig&>(value).GetEntity();
	}
	static const wxRegConfig& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRegConfig&>(value).GetEntity();
	}
	static wxRegConfig* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRegConfig&>(value).GetEntityPtr();
	}
	static const wxRegConfig* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRegConfig&>(value).GetEntityPtr();
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
