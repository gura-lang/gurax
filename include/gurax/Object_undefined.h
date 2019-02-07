//==============================================================================
// Object_Undefined.h
//==============================================================================
#ifndef GURAX_OBJECT_UNDEFINED_H
#define GURAX_OBJECT_UNDEFINED_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Undefined
//------------------------------------------------------------------------------
class KlassT_Undefined : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Undefined Klass_Undefined;

//------------------------------------------------------------------------------
// Object_Undefined
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Undefined : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Undefined);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Undefined");
public:
	// Constructor
	Object_Undefined() : Object(Klass_Undefined) {}
	// Copy constructor/operator
	Object_Undefined(const Object_Undefined& src) = delete;
	Object_Undefined& operator=(const Object_Undefined& src) = delete;
	// Move constructor/operator
	Object_Undefined(Object_Undefined&& src) = delete;
	Object_Undefined& operator=(Object_Undefined&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Object_Undefined() = default;
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
