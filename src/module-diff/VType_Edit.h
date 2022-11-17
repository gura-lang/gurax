//==============================================================================
// VType_Edit.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_VTYPE_Edit_H
#define GURAX_MODULE_DIFF_VTYPE_Edit_H
#include <gurax.h>
#include "Diff.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// VType_Edit
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Edit : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Edit VTYPE_Edit;

//------------------------------------------------------------------------------
// Value_Edit
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Edit : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Edit);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Edit");
protected:
	RefPtr<Diff> _pDiff;
	size_t _iSesElem;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Edit() = delete;
	Value_Edit(Diff* pDiff, size_t iSesElem, VType& vtype = VTYPE_Edit) :
		Value_Object(vtype), _pDiff(pDiff), _iSesElem(iSesElem) {}
	// Copy constructor/operator
	Value_Edit(const Value_Edit& src) :
		Value_Object(src), _pDiff(src._pDiff->Reference()), _iSesElem(src._iSesElem) {}
	Value_Edit& operator=(const Value_Edit& src) = delete;
	// Move constructor/operator
	Value_Edit(Value_Edit&& src) noexcept = delete;
	Value_Edit& operator=(Value_Edit&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Edit() = default;
public:
	const Diff::SesElem& GetSesElem() const { return _pDiff->GetSesElems()[_iSesElem]; }
public:
	static const Diff::SesElem& GetSesElem(const Value& value) {
		return dynamic_cast<const Value_Edit&>(value).GetSesElem();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
};

//-----------------------------------------------------------------------------
// Iterator_Edit
//-----------------------------------------------------------------------------
class Iterator_Edit : public Iterator {
private:
	RefPtr<Diff> _pDiff;
	size_t _iSesElemBegin;
	size_t _iSesElemEnd;
	size_t _iSesElem;
public:
	Iterator_Edit(Diff* pDiff, size_t iSesElemBegin, size_t iSesElemEnd);
	Iterator_Edit(Diff* pDiff);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenDetermined;
	}
	virtual size_t GetLength() const override { return _iSesElemEnd - _iSesElemBegin; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(diff)

#endif
