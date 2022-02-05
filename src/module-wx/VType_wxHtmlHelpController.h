//==============================================================================
// VType_wxHtmlHelpController.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXHTMLHELPCONTROLLER_H
#define GURAX_MODULE_WX_VTYPE_WXHTMLHELPCONTROLLER_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "Util.h"
#include "VType_wxHelpControllerBase.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxHtmlHelpController
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxHtmlHelpController : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxHtmlHelpController VTYPE_wxHtmlHelpController;

//------------------------------------------------------------------------------
// Value_wxHtmlHelpController
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxHtmlHelpController : public Value_wxHelpControllerBase {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxHtmlHelpController);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxHtmlHelpController");
protected:
	wxHtmlHelpController* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxHtmlHelpController() = delete;
	explicit Value_wxHtmlHelpController(wxHtmlHelpController* pEntity, VType& vtype = VTYPE_wxHtmlHelpController) :
		Value_wxHelpControllerBase(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxHtmlHelpController(const Value_wxHtmlHelpController& src) = delete;
	Value_wxHtmlHelpController& operator=(const Value_wxHtmlHelpController& src) = delete;
	// Move constructor/operator
	Value_wxHtmlHelpController(Value_wxHtmlHelpController&& src) noexcept = delete;
	Value_wxHtmlHelpController& operator=(Value_wxHtmlHelpController&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxHtmlHelpController() = default;
public:
	wxHtmlHelpController& GetEntity() { return *_pEntity; }
	const wxHtmlHelpController& GetEntity() const { return *_pEntity; }
	wxHtmlHelpController* GetEntityPtr() { return _pEntity; }
	const wxHtmlHelpController* GetEntityPtr() const { return _pEntity; }
public:
	static wxHtmlHelpController& GetEntity(Value& value) {
		return dynamic_cast<Value_wxHtmlHelpController&>(value).GetEntity();
	}
	static const wxHtmlHelpController& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxHtmlHelpController&>(value).GetEntity();
	}
	static wxHtmlHelpController* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxHtmlHelpController&>(value).GetEntityPtr();
	}
	static const wxHtmlHelpController* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxHtmlHelpController&>(value).GetEntityPtr();
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
