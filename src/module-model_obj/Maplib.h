//==============================================================================
// Maplib.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_MAPLIB_H
#define GURAX_MODULE_MODEL_OBJ_MAPLIB_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Maplib
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Maplib : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Maplib);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Maplib");
public:
	// Constructor
	Maplib() {}
	// Copy constructor/operator
	Maplib(const Maplib& src) = delete;
	Maplib& operator=(const Maplib& src) = delete;
	// Move constructor/operator
	Maplib(Maplib&& src) noexcept = delete;
	Maplib& operator=(Maplib&& src) noexcept = delete;
protected:
	~Maplib() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Maplib& other) const { return this == &other; }
	bool IsEqualTo(const Maplib& other) const { return IsIdentical(other); }
	bool IsLessThan(const Maplib& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// MaplibList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MaplibList : public ListBase<Maplib*> {
};

//------------------------------------------------------------------------------
// MaplibOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MaplibOwner : public MaplibList {
public:
	~MaplibOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
