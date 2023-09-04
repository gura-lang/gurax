//==============================================================================
// Referencer.h
//==============================================================================
#ifndef GURAX_REFERENCER_H
#define GURAX_REFERENCER_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Referencer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Referencer : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Referencer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Referencer");
private:
	RefPtr<Frame> _pFrame;
	const Symbol* _pSymbol;
	RefPtr<Value> _pValue;
public:
	// Constructor
	Referencer(Frame* pFrame, const Symbol* pSymbol, Value* pValue);
	// Copy constructor/operator
	Referencer(const Referencer& src) = delete;
	Referencer& operator=(const Referencer& src) = delete;
	// Move constructor/operator
	Referencer(Referencer&& src) noexcept = delete;
	Referencer& operator=(Referencer&& src) noexcept = delete;
protected:
	~Referencer() = default;
public:
	Frame& GetFrame() { return *_pFrame; }
	const Frame& GetFrame() const { return *_pFrame; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	void SetValue(Value* pValue);
	Value& GetValue() { return *_pValue; }
	const Value& GetValue() const { return *_pValue; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Referencer& other) const { return this == &other; }
	bool IsEqualTo(const Referencer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Referencer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ReferencerList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ReferencerList : public ListBase<Referencer*> {
};

//------------------------------------------------------------------------------
// ReferencerOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ReferencerOwner : public ReferencerList {
public:
	~ReferencerOwner() { Clear(); }
	void Clear();
};

}

#endif
