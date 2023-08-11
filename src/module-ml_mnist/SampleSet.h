//==============================================================================
// SampleSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_MNIST_SAMPLESET_H
#define GURAX_MODULE_ML_MNIST_SAMPLESET_H
#include <gurax.h>
#include "ImageSet.h"
#include "LabelSet.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// SampleSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SampleSet : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(SampleSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.mnist.SampleSet");
private:
	RefPtr<ImageSet> _pImageSet;
	RefPtr<LabelSet> _pLabelSet;
	NumList<size_t> _indices;
public:
	// Constructor
	SampleSet(ImageSet* pImageSet, LabelSet* pLabelSet);
	// Copy constructor/operator
	SampleSet(const SampleSet& src) = delete;
	SampleSet& operator=(const SampleSet& src) = delete;
	// Move constructor/operator
	SampleSet(SampleSet&& src) noexcept = delete;
	SampleSet& operator=(SampleSet&& src) noexcept = delete;
protected:
	~SampleSet() = default;
public:
	const ImageSet& GetImageSet() const { return *_pImageSet; }
	const LabelSet& GetLabelSet() const { return *_pLabelSet; }
public:
	void Shuffle(Random& random) { _indices.Shuffle(random); }
	size_t GetIndex(size_t i) const { return _indices[i]; }
	size_t GetNSamples() const { return _indices.size(); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const SampleSet& other) const { return this == &other; }
	bool IsEqualTo(const SampleSet& other) const { return IsIdentical(other); }
	bool IsLessThan(const SampleSet& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// SampleSetList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SampleSetList : public ListBase<SampleSet*> {
};

//------------------------------------------------------------------------------
// SampleSetOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SampleSetOwner : public SampleSetList {
public:
	~SampleSetOwner() { Clear(); }
	void Clear();
};

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Each : public Iterator {
private:
	RefPtr<SampleSet> _pSampleSet;
	const Array::ElemTypeT& _elemType;
	Double _numCeil;
	const Image::Format& _format;
	size_t _batchSize;
	size_t _idx;
public:
	Iterator_Each(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, Double numCeil, const Image::Format& format, size_t batchSize);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override;
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml_mnist)

#endif
