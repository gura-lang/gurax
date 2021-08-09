//==============================================================================
// VType_wxAffineMatrix2D.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXAFFINEMATRIX2D_H
#define GURAX_MODULE_WX_VTYPE_WXAFFINEMATRIX2D_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAffineMatrix2D
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAffineMatrix2D : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAffineMatrix2D VTYPE_wxAffineMatrix2D;

//------------------------------------------------------------------------------
// Value_wxAffineMatrix2D
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAffineMatrix2D : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAffineMatrix2D);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAffineMatrix2D");
protected:
	wxAffineMatrix2D _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAffineMatrix2D() = delete;
	explicit Value_wxAffineMatrix2D(const wxAffineMatrix2D& entity, VType& vtype = VTYPE_wxAffineMatrix2D) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxAffineMatrix2D(const Value_wxAffineMatrix2D& src) = delete;
	Value_wxAffineMatrix2D& operator=(const Value_wxAffineMatrix2D& src) = delete;
	// Move constructor/operator
	Value_wxAffineMatrix2D(Value_wxAffineMatrix2D&& src) noexcept = delete;
	Value_wxAffineMatrix2D& operator=(Value_wxAffineMatrix2D&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAffineMatrix2D() = default;
public:
	wxAffineMatrix2D& GetEntity() { return _entity; }
	const wxAffineMatrix2D& GetEntity() const { return _entity; }
	wxAffineMatrix2D* GetEntityPtr() { return &_entity; }
	const wxAffineMatrix2D* GetEntityPtr() const { return &_entity; }
public:
	static wxAffineMatrix2D& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAffineMatrix2D&>(value).GetEntity();
	}
	static const wxAffineMatrix2D& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAffineMatrix2D&>(value).GetEntity();
	}
	static wxAffineMatrix2D* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAffineMatrix2D&>(value).GetEntityPtr();
	}
	static const wxAffineMatrix2D* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAffineMatrix2D&>(value).GetEntityPtr();
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