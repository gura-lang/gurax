//==============================================================================
// Csh.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_CSH_H
#define GURAX_MODULE_MODEL_OBJ_CSH_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Csh
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Csh : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Csh);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Csh");
public:
	// Constructor
	Csh() {}
	// Copy constructor/operator
	Csh(const Csh& src) = delete;
	Csh& operator=(const Csh& src) = delete;
	// Move constructor/operator
	Csh(Csh&& src) noexcept = delete;
	Csh& operator=(Csh&& src) noexcept = delete;
protected:
	~Csh() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Csh& other) const { return this == &other; }
	bool IsEqualTo(const Csh& other) const { return IsIdentical(other); }
	bool IsLessThan(const Csh& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// CshList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CshList : public ListBase<Csh*> {
};

//------------------------------------------------------------------------------
// CshOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CshOwner : public CshList {
public:
	~CshOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
