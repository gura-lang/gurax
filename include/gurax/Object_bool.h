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
	// Class declaration
	class KlassEx : public Klass {
	public:
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
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
