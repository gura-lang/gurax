//==============================================================================
// Pointer.h
//==============================================================================
#ifndef GURAX_POINTER_H
#define GURAX_POINTER_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Pointer : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Pointer);
public:
	// Constructor
	Pointer() {}
	// Copy constructor/operator
	Pointer(const Pointer& src) = delete;
	Pointer& operator=(const Pointer& src) = delete;
	// Move constructor/operator
	Pointer(Pointer&& src) = delete;
	Pointer& operator=(Pointer&& src) noexcept = delete;
protected:
	~Pointer() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Pointer& other) const { return this == &other; }
	bool IsEqualTo(const Pointer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Pointer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
