//==============================================================================
// Argument.h
//==============================================================================
#ifndef GURAX_ARGUMENT_H
#define GURAX_ARGUMENT_H
#include "Referable.h"
#include "Attribute.h"
#include "Value.h"
#include "DeclCaller.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
class Argument : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Argument);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Argument");
private:
	RefPtr<DeclCaller> _pDeclCaller;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	Argument(DeclCaller* pDeclCaller, Attribute* pAttr) : _pDeclCaller(pDeclCaller), _pAttr(pAttr) {}
	// Copy constructor/operator
	Argument(const Argument& src);
	Argument& operator=(const Argument& src) = delete;
	// Move constructor/operator
	Argument(Argument&& src) = delete;
	Argument& operator=(Argument&& src) noexcept = delete;
protected:
	~Argument() = default;
public:
	const Attribute& GetAttr() const { return *_pAttr; }
	Argument* Clone() const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Argument& attr) const { return this == &attr; }
	bool IsEqualTo(const Argument& attr) const { return IsIdentical(attr); }
	bool IsLessThan(const Argument& attr) const { return this < &attr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
