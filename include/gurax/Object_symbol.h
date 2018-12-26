//==============================================================================
// Object_symbol.h
//==============================================================================
#ifndef GURAX_OBJECT_SYMBOL_H
#define GURAX_OBJECT_SYMBOL_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_symbol
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_symbol : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_symbol);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("symbol");
public:
	class KlassEx : public Klass {
	public:
		// Constructor
		KlassEx() : Klass(&Object::klass, "symbol") {}
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
	const Symbol* _pSymbol;
public:
	// Constructor
	explicit Object_symbol(const Symbol* pSymbol) : Object(klass), _pSymbol(pSymbol) {}
	// Copy constructor/operator
	Object_symbol(const Object_symbol& src) : Object(klass), _pSymbol(src._pSymbol) {}
	Object_symbol& operator=(const Object_symbol& src) { _pSymbol = src._pSymbol; return *this; }
	// Move constructor/operator
	Object_symbol(Object_symbol&& src) : Object(klass), _pSymbol(src._pSymbol) {}
	Object_symbol& operator=(Object_symbol&& src) noexcept { _pSymbol = src._pSymbol; return *this; }
protected:
	// Destructor
	~Object_symbol() = default;
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	virtual Object* Clone() const override { return Reference(); }
	virtual String ToString() const override { return String("`").append(_pSymbol->GetName()); }
	virtual String GenSource() const override { return ToString(); }
};

}

#endif
