//==============================================================================
// Parm.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_PARM_H
#define GURAX_MODULE_MODEL_OBJ_PARM_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Parm
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Parm : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Parm);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Parm");
public:
	// Constructor
	Parm() {}
	// Copy constructor/operator
	Parm(const Parm& src) = delete;
	Parm& operator=(const Parm& src) = delete;
	// Move constructor/operator
	Parm(Parm&& src) noexcept = delete;
	Parm& operator=(Parm&& src) noexcept = delete;
protected:
	~Parm() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Parm& other) const { return this == &other; }
	bool IsEqualTo(const Parm& other) const { return IsIdentical(other); }
	bool IsLessThan(const Parm& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ParmList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ParmList : public ListBase<Parm*> {
};

//------------------------------------------------------------------------------
// ParmOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ParmOwner : public ParmList {
public:
	~ParmOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
