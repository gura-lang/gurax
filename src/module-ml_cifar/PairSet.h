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
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const PairSet& other) const { return this == &other; }
	bool IsEqualTo(const PairSet& other) const { return IsIdentical(other); }
	bool IsLessThan(const PairSet& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// CifarList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CifarList : public ListBase<PairSet*> {
};

//------------------------------------------------------------------------------
// CifarOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CifarOwner : public CifarList {
public:
	~CifarOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml_cifar)

#endif
