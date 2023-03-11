//==============================================================================
// Step.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_STEP_H
#define GURAX_MODULE_MODEL_OBJ_STEP_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Step
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Step : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Step);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Step");
public:
	// Constructor
	Step() {}
	// Copy constructor/operator
	Step(const Step& src) = delete;
	Step& operator=(const Step& src) = delete;
	// Move constructor/operator
	Step(Step&& src) noexcept = delete;
	Step& operator=(Step&& src) noexcept = delete;
protected:
	~Step() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Step& other) const { return this == &other; }
	bool IsEqualTo(const Step& other) const { return IsIdentical(other); }
	bool IsLessThan(const Step& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// StepList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StepList : public ListBase<Step*> {
};

//------------------------------------------------------------------------------
// StepOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StepOwner : public StepList {
public:
	~StepOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
