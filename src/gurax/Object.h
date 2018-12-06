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
	protected:
		const TypeInfo *_pTypeInfoParent;
	public:
		// Default constructor
		TypeInfo(const TypeInfo* pTypeInfoParent = nullptr) : _pTypeInfoParent(pTypeInfoParent) {}
		// Copy constructor/operator
		TypeInfo(const TypeInfo& src) = delete;
		TypeInfo& operator=(const TypeInfo& src) = delete;
		// Move constructor/operator
		TypeInfo(TypeInfo&& src) = delete;
		TypeInfo& operator=(TypeInfo&& src) noexcept = delete;
		// Destructor
		~TypeInfo() = default;
	};
private:
	static const Object *_pObject_undefined;
	static const Object *_pObject_nil;
protected:
	const TypeInfo& _typeInfo;
public:
	static const TypeInfo typeInfo;
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
	virtual ~Object() = default;
public:
	// Referable accessor
	Gurax_DeclareReferable(Object);
public:
	Object(const TypeInfo& typeInfo) : _typeInfo(typeInfo) {}
	static void Bootup();
	const TypeInfo &GetTypeInfo() const { return _typeInfo; }
	static Object *nil() { return _pObject_nil->Reference(); }
	static Object *undefined() { return _pObject_undefined->Reference(); }
public:
	virtual Object *Clone() const = 0;
};

//------------------------------------------------------------------------------
// ObjectList
//------------------------------------------------------------------------------
class ObjectList : public std::vector<Object *> {
};

//------------------------------------------------------------------------------
// ObjectOwner
//------------------------------------------------------------------------------
class ObjectOwner : public ObjectList, public Referable {
protected:
	~ObjectOwner() { Clear(); }
public:
	// Referable accessor
	Gurax_DeclareReferable(ObjectOwner);
public:
	void Clear();
};

}

#endif
