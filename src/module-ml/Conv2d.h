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
	size_t _strides;
	size_t _padding;
	RefPtr<Array> _pArrayFwdSaved;
	RefPtr<Array> _pArrayFwd1; // (nSamples * nRowsOut * nColsOut, nChannels * nRowsFilter * nColsFilter)
	RefPtr<Array> _pArrayFwd2; // (nFilters, nChannels * nRowsFilter * nColsFilter)
	RefPtr<Array> _pArrayFwd3; // (nChannels * nRowsFilter * nColsFilter, nFilters)
	RefPtr<Array> _pArrayFwd4; // (nSamples * nRowsOut * nColsOut, nFilters)
	RefPtr<Array> _pArrayFwd5; // (nSamples, nRowsOut, nColsOut, nFilters)
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
	virtual const char* GetName() const override { return "ml.Conv2d"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
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
