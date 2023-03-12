//==============================================================================
// Usemap.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_USEMAP_H
#define GURAX_MODULE_MODEL_OBJ_USEMAP_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Usemap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Usemap : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Usemap);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Usemap");
public:
	// Constructor
	Usemap() {}
	// Copy constructor/operator
	Usemap(const Usemap& src) = delete;
	Usemap& operator=(const Usemap& src) = delete;
	// Move constructor/operator
	Usemap(Usemap&& src) noexcept = delete;
	Usemap& operator=(Usemap&& src) noexcept = delete;
protected:
	~Usemap() = default;
public:
	virtual bool FeedField(const char* field, size_t iParam) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Usemap& other) const { return this == &other; }
	bool IsEqualTo(const Usemap& other) const { return IsIdentical(other); }
	bool IsLessThan(const Usemap& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// UsemapList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE UsemapList : public ListBase<Usemap*> {
};

//------------------------------------------------------------------------------
// UsemapOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE UsemapOwner : public UsemapList {
public:
	~UsemapOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
