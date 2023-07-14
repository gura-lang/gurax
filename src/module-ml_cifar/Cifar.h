//==============================================================================
// Cifar.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CIFAR_CIFAR_H
#define GURAX_MODULE_ML_CIFAR_CIFAR_H
#include <gurax.h>

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
public:
	// Constructor
	Cifar() {}
	// Copy constructor/operator
	Cifar(const Cifar& src) = delete;
	Cifar& operator=(const Cifar& src) = delete;
	// Move constructor/operator
	Cifar(Cifar&& src) noexcept = delete;
	Cifar& operator=(Cifar&& src) noexcept = delete;
protected:
	~Cifar() = default;
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
