//==============================================================================
// Sigmoid.h
//==============================================================================
#ifndef GURAX_MODULE_ML_SIGMOID_H
#define GURAX_MODULE_ML_SIGMOID_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Sigmoid
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Sigmoid : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Sigmoid);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.Sigmoid");
private:
	RefPtr<Array> _pArrayFwdOutSaved;
public:
	// Constructor
	Sigmoid() : Gear(false) {}
	// Copy constructor/operator
	Sigmoid(const Sigmoid& src) = delete;
	Sigmoid& operator=(const Sigmoid& src) = delete;
	// Move constructor/operator
	Sigmoid(Sigmoid&& src) noexcept = delete;
	Sigmoid& operator=(Sigmoid&& src) noexcept = delete;
protected:
	~Sigmoid() = default;
public:
	static void Initialize();
public:
	virtual const char* GetName() const override { return "ml.Sigmoid"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, bool bwdPropagationFlag, const Array& array) override;
public:
	bool Serialize(Stream& stream) const;
	static Sigmoid* Deserialize(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Sigmoid& other) const { return this == &other; }
	bool IsEqualTo(const Sigmoid& other) const { return IsIdentical(other); }
	bool IsLessThan(const Sigmoid& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// SigmoidList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SigmoidList : public ListBase<Sigmoid*> {
};

//------------------------------------------------------------------------------
// SigmoidOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SigmoidOwner : public SigmoidList {
public:
	~SigmoidOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
