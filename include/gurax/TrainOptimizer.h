//==============================================================================
// TrainOptimizer.h
//==============================================================================
#ifndef GURAX_TRAINOPTIMIZER_H
#define GURAX_TRAINOPTIMIZER_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TrainOptimizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TrainOptimizer : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(TrainOptimizer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("TrainOptimizer");
public:
	// Constructor
	TrainOptimizer() {}
	// Copy constructor/operator
	TrainOptimizer(const TrainOptimizer& src) = delete;
	TrainOptimizer& operator=(const TrainOptimizer& src) = delete;
	// Move constructor/operator
	TrainOptimizer(TrainOptimizer&& src) noexcept = delete;
	TrainOptimizer& operator=(TrainOptimizer&& src) noexcept = delete;
protected:
	~TrainOptimizer() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const TrainOptimizer& other) const { return this == &other; }
	bool IsEqualTo(const TrainOptimizer& other) const { return IsIdentical(other); }
	bool IsLessThan(const TrainOptimizer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// TrainOptimizerList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TrainOptimizerList : public ListBase<TrainOptimizer*> {
};

//------------------------------------------------------------------------------
// TrainOptimizerOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TrainOptimizerOwner : public TrainOptimizerList {
public:
	~TrainOptimizerOwner() { Clear(); }
	void Clear();
};

}

#endif
