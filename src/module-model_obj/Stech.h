//==============================================================================
// Stech.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_STECH_H
#define GURAX_MODULE_MODEL_OBJ_STECH_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Stech
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stech : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Stech);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Stech");
public:
	// Constructor
	Stech() {}
	// Copy constructor/operator
	Stech(const Stech& src) = delete;
	Stech& operator=(const Stech& src) = delete;
	// Move constructor/operator
	Stech(Stech&& src) noexcept = delete;
	Stech& operator=(Stech&& src) noexcept = delete;
protected:
	~Stech() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Stech& other) const { return this == &other; }
	bool IsEqualTo(const Stech& other) const { return IsIdentical(other); }
	bool IsLessThan(const Stech& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// StechList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StechList : public ListBase<Stech*> {
};

//------------------------------------------------------------------------------
// StechOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StechOwner : public StechList {
public:
	~StechOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
