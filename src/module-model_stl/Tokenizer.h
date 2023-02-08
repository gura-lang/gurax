//==============================================================================
// Tokenizer.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_STL_TOKENIZER_H
#define GURAX_MODULE_MODEL_STL_TOKENIZER_H
#include <gurax.h>

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Tokenizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tokenizer : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Tokenizer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.stl.Tokenizer");
public:
	// Constructor
	Tokenizer() {}
	// Copy constructor/operator
	Tokenizer(const Tokenizer& src) = delete;
	Tokenizer& operator=(const Tokenizer& src) = delete;
	// Move constructor/operator
	Tokenizer(Tokenizer&& src) noexcept = delete;
	Tokenizer& operator=(Tokenizer&& src) noexcept = delete;
protected:
	~Tokenizer() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Tokenizer& other) const { return this == &other; }
	bool IsEqualTo(const Tokenizer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Tokenizer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(model_stl)

#endif
