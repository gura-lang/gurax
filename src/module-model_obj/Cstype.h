//==============================================================================
// Cstype.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_CSTYPE_H
#define GURAX_MODULE_MODEL_OBJ_CSTYPE_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Cstype
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Cstype : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Cstype);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Cstype");
public:
	// Constructor
	Cstype() {}
	// Copy constructor/operator
	Cstype(const Cstype& src) = delete;
	Cstype& operator=(const Cstype& src) = delete;
	// Move constructor/operator
	Cstype(Cstype&& src) noexcept = delete;
	Cstype& operator=(Cstype&& src) noexcept = delete;
protected:
	~Cstype() = default;
public:
	virtual const char* GetName() const override { return "Cstype"; }
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Cstype& other) const { return this == &other; }
	bool IsEqualTo(const Cstype& other) const { return IsIdentical(other); }
	bool IsLessThan(const Cstype& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// CstypeList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CstypeList : public ListBase<Cstype*> {
};

//------------------------------------------------------------------------------
// CstypeOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CstypeOwner : public CstypeList {
public:
	~CstypeOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
