//==============================================================================
// Object_attribute.h
//==============================================================================
#ifndef GURAX_OBJECT_ATTRIBUTE_H
#define GURAX_OBJECT_ATTRIBUTE_H
#include "Object.h"
#include "Attribute.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_attribute
//------------------------------------------------------------------------------
class KlassT_attribute : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_attribute Klass_attribute;

//------------------------------------------------------------------------------
// Object_attribute
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_attribute : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_attribute);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_attribute");
private:
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	Object_attribute() = delete;
	explicit Object_attribute(Attribute *pAttr) : Object(Klass_attribute), _pAttr(pAttr) {}
	// Copy constructor/operator
	Object_attribute(const Object_attribute& src) : Object(Klass_attribute), _pAttr(src._pAttr->Reference()) {}
	Object_attribute& operator=(const Object_attribute& src) { _pAttr.reset(src._pAttr->Reference()); return *this; }
	// Move constructor/operator
	Object_attribute(Object_attribute&& src) : Object(Klass_attribute), _pAttr(src._pAttr.release()) {}
	Object_attribute& operator=(Object_attribute&& src) noexcept { _pAttr.reset(src._pAttr.release()); return *this; }
protected:
	// Destructor
	~Object_attribute() = default;
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
			GetAttr().IsEqualTo(dynamic_cast<const Object_attribute*>(pObject)->GetAttr());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetAttr().IsLessThan(dynamic_cast<const Object_attribute*>(pObject)->GetAttr()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetAttr().ToString(ss);
	}
};

}

#endif
