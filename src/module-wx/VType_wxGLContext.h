//==============================================================================
// VType_wxGLContext.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGLCONTEXT_H
#define GURAX_MODULE_WX_VTYPE_WXGLCONTEXT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "Util.h"
#include "VType_wxObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGLContext
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGLContext : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGLContext VTYPE_wxGLContext;

//------------------------------------------------------------------------------
// Value_wxGLContext
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGLContext : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGLContext);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGLContext");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGLContext() = delete;
	explicit Value_wxGLContext(const wxGLContext& entity, VType& vtype = VTYPE_wxGLContext) :
		Value_wxObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxGLContext(const Value_wxGLContext& src) = delete;
	Value_wxGLContext& operator=(const Value_wxGLContext& src) = delete;
	// Move constructor/operator
	Value_wxGLContext(Value_wxGLContext&& src) noexcept = delete;
	Value_wxGLContext& operator=(Value_wxGLContext&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGLContext() = default;
public:
	wxGLContext& GetEntity() {
		return reinterpret_cast<wxGLContext&>(Value_wxObject::GetEntity());
	}
	const wxGLContext& GetEntity() const {
		return reinterpret_cast<const wxGLContext&>(Value_wxObject::GetEntity());
	}
	wxGLContext* GetEntityPtr() {
		return reinterpret_cast<wxGLContext*>(Value_wxObject::GetEntityPtr());
	}
	const wxGLContext* GetEntityPtr() const {
		return reinterpret_cast<const wxGLContext*>(Value_wxObject::GetEntityPtr());
	}
public:
	static wxGLContext& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGLContext&>(value).GetEntity();
	}
	static const wxGLContext& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGLContext&>(value).GetEntity();
	}
	static wxGLContext* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGLContext&>(value).GetEntityPtr();
	}
	static const wxGLContext* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGLContext&>(value).GetEntityPtr();
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
