//==============================================================================
// VType_wxSizer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSIZER_H
#define GURAX_MODULE_WX_VTYPE_WXSIZER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSizer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSizer VTYPE_wxSizer;

//------------------------------------------------------------------------------
// Value_wxSizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSizer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSizer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSizer");
protected:
	wxSizer* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSizer() = delete;
	explicit Value_wxSizer(wxSizer* pEntity, VType& vtype = VTYPE_wxSizer) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxSizer(const wxSizer& entity, VType& vtype = VTYPE_wxSizer) :
		Value_Object(vtype), _pEntity(const_cast<wxSizer*>(&entity)) {}
	// Copy constructor/operator
	Value_wxSizer(const Value_wxSizer& src) = delete;
	Value_wxSizer& operator=(const Value_wxSizer& src) = delete;
	// Move constructor/operator
	Value_wxSizer(Value_wxSizer&& src) noexcept = delete;
	Value_wxSizer& operator=(Value_wxSizer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSizer() = default;
public:
	wxSizer& GetEntity() { return *_pEntity; }
	const wxSizer& GetEntity() const { return *_pEntity; }
	wxSizer* GetEntityPtr() { return _pEntity; }
	const wxSizer* GetEntityPtr() const { return _pEntity; }
public:
	static wxSizer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSizer&>(value).GetEntity();
	}
	static const wxSizer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSizer&>(value).GetEntity();
	}
	static wxSizer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSizer&>(value).GetEntityPtr();
	}
	static const wxSizer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSizer&>(value).GetEntityPtr();
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
