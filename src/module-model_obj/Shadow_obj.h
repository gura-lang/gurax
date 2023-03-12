//==============================================================================
// Shadow_obj.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_SHADOW_OBJ_H
#define GURAX_MODULE_MODEL_OBJ_SHADOW_OBJ_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Shadow_obj
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Shadow_obj : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Shadow_obj);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Shadow_obj");
public:
	// Constructor
	Shadow_obj() {}
	// Copy constructor/operator
	Shadow_obj(const Shadow_obj& src) = delete;
	Shadow_obj& operator=(const Shadow_obj& src) = delete;
	// Move constructor/operator
	Shadow_obj(Shadow_obj&& src) noexcept = delete;
	Shadow_obj& operator=(Shadow_obj&& src) noexcept = delete;
protected:
	~Shadow_obj() = default;
public:
	virtual bool FeedField(const char* field, size_t iParam) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Shadow_obj& other) const { return this == &other; }
	bool IsEqualTo(const Shadow_obj& other) const { return IsIdentical(other); }
	bool IsLessThan(const Shadow_obj& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Shadow_objList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Shadow_objList : public ListBase<Shadow_obj*> {
};

//------------------------------------------------------------------------------
// Shadow_objOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Shadow_objOwner : public Shadow_objList {
public:
	~Shadow_objOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
