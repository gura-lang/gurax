//==============================================================================
// VType_wxPrinterDC.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPRINTERDC_H
#define GURAX_MODULE_WX_VTYPE_WXPRINTERDC_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dcprint.h>
#include "Util.h"
#include "VType_wxDC.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPrinterDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPrinterDC : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPrinterDC VTYPE_wxPrinterDC;

//------------------------------------------------------------------------------
// Value_wxPrinterDC
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPrinterDC : public Value_wxDC {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPrinterDC);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPrinterDC");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPrinterDC() = delete;
	Value_wxPrinterDC(wxDC* pEntity, VType& vtype = VTYPE_wxPrinterDC) :
		Value_wxDC(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxPrinterDC(const Value_wxPrinterDC& src) = delete;
	Value_wxPrinterDC& operator=(const Value_wxPrinterDC& src) = delete;
	// Move constructor/operator
	Value_wxPrinterDC(Value_wxPrinterDC&& src) noexcept = delete;
	Value_wxPrinterDC& operator=(Value_wxPrinterDC&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPrinterDC() = default;
public:
	wxPrinterDC& GetEntity() { return reinterpret_cast<wxPrinterDC&>(Value_wxDC::GetEntity()); }
	const wxPrinterDC& GetEntity() const { return reinterpret_cast<const wxPrinterDC&>(Value_wxDC::GetEntity()); }
	wxPrinterDC* GetEntityPtr() { return reinterpret_cast<wxPrinterDC*>(Value_wxDC::GetEntityPtr()); }\
	const wxPrinterDC* GetEntityPtr() const { return reinterpret_cast<const wxPrinterDC*>(Value_wxDC::GetEntityPtr()); }
public:
	static wxPrinterDC& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPrinterDC&>(value).GetEntity();
	}
	static const wxPrinterDC& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPrinterDC&>(value).GetEntity();
	}
	static wxPrinterDC* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPrinterDC&>(value).GetEntityPtr();
	}
	static const wxPrinterDC* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPrinterDC&>(value).GetEntityPtr();
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