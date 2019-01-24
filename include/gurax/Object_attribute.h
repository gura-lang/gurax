//==============================================================================
// Object_attribute.h
//==============================================================================
#ifndef GURAX_OBJECT_ATTRIBUTE_H
#define GURAX_OBJECT_ATTRIBUTE_H
#include "Object.h"
#include "Attribute.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_attribute
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_attribute : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_attribute);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_attribute");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	RefPtr<Attribute> _pAttribute;
public:
	// Constructor
	Object_attribute() = delete;
	explicit Object_attribute(Attribute *pAttribute) : Object(klass), _pAttribute(pAttribute) {}
	// Copy constructor/operator
	Object_attribute(const Object_attribute& src) : Object(klass), _pAttribute(src._pAttribute->Reference()) {}
	Object_attribute& operator=(const Object_attribute& src) { _pAttribute.reset(src._pAttribute->Reference()); return *this; }
	// Move constructor/operator
	Object_attribute(Object_attribute&& src) : Object(klass), _pAttribute(src._pAttribute.release()) {}
	Object_attribute& operator=(Object_attribute&& src) noexcept { _pAttribute.reset(src._pAttribute.release()); return *this; }
protected:
	// Destructor
	~Object_attribute() = default;
public:
	const Attribute* GetAttribute() const { return _pAttribute.get(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetAttribute()->CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetAttribute()->IsEqualTo(dynamic_cast<const Object_attribute*>(pObject)->GetAttribute());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetAttribute()->IsLessThan(dynamic_cast<const Object_attribute*>(pObject)->GetAttribute()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override {
		return _pAttribute->ToString(ss);
	}
};

}

#endif
