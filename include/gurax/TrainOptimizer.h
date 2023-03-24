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
	virtual void Reset() {}
	virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) = 0;
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

#if 0
//------------------------------------------------------------------------------
// TrainOptimizer_AdaGrad
//------------------------------------------------------------------------------
class TrainOptimizer_AdaGrad : public TrainOptimizer {
private:
	Double _learningRate;
	Double _epsilon;
public:
	class InstanceEx : public Instance {
	private:
		Double _learningRate;
		Double _epsilon;
		AutoPtr<Array> _pArrayH;
		AutoPtr<Array> _pArrayWork;
	public:
		inline InstanceEx(Double learningRate, Double epsilon) :
							_learningRate(learningRate), _epsilon(epsilon) {}
		virtual void Reset(Environment &env);
		virtual bool Update(Signal &sig, AutoPtr<Array> &pArray, const Array *pArrayGrad);
	};
public:
	inline TrainOptimizer_AdaGrad(Double learningRate, Double epsilon) : TrainOptimizer("adagrad"),
							_learningRate(learningRate), _epsilon(epsilon) {}
	virtual Instance *CreateInstance() const;
};

//------------------------------------------------------------------------------
// TrainOptimizer_Adam
//------------------------------------------------------------------------------
class TrainOptimizer_Adam : public TrainOptimizer {
public:
	class InstanceEx : public Instance {
	public:
		inline InstanceEx() {}
		virtual void Reset(Environment &env);
		virtual bool Update(Signal &sig, AutoPtr<Array> &pArray, const Array *pArrayGrad);
	};
public:
	inline TrainOptimizer_Adam() : TrainOptimizer("adam") {}
	virtual Instance *CreateInstance() const;
};

//------------------------------------------------------------------------------
// TrainOptimizer_GradientDescent
//------------------------------------------------------------------------------
class TrainOptimizer_GradientDescent : public TrainOptimizer {
private:
	Double _learningRate;
public:
	class InstanceEx : public Instance {
	private:
		Double _learningRate;
		AutoPtr<Array> _pArrayWork;
	public:
		inline InstanceEx(Double learningRate) : _learningRate(learningRate) {}
		virtual void Reset(Environment &env);
		virtual bool Update(Signal &sig, AutoPtr<Array> &pArray, const Array *pArrayGrad);
	};
public:
	inline TrainOptimizer_GradientDescent(Double learningRate) :
				TrainOptimizer("gradient_descent"), _learningRate(learningRate) {}
	virtual Instance *CreateInstance() const;
};

//------------------------------------------------------------------------------
// TrainOptimizer_Momentum
//------------------------------------------------------------------------------
class TrainOptimizer_Momentum : public TrainOptimizer {
private:
	Double _learningRate;
	Double _momentum;
public:
	class InstanceEx : public Instance {
	private:
		Double _learningRate;
		Double _momentum;
		AutoPtr<Array> _pArrayVel;
		AutoPtr<Array> _pArrayWork;
	public:
		inline InstanceEx(Double learningRate, Double momentum) :
						_learningRate(learningRate), _momentum(momentum) {}
		virtual void Reset(Environment &env);
		virtual bool Update(Signal &sig, AutoPtr<Array> &pArray, const Array *pArrayGrad);
	};
public:
	inline TrainOptimizer_Momentum(Double learningRate, Double momentum) : TrainOptimizer("momentum"),
						_learningRate(learningRate), _momentum(momentum) {}
	virtual Instance *CreateInstance() const;
};

//------------------------------------------------------------------------------
// TrainOptimizer_Nesterov
//------------------------------------------------------------------------------
class TrainOptimizer_Nesterov : public TrainOptimizer {
public:
	class InstanceEx : public Instance {
	public:
		inline InstanceEx() {}
		virtual void Reset(Environment &env);
		virtual bool Update(Signal &sig, AutoPtr<Array> &pArray, const Array *pArrayGrad);
	};
public:
	inline TrainOptimizer_Nesterov() : TrainOptimizer("nesterov") {}
	virtual Instance *CreateInstance() const;
};

//------------------------------------------------------------------------------
// TrainOptimizer_None
//-------------------------------------------------------------------------
class TrainOptimizer_None : public TrainOptimizer {
public:
	class InstanceEx : public Instance {
	public:
		inline InstanceEx() {}
		virtual bool Update(Signal &sig, AutoPtr<Array> &pArray, const Array *pArrayGrad);
	};
public:
	inline TrainOptimizer_None() : TrainOptimizer("none") {}
	virtual Instance *CreateInstance() const;
};

//------------------------------------------------------------------------------
// TrainOptimizer_RMSprop
//------------------------------------------------------------------------------
class TrainOptimizer_RMSprop : public TrainOptimizer {
public:
	class InstanceEx : public Instance {
	public:
		inline InstanceEx() {}
		virtual void Reset(Environment &env);
		virtual bool Update(Signal &sig, AutoPtr<Array> &pArray, const Array *pArrayGrad);
	};
public:
	inline TrainOptimizer_RMSprop() : TrainOptimizer("rmsprop") {}
	virtual Instance *CreateInstance() const;
};
#endif

}

#endif
