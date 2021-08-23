//==============================================================================
// VType_wxGridCellNumberRenderer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCELLNUMBERRENDERER_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCELLNUMBERRENDERER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"
#include "VType_wxGridCellStringRenderer.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCellNumberRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCellNumberRenderer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCellNumberRenderer VTYPE_wxGridCellNumberRenderer;

//------------------------------------------------------------------------------
// Value_wxGridCellNumberRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCellNumberRenderer : public Value_wxGridCellStringRenderer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCellNumberRenderer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCellNumberRenderer");
protected:
	wxObjectDataPtr<wxGridCellNumberRenderer> _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCellNumberRenderer() = delete;
	explicit Value_wxGridCellNumberRenderer(wxGridCellNumberRenderer* pEntity, VType& vtype = VTYPE_wxGridCellNumberRenderer) :
		Value_wxGridCellStringRenderer(pEntity, vtype), _pEntity(pEntity) { pEntity->IncRef(); }
	// Copy constructor/operator
	Value_wxGridCellNumberRenderer(const Value_wxGridCellNumberRenderer& src) = delete;
	Value_wxGridCellNumberRenderer& operator=(const Value_wxGridCellNumberRenderer& src) = delete;
	// Move constructor/operator
	Value_wxGridCellNumberRenderer(Value_wxGridCellNumberRenderer&& src) noexcept = delete;
	Value_wxGridCellNumberRenderer& operator=(Value_wxGridCellNumberRenderer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCellNumberRenderer() = default;
public:
	wxGridCellNumberRenderer& GetEntity() { return *_pEntity; }
	const wxGridCellNumberRenderer& GetEntity() const { return *_pEntity; }
	wxGridCellNumberRenderer* GetEntityPtr() { return _pEntity.get(); }
	const wxGridCellNumberRenderer* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxGridCellNumberRenderer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCellNumberRenderer&>(value).GetEntity();
	}
	static const wxGridCellNumberRenderer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCellNumberRenderer&>(value).GetEntity();
	}
	static wxGridCellNumberRenderer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCellNumberRenderer&>(value).GetEntityPtr();
	}
	static const wxGridCellNumberRenderer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCellNumberRenderer&>(value).GetEntityPtr();
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
