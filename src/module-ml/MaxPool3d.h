//==============================================================================
// MaxPool3d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_MAXPOOL3D_H
#define GURAX_MODULE_ML_MAXPOOL3D_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// MaxPool3d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MaxPool3d : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(MaxPool3d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.MaxPool3d");
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
	MaxPool3d(size_t nRowsKernel, size_t nColsKernel, size_t strideRow, size_t strideCol);
	// Copy constructor/operator
	MaxPool3d(const MaxPool3d& src) = delete;
	MaxPool3d& operator=(const MaxPool3d& src) = delete;
	// Move constructor/operator
	MaxPool3d(MaxPool3d&& src) noexcept = delete;
	MaxPool3d& operator=(MaxPool3d&& src) noexcept = delete;
protected:
	~MaxPool3d() = default;
public:
	static void Initialize();
public:
	bool CalcSizeOut(size_t nRowsIn, size_t nColsIn, size_t* pnRowsOut, size_t* pnColsOut) const;
	virtual const char* GetName() const override { return "ml.MaxPool3d"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, bool trainingFlag) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag) override;
public:
	bool Serialize(Stream& stream) const;
	static MaxPool3d* Deserialize(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const MaxPool3d& other) const { return this == &other; }
	bool IsEqualTo(const MaxPool3d& other) const { return IsIdentical(other); }
	bool IsLessThan(const MaxPool3d& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// MaxPool3dList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MaxPool3dList : public ListBase<MaxPool3d*> {
};

//------------------------------------------------------------------------------
// MaxPool3dOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MaxPool3dOwner : public MaxPool3dList {
public:
	~MaxPool3dOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
