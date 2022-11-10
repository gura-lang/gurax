﻿//==============================================================================
// VType_wxInputStream.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXINPUTSTREAM_H
#define GURAX_MODULE_WX_VTYPE_WXINPUTSTREAM_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxStreamBase.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxInputStream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxInputStream : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxInputStream VTYPE_wxInputStream;

//------------------------------------------------------------------------------
// Value_wxInputStream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxInputStream : public Value_wxStreamBase {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxInputStream);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxInputStream");
protected:
	wxInputStream* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxInputStream() = delete;
	explicit Value_wxInputStream(wxInputStream* pEntity, VType& vtype = VTYPE_wxInputStream) :
		Value_wxStreamBase(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxInputStream(const Value_wxInputStream& src) = delete;
	Value_wxInputStream& operator=(const Value_wxInputStream& src) = delete;
	// Move constructor/operator
	Value_wxInputStream(Value_wxInputStream&& src) noexcept = delete;
	Value_wxInputStream& operator=(Value_wxInputStream&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxInputStream() = default;
public:
	wxInputStream& GetEntity() { return *_pEntity; }
	const wxInputStream& GetEntity() const { return *_pEntity; }
	wxInputStream* GetEntityPtr() { return _pEntity; }
	const wxInputStream* GetEntityPtr() const { return _pEntity; }
public:
	static wxInputStream& GetEntity(Value& value) {
		return dynamic_cast<Value_wxInputStream&>(value).GetEntity();
	}
	static const wxInputStream& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxInputStream&>(value).GetEntity();
	}
	static wxInputStream* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxInputStream&>(value).GetEntityPtr();
	}
	static const wxInputStream* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxInputStream&>(value).GetEntityPtr();
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
