//==============================================================================
// Spoint.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_SPOINT_H
#define GURAX_MODULE_MODEL_OBJ_SPOINT_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Spoint
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Spoint : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Spoint);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Spoint");
public:
	// Constructor
	Spoint() {}
	// Copy constructor/operator
	Spoint(const Spoint& src) = delete;
	Spoint& operator=(const Spoint& src) = delete;
	// Move constructor/operator
	Spoint(Spoint&& src) noexcept = delete;
	Spoint& operator=(Spoint&& src) noexcept = delete;
protected:
	~Spoint() = default;
public:
	virtual const char* GetName() const override { return "Spoint"; }
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Spoint& other) const { return this == &other; }
	bool IsEqualTo(const Spoint& other) const { return IsIdentical(other); }
	bool IsLessThan(const Spoint& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// SpointList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SpointList : public ListBase<Spoint*> {
};

//------------------------------------------------------------------------------
// SpointOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SpointOwner : public SpointList {
public:
	~SpointOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
