﻿//==============================================================================
// VType_wxGraphicsRenderer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRAPHICSRENDERER_H
#define GURAX_MODULE_WX_VTYPE_WXGRAPHICSRENDERER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/graphics.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGraphicsRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGraphicsRenderer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGraphicsRenderer VTYPE_wxGraphicsRenderer;

//------------------------------------------------------------------------------
// Value_wxGraphicsRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGraphicsRenderer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGraphicsRenderer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGraphicsRenderer");
protected:
	wxGraphicsRenderer* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGraphicsRenderer() = delete;
	explicit Value_wxGraphicsRenderer(wxGraphicsRenderer* pEntity, VType& vtype = VTYPE_wxGraphicsRenderer) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxGraphicsRenderer(const wxGraphicsRenderer& entity, VType& vtype = VTYPE_wxGraphicsRenderer) :
		Value_Object(vtype), _pEntity(const_cast<wxGraphicsRenderer*>(&entity)) {}
	// Copy constructor/operator
	Value_wxGraphicsRenderer(const Value_wxGraphicsRenderer& src) = delete;
	Value_wxGraphicsRenderer& operator=(const Value_wxGraphicsRenderer& src) = delete;
	// Move constructor/operator
	Value_wxGraphicsRenderer(Value_wxGraphicsRenderer&& src) noexcept = delete;
	Value_wxGraphicsRenderer& operator=(Value_wxGraphicsRenderer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGraphicsRenderer() = default;
public:
	wxGraphicsRenderer& GetEntity() { return *_pEntity; }
	const wxGraphicsRenderer& GetEntity() const { return *_pEntity; }
	wxGraphicsRenderer* GetEntityPtr() { return _pEntity; }
	const wxGraphicsRenderer* GetEntityPtr() const { return _pEntity; }
public:
	static wxGraphicsRenderer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGraphicsRenderer&>(value).GetEntity();
	}
	static const wxGraphicsRenderer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGraphicsRenderer&>(value).GetEntity();
	}
	static wxGraphicsRenderer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGraphicsRenderer&>(value).GetEntityPtr();
	}
	static const wxGraphicsRenderer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGraphicsRenderer&>(value).GetEntityPtr();
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
