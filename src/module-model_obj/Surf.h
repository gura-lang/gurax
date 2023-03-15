//==============================================================================
// Surf.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_SURF_H
#define GURAX_MODULE_MODEL_OBJ_SURF_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Surf
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Surf : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Surf);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Surf");
public:
	// Constructor
	Surf() {}
	// Copy constructor/operator
	Surf(const Surf& src) = delete;
	Surf& operator=(const Surf& src) = delete;
	// Move constructor/operator
	Surf(Surf&& src) noexcept = delete;
	Surf& operator=(Surf&& src) noexcept = delete;
protected:
	~Surf() = default;
public:
	virtual const char* GetName() const override { return "Surf"; }
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Surf& other) const { return this == &other; }
	bool IsEqualTo(const Surf& other) const { return IsIdentical(other); }
	bool IsLessThan(const Surf& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// SurfList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SurfList : public ListBase<Surf*> {
};

//------------------------------------------------------------------------------
// SurfOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SurfOwner : public SurfList {
public:
	~SurfOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
