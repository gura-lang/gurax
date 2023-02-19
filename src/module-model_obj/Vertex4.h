//==============================================================================
// Vertex4.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VERTEX4_H
#define GURAX_MODULE_MODEL_OBJ_VERTEX4_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Vertex4
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Vertex4 : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Vertex4);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Vertex4");
public:
	// Constructor
	Vertex4() {}
	// Copy constructor/operator
	Vertex4(const Vertex4& src) = delete;
	Vertex4& operator=(const Vertex4& src) = delete;
	// Move constructor/operator
	Vertex4(Vertex4&& src) noexcept = delete;
	Vertex4& operator=(Vertex4&& src) noexcept = delete;
protected:
	~Vertex4() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Vertex4& other) const { return this == &other; }
	bool IsEqualTo(const Vertex4& other) const { return IsIdentical(other); }
	bool IsLessThan(const Vertex4& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Vertex4List
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Vertex4List : public ListBase<Vertex4*> {
};

//------------------------------------------------------------------------------
// Vertex4Owner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Vertex4Owner : public Vertex4List {
public:
	~Vertex4Owner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
