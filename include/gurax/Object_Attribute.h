//==============================================================================
// Object_Attribute.h
//==============================================================================
#ifndef GURAX_OBJECT_ATTRIBUTE_H
#define GURAX_OBJECT_ATTRIBUTE_H
#include "Object_Object.h"
#include "Attribute.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Attribute
//------------------------------------------------------------------------------
class VTypeT_Attribute : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VTypeT_Attribute VType_Attribute;

//------------------------------------------------------------------------------
// Object_Attribute
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Attribute : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Attribute);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Attribute");
private:
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	Object_Attribute() = delete;
	explicit Object_Attribute(Attribute* pAttr, VType& vtype = VType_Attribute) :
		Object_Object(vtype), _pAttr(pAttr) {}
	// Copy constructor/operator
	Object_Attribute(const Object_Attribute& src) : Object_Object(src), _pAttr(src._pAttr->Reference()) {}
	Object_Attribute& operator=(const Object_Attribute& src) = delete;
	// Move constructor/operator
	Object_Attribute(Object_Attribute&& src) = delete;
	Object_Attribute& operator=(Object_Attribute&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Attribute() = default;
public:
	Attribute& GetAttr() { return *_pAttr; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetAttr().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetAttr().IsEqualTo(dynamic_cast<const Object_Attribute*>(pObject)->GetAttr());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetAttr().IsLessThan(dynamic_cast<const Object_Attribute*>(pObject)->GetAttr()) :
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetAttr().ToString(ss);
	}
};

}

#endif
