//==============================================================================
// VType_wxFontInfo.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFONTINFO_H
#define GURAX_MODULE_WX_VTYPE_WXFONTINFO_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/font.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFontInfo
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFontInfo : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFontInfo VTYPE_wxFontInfo;

//------------------------------------------------------------------------------
// Value_wxFontInfo
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFontInfo : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFontInfo);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFontInfo");
protected:
	wxFontInfo _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFontInfo() = delete;
	explicit Value_wxFontInfo(const wxFontInfo& entity, VType& vtype = VTYPE_wxFontInfo) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxFontInfo(const Value_wxFontInfo& src) = delete;
	Value_wxFontInfo& operator=(const Value_wxFontInfo& src) = delete;
	// Move constructor/operator
	Value_wxFontInfo(Value_wxFontInfo&& src) noexcept = delete;
	Value_wxFontInfo& operator=(Value_wxFontInfo&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFontInfo() = default;
public:
	wxFontInfo& GetEntity() { return _entity; }
	const wxFontInfo& GetEntity() const { return _entity; }
	wxFontInfo* GetEntityPtr() { return &_entity; }
	const wxFontInfo* GetEntityPtr() const { return &_entity; }
public:
	static wxFontInfo& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFontInfo&>(value).GetEntity();
	}
	static const wxFontInfo& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFontInfo&>(value).GetEntity();
	}
	static wxFontInfo* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFontInfo&>(value).GetEntityPtr();
	}
	static const wxFontInfo* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFontInfo&>(value).GetEntityPtr();
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
