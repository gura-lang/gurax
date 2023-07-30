//==============================================================================
// Flatten.h
//==============================================================================
#ifndef GURAX_MODULE_ML_FLATTEN_H
#define GURAX_MODULE_ML_FLATTEN_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Flatten
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Flatten : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Flatten);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.Flatten");
private:
	RefPtr<ValueOwner> _pValuesDimSize; // all values are Number or Nil
private:
	RefPtr<Array> _pArrayFwdInSaved;
public:
	// Constructor
	Flatten(ValueOwner* pValuesDimSize) : Gear(false), _pValuesDimSize(pValuesDimSize) {}
	// Copy constructor/operator
	Flatten(const Flatten& src) = delete;
	Flatten& operator=(const Flatten& src) = delete;
	// Move constructor/operator
	Flatten(Flatten&& src) noexcept = delete;
	Flatten& operator=(Flatten&& src) noexcept = delete;
protected:
	~Flatten() = default;
public:
	static void Bootup();
public:
	virtual const char* GetName() const override { return "ml.Flatten"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, const Controller& controller) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag) override;
public:
	bool Serialize(Stream& stream) const;
	static Flatten* Deserialize(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Flatten& other) const { return this == &other; }
	bool IsEqualTo(const Flatten& other) const { return IsIdentical(other); }
	bool IsLessThan(const Flatten& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// FlattenList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE FlattenList : public ListBase<Flatten*> {
};

//------------------------------------------------------------------------------
// FlattenOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE FlattenOwner : public FlattenList {
public:
	~FlattenOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
