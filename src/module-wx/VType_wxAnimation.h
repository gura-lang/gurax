﻿//==============================================================================
// VType_wxAnimation.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXANIMATION_H
#define GURAX_MODULE_WX_VTYPE_WXANIMATION_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/animate.h>
#include "Util.h"
#include "VType_wxObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAnimation
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAnimation : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAnimation VTYPE_wxAnimation;

//------------------------------------------------------------------------------
// Value_wxAnimation
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAnimation : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAnimation);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAnimation");
protected:
	wxAnimation _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAnimation() = delete;
	explicit Value_wxAnimation(const wxAnimation& entity, VType& vtype = VTYPE_wxAnimation) :
		Value_wxObject(entity, vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxAnimation(const Value_wxAnimation& src) = delete;
	Value_wxAnimation& operator=(const Value_wxAnimation& src) = delete;
	// Move constructor/operator
	Value_wxAnimation(Value_wxAnimation&& src) noexcept = delete;
	Value_wxAnimation& operator=(Value_wxAnimation&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAnimation() = default;
public:
	wxAnimation& GetEntity() { return _entity; }
	const wxAnimation& GetEntity() const { return _entity; }
	wxAnimation* GetEntityPtr() { return &_entity; }
	const wxAnimation* GetEntityPtr() const { return &_entity; }
public:
	static wxAnimation& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAnimation&>(value).GetEntity();
	}
	static const wxAnimation& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAnimation&>(value).GetEntity();
	}
	static wxAnimation* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAnimation&>(value).GetEntityPtr();
	}
	static const wxAnimation* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAnimation&>(value).GetEntityPtr();
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
