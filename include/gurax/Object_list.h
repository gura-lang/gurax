//==============================================================================
// Object_list.h
//==============================================================================
#ifndef GURAX_OBJECT_LIST_H
#define GURAX_OBJECT_LIST_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_list
//------------------------------------------------------------------------------
class KlassT_list : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_list Klass_list;

//------------------------------------------------------------------------------
// Object_list
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_list : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_list);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_list");
private:
	RefPtr<ObjectTypedOwner> _pObjectTypedOwner;
public:
	// Constructor
	Object_list() : Object(Klass_list), _pObjectTypedOwner(new ObjectTypedOwner()) {}
	explicit Object_list(ObjectTypedOwner* pObjectTypedOwner) : Object(Klass_list), _pObjectTypedOwner(pObjectTypedOwner) {}
	// Copy constructor/operator
	Object_list(const Object_list& src) : Object(Klass_list), _pObjectTypedOwner(src._pObjectTypedOwner->CloneDeep()) {}
	Object_list& operator=(const Object_list& src) {
		_pObjectTypedOwner.reset(src._pObjectTypedOwner->CloneDeep()); return *this;
	}
	// Move constructor/operator
	Object_list(Object_list&& src) : Object(Klass_list), _pObjectTypedOwner(src._pObjectTypedOwner.release()) {}
	Object_list& operator=(Object_list&& src) noexcept {
		_pObjectTypedOwner.reset(src._pObjectTypedOwner.release()); return *this;
	}
protected:
	// Destructor
	~Object_list() = default;
public:
	ObjectTypedOwner& GetObjectTypedOwner() { return *_pObjectTypedOwner; }
	const ObjectTypedOwner& GetObjectTypedOwner() const { return *_pObjectTypedOwner; }
	const ObjectOwner& GetObjectOwner() const { return _pObjectTypedOwner->GetObjectOwner(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return new Object_list(*this); }
	virtual size_t DoCalcHash() const override {
		return GetObjectOwner().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetObjectOwner().IsEqualTo(dynamic_cast<const Object_list*>(pObject)->GetObjectOwner());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetObjectOwner().IsLessThan(dynamic_cast<const Object_list*>(pObject)->GetObjectOwner()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetObjectOwner().ToString(ss);
	}
};

}

#endif
