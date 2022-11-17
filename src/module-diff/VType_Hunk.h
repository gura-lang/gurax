//==============================================================================
// VType_Hunk.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_VTYPE_Hunk_H
#define GURAX_MODULE_DIFF_VTYPE_Hunk_H
#include <gurax.h>
#include "Hunk.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// VType_Hunk
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Hunk : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Hunk VTYPE_Hunk;

//------------------------------------------------------------------------------
// Value_Hunk
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Hunk : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Hunk);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Hunk");
protected:
	RefPtr<Hunk> _pHunk;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Hunk() = delete;
	explicit Value_Hunk(Hunk* pHunk, VType& vtype = VTYPE_Hunk) :
		Value_Object(vtype), _pHunk(pHunk) {}
	// Copy constructor/operator
	Value_Hunk(const Value_Hunk& src) :
		Value_Object(src), _pHunk(src._pHunk->Reference()) {}
	Value_Hunk& operator=(const Value_Hunk& src) = delete;
	// Move constructor/operator
	Value_Hunk(Value_Hunk&& src) noexcept = delete;
	Value_Hunk& operator=(Value_Hunk&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Hunk() = default;
public:
	const Hunk& GetHunk() const { return *_pHunk; }
public:
	static const Hunk& GetHunk(const Value& value) {
		return dynamic_cast<const Value_Hunk&>(value).GetHunk();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
};

//-----------------------------------------------------------------------------
// Iterator_Hunk
//-----------------------------------------------------------------------------
class Iterator_Hunk : public Iterator {
private:
	Hunk::Picker _picker;
public:
	Iterator_Hunk(Diff* pDiff, size_t nLinesCommon);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(diff)

#endif
