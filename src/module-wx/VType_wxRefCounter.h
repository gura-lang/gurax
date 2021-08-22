//==============================================================================
// VType_wxRefCounter.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXREFCOUNTER_H
#define GURAX_MODULE_WX_VTYPE_WXREFCOUNTER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRefCounter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRefCounter : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRefCounter VTYPE_wxRefCounter;

//------------------------------------------------------------------------------
// Value_wxRefCounter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRefCounter : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRefCounter);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRefCounter");
protected:
	wxObjectDataPtr<wxRefCounter> _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRefCounter() = delete;
	explicit Value_wxRefCounter(wxRefCounter* pEntity, VType& vtype = VTYPE_wxRefCounter) :
		Value_Object(vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRefCounter(const Value_wxRefCounter& src) = delete;
	Value_wxRefCounter& operator=(const Value_wxRefCounter& src) = delete;
	// Move constructor/operator
	Value_wxRefCounter(Value_wxRefCounter&& src) noexcept = delete;
	Value_wxRefCounter& operator=(Value_wxRefCounter&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRefCounter() = default;
public:
	wxRefCounter& GetEntity() { return *_pEntity; }
	const wxRefCounter& GetEntity() const { return *_pEntity; }
	wxRefCounter* GetEntityPtr() { return _pEntity.get(); }
	const wxRefCounter* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxRefCounter& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRefCounter&>(value).GetEntity();
	}
	static const wxRefCounter& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRefCounter&>(value).GetEntity();
	}
	static wxRefCounter* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRefCounter&>(value).GetEntityPtr();
	}
	static const wxRefCounter* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRefCounter&>(value).GetEntityPtr();
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
