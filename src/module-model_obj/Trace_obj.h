//==============================================================================
// Trace_obj.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_TRACE_OBJ_H
#define GURAX_MODULE_MODEL_OBJ_TRACE_OBJ_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Trace_obj
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Trace_obj : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Trace_obj);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Trace_obj");
public:
	// Constructor
	Trace_obj() {}
	// Copy constructor/operator
	Trace_obj(const Trace_obj& src) = delete;
	Trace_obj& operator=(const Trace_obj& src) = delete;
	// Move constructor/operator
	Trace_obj(Trace_obj&& src) noexcept = delete;
	Trace_obj& operator=(Trace_obj&& src) noexcept = delete;
protected:
	~Trace_obj() = default;
public:
	virtual const char* GetName() const override { return "Trace_obj"; }
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Trace_obj& other) const { return this == &other; }
	bool IsEqualTo(const Trace_obj& other) const { return IsIdentical(other); }
	bool IsLessThan(const Trace_obj& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Trace_objList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Trace_objList : public ListBase<Trace_obj*> {
};

//------------------------------------------------------------------------------
// Trace_objOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Trace_objOwner : public Trace_objList {
public:
	~Trace_objOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
