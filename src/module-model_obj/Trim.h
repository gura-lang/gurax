//==============================================================================
// Trim.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_TRIM_H
#define GURAX_MODULE_MODEL_OBJ_TRIM_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Trim
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Trim : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Trim);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Trim");
public:
	// Constructor
	Trim() {}
	// Copy constructor/operator
	Trim(const Trim& src) = delete;
	Trim& operator=(const Trim& src) = delete;
	// Move constructor/operator
	Trim(Trim&& src) noexcept = delete;
	Trim& operator=(Trim&& src) noexcept = delete;
protected:
	~Trim() = default;
public:
	virtual bool FeedField(const char* field, size_t iParam) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Trim& other) const { return this == &other; }
	bool IsEqualTo(const Trim& other) const { return IsIdentical(other); }
	bool IsLessThan(const Trim& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// TrimList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TrimList : public ListBase<Trim*> {
};

//------------------------------------------------------------------------------
// TrimOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TrimOwner : public TrimList {
public:
	~TrimOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
