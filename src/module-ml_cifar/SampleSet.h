//==============================================================================
// SampleSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CIFAR_SampleSet_H
#define GURAX_MODULE_ML_CIFAR_SampleSet_H
#include <gurax.h>
#include "LabelSet.h"
#include "ImageSet.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// SampleSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SampleSet : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(SampleSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.cifar.SampleSet");
private:
	bool _hasSuperClassFlag;
	size_t _nSamples;
	RefPtr<LabelSet> _pLabelSet;
	RefPtr<ImageSet> _pImageSet;
	NumList<size_t> _indices;
public:
	// Constructor
	SampleSet(bool hasSuperClassFlag);
	// Copy constructor/operator
	SampleSet(const SampleSet& src) = delete;
	SampleSet& operator=(const SampleSet& src) = delete;
	// Move constructor/operator
	SampleSet(SampleSet&& src) noexcept = delete;
	SampleSet& operator=(SampleSet&& src) noexcept = delete;
protected:
	~SampleSet() = default;
public:
	bool HasSuperClass() const { return _hasSuperClassFlag; }
	bool Read(Stream& stream);
	size_t GetNSamples() const { return _nSamples; }
	LabelSet& GetLabelSet() { return *_pLabelSet; }
	const LabelSet& GetLabelSet() const { return *_pLabelSet; }
	ImageSet& GetImageSet() { return *_pImageSet; }
	const ImageSet& GetImageSet() const { return *_pImageSet; }
public:
	void Shuffle(Random& random) { _indices.Shuffle(random); }
	size_t GetIndex(size_t i) const { return _indices[i]; }
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
	const Image::Format& _format;
	size_t _batchSize;
	Double _numCeil;
	size_t _idx;
	bool _defaultSuperClassFlag;
public:
	Iterator_Each(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, const Image::Format& format, size_t batchSize, Double numCeil, bool defaultSuperClassFlag);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override;
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml_cifar)

#endif
