//==============================================================================
// VType_wxBufferedDC.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXBUFFEREDDC_H
#define GURAX_MODULE_WX_VTYPE_WXBUFFEREDDC_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include "Util.h"
#include "VType_wxDC.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxBufferedDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxBufferedDC : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxBufferedDC VTYPE_wxBufferedDC;

//------------------------------------------------------------------------------
// Value_wxBufferedDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxBufferedDC : public Value_wxDC {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxBufferedDC);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxBufferedDC");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxBufferedDC() = delete;
	Value_wxBufferedDC(wxDC* pEntity, VType& vtype = VTYPE_wxBufferedDC) :
		Value_wxDC(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxBufferedDC(const Value_wxBufferedDC& src) = delete;
	Value_wxBufferedDC& operator=(const Value_wxBufferedDC& src) = delete;
	// Move constructor/operator
	Value_wxBufferedDC(Value_wxBufferedDC&& src) noexcept = delete;
	Value_wxBufferedDC& operator=(Value_wxBufferedDC&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxBufferedDC() = default;
public:
	wxBufferedDC& GetEntity() { return reinterpret_cast<wxBufferedDC&>(Value_wxDC::GetEntity()); }
	const wxBufferedDC& GetEntity() const { return reinterpret_cast<const wxBufferedDC&>(Value_wxDC::GetEntity()); }
	wxBufferedDC* GetEntityPtr() { return reinterpret_cast<wxBufferedDC*>(Value_wxDC::GetEntityPtr()); }\
	const wxBufferedDC* GetEntityPtr() const { return reinterpret_cast<const wxBufferedDC*>(Value_wxDC::GetEntityPtr()); }
public:
	static wxBufferedDC& GetEntity(Value& value) {
		return dynamic_cast<Value_wxBufferedDC&>(value).GetEntity();
	}
	static const wxBufferedDC& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxBufferedDC&>(value).GetEntity();
	}
	static wxBufferedDC* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxBufferedDC&>(value).GetEntityPtr();
	}
	static const wxBufferedDC* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxBufferedDC&>(value).GetEntityPtr();
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
