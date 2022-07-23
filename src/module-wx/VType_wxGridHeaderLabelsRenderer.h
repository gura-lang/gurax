//==============================================================================
// VType_wxGridHeaderLabelsRenderer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDHEADERLABELSRENDERER_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDHEADERLABELSRENDERER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridHeaderLabelsRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridHeaderLabelsRenderer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridHeaderLabelsRenderer VTYPE_wxGridHeaderLabelsRenderer;

//------------------------------------------------------------------------------
// Value_wxGridHeaderLabelsRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridHeaderLabelsRenderer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridHeaderLabelsRenderer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridHeaderLabelsRenderer");
protected:
	wxGridHeaderLabelsRenderer* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridHeaderLabelsRenderer() = delete;
	explicit Value_wxGridHeaderLabelsRenderer(wxGridHeaderLabelsRenderer* pEntity, VType& vtype = VTYPE_wxGridHeaderLabelsRenderer) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxGridHeaderLabelsRenderer(const wxGridHeaderLabelsRenderer& entity, VType& vtype = VTYPE_wxGridHeaderLabelsRenderer) :
		Value_Object(vtype), _pEntity(const_cast<wxGridHeaderLabelsRenderer*>(&entity)) {}
	// Copy constructor/operator
	Value_wxGridHeaderLabelsRenderer(const Value_wxGridHeaderLabelsRenderer& src) = delete;
	Value_wxGridHeaderLabelsRenderer& operator=(const Value_wxGridHeaderLabelsRenderer& src) = delete;
	// Move constructor/operator
	Value_wxGridHeaderLabelsRenderer(Value_wxGridHeaderLabelsRenderer&& src) noexcept = delete;
	Value_wxGridHeaderLabelsRenderer& operator=(Value_wxGridHeaderLabelsRenderer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridHeaderLabelsRenderer() = default;
public:
	wxGridHeaderLabelsRenderer& GetEntity() { return *_pEntity; }
	const wxGridHeaderLabelsRenderer& GetEntity() const { return *_pEntity; }
	wxGridHeaderLabelsRenderer* GetEntityPtr() { return _pEntity; }
	const wxGridHeaderLabelsRenderer* GetEntityPtr() const { return _pEntity; }
public:
	static wxGridHeaderLabelsRenderer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridHeaderLabelsRenderer&>(value).GetEntity();
	}
	static const wxGridHeaderLabelsRenderer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridHeaderLabelsRenderer&>(value).GetEntity();
	}
	static wxGridHeaderLabelsRenderer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridHeaderLabelsRenderer&>(value).GetEntityPtr();
	}
	static const wxGridHeaderLabelsRenderer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridHeaderLabelsRenderer&>(value).GetEntityPtr();
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