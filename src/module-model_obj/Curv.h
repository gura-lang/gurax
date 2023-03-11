//==============================================================================
// Curv.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_CURV_H
#define GURAX_MODULE_MODEL_OBJ_CURV_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Curv
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Curv : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Curv);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Curv");
public:
	// Constructor
	Curv() {}
	// Copy constructor/operator
	Curv(const Curv& src) = delete;
	Curv& operator=(const Curv& src) = delete;
	// Move constructor/operator
	Curv(Curv&& src) noexcept = delete;
	Curv& operator=(Curv&& src) noexcept = delete;
protected:
	~Curv() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Curv& other) const { return this == &other; }
	bool IsEqualTo(const Curv& other) const { return IsIdentical(other); }
	bool IsLessThan(const Curv& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// CurvList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CurvList : public ListBase<Curv*> {
};

//------------------------------------------------------------------------------
// CurvOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CurvOwner : public CurvList {
public:
	~CurvOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
