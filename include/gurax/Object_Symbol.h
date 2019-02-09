//==============================================================================
// Value_Symbol.h
//==============================================================================
#ifndef GURAX_OBJECT_SYMBOL_H
#define GURAX_OBJECT_SYMBOL_H
#include "Value_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Symbol
//------------------------------------------------------------------------------
class VType_Symbol : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Symbol VTYPE_Symbol;

//------------------------------------------------------------------------------
// Value_Symbol
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Symbol : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Symbol);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Symbol");
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	explicit Value_Symbol(VType& vtype = VTYPE_Symbol) = delete;
	explicit Value_Symbol(const Symbol* pSymbol, VType& vtype = VTYPE_Symbol) :
		Value_Object(vtype), _pSymbol(pSymbol) {}
	// Copy constructor/operator
	Value_Symbol(const Value_Symbol& src) :
		Value_Object(src), _pSymbol(src._pSymbol) {}
	Value_Symbol& operator=(const Value_Symbol& src) = delete;
	// Move constructor/operator
	Value_Symbol(Value_Symbol&& src) = delete;
	Value_Symbol& operator=(Value_Symbol&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Symbol() = default;
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSymbol()->CalcHash();
	}
	virtual bool IsEqualTo(const Object* pValue) const override {
		return IsSameType(pValue) &&
			GetSymbol()->IsEqualTo(dynamic_cast<const Value_Symbol*>(pValue)->GetSymbol());
	}
	virtual bool IsLessThan(const Object* pValue) const override {
		return IsSameType(pValue)?
			GetSymbol()->IsLessThan_UniqId(dynamic_cast<const Value_Symbol*>(pValue)->GetSymbol()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return String("`").append(_pSymbol->GetName());
	}
};

}

#endif
