//==============================================================================
// Ctech.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_CTECH_H
#define GURAX_MODULE_MODEL_OBJ_CTECH_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Ctech
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Ctech : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Ctech);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Ctech");
public:
	// Constructor
	Ctech() {}
	// Copy constructor/operator
	Ctech(const Ctech& src) = delete;
	Ctech& operator=(const Ctech& src) = delete;
	// Move constructor/operator
	Ctech(Ctech&& src) noexcept = delete;
	Ctech& operator=(Ctech&& src) noexcept = delete;
protected:
	~Ctech() = default;
public:
	virtual const char* GetName() const override { return "Ctech"; }
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Ctech& other) const { return this == &other; }
	bool IsEqualTo(const Ctech& other) const { return IsIdentical(other); }
	bool IsLessThan(const Ctech& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// CtechList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CtechList : public ListBase<Ctech*> {
};

//------------------------------------------------------------------------------
// CtechOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CtechOwner : public CtechList {
public:
	~CtechOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
