//==============================================================================
// ReLU.h
//==============================================================================
#ifndef GURAX_MODULE_ML_RELU_H
#define GURAX_MODULE_ML_RELU_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// ReLU
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ReLU : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(ReLU);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.ReLU");
private:
	RefPtr<Array> _pArrayBoolSaved;
public:
	// Constructor
	ReLU() : Gear(false) {}
	// Copy constructor/operator
	ReLU(const ReLU& src) = delete;
	ReLU& operator=(const ReLU& src) = delete;
	// Move constructor/operator
	ReLU(ReLU&& src) noexcept = delete;
	ReLU& operator=(ReLU&& src) noexcept = delete;
protected:
	~ReLU() = default;
public:
	static void Initialize();
public:
	virtual const char* GetName() const override { return "ml.ReLU"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, bool bwdPropagationFlag, const Array& array) override;
public:
	bool Serialize(Stream& stream) const;
	static ReLU* Deserialize(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ReLU& other) const { return this == &other; }
	bool IsEqualTo(const ReLU& other) const { return IsIdentical(other); }
	bool IsLessThan(const ReLU& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ReLUList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ReLUList : public ListBase<ReLU*> {
};

//------------------------------------------------------------------------------
// ReLUOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ReLUOwner : public ReLUList {
public:
	~ReLUOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
