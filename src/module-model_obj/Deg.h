//==============================================================================
// Deg.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_DEG_H
#define GURAX_MODULE_MODEL_OBJ_DEG_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Deg
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Deg : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Deg);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Deg");
public:
	// Constructor
	Deg() {}
	// Copy constructor/operator
	Deg(const Deg& src) = delete;
	Deg& operator=(const Deg& src) = delete;
	// Move constructor/operator
	Deg(Deg&& src) noexcept = delete;
	Deg& operator=(Deg&& src) noexcept = delete;
protected:
	~Deg() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Deg& other) const { return this == &other; }
	bool IsEqualTo(const Deg& other) const { return IsIdentical(other); }
	bool IsLessThan(const Deg& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// DegList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DegList : public ListBase<Deg*> {
};

//------------------------------------------------------------------------------
// DegOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DegOwner : public DegList {
public:
	~DegOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
