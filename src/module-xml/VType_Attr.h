//==============================================================================
// VType_Attr.h
//==============================================================================
#ifndef GURAX_MODULE_XML_VTYPE_ATTR_H
#define GURAX_MODULE_XML_VTYPE_ATTR_H
#include <gurax.h>
#include "Attr.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// VType_Attr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Attr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Attr VTYPE_Attr;

//------------------------------------------------------------------------------
// Value_Attr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Attr : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Attr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Attr");
protected:
	RefPtr<Attr> _pAttr;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Attr() = delete;
	explicit Value_Attr(Attr* pAttr, VType& vtype = VTYPE_Attr) :
		Value_Object(vtype), _pAttr(pAttr) {}
	// Copy constructor/operator
	Value_Attr(const Value_Attr& src) :
		Value_Object(src), _pAttr(src._pAttr->Reference()) {}
	Value_Attr& operator=(const Value_Attr& src) = delete;
	// Move constructor/operator
	Value_Attr(Value_Attr&& src) noexcept = delete;
	Value_Attr& operator=(Value_Attr&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Attr() = default;
public:
	Attr& GetAttr() { return *_pAttr; }
	const Attr& GetAttr() const { return *_pAttr; }
public:
	static Attr& GetAttr(Value& value) {
		return dynamic_cast<Value_Attr&>(value).GetAttr();
	}
	static const Attr& GetAttr(const Value& value) {
		return dynamic_cast<const Value_Attr&>(value).GetAttr();
	}
	static Attr* GetEntityPtr(Value& value) { return &GetAttr(value); }
	static const Attr* GetEntityPtr(const Value& value) { return &GetAttr(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetAttr().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetAttr().IsEqualTo(Value_Attr::GetAttr(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetAttr().IsLessThan(Value_Attr::GetAttr(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(xml)

#endif
