//==============================================================================
// Object_klass.h
//==============================================================================
#ifndef GURAX_OBJECT_KLASS_H
#define GURAX_OBJECT_KLASS_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_klass
//------------------------------------------------------------------------------
class KlassT_klass : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_klass Klass_klass;

//------------------------------------------------------------------------------
// Object_klass
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_klass : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_klass);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_klass");
private:
	Klass* _pKlassThis;
public:
	// Constructor
	Object_klass() = delete;
	explicit Object_klass(Klass& klassThis) : Object(Klass_klass), _pKlassThis(&klassThis) {}
	// Copy constructor/operator
	Object_klass(const Object_klass& src) : Object(Klass_klass), _pKlassThis(src._pKlassThis) {}
	Object_klass& operator=(const Object_klass& src) { _pKlassThis = src._pKlassThis; return *this; }
	// Move constructor/operator
	Object_klass(Object_klass&& src) : Object(Klass_klass), _pKlassThis(src._pKlassThis) {}
	Object_klass& operator=(Object_klass&& src) noexcept { _pKlassThis = src._pKlassThis; return *this; }
protected:
	// Destructor
	~Object_klass() = default;
public:
	Klass& GetKlassThis() { return *_pKlassThis; }
	const Klass& GetKlassThis() const { return *_pKlassThis; }
public:
	// Virtual klasss of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetKlassThis().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetKlassThis().IsEqualTo(dynamic_cast<const Object_klass*>(pObject)->GetKlassThis());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetKlassThis().IsLessThan(dynamic_cast<const Object_klass*>(pObject)->GetKlassThis()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetKlassThis().ToString(ss);
	}
};

}

#endif
