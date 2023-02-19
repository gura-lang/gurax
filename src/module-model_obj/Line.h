//==============================================================================
// Line.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_LINE_H
#define GURAX_MODULE_MODEL_OBJ_LINE_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Line
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Line : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Line);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Line");
public:
	// Constructor
	Line() {}
	// Copy constructor/operator
	Line(const Line& src) = delete;
	Line& operator=(const Line& src) = delete;
	// Move constructor/operator
	Line(Line&& src) noexcept = delete;
	Line& operator=(Line&& src) noexcept = delete;
protected:
	~Line() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Line& other) const { return this == &other; }
	bool IsEqualTo(const Line& other) const { return IsIdentical(other); }
	bool IsLessThan(const Line& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// LineList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LineList : public ListBase<Line*> {
};

//------------------------------------------------------------------------------
// LineOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LineOwner : public LineList {
public:
	~LineOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(model_obj)

#endif
