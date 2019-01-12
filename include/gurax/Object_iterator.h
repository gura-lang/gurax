//==============================================================================
// Object_iterator.h
//==============================================================================
#ifndef GURAX_OBJECT_ITERATOR_H
#define GURAX_OBJECT_ITERATOR_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_iterator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_iterator : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_iterator);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_iterator");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	RefPtr<Iterator> _pIterator;
public:
	// Constructor
	Object_iterator() = delete;
	explicit Object_iterator(Iterator *pIterator) : Object(klass), _pIterator(pIterator) {}
	// Copy constructor/operator
	Object_iterator(const Object_iterator& src) : Object(klass), _pIterator(src._pIterator->Reference()) {}
	Object_iterator& operator=(const Object_iterator& src) { _pIterator.reset(src._pIterator->Reference()); return *this; }
	// Move constructor/operator
	Object_iterator(Object_iterator&& src) : Object(klass), _pIterator(src._pIterator.release()) {}
	Object_iterator& operator=(Object_iterator&& src) noexcept { _pIterator.reset(src._pIterator.release()); return *this; }
protected:
	// Destructor
	~Object_iterator() = default;
public:
	const Iterator* GetIterator() const { return _pIterator.get(); }
public:
	// Virtual iterators of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return reinterpret_cast<size_t>(this); }
	virtual bool IsEqualTo(const Object* pObject) const override { return IsIdentical(pObject); }
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetIterator()->IsLessThan(dynamic_cast<const Object_iterator*>(pObject)->GetIterator()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle&) const override { return _pIterator->ToString(); }
};

}

#endif
