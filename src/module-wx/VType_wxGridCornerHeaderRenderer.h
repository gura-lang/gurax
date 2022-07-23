//==============================================================================
// VType_wxGridCornerHeaderRenderer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDCORNERHEADERRENDERER_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDCORNERHEADERRENDERER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridCornerHeaderRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridCornerHeaderRenderer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridCornerHeaderRenderer VTYPE_wxGridCornerHeaderRenderer;

//------------------------------------------------------------------------------
// Value_wxGridCornerHeaderRenderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridCornerHeaderRenderer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridCornerHeaderRenderer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridCornerHeaderRenderer");
protected:
	wxGridCornerHeaderRenderer* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridCornerHeaderRenderer() = delete;
	explicit Value_wxGridCornerHeaderRenderer(wxGridCornerHeaderRenderer* pEntity, VType& vtype = VTYPE_wxGridCornerHeaderRenderer) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxGridCornerHeaderRenderer(const wxGridCornerHeaderRenderer& entity, VType& vtype = VTYPE_wxGridCornerHeaderRenderer) :
		Value_Object(vtype), _pEntity(const_cast<wxGridCornerHeaderRenderer*>(&entity)) {}
	// Copy constructor/operator
	Value_wxGridCornerHeaderRenderer(const Value_wxGridCornerHeaderRenderer& src) = delete;
	Value_wxGridCornerHeaderRenderer& operator=(const Value_wxGridCornerHeaderRenderer& src) = delete;
	// Move constructor/operator
	Value_wxGridCornerHeaderRenderer(Value_wxGridCornerHeaderRenderer&& src) noexcept = delete;
	Value_wxGridCornerHeaderRenderer& operator=(Value_wxGridCornerHeaderRenderer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridCornerHeaderRenderer() = default;
public:
	wxGridCornerHeaderRenderer& GetEntity() { return *_pEntity; }
	const wxGridCornerHeaderRenderer& GetEntity() const { return *_pEntity; }
	wxGridCornerHeaderRenderer* GetEntityPtr() { return _pEntity; }
	const wxGridCornerHeaderRenderer* GetEntityPtr() const { return _pEntity; }
public:
	static wxGridCornerHeaderRenderer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridCornerHeaderRenderer&>(value).GetEntity();
	}
	static const wxGridCornerHeaderRenderer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridCornerHeaderRenderer&>(value).GetEntity();
	}
	static wxGridCornerHeaderRenderer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridCornerHeaderRenderer&>(value).GetEntityPtr();
	}
	static const wxGridCornerHeaderRenderer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridCornerHeaderRenderer&>(value).GetEntityPtr();
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