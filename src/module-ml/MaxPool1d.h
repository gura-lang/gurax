//==============================================================================
// MaxPool1d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_MAXPOOL1D_H
#define GURAX_MODULE_ML_MAXPOOL1D_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// MaxPool1d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MaxPool1d : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(MaxPool1d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.MaxPool1d");
private:
	size_t _nRowsKernel;
	size_t _nColsKernel;
	size_t _strideRow;
	size_t _strideCol;
private:
	RefPtr<Array> _pArrayFwdInSaved;
	RefPtr<Array> _pArrayFwdOutSaved;
	RefPtr<Array> _pArrayScanPosInSel;
public:
	// Constructor
	MaxPool1d(size_t nRowsKernel, size_t nColsKernel, size_t strideRow, size_t strideCol);
	// Copy constructor/operator
	MaxPool1d(const MaxPool1d& src) = delete;
	MaxPool1d& operator=(const MaxPool1d& src) = delete;
	// Move constructor/operator
	MaxPool1d(MaxPool1d&& src) noexcept = delete;
	MaxPool1d& operator=(MaxPool1d&& src) noexcept = delete;
protected:
	~MaxPool1d() = default;
public:
	static void Initialize();
public:
	bool CalcSizeOut(size_t nRowsIn, size_t nColsIn, size_t* pnRowsOut, size_t* pnColsOut) const;
	virtual const char* GetName() const override { return "ml.MaxPool1d"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, bool bwdPropagationFlag, const Array& array) override;
public:
	bool Serialize(Stream& stream) const;
	static MaxPool1d* Deserialize(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const MaxPool1d& other) const { return this == &other; }
	bool IsEqualTo(const MaxPool1d& other) const { return IsIdentical(other); }
	bool IsLessThan(const MaxPool1d& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// MaxPool1dList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MaxPool1dList : public ListBase<MaxPool1d*> {
};

//------------------------------------------------------------------------------
// MaxPool1dOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MaxPool1dOwner : public MaxPool1dList {
public:
	~MaxPool1dOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
