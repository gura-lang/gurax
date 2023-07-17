//==============================================================================
// Conv1d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CONV1D_H
#define GURAX_MODULE_ML_CONV1D_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv1d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Conv1d : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Conv1d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.Conv1d");
private:
	RefPtr<Array> _pArrayFwdOutSaved;
public:
	// Constructor
	Conv1d() : Gear(false) {}
	// Copy constructor/operator
	Conv1d(const Conv1d& src) = delete;
	Conv1d& operator=(const Conv1d& src) = delete;
	// Move constructor/operator
	Conv1d(Conv1d&& src) noexcept = delete;
	Conv1d& operator=(Conv1d&& src) noexcept = delete;
protected:
	~Conv1d() = default;
public:
	static void Initialize();
public:
	virtual const char* GetName() const override { return "ml.Conv1d"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, const Controller& controller) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag) override;
public:
	bool Serialize(Stream& stream) const;
	static Conv1d* Deserialize(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Conv1d& other) const { return this == &other; }
	bool IsEqualTo(const Conv1d& other) const { return IsIdentical(other); }
	bool IsLessThan(const Conv1d& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Conv1dList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Conv1dList : public ListBase<Conv1d*> {
};

//------------------------------------------------------------------------------
// Conv1dOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Conv1dOwner : public Conv1dList {
public:
	~Conv1dOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
