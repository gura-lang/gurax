//==============================================================================
// TrainOptimizer.h
//==============================================================================
#ifndef GURAX_TRAINOPTIMIZER_H
#define GURAX_TRAINOPTIMIZER_H
#include "Processor.h"
#include "Array.h"

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
protected:
	const char* _name;
public:
	class GURAX_DLLDECLARE Instance : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(Instance);
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("TrainOptimizer::Instance");
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
	TrainOptimizer(const char* name) : _name(name) {}
	// Copy constructor/operator
	TrainOptimizer(const TrainOptimizer& src) = delete;
	TrainOptimizer& operator=(const TrainOptimizer& src) = delete;
	// Move constructor/operator
	TrainOptimizer(TrainOptimizer&& src) noexcept = delete;
	TrainOptimizer& operator=(TrainOptimizer&& src) noexcept = delete;
protected:
	~TrainOptimizer() = default;
public:
	virtual Instance* CreateInstance() const = 0;
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

//------------------------------------------------------------------------------
// TrainOptimizer_None
//-------------------------------------------------------------------------
class TrainOptimizer_None : public TrainOptimizer {
public:
	class InstanceEx : public Instance {
	public:
		InstanceEx() {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	TrainOptimizer_None() : TrainOptimizer("None") {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(); }
};

//------------------------------------------------------------------------------
// TrainOptimizer_AdaGrad
//------------------------------------------------------------------------------
class TrainOptimizer_AdaGrad : public TrainOptimizer {
private:
	Double _learningRate;
	Double _epsilon;
	RefPtr<Array> _pArrayH;
	RefPtr<Array> _pArrayWork;
public:
	class InstanceEx : public Instance {
	private:
		Double _learningRate;
		Double _epsilon;
	public:
		InstanceEx(Double learningRate, Double epsilon) : _learningRate(learningRate), _epsilon(epsilon) {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	TrainOptimizer_AdaGrad(Double learningRate, Double epsilon) : TrainOptimizer("AdaGrad"), _learningRate(learningRate), _epsilon(epsilon) {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(_learningRate, _epsilon); }
};

//------------------------------------------------------------------------------
// TrainOptimizer_Adam
//------------------------------------------------------------------------------
class TrainOptimizer_Adam : public TrainOptimizer {
public:
	class InstanceEx : public Instance {
	public:
		InstanceEx() {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	TrainOptimizer_Adam() : TrainOptimizer("Adam") {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(); }
};

//------------------------------------------------------------------------------
// TrainOptimizer_GradientDescent
//------------------------------------------------------------------------------
class TrainOptimizer_GradientDescent : public TrainOptimizer {
public:
	class InstanceEx : public Instance {
	private:
		Double _learningRate;
		RefPtr<Array> _pArrayWork;
	public:
		InstanceEx(Double learningRate) : _learningRate(learningRate) {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
private:
	Double _learningRate;
public:
	TrainOptimizer_GradientDescent(Double learningRate) : TrainOptimizer("GradientDescent"), _learningRate(learningRate) {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(_learningRate); }
};

//------------------------------------------------------------------------------
// TrainOptimizer_Momentum
//------------------------------------------------------------------------------
class TrainOptimizer_Momentum : public TrainOptimizer {
public:
	class InstanceEx : public Instance {
	private:
		Double _learningRate;
		Double _momentum;
		RefPtr<Array> _pArrayVel;
		RefPtr<Array> _pArrayWork;
	public:
		InstanceEx(Double learningRate, Double momentum) : _learningRate(learningRate), _momentum(momentum) {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
private:
	Double _learningRate;
	Double _momentum;
public:
	TrainOptimizer_Momentum(Double learningRate, Double momentum) : TrainOptimizer("Momentum"), _learningRate(learningRate), _momentum(momentum) {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(_learningRate, _momentum); }
};

//------------------------------------------------------------------------------
// TrainOptimizer_Nesterov
//------------------------------------------------------------------------------
class TrainOptimizer_Nesterov : public TrainOptimizer {
public:
	class InstanceEx : public Instance {
	public:
		InstanceEx() {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	TrainOptimizer_Nesterov() : TrainOptimizer("Nesterov") {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(); }
};

//------------------------------------------------------------------------------
// TrainOptimizer_RMSprop
//------------------------------------------------------------------------------
class TrainOptimizer_RMSprop : public TrainOptimizer {
public:
	class InstanceEx : public Instance {
	public:
		InstanceEx() {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	TrainOptimizer_RMSprop() : TrainOptimizer("RMSprop") {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(); }
};

}

#endif
