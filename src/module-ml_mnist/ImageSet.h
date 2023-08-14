//==============================================================================
// ImageSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_MNIST_IMAGESET_H
#define GURAX_MODULE_ML_MNIST_IMAGESET_H
#include <gurax.h>

Gurax_BeginModuleScope(ml_mnist)

class SampleSet;

//------------------------------------------------------------------------------
// ImageSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageSet : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ImageSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.mnist.ImageSet");
public:
	struct Header {
		Gurax_PackedUInt32_BE(magicNumber);
		Gurax_PackedUInt32_BE(nSamples);
		Gurax_PackedUInt32_BE(nRows);
		Gurax_PackedUInt32_BE(nCols);
	};
private:
	size_t _nSamples;
	size_t _nRows;
	size_t _nCols;
	RefPtr<Memory> _pMemory;
public:
	// Constructor
	ImageSet() : _nSamples(0), _nRows(0), _nCols(0) {}
	// Copy constructor/operator
	ImageSet(const ImageSet& src) = delete;
	ImageSet& operator=(const ImageSet& src) = delete;
	// Move constructor/operator
	ImageSet(ImageSet&& src) noexcept = delete;
	ImageSet& operator=(ImageSet&& src) noexcept = delete;
protected:
	~ImageSet() = default;
public:
	static void Bootup();
public:
	size_t GetNSamples() const { return _nSamples; }
	size_t GetNRows() const { return _nRows; }
	size_t GetNCols() const { return _nCols; }
	bool Read(Stream& stream);
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

Gurax_EndModuleScope(ml_mnist)

#endif
