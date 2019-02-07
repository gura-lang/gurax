//==============================================================================
// Object_undefined.h
//==============================================================================
#ifndef GURAX_OBJECT_UNDEFINED_H
#define GURAX_OBJECT_UNDEFINED_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_undefined
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_undefined : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_undefined);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_undefined");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare(Frame* pFrame) override;
	};
	static KlassEx klass;
public:
	// Constructor
	Object_undefined() : Object(klass) {}
	// Copy constructor/operator
	Object_undefined(const Object_undefined& src) = delete;
	Object_undefined& operator=(const Object_undefined& src) = delete;
	// Move constructor/operator
	Object_undefined(Object_undefined&& src) = delete;
	Object_undefined& operator=(Object_undefined&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Object_undefined() = default;
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Object* pObject) const override { return IsSameType(pObject); }
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)? false : GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return "undefined";
	}
};

}

#endif
