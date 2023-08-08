//==============================================================================
// LabelSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_MNIST_LABELSET_H
#define GURAX_MODULE_ML_MNIST_LABELSET_H
#include <gurax.h>

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// LabelSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LabelSet : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(LabelSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.mnist.LabelSet");
private:
	bool _qmnistFlag;
	size_t _nSamples;
	size_t _nFields;
	size_t _nClasses;
	RefPtr<Memory> _pMemory;
public:
	// Constructor
	LabelSet() : _qmnistFlag(false), _nSamples(0), _nFields(1), _nClasses(0) {}
	// Copy constructor/operator
	LabelSet(const LabelSet& src) = delete;
	LabelSet& operator=(const LabelSet& src) = delete;
	// Move constructor/operator
	LabelSet(LabelSet&& src) noexcept = delete;
	LabelSet& operator=(LabelSet&& src) noexcept = delete;
protected:
	~LabelSet() = default;
public:
	size_t GetNSamples() const { return _nSamples; }
	size_t GetNClasses() const { return _nClasses; }
	bool Read(Stream& stream);
	UInt32 GetLabel(size_t iSample) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const LabelSet& other) const { return this == &other; }
	bool IsEqualTo(const LabelSet& other) const { return IsIdentical(other); }
	bool IsLessThan(const LabelSet& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// LabelSetList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LabelSetList : public ListBase<LabelSet*> {
};

//------------------------------------------------------------------------------
// LabelSetOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LabelSetOwner : public LabelSetList {
public:
	~LabelSetOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml_mnist)

#endif
