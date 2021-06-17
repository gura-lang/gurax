//==============================================================================
// VType_wxSizerFlags.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSIZERFLAGS_H
#define GURAX_MODULE_WX_VTYPE_WXSIZERFLAGS_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSizerFlags
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSizerFlags : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSizerFlags VTYPE_wxSizerFlags;

//------------------------------------------------------------------------------
// Value_wxSizerFlags
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSizerFlags : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSizerFlags);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSizerFlags");
protected:
	wxSizerFlags _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSizerFlags() = delete;
	explicit Value_wxSizerFlags(const wxSizerFlags& entity, VType& vtype = VTYPE_wxSizerFlags) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxSizerFlags(const Value_wxSizerFlags& src) = delete;
	Value_wxSizerFlags& operator=(const Value_wxSizerFlags& src) = delete;
	// Move constructor/operator
	Value_wxSizerFlags(Value_wxSizerFlags&& src) noexcept = delete;
	Value_wxSizerFlags& operator=(Value_wxSizerFlags&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSizerFlags() = default;
public:
	wxSizerFlags& GetEntity() { return _entity; }
	const wxSizerFlags& GetEntity() const { return _entity; }
	wxSizerFlags* GetEntityPtr() { return &_entity; }
	const wxSizerFlags* GetEntityPtr() const { return &_entity; }
public:
	static wxSizerFlags& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSizerFlags&>(value).GetEntity();
	}
	static const wxSizerFlags& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSizerFlags&>(value).GetEntity();
	}
	static wxSizerFlags* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSizerFlags&>(value).GetEntityPtr();
	}
	static const wxSizerFlags* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSizerFlags&>(value).GetEntityPtr();
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
