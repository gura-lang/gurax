//==============================================================================
// Argument.h
//==============================================================================
#ifndef GURAX_ARGUMENT_H
#define GURAX_ARGUMENT_H
#include "Attribute.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
class Argument : public Referable {
public:
	Gurax_DeclareReferable(Argument);
public:
	// Constructor
	Argument() {}
	// Copy constructor/operator
	Argument(const Argument& src) = delete;
	Argument& operator=(const Argument& src) = delete;
	// Move constructor/operator
	Argument(Argument&& src) = delete;
	Argument& operator=(Argument&& src) noexcept = delete;
protected:
	~Argument() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Argument& attr) const { return this == &attr; }
	bool IsEqualTo(const Argument& attr) const { return IsIdentical(attr); }
	bool IsLessThan(const Argument& attr) const { return this < &attr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
