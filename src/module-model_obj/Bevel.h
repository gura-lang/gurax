//==============================================================================
// Bevel.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_BEVEL_H
#define GURAX_MODULE_MODEL_OBJ_BEVEL_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Bevel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Bevel : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Bevel);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Bevel");
public:
	// Constructor
	Bevel() {}
	// Copy constructor/operator
	Bevel(const Bevel& src) = delete;
	Bevel& operator=(const Bevel& src) = delete;
	// Move constructor/operator
	Bevel(Bevel&& src) noexcept = delete;
	Bevel& operator=(Bevel&& src) noexcept = delete;
protected:
	~Bevel() = default;
public:
	virtual const char* GetName() const override { return "Bevel"; }
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Bevel& other) const { return this == &other; }
	bool IsEqualTo(const Bevel& other) const { return IsIdentical(other); }
	bool IsLessThan(const Bevel& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// BevelList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE BevelList : public ListBase<Bevel*> {
};

//------------------------------------------------------------------------------
// BevelOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE BevelOwner : public BevelList {
public:
	~BevelOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
