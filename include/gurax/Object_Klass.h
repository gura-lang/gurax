//==============================================================================
// Object_Klass.h
//==============================================================================
#ifndef GURAX_OBJECT_KLASS_H
#define GURAX_OBJECT_KLASS_H
#include "Object_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Klass
//------------------------------------------------------------------------------
class KlassT_Klass : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Klass Klass_Klass;

//------------------------------------------------------------------------------
// Object_Klass
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Klass : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Klass);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Klass");
private:
	Klass* _pKlassThis;
public:
	// Constructor
	Object_Klass() = delete;
	explicit Object_Klass(Klass& klassThis, Klass& klass = Klass_Klass) :
		Object_Object(klass), _pKlassThis(&klassThis) {}
	// Copy constructor/operator
	Object_Klass(const Object_Klass& src) :
		Object_Object(src), _pKlassThis(src._pKlassThis) {}
	Object_Klass& operator=(const Object_Klass& src) = delete;
	// Move constructor/operator
	Object_Klass(Object_Klass&& src) = delete;
	Object_Klass& operator=(Object_Klass&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Klass() = default;
public:
	Klass& GetKlassThis() { return *_pKlassThis; }
	const Klass& GetKlassThis() const { return *_pKlassThis; }
public:
	// Virtual klasss of Object
	virtual Frame* ProvideFrame() override { return &GetKlassThis().GetFrame(); }
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetKlassThis().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetKlassThis().IsEqualTo(dynamic_cast<const Object_Klass*>(pObject)->GetKlassThis());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetKlassThis().IsLessThan(dynamic_cast<const Object_Klass*>(pObject)->GetKlassThis()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetKlassThis().ToString(ss);
	}
};

}

#endif
