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
	const Image::Format& _format;
	size_t _batchSize;
	Double _numCeil;
	size_t _idx;
	bool _defaultSuperClassFlag;
	RefPtr<Array> _pArrayInput;
	RefPtr<Array> _pArrayResult;
	RefPtr<Array> _pArrayResultSuper;
	RefPtr<Image> _pImage;
	RefPtr<ValueOwner> _pValuesLabel;
	RefPtr<ValueOwner> _pValuesLabelSuper;
	RefPtr<ValueOwner> _pValuesLabelName;
	RefPtr<ValueOwner> _pValuesLabelSuperName;
public:
	// Constructor
	Sample(SampleSet* pSampleSet, const Array::ElemTypeT& elemType, const Image::Format& format, size_t batchSize, Double numCeil, size_t idx, bool defaultSuperClassFlag);
	// Copy constructor/operator
	Sample(const Sample& src) = delete;
	Sample& operator=(const Sample& src) = delete;
	// Move constructor/operator
	Sample(Sample&& src) noexcept = delete;
	Sample& operator=(Sample&& src) noexcept = delete;
protected:
	~Sample() = default;
public:
	bool HasSuperClass() const { return _pSampleSet->HasSuperClass(); }
	bool GetSuperClassFlag(const Attribute& attr) const;
	const Array& GetArrayInput();
	const Array& GetArrayResult();
	const Array& GetArrayResultSuper();
	const Image& GetImage();
	UInt8 GetLabel(size_t idx) const;
	UInt8 GetLabel() const { return GetLabel(_idx); }
	UInt8 GetLabelSuper(size_t idx) const;
	UInt8 GetLabelSuper() const { return GetLabelSuper(_idx); }
	String GetLabelName(size_t idx) const;
	String GetLabelName() const { return GetLabelName(_idx); }
	String GetLabelNameSuper(size_t idx) const;
	String GetLabelNameSuper() const { return GetLabelNameSuper(_idx); }
	const ValueOwner& GetValuesLabel();
	const ValueOwner& GetValuesLabelSuper();
	const ValueOwner& GetValuesLabelName();
	const ValueOwner& GetValuesLabelNameSuper();
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
