//==============================================================================
// Reshape.h
//==============================================================================
#ifndef GURAX_MODULE_ML_RESHAPE_H
#define GURAX_MODULE_ML_RESHAPE_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Reshape
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Reshape : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Reshape);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.Reshape");
private:
	RefPtr<ValueOwner> _pValuesDimSize; // all values are Number or Nil
private:
	RefPtr<Array> _pArrayFwdInSaved;
public:
	// Constructor
	Reshape(ValueOwner* pValuesDimSize) : Gear(false), _pValuesDimSize(pValuesDimSize) {}
	// Copy constructor/operator
	Reshape(const Reshape& src) = delete;
	Reshape& operator=(const Reshape& src) = delete;
	// Move constructor/operator
	Reshape(Reshape&& src) noexcept = delete;
	Reshape& operator=(Reshape&& src) noexcept = delete;
protected:
	~Reshape() = default;
public:
	static void Initialize();
public:
	virtual const char* GetName() const override { return "ml.Reshape"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, const Controller& controller) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag) override;
public:
	bool Serialize(Stream& stream) const;
	static Reshape* Deserialize(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Reshape& other) const { return this == &other; }
	bool IsEqualTo(const Reshape& other) const { return IsIdentical(other); }
	bool IsLessThan(const Reshape& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ReshapeList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ReshapeList : public ListBase<Reshape*> {
};

//------------------------------------------------------------------------------
// ReshapeOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ReshapeOwner : public ReshapeList {
public:
	~ReshapeOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
