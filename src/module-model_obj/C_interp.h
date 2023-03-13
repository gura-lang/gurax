//==============================================================================
// C_interp.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_C_INTERP_H
#define GURAX_MODULE_MODEL_OBJ_C_INTERP_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// C_interp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE C_interp : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(C_interp);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.C_interp");
public:
	// Constructor
	C_interp() {}
	// Copy constructor/operator
	C_interp(const C_interp& src) = delete;
	C_interp& operator=(const C_interp& src) = delete;
	// Move constructor/operator
	C_interp(C_interp&& src) noexcept = delete;
	C_interp& operator=(C_interp&& src) noexcept = delete;
protected:
	~C_interp() = default;
public:
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const C_interp& other) const { return this == &other; }
	bool IsEqualTo(const C_interp& other) const { return IsIdentical(other); }
	bool IsLessThan(const C_interp& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// C_interpList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE C_interpList : public ListBase<C_interp*> {
};

//------------------------------------------------------------------------------
// C_interpOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE C_interpOwner : public C_interpList {
public:
	~C_interpOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
