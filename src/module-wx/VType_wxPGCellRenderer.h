//==============================================================================
// VType_wxPGCellRenderer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPGCELLRENDERER_H
#define GURAX_MODULE_WX_VTYPE_WXPGCELLRENDERER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/property.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPGCellRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPGCellRenderer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPGCellRenderer VTYPE_wxPGCellRenderer;

//------------------------------------------------------------------------------
// Value_wxPGCellRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPGCellRenderer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPGCellRenderer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPGCellRenderer");
protected:
	wxPGCellRenderer* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPGCellRenderer() = delete;
	explicit Value_wxPGCellRenderer(wxPGCellRenderer* pEntity, VType& vtype = VTYPE_wxPGCellRenderer) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxPGCellRenderer(const wxPGCellRenderer& entity, VType& vtype = VTYPE_wxPGCellRenderer) :
		Value_Object(vtype), _pEntity(const_cast<wxPGCellRenderer*>(&entity)) {}
	// Copy constructor/operator
	Value_wxPGCellRenderer(const Value_wxPGCellRenderer& src) = delete;
	Value_wxPGCellRenderer& operator=(const Value_wxPGCellRenderer& src) = delete;
	// Move constructor/operator
	Value_wxPGCellRenderer(Value_wxPGCellRenderer&& src) noexcept = delete;
	Value_wxPGCellRenderer& operator=(Value_wxPGCellRenderer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPGCellRenderer() = default;
public:
	wxPGCellRenderer& GetEntity() { return *_pEntity; }
	const wxPGCellRenderer& GetEntity() const { return *_pEntity; }
	wxPGCellRenderer* GetEntityPtr() { return _pEntity; }
	const wxPGCellRenderer* GetEntityPtr() const { return _pEntity; }
public:
	static wxPGCellRenderer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPGCellRenderer&>(value).GetEntity();
	}
	static const wxPGCellRenderer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPGCellRenderer&>(value).GetEntity();
	}
	static wxPGCellRenderer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPGCellRenderer&>(value).GetEntityPtr();
	}
	static const wxPGCellRenderer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPGCellRenderer&>(value).GetEntityPtr();
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
