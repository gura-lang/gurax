//==============================================================================
// Gear.h
//==============================================================================
#ifndef GURAX_GEAR_H
#define GURAX_GEAR_H
#include "Optimizer.h"
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
private:
	bool _hasVulnerableParamFlag;
public:
	// Constructor
	Gear(bool hasVulnerableParamFlag) : _hasVulnerableParamFlag(hasVulnerableParamFlag) {}
	// Copy constructor/operator
	Gear(const Gear& src) = delete;
	Gear& operator=(const Gear& src) = delete;
	// Move constructor/operator
	Gear(Gear&& src) noexcept = delete;
	Gear& operator=(Gear&& src) noexcept = delete;
protected:
	~Gear() = default;
public:
	bool HasVulnerableParam() const { return _hasVulnerableParamFlag; }
public:
	virtual void SetOptimizer(const Optimizer& optimizer) {}
	virtual const char* GetName() const = 0; 
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, bool trainingFlag) = 0;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag) = 0;
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
