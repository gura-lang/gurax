//==============================================================================
// Object.h
//==============================================================================
#ifndef GURAX_OBJECT_H
#define GURAX_OBJECT_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object
//------------------------------------------------------------------------------
class Object : public Referable {
public:
	class TypeInfo {
	public:
		// Default constructor
		TypeInfo() {}
		// Copy constructor/operator
		TypeInfo(const TypeInfo& src) = delete;
		TypeInfo& operator=(const TypeInfo& src) = delete;
		// Move constructor/operator
		TypeInfo(TypeInfo&& src) = delete;
		TypeInfo& operator=(TypeInfo&& src) noexcept = delete;
		// Destructor
		~TypeInfo() = default;
	};
protected:
	const TypeInfo& _typeInfo;
public:
	// Default constructor
	Object() = delete;
	// Copy constructor/operator
	Object(const Object& src) = delete;
	Object& operator=(const Object& src) = delete;
	// Move constructor/operator
	Object(Object&& src) = delete;
	Object& operator=(Object&& src) noexcept = delete;
protected:
	// Destructor
	~Object() = default;
public:
	Gurax_DeclareReferable(Object);
public:
	Object(const TypeInfo& typeInfo) : _typeInfo(typeInfo) {}
	const TypeInfo &GetTypeInfo() const { return _typeInfo; }
};

}

#endif
