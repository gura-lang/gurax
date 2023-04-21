//==============================================================================
// Softmax.h
//==============================================================================
#ifndef GURAX_MODULE_ML_SOFTMAX_H
#define GURAX_MODULE_ML_SOFTMAX_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Softmax
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Softmax : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Softmax);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.Softmax");
private:
	RefPtr<Array> _pArrayFwd;
public:
	// Constructor
	Softmax() {}
	// Copy constructor/operator
	Softmax(const Softmax& src) = delete;
	Softmax& operator=(const Softmax& src) = delete;
	// Move constructor/operator
	Softmax(Softmax&& src) noexcept = delete;
	Softmax& operator=(Softmax&& src) noexcept = delete;
protected:
	~Softmax() = default;
public:
	static void Initialize();
public:
	virtual const char* GetName() const override { return "ml.Softmax"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Softmax& other) const { return this == &other; }
	bool IsEqualTo(const Softmax& other) const { return IsIdentical(other); }
	bool IsLessThan(const Softmax& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// SoftmaxList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SoftmaxList : public ListBase<Softmax*> {
};

//------------------------------------------------------------------------------
// SoftmaxOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SoftmaxOwner : public SoftmaxList {
public:
	~SoftmaxOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
