//==============================================================================
// ImageSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_MNIST_IMAGESET_H
#define GURAX_MODULE_ML_MNIST_IMAGESET_H
#include <gurax.h>

Gurax_BeginModuleScope(ml_mnist)

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
		Gurax_PackedUInt32_BE(nImages);
		Gurax_PackedUInt32_BE(nRows);
		Gurax_PackedUInt32_BE(nCols);
	};
private:
	size_t _nImages;
	size_t _nRows;
	size_t _nCols;
	RefPtr<Memory> _pMemory;
public:
	// Constructor
	ImageSet() : _nImages(0), _nRows(0), _nCols(0) {}
	// Copy constructor/operator
	ImageSet(const ImageSet& src) = delete;
	ImageSet& operator=(const ImageSet& src) = delete;
	// Move constructor/operator
	ImageSet(ImageSet&& src) noexcept = delete;
	ImageSet& operator=(ImageSet&& src) noexcept = delete;
protected:
	~ImageSet() = default;
public:
	size_t CountImages() const { return _nImages; }
	size_t CountRows() const { return _nRows; }
	size_t CountCols() const { return _nCols; }
	bool Read(Stream& stream);
	Array* ToArray(const Array::ElemTypeT& elemType, bool flattenFlag, Float numMax) const;
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
