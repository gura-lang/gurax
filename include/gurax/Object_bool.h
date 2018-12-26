//==============================================================================
// Object_bool.h
//==============================================================================
#ifndef GURAX_OBJECT_BOOL_H
#define GURAX_OBJECT_BOOL_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_bool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_bool : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_bool);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("bool");
public:
	class KlassEx : public Klass {
	public:
		// Constructor
		KlassEx() : Klass(&Object::klass, "bool") {}
		// Copy constructor/operator
		KlassEx(const KlassEx& src) = delete;
		KlassEx& operator=(const KlassEx& src) = delete;
		// Move constructor/operator
		KlassEx(KlassEx&& src) = delete;
		KlassEx& operator=(KlassEx&& src) noexcept = delete;
		// Destructor
		~KlassEx() = default;
	};
public:
	static const KlassEx klass;
private:
	bool _flag;
public:
	// Constructor
	explicit Object_bool(bool flag) : Object(klass), _flag(flag) {}
	// Copy constructor/operator
	Object_bool(const Object_bool& src) : Object(klass), _flag(src._flag) {}
	Object_bool& operator=(const Object_bool& src) { _flag = src._flag; return *this; }
	// Move constructor/operator
	Object_bool(Object_bool&& src) : Object(klass), _flag(src._flag) {}
	Object_bool& operator=(Object_bool&& src) noexcept { _flag = src._flag; return *this; }
protected:
	// Destructor
	~Object_bool() = default;
public:
	bool GetBool() const { return _flag; }
	virtual Object* Clone() const override { return Reference(); }
	virtual String ToString() const override { return _flag? "true" : "false"; }
	virtual String GenSource() const override { return ToString(); }
};

}

#endif
