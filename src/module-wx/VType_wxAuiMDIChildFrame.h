//==============================================================================
// VType_wxAuiMDIChildFrame.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXAUIMDICHILDFRAME_H
#define GURAX_MODULE_WX_VTYPE_WXAUIMDICHILDFRAME_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/aui/tabmdi.h>
#include "Util.h"
#include "VType_wxFrame.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAuiMDIChildFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAuiMDIChildFrame : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAuiMDIChildFrame VTYPE_wxAuiMDIChildFrame;

//------------------------------------------------------------------------------
// Value_wxAuiMDIChildFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAuiMDIChildFrame : public Value_wxFrame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAuiMDIChildFrame);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAuiMDIChildFrame");
protected:
	wxWeakRef<wxAuiMDIChildFrame> _pEntity;
public:
	class EntityT : public wxAuiMDIChildFrame {
	public:
		using wxAuiMDIChildFrame::wxAuiMDIChildFrame;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAuiMDIChildFrame() = delete;
	explicit Value_wxAuiMDIChildFrame(wxAuiMDIChildFrame* pEntity, VType& vtype = VTYPE_wxAuiMDIChildFrame) :
		Value_wxFrame(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxAuiMDIChildFrame(const Value_wxAuiMDIChildFrame& src) = delete;
	Value_wxAuiMDIChildFrame& operator=(const Value_wxAuiMDIChildFrame& src) = delete;
	// Move constructor/operator
	Value_wxAuiMDIChildFrame(Value_wxAuiMDIChildFrame&& src) noexcept = delete;
	Value_wxAuiMDIChildFrame& operator=(Value_wxAuiMDIChildFrame&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAuiMDIChildFrame() = default;
public:
	wxAuiMDIChildFrame& GetEntity() { return *_pEntity; }
	const wxAuiMDIChildFrame& GetEntity() const { return *_pEntity; }
	wxAuiMDIChildFrame* GetEntityPtr() { return _pEntity.get(); }
	const wxAuiMDIChildFrame* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxAuiMDIChildFrame& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAuiMDIChildFrame&>(value).GetEntity();
	}
	static const wxAuiMDIChildFrame& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAuiMDIChildFrame&>(value).GetEntity();
	}
	static wxAuiMDIChildFrame* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAuiMDIChildFrame&>(value).GetEntityPtr();
	}
	static const wxAuiMDIChildFrame* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAuiMDIChildFrame&>(value).GetEntityPtr();
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
