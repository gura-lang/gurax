//==============================================================================
// Dropout.h
//==============================================================================
#ifndef GURAX_MODULE_ML_DROPOUT_H
#define GURAX_MODULE_ML_DROPOUT_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Dropout
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Dropout : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Dropout);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.Dropout");
private:
	RefPtr<Array> _pArrayBoolSaved;
public:
	// Constructor
	Dropout() : Gear(false) {}
	// Copy constructor/operator
	Dropout(const Dropout& src) = delete;
	Dropout& operator=(const Dropout& src) = delete;
	// Move constructor/operator
	Dropout(Dropout&& src) noexcept = delete;
	Dropout& operator=(Dropout&& src) noexcept = delete;
protected:
	~Dropout() = default;
public:
	static void Initialize();
public:
	virtual const char* GetName() const override { return "ml.Dropout"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, bool trainingFlag) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag) override;
public:
	bool Serialize(Stream& stream) const;
	static Dropout* Deserialize(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Dropout& other) const { return this == &other; }
	bool IsEqualTo(const Dropout& other) const { return IsIdentical(other); }
	bool IsLessThan(const Dropout& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// DropoutList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DropoutList : public ListBase<Dropout*> {
};

//------------------------------------------------------------------------------
// DropoutOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DropoutOwner : public DropoutList {
public:
	~DropoutOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
