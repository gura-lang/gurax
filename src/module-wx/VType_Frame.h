//==============================================================================
// VType_Frame.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_FRAME_H
#define GURAX_MODULE_WX_VTYPE_FRAME_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_Frame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Frame : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Frame VTYPE_Frame;

//------------------------------------------------------------------------------
// Value_Frame
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Frame : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Frame);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Frame");
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
	Value_Frame() = delete;
	explicit Value_Frame(EntityT* pEntity, VType& vtype = VTYPE_Frame) :
		Value_wxWindow(pEntity, vtype) {}
	// Copy constructor/operator
	Value_Frame(const Value_Frame& src) = delete;
	Value_Frame& operator=(const Value_Frame& src) = delete;
	// Move constructor/operator
	Value_Frame(Value_Frame&& src) noexcept = delete;
	Value_Frame& operator=(Value_Frame&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Frame() = default;
public:
	wxFrame* GetEntity() { return wxDynamicCast(Value_wxWindow::GetEntity(), wxFrame); }
	const wxFrame* GetEntity() const { return wxDynamicCast(Value_wxWindow::GetEntity(), wxFrame); }
public:
	static wxFrame* GetEntity(Value& value) {
		return dynamic_cast<Value_Frame&>(value).GetEntity();
	}
	static const wxFrame* GetEntity(const Value& value) {
		return dynamic_cast<const Value_Frame&>(value).GetEntity();
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
