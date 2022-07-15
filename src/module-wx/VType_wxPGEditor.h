//==============================================================================
// VType_wxPGEditor.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPGEDITOR_H
#define GURAX_MODULE_WX_VTYPE_WXPGEDITOR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/editors.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPGEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPGEditor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPGEditor VTYPE_wxPGEditor;

//------------------------------------------------------------------------------
// Value_wxPGEditor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPGEditor : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPGEditor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPGEditor");
protected:
	wxPGEditor* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPGEditor() = delete;
	explicit Value_wxPGEditor(wxPGEditor* pEntity, VType& vtype = VTYPE_wxPGEditor) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxPGEditor(const wxPGEditor& entity, VType& vtype = VTYPE_wxPGEditor) :
		Value_Object(vtype), _pEntity(const_cast<wxPGEditor*>(&entity)) {}
	// Copy constructor/operator
	Value_wxPGEditor(const Value_wxPGEditor& src) = delete;
	Value_wxPGEditor& operator=(const Value_wxPGEditor& src) = delete;
	// Move constructor/operator
	Value_wxPGEditor(Value_wxPGEditor&& src) noexcept = delete;
	Value_wxPGEditor& operator=(Value_wxPGEditor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPGEditor() = default;
public:
	wxPGEditor& GetEntity() { return *_pEntity; }
	const wxPGEditor& GetEntity() const { return *_pEntity; }
	wxPGEditor* GetEntityPtr() { return _pEntity; }
	const wxPGEditor* GetEntityPtr() const { return _pEntity; }
public:
	static wxPGEditor& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPGEditor&>(value).GetEntity();
	}
	static const wxPGEditor& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPGEditor&>(value).GetEntity();
	}
	static wxPGEditor* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPGEditor&>(value).GetEntityPtr();
	}
	static const wxPGEditor* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPGEditor&>(value).GetEntityPtr();
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