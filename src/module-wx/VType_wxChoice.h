//==============================================================================
// VType_wxChoice.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCHOICE_H
#define GURAX_MODULE_WX_VTYPE_WXCHOICE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxChoice
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxChoice : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxChoice VTYPE_wxChoice;

//------------------------------------------------------------------------------
// Value_wxChoice
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxChoice : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxChoice);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxChoice");
public:
	class EntityT : public wxChoice {
	public:
		using wxChoice::wxChoice;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxChoice() = delete;
	explicit Value_wxChoice(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxChoice) :
		Value_wxControl(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxChoice(const Value_wxChoice& src) = delete;
	Value_wxChoice& operator=(const Value_wxChoice& src) = delete;
	// Move constructor/operator
	Value_wxChoice(Value_wxChoice&& src) noexcept = delete;
	Value_wxChoice& operator=(Value_wxChoice&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxChoice() = default;
public:
	wxChoice& GetEntity() {
		return reinterpret_cast<wxChoice&>(Value_wxEvtHandler::GetEntity());
	}
	const wxChoice& GetEntity() const {
		return reinterpret_cast<const wxChoice&>(Value_wxEvtHandler::GetEntity());
	}
	wxChoice* GetEntityPtr() {
		return reinterpret_cast<wxChoice*>(Value_wxEvtHandler::GetEntityPtr());
	}
	const wxChoice* GetEntityPtr() const {
		return reinterpret_cast<const wxChoice*>(Value_wxEvtHandler::GetEntityPtr());
	}
public:
	static wxChoice& GetEntity(Value& value) {
		return dynamic_cast<Value_wxChoice&>(value).GetEntity();
	}
	static const wxChoice& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxChoice&>(value).GetEntity();
	}
	static wxChoice* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxChoice&>(value).GetEntityPtr();
	}
	static const wxChoice* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxChoice&>(value).GetEntityPtr();
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
