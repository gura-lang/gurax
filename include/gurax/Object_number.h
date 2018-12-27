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
public:
	class KlassEx : public Gurax::Klass {
	public:
		// Constructor
		KlassEx() : Klass(&Object::klass, "number") {}
	public:
		virtual void DoPrepare() override;
	};
public:
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
	Double GetDouble() const { return _num; }
	virtual Object* Clone() const override { return Reference(); }
	virtual String ToString() const override { return std::to_string(_num); }
	virtual String GenSource() const override { return ToString(); }
};

}

#endif
