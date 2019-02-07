//==============================================================================
// Object_Symbol.h
//==============================================================================
#ifndef GURAX_OBJECT_SYMBOL_H
#define GURAX_OBJECT_SYMBOL_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Symbol
//------------------------------------------------------------------------------
class KlassT_Symbol : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Symbol Klass_Symbol;

//------------------------------------------------------------------------------
// Object_Symbol
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Symbol : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Symbol);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Symbol");
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	explicit Object_Symbol(const Symbol* pSymbol) : Object(Klass_Symbol), _pSymbol(pSymbol) {}
	// Copy constructor/operator
	Object_Symbol(const Object_Symbol& src) : Object(Klass_Symbol), _pSymbol(src._pSymbol) {}
	Object_Symbol& operator=(const Object_Symbol& src) { _pSymbol = src._pSymbol; return *this; }
	// Move constructor/operator
	Object_Symbol(Object_Symbol&& src) : Object(Klass_Symbol), _pSymbol(src._pSymbol) {}
	Object_Symbol& operator=(Object_Symbol&& src) noexcept { _pSymbol = src._pSymbol; return *this; }
protected:
	// Destructor
	~Object_Symbol() = default;
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSymbol()->CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetSymbol()->IsEqualTo(dynamic_cast<const Object_Symbol*>(pObject)->GetSymbol());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetSymbol()->IsLessThan_UniqId(dynamic_cast<const Object_Symbol*>(pObject)->GetSymbol()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return String("`").append(_pSymbol->GetName());
	}
};

}

#endif
