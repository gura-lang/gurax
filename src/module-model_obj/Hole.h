//==============================================================================
// Hole.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_HOLE_H
#define GURAX_MODULE_MODEL_OBJ_HOLE_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Hole
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Hole : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Hole);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Hole");
public:
	// Constructor
	Hole() {}
	// Copy constructor/operator
	Hole(const Hole& src) = delete;
	Hole& operator=(const Hole& src) = delete;
	// Move constructor/operator
	Hole(Hole&& src) noexcept = delete;
	Hole& operator=(Hole&& src) noexcept = delete;
protected:
	~Hole() = default;
public:
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Hole& other) const { return this == &other; }
	bool IsEqualTo(const Hole& other) const { return IsIdentical(other); }
	bool IsLessThan(const Hole& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// HoleList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE HoleList : public ListBase<Hole*> {
};

//------------------------------------------------------------------------------
// HoleOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE HoleOwner : public HoleList {
public:
	~HoleOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
