//==============================================================================
// Argument.h
//==============================================================================
#ifndef GURAX_ARGUMENT_H
#define GURAX_ARGUMENT_H
#include "Attribute.h"
#include "Value.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
class Argument {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Argument");
private:
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	Argument(Attribute* pAttr) : _pAttr(pAttr) {}
	// Copy constructor/operator
	Argument(const Argument& src);
	Argument& operator=(const Argument& src) = delete;
	// Move constructor/operator
	Argument(Argument&& src) = delete;
	Argument& operator=(Argument&& src) noexcept = delete;
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
