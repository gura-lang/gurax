//==============================================================================
// Object_list.h
//==============================================================================
#ifndef GURAX_OBJECT_LIST_H
#define GURAX_OBJECT_LIST_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_list
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_list : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_list);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_list");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	RefPtr<ObjectOwner> _pObjectOwner;
public:
	// Constructor
	Object_list() : Object(klass), _pObjectOwner(new ObjectOwner()) {}
	explicit Object_list(ObjectOwner* pObjectOwner) : Object(klass), _pObjectOwner(pObjectOwner) {}
	// Copy constructor/operator
	Object_list(const Object_list& src) : Object(klass), _pObjectOwner(src._pObjectOwner->CloneDeep()) {}
	Object_list& operator=(const Object_list& src) {
		_pObjectOwner.reset(src._pObjectOwner->CloneDeep()); return *this;
	}
	// Move constructor/operator
	Object_list(Object_list&& src) : Object(klass), _pObjectOwner(src._pObjectOwner.release()) {}
	Object_list& operator=(Object_list&& src) noexcept {
		_pObjectOwner.reset(src._pObjectOwner.release()); return *this;
	}
protected:
	// Destructor
	~Object_list() = default;
public:
	ObjectOwner& GetObjectOwner() { return *_pObjectOwner; }
	const ObjectOwner& GetObjectOwner() const { return *_pObjectOwner; }
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
