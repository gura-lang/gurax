//==============================================================================
// VType_wxFrame.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFRAME_H
#define GURAX_MODULE_WX_VTYPE_WXFRAME_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFrame : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFrame VTYPE_wxFrame;

//------------------------------------------------------------------------------
// Value_wxFrame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFrame : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFrame);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFrame");
public:
	class EntityT : public wxFrame {
	public:
		using EntitySuper = wxFrame;
		using wxFrame::wxFrame;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFrame() = delete;
	explicit Value_wxFrame(wxTrackable* pEntity, VType& vtype = VTYPE_wxFrame) :
		Value_wxWindow(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxFrame(const Value_wxFrame& src) = delete;
	Value_wxFrame& operator=(const Value_wxFrame& src) = delete;
	// Move constructor/operator
	Value_wxFrame(Value_wxFrame&& src) noexcept = delete;
	Value_wxFrame& operator=(Value_wxFrame&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFrame() = default;
public:
	wxFrame* GetEntity() {
		return reinterpret_cast<wxFrame*>(Value_wxTrackable::GetEntity());
	}
	const wxFrame* GetEntity() const {
		return reinterpret_cast<const wxFrame*>(Value_wxTrackable::GetEntity());
	}
public:
	static wxFrame* GetEntity(Value& value) {
		return dynamic_cast<Value_wxFrame&>(value).GetEntity();
	}
	static const wxFrame* GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFrame&>(value).GetEntity();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntity(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntity(*this) == GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(GetEntity(*this) < GetEntity(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif
