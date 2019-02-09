//==============================================================================
// Object_Iterator.h
//==============================================================================
#ifndef GURAX_OBJECT_ITERATOR_H
#define GURAX_OBJECT_ITERATOR_H
#include "Object_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Iterator
//------------------------------------------------------------------------------
class VType_Iterator : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Iterator VTYPE_Iterator;

//------------------------------------------------------------------------------
// Object_Iterator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Iterator : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Iterator);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Iterator");
private:
	RefPtr<Iterator> _pIterator;
public:
	// Constructor
	Object_Iterator() = delete;
	explicit Object_Iterator(Iterator *pIterator, VType& vtype = VTYPE_Iterator) :
		Object_Object(vtype), _pIterator(pIterator) {}
	// Copy constructor/operator
	Object_Iterator(const Object_Iterator& src) :
		Object_Object(src), _pIterator(src._pIterator->Reference()) {}
		Object_Iterator& operator=(const Object_Iterator& src) = delete;
	// Move constructor/operator
	Object_Iterator(Object_Iterator&& src) = delete;
	Object_Iterator& operator=(Object_Iterator&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Iterator() = default;
public:
	Iterator& GetIterator() { return *_pIterator; }
	const Iterator& GetIterator() const { return *_pIterator; }
public:
	// Virtual iterators of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetIterator().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetIterator().IsEqualTo(dynamic_cast<const Object_Iterator*>(pObject)->GetIterator());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetIterator().IsLessThan(dynamic_cast<const Object_Iterator*>(pObject)->GetIterator()) :
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetIterator().ToString(ss);
	}
};

}

#endif
