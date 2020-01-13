//==============================================================================
// Stat.h
//==============================================================================
#ifndef GURAX_STAT_H
#define GURAX_STAT_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stat : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Stat);
public:
	// Constructor
	Stat() {}
	// Copy constructor/operator
	Stat(const Stat& src) = delete;
	Stat& operator=(const Stat& src) = delete;
	// Move constructor/operator
	Stat(Stat&& src) = delete;
	Stat& operator=(Stat&& src) noexcept = delete;
protected:
	~Stat() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Stat& other) const { return this == &other; }
	bool IsEqualTo(const Stat& other) const { return IsIdentical(other); }
	bool IsLessThan(const Stat& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
