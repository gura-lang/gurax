//==============================================================================
// VType_wxValidator.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXVALIDATOR_H
#define GURAX_MODULE_WX_VTYPE_WXVALIDATOR_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvtHandler.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxValidator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxValidator : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxValidator VTYPE_wxValidator;

//------------------------------------------------------------------------------
// Value_wxValidator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxValidator : public Value_wxEvtHandler {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxValidator);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxValidator");
public:
	class EntityT : public wxValidator {
	public:
		using wxValidator::wxValidator;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxValidator() = delete;
	explicit Value_wxValidator(wxEvtHandler* pEntity, VType& vtype = VTYPE_wxValidator) :
		Value_wxEvtHandler(pEntity, vtype) {}
	// Copy constructor/operator
	Value_wxValidator(const Value_wxValidator& src) = delete;
	Value_wxValidator& operator=(const Value_wxValidator& src) = delete;
	// Move constructor/operator
	Value_wxValidator(Value_wxValidator&& src) noexcept = delete;
	Value_wxValidator& operator=(Value_wxValidator&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxValidator() = default;
public:
	wxValidator& GetEntity() {
		return reinterpret_cast<wxValidator&>(Value_wxEvtHandler::GetEntity());
	}
	const wxValidator& GetEntity() const {
		return reinterpret_cast<const wxValidator&>(Value_wxEvtHandler::GetEntity());
	}
	wxValidator* GetEntityPtr() {
		return reinterpret_cast<wxValidator*>(Value_wxEvtHandler::GetEntityPtr());
	}
	const wxValidator* GetEntityPtr() const {
		return reinterpret_cast<const wxValidator*>(Value_wxEvtHandler::GetEntityPtr());
	}
public:
	static wxValidator& GetEntity(Value& value) {
		return dynamic_cast<Value_wxValidator&>(value).GetEntity();
	}
	static const wxValidator& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxValidator&>(value).GetEntity();
	}
	static wxValidator* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxValidator&>(value).GetEntityPtr();
	}
	static const wxValidator* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxValidator&>(value).GetEntityPtr();
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
