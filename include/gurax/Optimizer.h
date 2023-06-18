//==============================================================================
// Optimizer.h
//==============================================================================
#ifndef GURAX_OPTIMIZER_H
#define GURAX_OPTIMIZER_H
#include "Referable.h"
#include "Symbols.h"
#include "Memory.h"
#include "Processor.h"
#include "Array.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Optimizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Optimizer : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Optimizer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Optimizer");
protected:
	const char* _name;
public:
	class GURAX_DLLDECLARE Instance : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(Instance);
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("Optimizer::Instance");
	public:
		// Constructor
		Instance() {}
		// Copy constructor/operator
		Instance(const Instance& src) = delete;
		Instance& operator=(const Instance& src) = delete;
		// Move constructor/operator
		Instance(Instance&& src) noexcept = delete;
		Instance& operator=(Instance&& src) noexcept = delete;
	protected:
		~Instance() = default;
	public:
		virtual void Reset() {}
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) = 0;
	};
public:
	// Constructor
	Optimizer(const char* name) : _name(name) {}
	// Copy constructor/operator
	Optimizer(const Optimizer& src) = delete;
	Optimizer& operator=(const Optimizer& src) = delete;
	// Move constructor/operator
	Optimizer(Optimizer&& src) noexcept = delete;
	Optimizer& operator=(Optimizer&& src) noexcept = delete;
protected:
	~Optimizer() = default;
public:
	const char* GetName() const { return _name; }
	virtual Instance* CreateInstance() const = 0;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Optimizer& other) const { return this == &other; }
	bool IsEqualTo(const Optimizer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Optimizer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// OptimizerList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE OptimizerList : public ListBase<Optimizer*> {
};

//------------------------------------------------------------------------------
// OptimizerOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE OptimizerOwner : public OptimizerList {
public:
	~OptimizerOwner() { Clear(); }
	void Clear();
};

//------------------------------------------------------------------------------
// Optimizer_None
//-------------------------------------------------------------------------
class Optimizer_None : public Optimizer {
public:
	class InstanceEx : public Instance {
	public:
		InstanceEx() {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	Optimizer_None() : Optimizer("None") {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(); }
};

}

#endif
