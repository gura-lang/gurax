//==============================================================================
// ImageSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CIFAR_IMAGESET_H
#define GURAX_MODULE_ML_CIFAR_IMAGESET_H
#include <gurax.h>

Gurax_BeginModuleScope(ml_cifar)

class SampleSet;

//------------------------------------------------------------------------------
// ImageSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageSet : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ImageSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.cifar.ImageSet");
public:
	static const size_t nChannels = 3;
	static const size_t nRows = 32;
	static const size_t nCols = 32;
private:
	Binary _buff;
public:
	static void Bootup();
public:
	// Constructor
	ImageSet();
	// Copy constructor/operator
	ImageSet(const ImageSet& src) = delete;
	ImageSet& operator=(const ImageSet& src) = delete;
	// Move constructor/operator
	ImageSet(ImageSet&& src) noexcept = delete;
	ImageSet& operator=(ImageSet&& src) noexcept = delete;
protected:
	~ImageSet() = default;
public:
	void Add(const UInt8* buffImage, size_t bytes) { _buff.append(buffImage, bytes); }
	void ExtractAsArray(RefPtr<Array>& pArray, const SampleSet& sampleSet, const Array::ElemTypeT& elemType, size_t batchSize, Double numCeil, size_t idx) const;
	void ExtractAsImage(RefPtr<Image>& pImage, const SampleSet& sampleSet, const Image::Format& format, size_t batchSize, size_t idx) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ImageSet& other) const { return this == &other; }
	bool IsEqualTo(const ImageSet& other) const { return IsIdentical(other); }
	bool IsLessThan(const ImageSet& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ImageSetList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageSetList : public ListBase<ImageSet*> {
};

//------------------------------------------------------------------------------
// ImageSetOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageSetOwner : public ImageSetList {
public:
	~ImageSetOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml_cifar)

#endif
