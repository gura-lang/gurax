//==============================================================================
// Mtllib.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_MTLLIB_H
#define GURAX_MODULE_MODEL_OBJ_MTLLIB_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Mtllib
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Mtllib : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Mtllib);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Mtllib");
public:
	// Constructor
	Mtllib() {}
	// Copy constructor/operator
	Mtllib(const Mtllib& src) = delete;
	Mtllib& operator=(const Mtllib& src) = delete;
	// Move constructor/operator
	Mtllib(Mtllib&& src) noexcept = delete;
	Mtllib& operator=(Mtllib&& src) noexcept = delete;
protected:
	~Mtllib() = default;
public:
	virtual bool FeedField(const char* field, size_t iParam) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Mtllib& other) const { return this == &other; }
	bool IsEqualTo(const Mtllib& other) const { return IsIdentical(other); }
	bool IsLessThan(const Mtllib& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// MtllibList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MtllibList : public ListBase<Mtllib*> {
};

//------------------------------------------------------------------------------
// MtllibOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MtllibOwner : public MtllibList {
public:
	~MtllibOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif