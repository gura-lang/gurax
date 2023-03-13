//==============================================================================
// ObjectName.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_OBJECTNAME_H
#define GURAX_MODULE_MODEL_OBJ_OBJECTNAME_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// ObjectName
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectName : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(ObjectName);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.ObjectName");
public:
	// Constructor
	ObjectName() {}
	// Copy constructor/operator
	ObjectName(const ObjectName& src) = delete;
	ObjectName& operator=(const ObjectName& src) = delete;
	// Move constructor/operator
	ObjectName(ObjectName&& src) noexcept = delete;
	ObjectName& operator=(ObjectName&& src) noexcept = delete;
protected:
	~ObjectName() = default;
public:
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ObjectName& other) const { return this == &other; }
	bool IsEqualTo(const ObjectName& other) const { return IsIdentical(other); }
	bool IsLessThan(const ObjectName& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ObjectNameList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectNameList : public ListBase<ObjectName*> {
};

//------------------------------------------------------------------------------
// ObjectNameOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ObjectNameOwner : public ObjectNameList {
public:
	~ObjectNameOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
