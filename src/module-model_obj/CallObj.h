//==============================================================================
// CallObj.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_CALLOBJ_H
#define GURAX_MODULE_MODEL_OBJ_CALLOBJ_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// CallObj
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CallObj : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(CallObj);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.CallObj");
public:
	// Constructor
	CallObj() {}
	// Copy constructor/operator
	CallObj(const CallObj& src) = delete;
	CallObj& operator=(const CallObj& src) = delete;
	// Move constructor/operator
	CallObj(CallObj&& src) noexcept = delete;
	CallObj& operator=(CallObj&& src) noexcept = delete;
protected:
	~CallObj() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const CallObj& other) const { return this == &other; }
	bool IsEqualTo(const CallObj& other) const { return IsIdentical(other); }
	bool IsLessThan(const CallObj& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// CallObjList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CallObjList : public ListBase<CallObj*> {
};

//------------------------------------------------------------------------------
// CallObjOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CallObjOwner : public CallObjList {
public:
	~CallObjOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
