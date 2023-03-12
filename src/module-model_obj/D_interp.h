//==============================================================================
// D_interp.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_D_INTERP_H
#define GURAX_MODULE_MODEL_OBJ_D_INTERP_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// D_interp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE D_interp : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(D_interp);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.D_interp");
public:
	// Constructor
	D_interp() {}
	// Copy constructor/operator
	D_interp(const D_interp& src) = delete;
	D_interp& operator=(const D_interp& src) = delete;
	// Move constructor/operator
	D_interp(D_interp&& src) noexcept = delete;
	D_interp& operator=(D_interp&& src) noexcept = delete;
protected:
	~D_interp() = default;
public:
	virtual bool FeedField(const char* field, size_t iParam) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const D_interp& other) const { return this == &other; }
	bool IsEqualTo(const D_interp& other) const { return IsIdentical(other); }
	bool IsLessThan(const D_interp& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// D_interpList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE D_interpList : public ListBase<D_interp*> {
};

//------------------------------------------------------------------------------
// D_interpOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE D_interpOwner : public D_interpList {
public:
	~D_interpOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
