//==============================================================================
// Conv2d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CONV2D_H
#define GURAX_MODULE_ML_CONV2D_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv2d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Conv2d : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Conv2d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.Conv2d");
private:
	RefPtr<Array> _pArrayFilter;
	RefPtr<Array> _pArrayFilterGrad;
	size_t _strides;
	size_t _padding;
	RefPtr<Array> _pArrayFwdInSaved;
	RefPtr<Array> _pArrayFwdOutSaved;
	RefPtr<Array> _pArrayFwd1, _pArrayFwd2, _pArrayFwd3, _pArrayFwd4, _pArrayFwd5;
	RefPtr<Array> _pArrayBwd1, _pArrayBwd2, _pArrayBwd3, _pArrayBwd4, _pArrayBwd5, _pArrayBwd6;
	RefPtr<Optimizer::Instance> _pOptimizerInstance;
public:
	// Constructor
	Conv2d(Array* pArrayFilter, size_t strides, size_t padding);
	// Copy constructor/operator
	Conv2d(const Conv2d& src) = delete;
	Conv2d& operator=(const Conv2d& src) = delete;
	// Move constructor/operator
	Conv2d(Conv2d&& src) noexcept = delete;
	Conv2d& operator=(Conv2d&& src) noexcept = delete;
protected:
	~Conv2d() = default;
public:
	static void Initialize();
	static bool ValidateArrayFilter(const Array& arrayFilter);
public:
	virtual void SetOptimizer(const Optimizer& optimizer) override { _pOptimizerInstance.reset(optimizer.CreateInstance()); }
	virtual const char* GetName() const override { return "ml.Conv2d"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, bool bwdPropagationFlag, const Array& array) override;
public:
	const Array& GetArrayFilter() const { return *_pArrayFilter; }
	const Array& GetArrayFilterGrad() const { return *_pArrayFilterGrad; }
	bool IsValidArrayFilterGrad() const { return !_pArrayFilterGrad.IsNull(); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Conv2d& other) const { return this == &other; }
	bool IsEqualTo(const Conv2d& other) const { return IsIdentical(other); }
	bool IsLessThan(const Conv2d& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Conv2dList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Conv2dList : public ListBase<Conv2d*> {
};

//------------------------------------------------------------------------------
// Conv2dOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Conv2dOwner : public Conv2dList {
public:
	~Conv2dOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
