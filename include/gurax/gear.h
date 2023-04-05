//==============================================================================
// Gear.h
//==============================================================================
#ifndef GURAX_GEAR_H
#define GURAX_GEAR_H
#include "String.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Gear
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Gear : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Gear);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Gear");
public:
	// Constructor
	Gear() {}
	// Copy constructor/operator
	Gear(const Gear& src) = delete;
	Gear& operator=(const Gear& src) = delete;
	// Move constructor/operator
	Gear(Gear&& src) noexcept = delete;
	Gear& operator=(Gear&& src) noexcept = delete;
protected:
	~Gear() = default;
public:
	const char* GetName() { return ""; } 
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Gear& other) const { return this == &other; }
	bool IsEqualTo(const Gear& other) const { return IsIdentical(other); }
	bool IsLessThan(const Gear& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// GearList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE GearList : public ListBase<Gear*> {
};

//------------------------------------------------------------------------------
// GearOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE GearOwner : public GearList {
public:
	~GearOwner() { Clear(); }
	void Clear();
};

}

#endif