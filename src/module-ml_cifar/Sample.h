//==============================================================================
// Sample.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CIFAR_SAMPLE_H
#define GURAX_MODULE_ML_CIFAR_SAMPLE_H
#include <gurax.h>
#include "SampleSet.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Sample
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Sample : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Sample);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.cifar.Sample");
private:
	RefPtr<SampleSet> _pSampleSet;
	const Array::ElemTypeT& _elemType;
	Double _numCeil;
	const Image::Format& _format;
	size_t _iSample;
	RefPtr<Array> _pArrayInput;
	RefPtr<Array> _pArrayResult;
	RefPtr<Image> _pImage;
public:
	// Constructor
	Sample(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, Double numCeil, const Image::Format& format, size_t iSample);
	// Copy constructor/operator
	Sample(const Sample& src) = delete;
	Sample& operator=(const Sample& src) = delete;
	// Move constructor/operator
	Sample(Sample&& src) noexcept = delete;
	Sample& operator=(Sample&& src) noexcept = delete;
protected:
	~Sample() = default;
public:
	const Array& GetArrayInput();
	const Array& GetArrayResult();
	const Image& GetImage();
	UInt8 GetLabel() const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Sample& other) const { return this == &other; }
	bool IsEqualTo(const Sample& other) const { return IsIdentical(other); }
	bool IsLessThan(const Sample& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// SampleList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SampleList : public ListBase<Sample*> {
};

//------------------------------------------------------------------------------
// SampleOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SampleOwner : public SampleList {
public:
	~SampleOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml_cifar)

#endif
