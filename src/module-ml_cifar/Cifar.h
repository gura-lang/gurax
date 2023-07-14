//==============================================================================
// Cifar.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CIFAR_CIFAR_H
#define GURAX_MODULE_ML_CIFAR_CIFAR_H
#include <gurax.h>
#include "LabelSet.h"
#include "ImageSet.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Cifar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Cifar : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Cifar);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.cifar.Cifar");
private:
	bool _superClassFlag;
	size_t _nImages;
	RefPtr<LabelSet> _pLabelSet;
	RefPtr<ImageSet> _pImageSet;
public:
	// Constructor
	Cifar(bool superClassFlag);
	// Copy constructor/operator
	Cifar(const Cifar& src) = delete;
	Cifar& operator=(const Cifar& src) = delete;
	// Move constructor/operator
	Cifar(Cifar&& src) noexcept = delete;
	Cifar& operator=(Cifar&& src) noexcept = delete;
protected:
	~Cifar() = default;
public:
	bool Read(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Cifar& other) const { return this == &other; }
	bool IsEqualTo(const Cifar& other) const { return IsIdentical(other); }
	bool IsLessThan(const Cifar& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// CifarList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CifarList : public ListBase<Cifar*> {
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
