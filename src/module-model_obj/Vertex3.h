//==============================================================================
// Vertex3.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VERTEX3_H
#define GURAX_MODULE_MODEL_OBJ_VERTEX3_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Vertex3
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Vertex3 : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Vertex3);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Vertex3");
private:
	Double _x, _y, _z;
public:
	// Constructor
	Vertex3() : _x(0), _y(0), _z(0) {}
	Vertex3(Double x, Double y, Double z) : _x(x), _y(y), _z(z) {}
	// Copy constructor/operator
	Vertex3(const Vertex3& src) = delete;
	Vertex3& operator=(const Vertex3& src) = delete;
	// Move constructor/operator
	Vertex3(Vertex3&& src) noexcept = delete;
	Vertex3& operator=(Vertex3&& src) noexcept = delete;
protected:
	~Vertex3() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Vertex3& other) const { return this == &other; }
	bool IsEqualTo(const Vertex3& other) const { return IsIdentical(other); }
	bool IsLessThan(const Vertex3& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Vertex3List
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Vertex3List : public ListBase<Vertex3*> {
};

//------------------------------------------------------------------------------
// Vertex3Owner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Vertex3Owner : public Vertex3List {
public:
	~Vertex3Owner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
