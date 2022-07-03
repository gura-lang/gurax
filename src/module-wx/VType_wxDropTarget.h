//==============================================================================
// VType_wxDropTarget.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXDROPTARGET_H
#define GURAX_MODULE_WX_VTYPE_WXDROPTARGET_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dnd.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxDropTarget
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxDropTarget : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxDropTarget VTYPE_wxDropTarget;

//------------------------------------------------------------------------------
// Value_wxDropTarget
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxDropTarget : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxDropTarget);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxDropTarget");
protected:
	wxDropTarget* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxDropTarget() = delete;
	explicit Value_wxDropTarget(wxDropTarget* pEntity, VType& vtype = VTYPE_wxDropTarget) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxDropTarget(const wxDropTarget& entity, VType& vtype = VTYPE_wxDropTarget) :
		Value_Object(vtype), _pEntity(const_cast<wxDropTarget*>(&entity)) {}
	// Copy constructor/operator
	Value_wxDropTarget(const Value_wxDropTarget& src) = delete;
	Value_wxDropTarget& operator=(const Value_wxDropTarget& src) = delete;
	// Move constructor/operator
	Value_wxDropTarget(Value_wxDropTarget&& src) noexcept = delete;
	Value_wxDropTarget& operator=(Value_wxDropTarget&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxDropTarget() = default;
public:
	wxDropTarget& GetEntity() { return *_pEntity; }
	const wxDropTarget& GetEntity() const { return *_pEntity; }
	wxDropTarget* GetEntityPtr() { return _pEntity; }
	const wxDropTarget* GetEntityPtr() const { return _pEntity; }
public:
	static wxDropTarget& GetEntity(Value& value) {
		return dynamic_cast<Value_wxDropTarget&>(value).GetEntity();
	}
	static const wxDropTarget& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxDropTarget&>(value).GetEntity();
	}
	static wxDropTarget* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxDropTarget&>(value).GetEntityPtr();
	}
	static const wxDropTarget* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxDropTarget&>(value).GetEntityPtr();
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
