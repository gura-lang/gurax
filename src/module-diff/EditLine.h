//==============================================================================
// EditLine.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_EDITLINE_H
#define GURAX_MODULE_DIFF_EDITLINE_H
#include <gurax.h>

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// EditLine
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE EditLine : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(EditLine);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("diff.EditLine");
public:
	// Constructor
	EditLine() {}
	// Copy constructor/operator
	EditLine(const EditLine& src) = delete;
	EditLine& operator=(const EditLine& src) = delete;
	// Move constructor/operator
	EditLine(EditLine&& src) noexcept = delete;
	EditLine& operator=(EditLine&& src) noexcept = delete;
protected:
	~EditLine() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const EditLine& other) const { return this == &other; }
	bool IsEqualTo(const EditLine& other) const { return IsIdentical(other); }
	bool IsLessThan(const EditLine& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(diff)

#endif
