//==============================================================================
// VType_wxCaret.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCARET_H
#define GURAX_MODULE_WX_VTYPE_WXCARET_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxCaret
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxCaret : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxCaret VTYPE_wxCaret;

//------------------------------------------------------------------------------
// Value_wxCaret
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxCaret : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxCaret);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxCaret");
protected:
	wxCaret* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxCaret() = delete;
	explicit Value_wxCaret(wxCaret* pEntity, VType& vtype = VTYPE_wxCaret) :
		Value_Object(vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxCaret(const Value_wxCaret& src) = delete;
	Value_wxCaret& operator=(const Value_wxCaret& src) = delete;
	// Move constructor/operator
	Value_wxCaret(Value_wxCaret&& src) noexcept = delete;
	Value_wxCaret& operator=(Value_wxCaret&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxCaret() = default;
public:
	wxCaret& GetEntity() { return *_pEntity; }
	const wxCaret& GetEntity() const { return *_pEntity; }
	wxCaret* GetEntityPtr() { return _pEntity; }
	const wxCaret* GetEntityPtr() const { return _pEntity; }
public:
	static wxCaret& GetEntity(Value& value) {
		return dynamic_cast<Value_wxCaret&>(value).GetEntity();
	}
	static const wxCaret& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxCaret&>(value).GetEntity();
	}
	static wxCaret* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxCaret&>(value).GetEntityPtr();
	}
	static const wxCaret* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxCaret&>(value).GetEntityPtr();
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