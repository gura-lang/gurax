//==============================================================================
// Argument.h
//==============================================================================
#ifndef GURAX_ARGUMENT_H
#define GURAX_ARGUMENT_H
#include "ArgSlot.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Argument : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Argument);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Argument");
public:
private:
	RefPtr<DeclCaller> _pDeclCaller;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	Argument(DeclCaller* pDeclCaller, Attribute* pAttr);
	// Copy constructor/operator
	Argument(const Argument& src) = delete;
	Argument& operator=(const Argument& src) = delete;
	// Move constructor/operator
	Argument(Argument&& src) = delete;
	Argument& operator=(Argument&& src) noexcept = delete;
protected:
	~Argument() = default;
public:
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Argument& attr) const { return this == &attr; }
	bool IsEqualTo(const Argument& attr) const { return IsIdentical(attr); }
	bool IsLessThan(const Argument& attr) const { return this < &attr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
