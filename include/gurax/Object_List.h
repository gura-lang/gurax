//==============================================================================
// Object_List.h
//==============================================================================
#ifndef GURAX_OBJECT_LIST_H
#define GURAX_OBJECT_LIST_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_List
//------------------------------------------------------------------------------
class KlassT_List : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_List Klass_List;

//------------------------------------------------------------------------------
// Object_List
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_List : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_List);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_List");
private:
	RefPtr<ObjectTypedOwner> _pObjectTypedOwner;
public:
	// Constructor
	Object_List() : Object(Klass_List), _pObjectTypedOwner(new ObjectTypedOwner()) {}
	explicit Object_List(ObjectTypedOwner* pObjectTypedOwner) : Object(Klass_List), _pObjectTypedOwner(pObjectTypedOwner) {}
	// Copy constructor/operator
	Object_List(const Object_List& src) : Object(Klass_List), _pObjectTypedOwner(src._pObjectTypedOwner->CloneDeep()) {}
	Object_List& operator=(const Object_List& src) {
		_pObjectTypedOwner.reset(src._pObjectTypedOwner->CloneDeep()); return *this;
	}
	// Move constructor/operator
	Object_List(Object_List&& src) : Object(Klass_List), _pObjectTypedOwner(src._pObjectTypedOwner.release()) {}
	Object_List& operator=(Object_List&& src) noexcept {
		_pObjectTypedOwner.reset(src._pObjectTypedOwner.release()); return *this;
	}
protected:
	// Destructor
	~Object_List() = default;
public:
	ObjectTypedOwner& GetObjectTypedOwner() { return *_pObjectTypedOwner; }
	const ObjectTypedOwner& GetObjectTypedOwner() const { return *_pObjectTypedOwner; }
	const ObjectOwner& GetObjectOwner() const { return _pObjectTypedOwner->GetObjectOwner(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return new Object_List(*this); }
	virtual size_t DoCalcHash() const override {
		return GetObjectOwner().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetObjectOwner().IsEqualTo(dynamic_cast<const Object_List*>(pObject)->GetObjectOwner());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetObjectOwner().IsLessThan(dynamic_cast<const Object_List*>(pObject)->GetObjectOwner()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetObjectOwner().ToString(ss);
	}
};

}

#endif
