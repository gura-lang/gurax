//==============================================================================
// VType_wxMDIParentFrame.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMDIPARENTFRAME_H
#define GURAX_MODULE_WX_VTYPE_WXMDIPARENTFRAME_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/mdi.h>
#include "Util.h"
#include "VType_wxFrame.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMDIParentFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMDIParentFrame : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMDIParentFrame VTYPE_wxMDIParentFrame;

//------------------------------------------------------------------------------
// Value_wxMDIParentFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMDIParentFrame : public Value_wxFrame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMDIParentFrame);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMDIParentFrame");
protected:
	wxWeakRef<wxMDIParentFrame> _pEntity;
public:
	class EntityT : public wxMDIParentFrame {
	public:
		using wxMDIParentFrame::wxMDIParentFrame;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxMDIParentFrame() = delete;
	explicit Value_wxMDIParentFrame(wxMDIParentFrame* pEntity, VType& vtype = VTYPE_wxMDIParentFrame) :
		Value_wxFrame(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxMDIParentFrame(const Value_wxMDIParentFrame& src) = delete;
	Value_wxMDIParentFrame& operator=(const Value_wxMDIParentFrame& src) = delete;
	// Move constructor/operator
	Value_wxMDIParentFrame(Value_wxMDIParentFrame&& src) noexcept = delete;
	Value_wxMDIParentFrame& operator=(Value_wxMDIParentFrame&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMDIParentFrame() = default;
public:
	wxMDIParentFrame& GetEntity() { return *_pEntity; }
	const wxMDIParentFrame& GetEntity() const { return *_pEntity; }
	wxMDIParentFrame* GetEntityPtr() { return _pEntity.get(); }
	const wxMDIParentFrame* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxMDIParentFrame& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMDIParentFrame&>(value).GetEntity();
	}
	static const wxMDIParentFrame& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMDIParentFrame&>(value).GetEntity();
	}
	static wxMDIParentFrame* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMDIParentFrame&>(value).GetEntityPtr();
	}
	static const wxMDIParentFrame* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMDIParentFrame&>(value).GetEntityPtr();
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
