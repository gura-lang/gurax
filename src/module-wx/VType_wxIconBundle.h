//==============================================================================
// VType_wxIconBundle.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXICONBUNDLE_H
#define GURAX_MODULE_WX_VTYPE_WXICONBUNDLE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxGDIObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxIconBundle
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxIconBundle : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxIconBundle VTYPE_wxIconBundle;

//------------------------------------------------------------------------------
// Value_wxIconBundle
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxIconBundle : public Value_wxGDIObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxIconBundle);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxIconBundle");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxIconBundle() = delete;
	explicit Value_wxIconBundle(const wxIconBundle& entity, VType& vtype = VTYPE_wxIconBundle) :
		Value_wxGDIObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxIconBundle(const Value_wxIconBundle& src) = delete;
	Value_wxIconBundle& operator=(const Value_wxIconBundle& src) = delete;
	// Move constructor/operator
	Value_wxIconBundle(Value_wxIconBundle&& src) noexcept = delete;
	Value_wxIconBundle& operator=(Value_wxIconBundle&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxIconBundle() = default;
public:
	wxIconBundle& GetEntity() { return reinterpret_cast<wxIconBundle&>(Value_wxGDIObject::GetEntity()); }
	const wxIconBundle& GetEntity() const { return reinterpret_cast<const wxIconBundle&>(Value_wxGDIObject::GetEntity()); }
	wxIconBundle* GetEntityPtr() { return reinterpret_cast<wxIconBundle*>(Value_wxGDIObject::GetEntityPtr()); }\
	const wxIconBundle* GetEntityPtr() const { return reinterpret_cast<const wxIconBundle*>(Value_wxGDIObject::GetEntityPtr()); }
public:
	static wxIconBundle& GetEntity(Value& value) {
		return dynamic_cast<Value_wxIconBundle&>(value).GetEntity();
	}
	static const wxIconBundle& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxIconBundle&>(value).GetEntity();
	}
	static wxIconBundle* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxIconBundle&>(value).GetEntityPtr();
	}
	static const wxIconBundle* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxIconBundle&>(value).GetEntityPtr();
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
