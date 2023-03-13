//==============================================================================
// Vertex4.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VERTEX4_H
#define GURAX_MODULE_MODEL_OBJ_VERTEX4_H
#include <gurax.h>
#include "Data.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Vertex4
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Vertex4 : public Referable, public Data {
public:
	// Referable declaration
	Gurax_DeclareReferable(Vertex4);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Vertex4");
private:
	Double _x, _y, _z, _w;
public:
	// Constructor
	Vertex4() : _x(0), _y(0), _z(0), _w(0) {}
	Vertex4(Double x, Double y, Double z, Double w) : _x(x), _y(y), _z(z), _w(w) {}
	// Copy constructor/operator
	Vertex4(const Vertex4& src) = delete;
	Vertex4& operator=(const Vertex4& src) = delete;
	// Move constructor/operator
	Vertex4(Vertex4&& src) noexcept = delete;
	Vertex4& operator=(Vertex4&& src) noexcept = delete;
protected:
	~Vertex4() = default;
public:
	virtual bool FeedField(const Tokenizer& tokenizer, size_t iParam) override;
	virtual bool FinishField(const Tokenizer& tokenizer, size_t nParams) override;
public:
	Double GetX() const { return _x; }
	Double GetY() const { return _y; }
	Double GetZ() const { return _z; }
	Double GetW() const { return _w; }
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
