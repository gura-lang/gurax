//==============================================================================
// Object_Bool.h
//==============================================================================
#ifndef GURAX_OBJECT_BOOL_H
#define GURAX_OBJECT_BOOL_H
#include "Object_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Bool
//------------------------------------------------------------------------------
class KlassT_Bool : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Bool Klass_Bool;

//------------------------------------------------------------------------------
// Object_Bool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Bool : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Bool);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Bool");
private:
	bool _flag;
public:
	// Constructor
	explicit Object_Bool(bool flag, Klass& klass = Klass_Bool) : Object_Object(klass), _flag(flag) {}
	// Copy constructor/operator
	Object_Bool(const Object_Bool& src) : Object_Object(src), _flag(src._flag) {}
	Object_Bool& operator=(const Object_Bool& src) = delete;
	// Move constructor/operator
	Object_Bool(Object_Bool&& src) = delete;
	Object_Bool& operator=(Object_Bool&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Bool() = default;
public:
	bool GetBool() const { return _flag; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return static_cast<size_t>(GetBool());
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) && GetBool() == dynamic_cast<const Object_Bool*>(pObject)->GetBool();
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetBool() < dynamic_cast<const Object_Bool*>(pObject)->GetBool() :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return _flag? "true" : "false";
	}
};

}

#endif
