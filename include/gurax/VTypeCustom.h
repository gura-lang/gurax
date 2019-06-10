//==============================================================================
// VTypeCustom.h
//==============================================================================
#ifndef GURAX_VTYPECUSTOM_H
#define GURAX_VTYPECUSTOM_H
#include "Value.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VTypeCustom
//------------------------------------------------------------------------------
class VTypeCustom : public VType {
public:
	class Constructor : public Function {
	protected:
		VTypeCustom& _vtypeCustom;
		RefPtr<Function> _pFuncInitializer;
	public:
		Constructor(VTypeCustom& vtypeCustom, Function* pFuncInitializer);
	public:
		VTypeCustom& GetVTypeCustom() const { return _vtypeCustom; }
		const Function& GetFuncInitializer() const { return *_pFuncInitializer; }
	public:
		// Virtual functions of Function
		virtual Value* DoEval(Processor& processor, Argument& argument) const override;
		virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
	};
private:
	size_t _nProps;
	RefPtr<ValueOwner> _pValuesPropInit;
public:
	VTypeCustom() : VType(Symbol::Empty), _nProps(0), _pValuesPropInit(new ValueOwner()) {}
public:
	size_t AddProp() { return _nProps++; }
	size_t CountProps() const { return _nProps; }
	void AssignFunction(Function* pFunction);
	void AssignPropHandler(Frame& frame, const Symbol* pSymbol, bool listVarFlag,
						   const Attribute& attr, RefPtr<Value> pValueInit);
public:
	virtual Value* DoCastFrom(const Value& value) const override;
};

//------------------------------------------------------------------------------
// ValueCustom
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueCustom : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueCustom);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ValueCustom");
protected:
	RefPtr<ValueOwner> _pValuesProp;
public:
	// Constructor
	explicit ValueCustom(VTypeCustom& vtypeCustom) :
		Value_Object(vtypeCustom),
		_pValuesProp(new ValueOwner(vtypeCustom.CountProps(), Value::nil(vtypeCustom.CountProps()))) {}
	// Copy constructor/operator
	ValueCustom(const ValueCustom& src) = delete;
	ValueCustom& operator=(const ValueCustom& src) = delete;
	// Move constructor/operator
	ValueCustom(ValueCustom&& src) = delete;
	ValueCustom& operator=(ValueCustom&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~ValueCustom() = default;
public:
	void SetCustomProp(size_t iProp, Value* pValue);
	Value* GetCustomProp(size_t iProp) { return (*_pValuesProp)[iProp]->Reference(); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value* pValue) const override { return IsSameType(pValue); }
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)? false : GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDigest(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
};

}

#endif
