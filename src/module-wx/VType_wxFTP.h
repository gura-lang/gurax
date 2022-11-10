﻿//==============================================================================
// VType_wxFTP.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFTP_H
#define GURAX_MODULE_WX_VTYPE_WXFTP_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/protocol/ftp.h>
#include "Util.h"
#include "VType_wxProtocol.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFTP
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFTP : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFTP VTYPE_wxFTP;

//------------------------------------------------------------------------------
// Value_wxFTP
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFTP : public Value_wxProtocol {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFTP);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFTP");
protected:
	wxFTP* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFTP() = delete;
	explicit Value_wxFTP(wxFTP* pEntity, VType& vtype = VTYPE_wxFTP) :
		Value_wxProtocol(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxFTP(const Value_wxFTP& src) = delete;
	Value_wxFTP& operator=(const Value_wxFTP& src) = delete;
	// Move constructor/operator
	Value_wxFTP(Value_wxFTP&& src) noexcept = delete;
	Value_wxFTP& operator=(Value_wxFTP&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFTP() = default;
public:
	wxFTP& GetEntity() { return *_pEntity; }
	const wxFTP& GetEntity() const { return *_pEntity; }
	wxFTP* GetEntityPtr() { return _pEntity; }
	const wxFTP* GetEntityPtr() const { return _pEntity; }
public:
	static wxFTP& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFTP&>(value).GetEntity();
	}
	static const wxFTP& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFTP&>(value).GetEntity();
	}
	static wxFTP* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFTP&>(value).GetEntityPtr();
	}
	static const wxFTP* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFTP&>(value).GetEntityPtr();
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
