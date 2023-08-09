//==============================================================================
// PairSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CIFAR_PAIRSET_H
#define GURAX_MODULE_ML_CIFAR_PAIRSET_H
#include <gurax.h>
#include "LabelSet.h"
#include "ImageSet.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// PairSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PairSet : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PairSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.cifar.PairSet");
private:
	bool _superClassFlag;
	size_t _nSamples;
	RefPtr<LabelSet> _pLabelSet;
	RefPtr<ImageSet> _pImageSet;
	NumList<size_t> _indices;
public:
	// Constructor
	PairSet(bool superClassFlag);
	// Copy constructor/operator
	PairSet(const PairSet& src) = delete;
	PairSet& operator=(const PairSet& src) = delete;
	// Move constructor/operator
	PairSet(PairSet&& src) noexcept = delete;
	PairSet& operator=(PairSet&& src) noexcept = delete;
protected:
	~PairSet() = default;
public:
	bool Read(Stream& stream);
	size_t GetNSamples() const { return _nSamples; }
	const LabelSet& GetLabelSet() const { return *_pLabelSet; }
	const ImageSet& GetImageSet() const { return *_pImageSet; }
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
// Iterator_Each
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Each : public Iterator {
private:
	RefPtr<PairSet> _pPairSet;
	const Array::ElemTypeT& _elemType;
	RefPtr<Array> _pArrayImage;
	RefPtr<Array> _pArrayLabel;
	RefPtr<Image> _pImage;
	Double _numCeil;
	const Image::Format* _pFormat;
	size_t _idx;
public:
	Iterator_Each(PairSet* pPairSet, const Array::ElemTypeT& elemType, Double numCeil, const Image::Format* pFormat);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override;
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml_cifar)

#endif
