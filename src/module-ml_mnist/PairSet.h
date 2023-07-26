//==============================================================================
// PairSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_MNIST_PAIRSET_H
#define GURAX_MODULE_ML_MNIST_PAIRSET_H
#include <gurax.h>
#include "ImageSet.h"
#include "LabelSet.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// PairSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PairSet : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PairSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.mnist.PairSet");
private:
	RefPtr<ImageSet> _pImageSet;
	RefPtr<LabelSet> _pLabelSet;
	NumList<size_t> _indices;
public:
	// Constructor
	PairSet(ImageSet* pImageSet, LabelSet* pLabelSet);
	// Copy constructor/operator
	PairSet(const PairSet& src) = delete;
	PairSet& operator=(const PairSet& src) = delete;
	// Move constructor/operator
	PairSet(PairSet&& src) noexcept = delete;
	PairSet& operator=(PairSet&& src) noexcept = delete;
protected:
	~PairSet() = default;
public:
	const ImageSet& GetImageSet() const { return *_pImageSet; }
	const LabelSet& GetLabelSet() const { return *_pLabelSet; }
public:
	void Shuffle(Random& random) { _indices.Shuffle(random); }
	size_t GetIndex(size_t i) const { return _indices[i]; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const PairSet& other) const { return this == &other; }
	bool IsEqualTo(const PairSet& other) const { return IsIdentical(other); }
	bool IsLessThan(const PairSet& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// PairSetList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PairSetList : public ListBase<PairSet*> {
};

//------------------------------------------------------------------------------
// PairSetOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PairSetOwner : public PairSetList {
public:
	~PairSetOwner() { Clear(); }
	void Clear();
};

//------------------------------------------------------------------------------
// Iterator_EachBatch
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_EachBatch : public Iterator {
private:
	RefPtr<PairSet> _pPairSet;
	RefPtr<Array> _pArrayImage;
	RefPtr<Array> _pArrayLabel;
	size_t _batchSize;
	Double _numCeil;
	size_t _idx;
public:
	Iterator_EachBatch(PairSet* pPairSet, const Array::ElemTypeT& elemType, size_t batchSize, Double numCeil);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenDetermined;
	}
	virtual size_t GetLength() const override;
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml_mnist)

#endif
