﻿//==============================================================================
// VType_wxGridCellEnumRenderer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCELLENUMRENDERER_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCELLENUMRENDERER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxGridCellStringRenderer.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCellEnumRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCellEnumRenderer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCellEnumRenderer VTYPE_wxGridCellEnumRenderer;

//------------------------------------------------------------------------------
// Value_wxGridCellEnumRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCellEnumRenderer : public Value_wxGridCellStringRenderer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCellEnumRenderer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCellEnumRenderer");
protected:
	wxObjectDataPtr<wxGridCellEnumRenderer> _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCellEnumRenderer() = delete;
	explicit Value_wxGridCellEnumRenderer(wxGridCellEnumRenderer* pEntity, VType& vtype = VTYPE_wxGridCellEnumRenderer) :
		Value_wxGridCellStringRenderer(pEntity, vtype), _pEntity(pEntity) { pEntity->IncRef(); }
	// Copy constructor/operator
	Value_wxGridCellEnumRenderer(const Value_wxGridCellEnumRenderer& src) = delete;
	Value_wxGridCellEnumRenderer& operator=(const Value_wxGridCellEnumRenderer& src) = delete;
	// Move constructor/operator
	Value_wxGridCellEnumRenderer(Value_wxGridCellEnumRenderer&& src) noexcept = delete;
	Value_wxGridCellEnumRenderer& operator=(Value_wxGridCellEnumRenderer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCellEnumRenderer() = default;
public:
	wxGridCellEnumRenderer& GetEntity() { return *_pEntity; }
	const wxGridCellEnumRenderer& GetEntity() const { return *_pEntity; }
	wxGridCellEnumRenderer* GetEntityPtr() { return _pEntity.get(); }
	const wxGridCellEnumRenderer* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxGridCellEnumRenderer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCellEnumRenderer&>(value).GetEntity();
	}
	static const wxGridCellEnumRenderer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCellEnumRenderer&>(value).GetEntity();
	}
	static wxGridCellEnumRenderer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCellEnumRenderer&>(value).GetEntityPtr();
	}
	static const wxGridCellEnumRenderer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCellEnumRenderer&>(value).GetEntityPtr();
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
