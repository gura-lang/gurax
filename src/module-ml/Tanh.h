//==============================================================================
// Tanh.h
//==============================================================================
#ifndef GURAX_MODULE_ML_TANH_H
#define GURAX_MODULE_ML_TANH_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Tanh
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tanh : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Tanh);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.Tanh");
private:
	RefPtr<Array> _pArrayFwdOutSaved;
public:
	// Constructor
	Tanh() : Gear(false) {}
	// Copy constructor/operator
	Tanh(const Tanh& src) = delete;
	Tanh& operator=(const Tanh& src) = delete;
	// Move constructor/operator
	Tanh(Tanh&& src) noexcept = delete;
	Tanh& operator=(Tanh&& src) noexcept = delete;
protected:
	~Tanh() = default;
public:
	static void Initialize();
public:
	virtual const char* GetName() const override { return "ml.Tanh"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, bool bwdPropagationFlag, const Array& array) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Tanh& other) const { return this == &other; }
	bool IsEqualTo(const Tanh& other) const { return IsIdentical(other); }
	bool IsLessThan(const Tanh& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// TanhList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TanhList : public ListBase<Tanh*> {
};

//------------------------------------------------------------------------------
// TanhOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TanhOwner : public TanhList {
public:
	~TanhOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
