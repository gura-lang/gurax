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
