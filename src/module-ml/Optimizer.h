//==============================================================================
// Optimizer.h
//==============================================================================
#ifndef GURAX_MODULE_ML_OPTIMIZER_H
#define GURAX_MODULE_ML_OPTIMIZER_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

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

//------------------------------------------------------------------------------
// Optimizer_AdaGrad
//------------------------------------------------------------------------------
class Optimizer_AdaGrad : public Optimizer {
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
	Optimizer_AdaGrad(Double learningRate, Double epsilon) : Optimizer("AdaGrad"), _learningRate(learningRate), _epsilon(epsilon) {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(_learningRate, _epsilon); }
};

//------------------------------------------------------------------------------
// Optimizer_Adam
//------------------------------------------------------------------------------
class Optimizer_Adam : public Optimizer {
public:
	class InstanceEx : public Instance {
	public:
		InstanceEx() {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	Optimizer_Adam() : Optimizer("Adam") {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(); }
};

//------------------------------------------------------------------------------
// Optimizer_GradientDescent
//------------------------------------------------------------------------------
class Optimizer_GradientDescent : public Optimizer {
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
	Optimizer_GradientDescent(Double learningRate) : Optimizer("GradientDescent"), _learningRate(learningRate) {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(_learningRate); }
};

//------------------------------------------------------------------------------
// Optimizer_Momentum
//------------------------------------------------------------------------------
class Optimizer_Momentum : public Optimizer {
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
	Optimizer_Momentum(Double learningRate, Double momentum) : Optimizer("Momentum"), _learningRate(learningRate), _momentum(momentum) {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(_learningRate, _momentum); }
};

//------------------------------------------------------------------------------
// Optimizer_Nesterov
//------------------------------------------------------------------------------
class Optimizer_Nesterov : public Optimizer {
public:
	class InstanceEx : public Instance {
	public:
		InstanceEx() {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	Optimizer_Nesterov() : Optimizer("Nesterov") {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(); }
};

//------------------------------------------------------------------------------
// Optimizer_RMSprop
//------------------------------------------------------------------------------
class Optimizer_RMSprop : public Optimizer {
public:
	class InstanceEx : public Instance {
	public:
		InstanceEx() {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	Optimizer_RMSprop() : Optimizer("RMSprop") {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(); }
};

Gurax_EndModuleScope(ml)

#endif
