//==============================================================================
// Scrv.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_SCRV_H
#define GURAX_MODULE_MODEL_OBJ_SCRV_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Scrv
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Scrv : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Scrv);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Scrv");
public:
	// Constructor
	Scrv() {}
	// Copy constructor/operator
	Scrv(const Scrv& src) = delete;
	Scrv& operator=(const Scrv& src) = delete;
	// Move constructor/operator
	Scrv(Scrv&& src) noexcept = delete;
	Scrv& operator=(Scrv&& src) noexcept = delete;
protected:
	~Scrv() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Scrv& other) const { return this == &other; }
	bool IsEqualTo(const Scrv& other) const { return IsIdentical(other); }
	bool IsLessThan(const Scrv& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ScrvList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ScrvList : public ListBase<Scrv*> {
};

//------------------------------------------------------------------------------
// ScrvOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ScrvOwner : public ScrvList {
public:
	~ScrvOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
