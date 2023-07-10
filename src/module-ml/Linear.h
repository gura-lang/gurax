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
	size_t _nRowsIn;
	size_t _nColsIn;
	size_t _nColsOut;
private:
	RefPtr<Array> _pArrayDot;
	RefPtr<Array> _pArrayBias;
	RefPtr<Array> _pArrayInTrans;
	RefPtr<Array> _pArrayDotTrans;
	RefPtr<Optimizer::Instance> _pOptimizerInstDot;
	RefPtr<Optimizer::Instance> _pOptimizerInstBias;
public:
	// Constructor
	Linear(size_t nRowsIn, size_t nColsIn, size_t nColsOut);
	Linear(size_t nRowsIn, size_t nColsIn, size_t nColsOut, Array* pArrayDot, Array* pArrayBias);
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
		_pOptimizerInstDot.reset(optimizer.CreateInstance());
		_pOptimizerInstBias.reset(optimizer.CreateInstance());
	}
	virtual const char* GetName() const override { return "ml.Linear"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, bool trainingFlag) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag) override;
public:
	bool Serialize(Stream& stream) const;
	static Linear* Deserialize(Stream& stream);
public:
	size_t GetNRowsIn() const { return _nRowsIn; }
	size_t GetNColsIn() const { return _nColsIn; }
public:
	//const Array& GetArrayFilter() const { return *_pArrayFilter; }
	//const Array& GetArrayFilterGrad() const { return *_pArrayFilterGrad; }
	//const Array& GetArrayBias() const { return *_pArrayBias; }
	//const Array& GetArrayBiasGrad() const { return *_pArrayBiasGrad; }
	//bool IsValidArrayFilterGrad() const { return !_pArrayFilterGrad.IsNull(); }
	//bool IsValidArrayBiasGrad() const { return !_pArrayBiasGrad.IsNull(); }
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
