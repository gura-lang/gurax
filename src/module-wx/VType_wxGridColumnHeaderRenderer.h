﻿//==============================================================================
// VType_wxGridColumnHeaderRenderer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCOLUMNHEADERRENDERER_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCOLUMNHEADERRENDERER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxGridHeaderLabelsRenderer.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridColumnHeaderRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridColumnHeaderRenderer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridColumnHeaderRenderer VTYPE_wxGridColumnHeaderRenderer;

//------------------------------------------------------------------------------
// Value_wxGridColumnHeaderRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridColumnHeaderRenderer : public Value_wxGridHeaderLabelsRenderer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridColumnHeaderRenderer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridColumnHeaderRenderer");
protected:
	wxGridColumnHeaderRenderer* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridColumnHeaderRenderer() = delete;
	explicit Value_wxGridColumnHeaderRenderer(wxGridColumnHeaderRenderer* pEntity, VType& vtype = VTYPE_wxGridColumnHeaderRenderer) :
		Value_wxGridHeaderLabelsRenderer(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxGridColumnHeaderRenderer(const Value_wxGridColumnHeaderRenderer& src) = delete;
	Value_wxGridColumnHeaderRenderer& operator=(const Value_wxGridColumnHeaderRenderer& src) = delete;
	// Move constructor/operator
	Value_wxGridColumnHeaderRenderer(Value_wxGridColumnHeaderRenderer&& src) noexcept = delete;
	Value_wxGridColumnHeaderRenderer& operator=(Value_wxGridColumnHeaderRenderer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridColumnHeaderRenderer() = default;
public:
	wxGridColumnHeaderRenderer& GetEntity() { return *_pEntity; }
	const wxGridColumnHeaderRenderer& GetEntity() const { return *_pEntity; }
	wxGridColumnHeaderRenderer* GetEntityPtr() { return _pEntity; }
	const wxGridColumnHeaderRenderer* GetEntityPtr() const { return _pEntity; }
public:
	static wxGridColumnHeaderRenderer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridColumnHeaderRenderer&>(value).GetEntity();
	}
	static const wxGridColumnHeaderRenderer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridColumnHeaderRenderer&>(value).GetEntity();
	}
	static wxGridColumnHeaderRenderer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridColumnHeaderRenderer&>(value).GetEntityPtr();
	}
	static const wxGridColumnHeaderRenderer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridColumnHeaderRenderer&>(value).GetEntityPtr();
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
