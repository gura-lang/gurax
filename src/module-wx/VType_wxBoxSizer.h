//==============================================================================
// VType_wxBoxSizer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXBOXSIZER_H
#define GURAX_MODULE_WX_VTYPE_WXBOXSIZER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxSizer.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxBoxSizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxBoxSizer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxBoxSizer VTYPE_wxBoxSizer;

//------------------------------------------------------------------------------
// Value_wxBoxSizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxBoxSizer : public Value_wxSizer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxBoxSizer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxBoxSizer");
protected:
	wxBoxSizer* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxBoxSizer() = delete;
	explicit Value_wxBoxSizer(wxBoxSizer* pEntity, VType& vtype = VTYPE_wxBoxSizer) :
		Value_wxSizer(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxBoxSizer(const Value_wxBoxSizer& src) = delete;
	Value_wxBoxSizer& operator=(const Value_wxBoxSizer& src) = delete;
	// Move constructor/operator
	Value_wxBoxSizer(Value_wxBoxSizer&& src) noexcept = delete;
	Value_wxBoxSizer& operator=(Value_wxBoxSizer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxBoxSizer() = default;
public:
	wxBoxSizer& GetEntity() { return *_pEntity; }
	const wxBoxSizer& GetEntity() const { return *_pEntity; }
	wxBoxSizer* GetEntityPtr() { return _pEntity; }
	const wxBoxSizer* GetEntityPtr() const { return _pEntity; }
public:
	static wxBoxSizer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxBoxSizer&>(value).GetEntity();
	}
	static const wxBoxSizer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxBoxSizer&>(value).GetEntity();
	}
	static wxBoxSizer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxBoxSizer&>(value).GetEntityPtr();
	}
	static const wxBoxSizer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxBoxSizer&>(value).GetEntityPtr();
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
