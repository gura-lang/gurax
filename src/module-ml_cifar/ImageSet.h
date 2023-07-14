//==============================================================================
// ImageSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CIFAR_IMAGESET_H
#define GURAX_MODULE_ML_CIFAR_IMAGESET_H
#include <gurax.h>

Gurax_BeginModuleScope(ml_cifar)

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
	static const size_t nRowsImage = 32;
	static const size_t nColsImage = 32;
private:
	Binary _buff;
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
	void Add(UInt8* buffImage) { _buff += buffImage; }
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
