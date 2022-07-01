//==============================================================================
// VType_wxPGEditorDialogAdapter.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPGEDITORDIALOGADAPTER_H
#define GURAX_MODULE_WX_VTYPE_WXPGEDITORDIALOGADAPTER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/editors.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPGEditorDialogAdapter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPGEditorDialogAdapter : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPGEditorDialogAdapter VTYPE_wxPGEditorDialogAdapter;

//------------------------------------------------------------------------------
// Value_wxPGEditorDialogAdapter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPGEditorDialogAdapter : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPGEditorDialogAdapter);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPGEditorDialogAdapter");
protected:
	wxPGEditorDialogAdapter* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPGEditorDialogAdapter() = delete;
	explicit Value_wxPGEditorDialogAdapter(wxPGEditorDialogAdapter* pEntity, VType& vtype = VTYPE_wxPGEditorDialogAdapter) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxPGEditorDialogAdapter(const wxPGEditorDialogAdapter& entity, VType& vtype = VTYPE_wxPGEditorDialogAdapter) :
		Value_Object(vtype), _pEntity(const_cast<wxPGEditorDialogAdapter*>(&entity)) {}
	// Copy constructor/operator
	Value_wxPGEditorDialogAdapter(const Value_wxPGEditorDialogAdapter& src) = delete;
	Value_wxPGEditorDialogAdapter& operator=(const Value_wxPGEditorDialogAdapter& src) = delete;
	// Move constructor/operator
	Value_wxPGEditorDialogAdapter(Value_wxPGEditorDialogAdapter&& src) noexcept = delete;
	Value_wxPGEditorDialogAdapter& operator=(Value_wxPGEditorDialogAdapter&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPGEditorDialogAdapter() = default;
public:
	wxPGEditorDialogAdapter& GetEntity() { return *_pEntity; }
	const wxPGEditorDialogAdapter& GetEntity() const { return *_pEntity; }
	wxPGEditorDialogAdapter* GetEntityPtr() { return _pEntity; }
	const wxPGEditorDialogAdapter* GetEntityPtr() const { return _pEntity; }
public:
	static wxPGEditorDialogAdapter& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPGEditorDialogAdapter&>(value).GetEntity();
	}
	static const wxPGEditorDialogAdapter& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPGEditorDialogAdapter&>(value).GetEntity();
	}
	static wxPGEditorDialogAdapter* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPGEditorDialogAdapter&>(value).GetEntityPtr();
	}
	static const wxPGEditorDialogAdapter* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPGEditorDialogAdapter&>(value).GetEntityPtr();
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
