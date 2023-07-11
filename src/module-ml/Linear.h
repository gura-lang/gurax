//==============================================================================
// Linear.h
//==============================================================================
#ifndef GURAX_MODULE_ML_LINEAR_H
#define GURAX_MODULE_ML_LINEAR_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Linear
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Linear : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Linear);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.Linear");
private:
	size_t _nColsOut;
private:
	const Array::ElemTypeT& _elemType;
	RefPtr<Array> _pArrayFwdIn;
	RefPtr<Array> _pArrayWeight;
	RefPtr<Array> _pArrayWeightGrad;
	RefPtr<Array> _pArrayBias;
	RefPtr<Array> _pArrayBiasGrad;
	RefPtr<Array> _pArrayFwdInTrans;
	RefPtr<Array> _pArrayWeightTrans;
	RefPtr<Array> _pArrayFwd1;
	RefPtr<Optimizer::Instance> _pOptimizerInstWeight;
	RefPtr<Optimizer::Instance> _pOptimizerInstBias;
public:
	// Constructor
	Linear(size_t nColsOut, const Array::ElemTypeT& elemType);
	Linear(Array* pArrayWeight, Array* pArrayBias);
	// Copy constructor/operator
	Linear(const Linear& src) = delete;
	Linear& operator=(const Linear& src) = delete;
	// Move constructor/operator
	Linear(Linear&& src) noexcept = delete;
	Linear& operator=(Linear&& src) noexcept = delete;
protected:
	~Linear() = default;
public:
	static void Initialize();
public:
	virtual void SetOptimizer(const Optimizer& optimizer) override {
		_pOptimizerInstWeight.reset(optimizer.CreateInstance());
		_pOptimizerInstBias.reset(optimizer.CreateInstance());
	}
	virtual const char* GetName() const override { return "ml.Linear"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, bool trainingFlag) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag) override;
public:
	bool Serialize(Stream& stream) const;
	static Linear* Deserialize(Stream& stream);
public:
	size_t GetNColsOut() const { return _nColsOut; }
public:
	const Array& GetArrayWeight() const { return *_pArrayWeight; }
	const Array& GetArrayWeightGrad() const { return *_pArrayWeightGrad; }
	const Array& GetArrayBias() const { return *_pArrayBias; }
	const Array& GetArrayBiasGrad() const { return *_pArrayBiasGrad; }
	bool HasArrayWeight() const { return !_pArrayWeight.IsNull(); }
	bool HasArrayWeightGrad() const { return !_pArrayWeightGrad.IsNull(); }
	bool HasArrayBias() const { return !_pArrayBias.IsNull(); }
	bool HasArrayBiasGrad() const { return !_pArrayBiasGrad.IsNull(); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Linear& other) const { return this == &other; }
	bool IsEqualTo(const Linear& other) const { return IsIdentical(other); }
	bool IsLessThan(const Linear& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// LinearList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LinearList : public ListBase<Linear*> {
};

//------------------------------------------------------------------------------
// LinearOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LinearOwner : public LinearList {
public:
	~LinearOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
