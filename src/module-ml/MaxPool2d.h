//==============================================================================
// MaxPool2d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_MAXPOOL2D_H
#define GURAX_MODULE_ML_MAXPOOL2D_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// MaxPool2d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MaxPool2d : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(MaxPool2d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.MaxPool2d");
private:
	size_t _nRowsKernel;
	size_t _nColsKernel;
	size_t _stridesRow;
	size_t _stridesCol;
	RefPtr<Array> _pArrayFwdInSaved;
	RefPtr<Array> _pArrayFwdOutSaved;
	RefPtr<Array> _pArrayScanPosInSel;
public:
	// Constructor
	MaxPool2d(size_t nRowsKernel, size_t nColsKernel, size_t stridesRow, size_t stridesCol);
	// Copy constructor/operator
	MaxPool2d(const MaxPool2d& src) = delete;
	MaxPool2d& operator=(const MaxPool2d& src) = delete;
	// Move constructor/operator
	MaxPool2d(MaxPool2d&& src) noexcept = delete;
	MaxPool2d& operator=(MaxPool2d&& src) noexcept = delete;
protected:
	~MaxPool2d() = default;
public:
	static void Initialize();
public:
	bool CalcSizeOut(size_t nRowsIn, size_t nColsIn, size_t* pnRowsOut, size_t* pnColsOut) const;
	virtual const char* GetName() const override { return "ml.MaxPool2d"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, bool bwdPropagationFlag, const Array& array) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const MaxPool2d& other) const { return this == &other; }
	bool IsEqualTo(const MaxPool2d& other) const { return IsIdentical(other); }
	bool IsLessThan(const MaxPool2d& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// MaxPool2dList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MaxPool2dList : public ListBase<MaxPool2d*> {
};

//------------------------------------------------------------------------------
// MaxPool2dOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MaxPool2dOwner : public MaxPool2dList {
public:
	~MaxPool2dOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
