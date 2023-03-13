//==============================================================================
// Connect.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_CONNECT_H
#define GURAX_MODULE_MODEL_OBJ_CONNECT_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Connect
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Connect : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Connect);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Connect");
public:
	// Constructor
	Connect() {}
	// Copy constructor/operator
	Connect(const Connect& src) = delete;
	Connect& operator=(const Connect& src) = delete;
	// Move constructor/operator
	Connect(Connect&& src) noexcept = delete;
	Connect& operator=(Connect&& src) noexcept = delete;
protected:
	~Connect() = default;
public:
	virtual bool FeedField(const char* field, size_t iParam) override;
	virtual bool FinishField(size_t nParams) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Connect& other) const { return this == &other; }
	bool IsEqualTo(const Connect& other) const { return IsIdentical(other); }
	bool IsLessThan(const Connect& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ConnectList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ConnectList : public ListBase<Connect*> {
};

//------------------------------------------------------------------------------
// ConnectOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ConnectOwner : public ConnectList {
public:
	~ConnectOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
