//==============================================================================
// Usemtl.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_USEMTL_H
#define GURAX_MODULE_MODEL_OBJ_USEMTL_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Usemtl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Usemtl : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Usemtl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Usemtl");
private:
	String _materialName;
public:
	// Constructor
	Usemtl() {}
	// Copy constructor/operator
	Usemtl(const Usemtl& src) = delete;
	Usemtl& operator=(const Usemtl& src) = delete;
	// Move constructor/operator
	Usemtl(Usemtl&& src) noexcept = delete;
	Usemtl& operator=(Usemtl&& src) noexcept = delete;
protected:
	~Usemtl() = default;
public:
	virtual const char* GetName() const override { return "Usemtl"; }
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Usemtl& other) const { return this == &other; }
	bool IsEqualTo(const Usemtl& other) const { return IsIdentical(other); }
	bool IsLessThan(const Usemtl& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// UsemtlList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE UsemtlList : public ListBase<Usemtl*> {
};

//------------------------------------------------------------------------------
// UsemtlOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE UsemtlOwner : public UsemtlList {
public:
	~UsemtlOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
