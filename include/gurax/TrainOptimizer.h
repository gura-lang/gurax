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
	class GURAX_DLLDECLARE Factory : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(Factory);
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("TrainOptimizer::Factory");
	protected:
		const char* _name;
	public:
		// Constructor
		Factory(const char* name) : _name(name) {}
		// Copy constructor/operator
		Factory(const Factory& src) = delete;
		Factory& operator=(const Factory& src) = delete;
		// Move constructor/operator
		Factory(Factory&& src) noexcept = delete;
		Factory& operator=(Factory&& src) noexcept = delete;
	protected:
		~Factory() = default;
	public:
		virtual TrainOptimizer* CreateInstance() const = 0;
	};
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

//------------------------------------------------------------------------------
// TrainOptimizer_None
//-------------------------------------------------------------------------
class TrainOptimizer_None : public TrainOptimizer {
public:
	class FactoryEx : public Factory {
	public:
		FactoryEx() : Factory("None") {}
		virtual TrainOptimizer *CreateInstance() const override { return new TrainOptimizer_None(); }
	};
public:
	TrainOptimizer_None() {}
	virtual void Reset() override;
	virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
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
	class FactoryEx : public Factory {
	private:
		Double _learningRate;
		Double _epsilon;
	public:
		FactoryEx(Double learningRate, Double epsilon) : Factory("AdaGrad"),
							_learningRate(learningRate), _epsilon(epsilon) {}
		virtual TrainOptimizer* CreateInstance() const override {
			return new TrainOptimizer_AdaGrad(_learningRate, _epsilon);
		}
	};
public:
	TrainOptimizer_AdaGrad(Double learningRate, Double epsilon) : _learningRate(learningRate), _epsilon(epsilon) {}
	virtual void Reset() override;
	virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
};

//------------------------------------------------------------------------------
// TrainOptimizer_Adam
//------------------------------------------------------------------------------
class TrainOptimizer_Adam : public TrainOptimizer {
public:
	class FactoryEx : public Factory {
	public:
		FactoryEx() : Factory("Adam") {}
		virtual TrainOptimizer *CreateInstance() const override { return new TrainOptimizer_Adam(); }
	};
public:
	TrainOptimizer_Adam() {}
	virtual void Reset() override;
	virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
};

//------------------------------------------------------------------------------
// TrainOptimizer_GradientDescent
//------------------------------------------------------------------------------
class TrainOptimizer_GradientDescent : public TrainOptimizer {
public:
	class FactoryEx : public Factory {
	private:
		Double _learningRate;
	public:
		FactoryEx(Double learningRate) : Factory("GradientDescent"), _learningRate(learningRate) {}
		virtual TrainOptimizer *CreateInstance() const override { return new TrainOptimizer_GradientDescent(_learningRate); }
	};
private:
	Double _learningRate;
	RefPtr<Array> _pArrayWork;
public:
	TrainOptimizer_GradientDescent(Double learningRate) : _learningRate(learningRate) {}
	virtual void Reset() override;
	virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
};

//------------------------------------------------------------------------------
// TrainOptimizer_Momentum
//------------------------------------------------------------------------------
class TrainOptimizer_Momentum : public TrainOptimizer {
public:
	class FactoryEx : public Factory {
	private:
		Double _learningRate;
		Double _momentum;
	public:
		FactoryEx(Double learningRate, Double momentum) :
				Factory("Momentum"), _learningRate(learningRate), _momentum(momentum) {}
		virtual TrainOptimizer *CreateInstance() const override { return new TrainOptimizer_Momentum(_learningRate, _momentum); }
	};
private:
	Double _learningRate;
	Double _momentum;
	RefPtr<Array> _pArrayVel;
	RefPtr<Array> _pArrayWork;
public:
	TrainOptimizer_Momentum(Double learningRate, Double momentum) : _learningRate(learningRate), _momentum(momentum) {}
	virtual void Reset() override;
	virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
};

//------------------------------------------------------------------------------
// TrainOptimizer_Nesterov
//------------------------------------------------------------------------------
class TrainOptimizer_Nesterov : public TrainOptimizer {
public:
	class FactoryEx : public Factory {
	public:
		FactoryEx() : Factory("Nesterov") {}
		virtual TrainOptimizer *CreateInstance() const override { return new TrainOptimizer_Nesterov(); }
	};
public:
	TrainOptimizer_Nesterov() {}
	virtual void Reset() override;
	virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
};

//------------------------------------------------------------------------------
// TrainOptimizer_RMSprop
//------------------------------------------------------------------------------
class TrainOptimizer_RMSprop : public TrainOptimizer {
public:
	class FactoryEx : public Factory {
	public:
		FactoryEx() : Factory("RMSprop") {}
		virtual TrainOptimizer *CreateInstance() const override { return new TrainOptimizer_RMSprop(); }
	};
public:
	TrainOptimizer_RMSprop() {}
	virtual void Reset() override;
	virtual bool Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad) override;
};

}

#endif
