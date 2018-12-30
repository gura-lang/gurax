//==============================================================================
// Object_number.h
//==============================================================================
#ifndef GURAX_OBJECT_NUMBER_H
#define GURAX_OBJECT_NUMBER_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_number
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_number : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_number);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("number");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	Double _num;
public:
	// Constructor
	explicit Object_number(Double num = 0.) : Object(klass), _num(num) {}
	// Copy constructor/operator
	Object_number(const Object_number& src) : Object(klass), _num(src._num) {}
	Object_number& operator=(const Object_number& src) { _num = src._num; return *this; }
	// Move constructor/operator
	Object_number(Object_number&& src) : Object(klass), _num(src._num) {}
	Object_number& operator=(Object_number&& src) noexcept { _num = src._num; return *this; }
protected:
	// Destructor
	~Object_number() = default;
public:
	template<typename T> T Get() const { return static_cast<T>(_num); }
	Double GetDouble() const { return _num; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return Get<size_t>(); }
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) && GetDouble() == dynamic_cast<const Object_number*>(pObject)->GetDouble();
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetDouble() < dynamic_cast<const Object_number*>(pObject)->GetDouble() :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle&) const override { return std::to_string(_num); }
};

}

#endif
