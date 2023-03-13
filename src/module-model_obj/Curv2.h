//==============================================================================
// Curv2.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_CURV2_H
#define GURAX_MODULE_MODEL_OBJ_CURV2_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Curv2
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Curv2 : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Curv2);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Curv2");
public:
	// Constructor
	Curv2() {}
	// Copy constructor/operator
	Curv2(const Curv2& src) = delete;
	Curv2& operator=(const Curv2& src) = delete;
	// Move constructor/operator
	Curv2(Curv2&& src) noexcept = delete;
	Curv2& operator=(Curv2&& src) noexcept = delete;
protected:
	~Curv2() = default;
public:
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Curv2& other) const { return this == &other; }
	bool IsEqualTo(const Curv2& other) const { return IsIdentical(other); }
	bool IsLessThan(const Curv2& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Curv2List
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Curv2List : public ListBase<Curv2*> {
};

//------------------------------------------------------------------------------
// Curv2Owner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Curv2Owner : public Curv2List {
public:
	~Curv2Owner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
