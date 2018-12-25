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
public:
	class TypeInfoEx : public TypeInfo {
	public:
		// Constructor
		TypeInfoEx() : TypeInfo(&Object::typeInfo, "number") {}
		// Copy constructor/operator
		TypeInfoEx(const TypeInfoEx& src) = delete;
		TypeInfoEx& operator=(const TypeInfoEx& src) = delete;
		// Move constructor/operator
		TypeInfoEx(TypeInfoEx&& src) = delete;
		TypeInfoEx& operator=(TypeInfoEx&& src) noexcept = delete;
		// Destructor
		~TypeInfoEx() = default;
	public:
		virtual Object* Clone(const Object* pObj) const override {
			return static_cast<const Object_number*>(pObj)->Reference();
		}
	};
public:
	static const TypeInfoEx typeInfo;
private:
	Double _num;
public:
	// Constructor
	explicit Object_number(Double num = 0.) : Object(typeInfo), _num(num) {}
	// Copy constructor/operator
	Object_number(const Object_number& src) : Object(typeInfo), _num(src._num) {}
	Object_number& operator=(const Object_number& src) { _num = src._num; return *this; }
	// Move constructor/operator
	Object_number(Object_number&& src) : Object(typeInfo), _num(src._num) {}
	Object_number& operator=(Object_number&& src) noexcept { _num = src._num; return *this; }
protected:
	// Destructor
	~Object_number() = default;
public:
	Double GetDouble() const { return _num; }
};

}

#endif
