﻿//==============================================================================
// VType_wxURL.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXURL_H
#define GURAX_MODULE_WX_VTYPE_WXURL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/url.h>
#include "Util.h"
#include "VType_wxURI.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxURL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxURL : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxURL VTYPE_wxURL;

//------------------------------------------------------------------------------
// Value_wxURL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxURL : public Value_wxURI {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxURL);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxURL");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxURL() = delete;
	explicit Value_wxURL(const wxURL& entity, VType& vtype = VTYPE_wxURL) :
		Value_wxURI(entity, vtype) {}
	// Copy constructor/operator
	Value_wxURL(const Value_wxURL& src) = delete;
	Value_wxURL& operator=(const Value_wxURL& src) = delete;
	// Move constructor/operator
	Value_wxURL(Value_wxURL&& src) noexcept = delete;
	Value_wxURL& operator=(Value_wxURL&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxURL() = default;
public:
	wxURL& GetEntity() { return reinterpret_cast<wxURL&>(Value_wxURI::GetEntity()); }
	const wxURL& GetEntity() const { return reinterpret_cast<const wxURL&>(Value_wxURI::GetEntity()); }
	wxURL* GetEntityPtr() { return reinterpret_cast<wxURL*>(Value_wxURI::GetEntityPtr()); }\
	const wxURL* GetEntityPtr() const { return reinterpret_cast<const wxURL*>(Value_wxURI::GetEntityPtr()); }
public:
	static wxURL& GetEntity(Value& value) {
		return dynamic_cast<Value_wxURL&>(value).GetEntity();
	}
	static const wxURL& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxURL&>(value).GetEntity();
	}
	static wxURL* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxURL&>(value).GetEntityPtr();
	}
	static const wxURL* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxURL&>(value).GetEntityPtr();
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
