//==============================================================================
// VType_wxTrackable.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXTRACKABLE_H
#define GURAX_MODULE_WX_VTYPE_WXTRACKABLE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxTrackable
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxTrackable : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxTrackable VTYPE_wxTrackable;

//------------------------------------------------------------------------------
// Value_wxTrackable
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxTrackable : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxTrackable);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxTrackable");
protected:
	wxWeakRef<wxTrackable> _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxTrackable() = delete;
	explicit Value_wxTrackable(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxTrackable) :
		Value_Object(vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxTrackable(const Value_wxTrackable& src) = delete;
	Value_wxTrackable& operator=(const Value_wxTrackable& src) = delete;
	// Move constructor/operator
	Value_wxTrackable(Value_wxTrackable&& src) noexcept = delete;
	Value_wxTrackable& operator=(Value_wxTrackable&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxTrackable() = default;
public:
	wxTrackable* GetEntity() { return _pEntity.get(); }
	const wxTrackable* GetEntity() const { return _pEntity.get(); }
public:
	static wxTrackable* GetEntity(Value& value) {
		return dynamic_cast<Value_wxTrackable&>(value).GetEntity();
	}
	static const wxTrackable* GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxTrackable&>(value).GetEntity();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntity(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity(*this) == GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(GetEntity(*this) < GetEntity(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif
