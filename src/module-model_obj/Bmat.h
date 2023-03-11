//==============================================================================
// Bmat.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_BMAT_H
#define GURAX_MODULE_MODEL_OBJ_BMAT_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Bmat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Bmat : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Bmat);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Bmat");
public:
	// Constructor
	Bmat() {}
	// Copy constructor/operator
	Bmat(const Bmat& src) = delete;
	Bmat& operator=(const Bmat& src) = delete;
	// Move constructor/operator
	Bmat(Bmat&& src) noexcept = delete;
	Bmat& operator=(Bmat&& src) noexcept = delete;
protected:
	~Bmat() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Bmat& other) const { return this == &other; }
	bool IsEqualTo(const Bmat& other) const { return IsIdentical(other); }
	bool IsLessThan(const Bmat& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// BmatList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE BmatList : public ListBase<Bmat*> {
};

//------------------------------------------------------------------------------
// BmatOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE BmatOwner : public BmatList {
public:
	~BmatOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
