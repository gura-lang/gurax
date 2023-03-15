//==============================================================================
// Beval.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_BEVAL_H
#define GURAX_MODULE_MODEL_OBJ_BEVAL_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Beval
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Beval : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Beval);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Beval");
public:
	// Constructor
	Beval() {}
	// Copy constructor/operator
	Beval(const Beval& src) = delete;
	Beval& operator=(const Beval& src) = delete;
	// Move constructor/operator
	Beval(Beval&& src) noexcept = delete;
	Beval& operator=(Beval&& src) noexcept = delete;
protected:
	~Beval() = default;
public:
	virtual const char* GetName() const override { return "Beval"; }
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Beval& other) const { return this == &other; }
	bool IsEqualTo(const Beval& other) const { return IsIdentical(other); }
	bool IsLessThan(const Beval& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// BevalList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE BevalList : public ListBase<Beval*> {
};

//------------------------------------------------------------------------------
// BevalOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE BevalOwner : public BevalList {
public:
	~BevalOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
