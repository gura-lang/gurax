//==============================================================================
// Object_Attribute.h
//==============================================================================
#ifndef GURAX_OBJECT_ATTRIBUTE_H
#define GURAX_OBJECT_ATTRIBUTE_H
#include "Object.h"
#include "Attribute.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Attribute
//------------------------------------------------------------------------------
class KlassT_Attribute : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Attribute Klass_Attribute;

//------------------------------------------------------------------------------
// Object_Attribute
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Attribute : public Object {
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
	explicit Object_Attribute(Attribute *pAttr) : Object(Klass_Attribute), _pAttr(pAttr) {}
	// Copy constructor/operator
	Object_Attribute(const Object_Attribute& src) : Object(Klass_Attribute), _pAttr(src._pAttr->Reference()) {}
	Object_Attribute& operator=(const Object_Attribute& src) { _pAttr.reset(src._pAttr->Reference()); return *this; }
	// Move constructor/operator
	Object_Attribute(Object_Attribute&& src) : Object(Klass_Attribute), _pAttr(src._pAttr.release()) {}
	Object_Attribute& operator=(Object_Attribute&& src) noexcept { _pAttr.reset(src._pAttr.release()); return *this; }
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
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetAttr().ToString(ss);
	}
};

}

#endif
