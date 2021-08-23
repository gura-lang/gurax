//==============================================================================
// VType_wxGridCellFloatRenderer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCELLFLOATRENDERER_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCELLFLOATRENDERER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxGridCellStringRenderer.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCellFloatRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCellFloatRenderer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCellFloatRenderer VTYPE_wxGridCellFloatRenderer;

//------------------------------------------------------------------------------
// Value_wxGridCellFloatRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCellFloatRenderer : public Value_wxGridCellStringRenderer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCellFloatRenderer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCellFloatRenderer");
protected:
	wxObjectDataPtr<wxGridCellFloatRenderer> _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCellFloatRenderer() = delete;
	explicit Value_wxGridCellFloatRenderer(wxGridCellFloatRenderer* pEntity, VType& vtype = VTYPE_wxGridCellFloatRenderer) :
		Value_wxGridCellStringRenderer(pEntity, vtype), _pEntity(pEntity) { pEntity->IncRef(); }
	// Copy constructor/operator
	Value_wxGridCellFloatRenderer(const Value_wxGridCellFloatRenderer& src) = delete;
	Value_wxGridCellFloatRenderer& operator=(const Value_wxGridCellFloatRenderer& src) = delete;
	// Move constructor/operator
	Value_wxGridCellFloatRenderer(Value_wxGridCellFloatRenderer&& src) noexcept = delete;
	Value_wxGridCellFloatRenderer& operator=(Value_wxGridCellFloatRenderer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCellFloatRenderer() = default;
public:
	wxGridCellFloatRenderer& GetEntity() { return *_pEntity; }
	const wxGridCellFloatRenderer& GetEntity() const { return *_pEntity; }
	wxGridCellFloatRenderer* GetEntityPtr() { return _pEntity.get(); }
	const wxGridCellFloatRenderer* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxGridCellFloatRenderer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCellFloatRenderer&>(value).GetEntity();
	}
	static const wxGridCellFloatRenderer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCellFloatRenderer&>(value).GetEntity();
	}
	static wxGridCellFloatRenderer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCellFloatRenderer&>(value).GetEntityPtr();
	}
	static const wxGridCellFloatRenderer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCellFloatRenderer&>(value).GetEntityPtr();
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
