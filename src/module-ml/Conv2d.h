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
	size_t _nFilters;
	size_t _nRowsFilter;
	size_t _nColsFilter;
private:
	size_t _stride;
	size_t _padding;
private:
	RefPtr<Array> _pArrayFilter;
	RefPtr<Array> _pArrayFilterGrad;
	RefPtr<Array> _pArrayBias;
	RefPtr<Array> _pArrayBiasGrad;
	RefPtr<Array> _pArrayFwdInSaved;
	RefPtr<Array> _pArrayFwdOutSaved;
	RefPtr<Array> _pArrayFwd1, _pArrayFwd2, _pArrayFwd3, _pArrayFwd4, _pArrayFwd5, _pArrayFwd6;
	RefPtr<Array> _pArrayBwd1, _pArrayBwd2, _pArrayBwd3, _pArrayBwd4, _pArrayBwd5, _pArrayBwd6;
	RefPtr<Optimizer::Instance> _pOptimizerInstFilter;
	RefPtr<Optimizer::Instance> _pOptimizerInstBias;
public:
	// Constructor
	Conv2d(size_t nFilters, size_t nRowsFilter, size_t nColsFilter, size_t stride, size_t padding);
	Conv2d(Array* pArrayFilter, Array* pArrayBias, size_t stride, size_t padding);
	// Copy constructor/operator
	Conv2d(const Conv2d& src) = delete;
	Conv2d& operator=(const Conv2d& src) = delete;
	// Move constructor/operator
	Conv2d(Conv2d&& src) noexcept = delete;
	Conv2d& operator=(Conv2d&& src) noexcept = delete;
protected:
	~Conv2d() = default;
public:
	static void Bootup();
	static bool ValidateArrayFilter(const Array& arrayFilter);
public:
	size_t GetNFilters() const { return _nFilters; }
	size_t GetNRowsFilter() const { return _nRowsFilter; }
	size_t GetNColsFilter() const { return _nColsFilter; }
	size_t GetStride() const { return _stride; }
	size_t GetPadding() const { return _padding; }
	size_t CalcNRowsOut(size_t nRowsIn) const { return (nRowsIn + 2 * _padding - _nRowsFilter) / _stride + 1; }
	size_t CalcNColsOut(size_t nColsIn) const { return (nColsIn + 2 * _padding - _nColsFilter) / _stride + 1; }
	virtual void SetOptimizer(const Optimizer& optimizer) override {
		_pOptimizerInstFilter.reset(optimizer.CreateInstance());
		_pOptimizerInstBias.reset(optimizer.CreateInstance());
	}
	virtual const char* GetName() const override { return "ml.Conv2d"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, const Controller& controller) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag) override;
public:
	bool Serialize(Stream& stream) const;
	static Conv2d* Deserialize(Stream& stream);
public:
	const Array& GetArrayFilter() const { return *_pArrayFilter; }
	const Array& GetArrayFilterGrad() const { return *_pArrayFilterGrad; }
	const Array& GetArrayBias() const { return *_pArrayBias; }
	const Array& GetArrayBiasGrad() const { return *_pArrayBiasGrad; }
	bool HasArrayFilter() const { return !_pArrayFilter.IsNull(); }
	bool HasArrayBias() const { return !_pArrayBias.IsNull(); }
	bool HasArrayFilterGrad() const { return !_pArrayFilterGrad.IsNull(); }
	bool HasArrayBiasGrad() const { return !_pArrayBiasGrad.IsNull(); }
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
