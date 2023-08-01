//==============================================================================
// Optimizers.h
//==============================================================================
#ifndef GURAX_MODULE_ML_OPTIMIZERS_H
#define GURAX_MODULE_ML_OPTIMIZERS_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Optimizer_None
//-------------------------------------------------------------------------
class Optimizer_None : public Optimizer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Optimizer_None);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Optimizer_None");
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
public:
	// Referable declaration
	Gurax_DeclareReferable(Optimizer_AdaGrad);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Optimizer_AdaGrad");
public:
	class InstanceEx : public Instance {
	private:
		RefPtr<Optimizer_AdaGrad> _pOptimizer;
		RefPtr<Array> _pArrayH;
		RefPtr<Array> _pArrayWork;
	public:
		InstanceEx(Optimizer_AdaGrad* pOptimizer) : _pOptimizer(pOptimizer) {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
private:
	Double _learningRate;
	Double _epsilon;
public:
	Optimizer_AdaGrad(Double learningRate, Double epsilon) : Optimizer("AdaGrad"), _learningRate(learningRate), _epsilon(epsilon) {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(Reference()); }
public:
	Double GetLearningRate() const { return _learningRate; }
	void SetLearningRate(Double learningRate) { _learningRate = learningRate; }
	Double GetEpsilon() const { return _epsilon; }
	void SetEpsilon(Double epsilon) { _epsilon = epsilon; }
};

//------------------------------------------------------------------------------
// Optimizer_Adam
//------------------------------------------------------------------------------
class Optimizer_Adam : public Optimizer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Optimizer_Adam);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Optimizer_Adam");
public:
	class InstanceEx : public Instance {
	private:
		RefPtr<Optimizer_Adam> _pOptimizer;
	public:
		InstanceEx(Optimizer_Adam* pOptimizer) : _pOptimizer(pOptimizer) {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	Optimizer_Adam() : Optimizer("Adam") {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(Reference()); }
};

//------------------------------------------------------------------------------
// Optimizer_GradientDescent
//------------------------------------------------------------------------------
class Optimizer_GradientDescent : public Optimizer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Optimizer_GradientDescent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Optimizer_GradientDescent");
public:
	class InstanceEx : public Instance {
	private:
		RefPtr<Optimizer_GradientDescent> _pOptimizer;
		RefPtr<Array> _pArrayWork;
	public:
		InstanceEx(Optimizer_GradientDescent* pOptimizer) : _pOptimizer(pOptimizer) {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
private:
	Double _learningRate;
public:
	Optimizer_GradientDescent(Double learningRate) : Optimizer("GradientDescent"), _learningRate(learningRate) {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(Reference()); }
public:
	Double GetLearningRate() const { return _learningRate; }
	void SetLearningRate(Double learningRate) { _learningRate = learningRate; }
public:
	virtual void GatherMemberSymbol(SymbolList& symbolList) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr);
	virtual bool DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr);
};

//------------------------------------------------------------------------------
// Optimizer_Momentum
//------------------------------------------------------------------------------
class Optimizer_Momentum : public Optimizer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Optimizer_Momentum);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Optimizer_Momentum");
public:
	class InstanceEx : public Instance {
	private:
		RefPtr<Optimizer_Momentum> _pOptimizer;
		RefPtr<Array> _pArrayVel;
		RefPtr<Array> _pArrayWork;
	public:
		InstanceEx(Optimizer_Momentum* pOptimizer) : _pOptimizer(pOptimizer) {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
private:
	Double _learningRate;
	Double _momentum;
public:
	Optimizer_Momentum(Double learningRate, Double momentum) : Optimizer("Momentum"), _learningRate(learningRate), _momentum(momentum) {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(Reference()); }
public:
	Double GetLearningRate() const { return _learningRate; }
	void SetLearningRate(Double learningRate) { _learningRate = learningRate; }
	Double GetMomentum() const { return _momentum; }
	void SetMomentum(Double momentum) { _momentum = momentum; }
};

//------------------------------------------------------------------------------
// Optimizer_Nesterov
//------------------------------------------------------------------------------
class Optimizer_Nesterov : public Optimizer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Optimizer_Nesterov);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Optimizer_Nesterov");
public:
	class InstanceEx : public Instance {
	private:
		RefPtr<Optimizer_Nesterov> _pOptimizer;
	public:
		InstanceEx(Optimizer_Nesterov* pOptimizer) : _pOptimizer(pOptimizer) {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	Optimizer_Nesterov() : Optimizer("Nesterov") {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(Reference()); }
};

//------------------------------------------------------------------------------
// Optimizer_RMSprop
//------------------------------------------------------------------------------
class Optimizer_RMSprop : public Optimizer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Optimizer_RMSprop);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Optimizer_RMSprop");
public:
	class InstanceEx : public Instance {
	private:
		RefPtr<Optimizer_RMSprop> _pOptimizer;
	public:
		InstanceEx(Optimizer_RMSprop* pOptimizer) : _pOptimizer(pOptimizer) {}
		virtual void Reset() override;
		virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
	};
public:
	Optimizer_RMSprop() : Optimizer("RMSprop") {}
	virtual Instance* CreateInstance() const override { return new InstanceEx(Reference()); }
};

Gurax_EndModuleScope(ml)

#endif
