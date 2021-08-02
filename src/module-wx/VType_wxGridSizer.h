//==============================================================================
// VType_wxGridSizer.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDSIZER_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDSIZER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxSizer.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridSizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridSizer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridSizer VTYPE_wxGridSizer;

//------------------------------------------------------------------------------
// Value_wxGridSizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridSizer : public Value_wxSizer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridSizer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridSizer");
protected:
	wxGridSizer* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridSizer() = delete;
	explicit Value_wxGridSizer(wxGridSizer* pEntity, VType& vtype = VTYPE_wxGridSizer) :
		Value_wxSizer(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxGridSizer(const Value_wxGridSizer& src) = delete;
	Value_wxGridSizer& operator=(const Value_wxGridSizer& src) = delete;
	// Move constructor/operator
	Value_wxGridSizer(Value_wxGridSizer&& src) noexcept = delete;
	Value_wxGridSizer& operator=(Value_wxGridSizer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridSizer() = default;
public:
	wxGridSizer& GetEntity() { return *_pEntity; }
	const wxGridSizer& GetEntity() const { return *_pEntity; }
	wxGridSizer* GetEntityPtr() { return _pEntity; }
	const wxGridSizer* GetEntityPtr() const { return _pEntity; }
public:
	static wxGridSizer& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridSizer&>(value).GetEntity();
	}
	static const wxGridSizer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridSizer&>(value).GetEntity();
	}
	static wxGridSizer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridSizer&>(value).GetEntityPtr();
	}
	static const wxGridSizer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridSizer&>(value).GetEntityPtr();
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
