//==============================================================================
// Object_argument.h
//==============================================================================
#ifndef GURAX_OBJECT_ARGUMENT_H
#define GURAX_OBJECT_ARGUMENT_H
#include "Object.h"
#include "Argument.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_argument
//------------------------------------------------------------------------------
class KlassT_argument : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_argument Klass_argument;

//------------------------------------------------------------------------------
// Object_argument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_argument : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_argument);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_argument");
private:
	std::unique_ptr<Argument> _pArgument;
public:
	// Constructor
	Object_argument() = delete;
	explicit Object_argument(Argument *pArgument) : Object(Klass_argument), _pArgument(pArgument) {}
	// Copy constructor/operator
	Object_argument(const Object_argument& src) : Object(Klass_argument), _pArgument(src._pArgument->Clone()) {}
	Object_argument& operator=(const Object_argument& src) {
		_pArgument.reset(src._pArgument->Clone()); return *this;
	}
	// Move constructor/operator
	Object_argument(Object_argument&& src) : Object(Klass_argument), _pArgument(src._pArgument.release()) {}
	Object_argument& operator=(Object_argument&& src) noexcept {
		_pArgument.reset(src._pArgument.release()); return *this;
	}
protected:
	// Destructor
	~Object_argument() = default;
public:
	Argument& GetArgument() { return *_pArgument; }
	const Argument& GetArgument() const { return *_pArgument; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetArgument().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetArgument().IsEqualTo(dynamic_cast<const Object_argument*>(pObject)->GetArgument());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetArgument().IsLessThan(dynamic_cast<const Object_argument*>(pObject)->GetArgument()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetArgument().ToString(ss);
	}
};

}

#endif
