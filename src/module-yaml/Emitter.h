//==============================================================================
// Emitter.h
//==============================================================================
#ifndef GURAX_MODULE_YAML_EMITTER_H
#define GURAX_MODULE_YAML_EMITTER_H
#include <gurax.h>

Gurax_BeginModuleScope(yaml)

//------------------------------------------------------------------------------
// Emitter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Emitter : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Emitter);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("yaml.Emitter");
public:
	// Constructor
	Emitter() {}
	// Copy constructor/operator
	Emitter(const Emitter& src) = delete;
	Emitter& operator=(const Emitter& src) = delete;
	// Move constructor/operator
	Emitter(Emitter&& src) noexcept = delete;
	Emitter& operator=(Emitter&& src) noexcept = delete;
protected:
	~Emitter() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Emitter& other) const { return this == &other; }
	bool IsEqualTo(const Emitter& other) const { return IsIdentical(other); }
	bool IsLessThan(const Emitter& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(yaml)

#endif
