//==============================================================================
// VType_Validator.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_VALIDATOR_H
#define GURAX_MODULE_WX_VTYPE_VALIDATOR_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_EvtHandler.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_Validator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Validator : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Validator VTYPE_Validator;

//------------------------------------------------------------------------------
// Value_Validator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Validator : public Value_EvtHandler {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Validator);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Validator");
public:
	class EntityT : public wxValidator {
	public:
		using EntitySuper = wxValidator;
		using wxValidator::wxValidator;
	public:
		EntityCore core;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_Validator() = delete;
	explicit Value_Validator(wxValidator* pEntity, VType& vtype = VTYPE_Validator) :
		Value_EvtHandler(pEntity, vtype) {}
	// Copy constructor/operator
	Value_Validator(const Value_Validator& src) = delete;
	Value_Validator& operator=(const Value_Validator& src) = delete;
	// Move constructor/operator
	Value_Validator(Value_Validator&& src) noexcept = delete;
	Value_Validator& operator=(Value_Validator&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Validator() = default;
public:
	wxValidator* GetEntity() { return wxDynamicCast(Value_EvtHandler::GetEntity(), wxValidator); }
	const wxValidator* GetEntity() const { return wxDynamicCast(Value_EvtHandler::GetEntity(), wxValidator); }
public:
	static wxValidator* GetEntity(Value& value) {
		return dynamic_cast<Value_Validator&>(value).GetEntity();
	}
	static const wxValidator* GetEntity(const Value& value) {
		return dynamic_cast<const Value_Validator&>(value).GetEntity();
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
