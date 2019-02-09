//==============================================================================
// Value_Attribute.h
//==============================================================================
#ifndef GURAX_OBJECT_ATTRIBUTE_H
#define GURAX_OBJECT_ATTRIBUTE_H
#include "Value_Object.h"
#include "Attribute.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Attribute
//------------------------------------------------------------------------------
class VType_Attribute : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Attribute VTYPE_Attribute;

//------------------------------------------------------------------------------
// Value_Attribute
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Attribute : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Attribute);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Attribute");
private:
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	Value_Attribute() = delete;
	explicit Value_Attribute(Attribute* pAttr, VType& vtype = VTYPE_Attribute) :
		Value_Object(vtype), _pAttr(pAttr) {}
	// Copy constructor/operator
	Value_Attribute(const Value_Attribute& src) : Value_Object(src), _pAttr(src._pAttr->Reference()) {}
	Value_Attribute& operator=(const Value_Attribute& src) = delete;
	// Move constructor/operator
	Value_Attribute(Value_Attribute&& src) = delete;
	Value_Attribute& operator=(Value_Attribute&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Attribute() = default;
public:
	Attribute& GetAttr() { return *_pAttr; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetAttr().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pValue) const override {
		return IsSameType(pValue) &&
			GetAttr().IsEqualTo(dynamic_cast<const Value_Attribute*>(pValue)->GetAttr());
	}
	virtual bool IsLessThan(const Object* pValue) const override {
		return IsSameType(pValue)?
			GetAttr().IsLessThan(dynamic_cast<const Value_Attribute*>(pValue)->GetAttr()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetAttr().ToString(ss);
	}
};

}

#endif
