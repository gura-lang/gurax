//==============================================================================
// VType_wxWindowDC.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXWINDOWDC_H
#define GURAX_MODULE_WX_VTYPE_WXWINDOWDC_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dcclient.h>
#include "Util.h"
#include "VType_wxDC.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxWindowDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxWindowDC : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxWindowDC VTYPE_wxWindowDC;

//------------------------------------------------------------------------------
// Value_wxWindowDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxWindowDC : public Value_wxDC {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxWindowDC);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxWindowDC");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxWindowDC() = delete;
	explicit Value_wxWindowDC(const wxWindowDC& entity, VType& vtype = VTYPE_wxWindowDC) :
		Value_wxDC(entity, vtype) {}
	// Copy constructor/operator
	Value_wxWindowDC(const Value_wxWindowDC& src) = delete;
	Value_wxWindowDC& operator=(const Value_wxWindowDC& src) = delete;
	// Move constructor/operator
	Value_wxWindowDC(Value_wxWindowDC&& src) noexcept = delete;
	Value_wxWindowDC& operator=(Value_wxWindowDC&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxWindowDC() = default;
public:
	wxWindowDC& GetEntity() { return reinterpret_cast<wxWindowDC&>(Value_wxDC::GetEntity()); }
	const wxWindowDC& GetEntity() const { return reinterpret_cast<const wxWindowDC&>(Value_wxDC::GetEntity()); }
	wxWindowDC* GetEntityPtr() { return reinterpret_cast<wxWindowDC*>(Value_wxDC::GetEntityPtr()); }\
	const wxWindowDC* GetEntityPtr() const { return reinterpret_cast<const wxWindowDC*>(Value_wxDC::GetEntityPtr()); }
public:
	static wxWindowDC& GetEntity(Value& value) {
		return dynamic_cast<Value_wxWindowDC&>(value).GetEntity();
	}
	static const wxWindowDC& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxWindowDC&>(value).GetEntity();
	}
	static wxWindowDC* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxWindowDC&>(value).GetEntityPtr();
	}
	static const wxWindowDC* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxWindowDC&>(value).GetEntityPtr();
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
