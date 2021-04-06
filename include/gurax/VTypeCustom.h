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
class GURAX_DLLDECLARE VTypeCustom : public VType {
public:
	class ConstructorClass : public Function {
	protected:
		VTypeCustom& _vtypeCustom;
		RefPtr<Expr_Block> _pExprBody;
		const PUnit* _pPUnitBody;
		RefPtr<Function> _pConstructorInh;	// this may be nullptr
	public:
		ConstructorClass(VTypeCustom& vtypeCustom, DeclCallable* pDeclCallable, Expr_Block* pExprBody, Function* pConstructorInh);
	public:
		VTypeCustom& GetVTypeCustom() const { return _vtypeCustom; }
	public:
		// Virtual functions of Function
		virtual const Expr_Block& GetExprBody() const override { return *_pExprBody; }
		virtual const PUnit* GetPUnitBody() const override { return _pPUnitBody; }
		virtual Value* DoEval(Processor& processor, Argument& argument) const override;
		virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
	};
	class ConstructorStruct : public Function {
	protected:
		VTypeCustom& _vtypeCustom;
		RefPtr<PropSlotOwner> _pPropSlotOwner;
	public:
		ConstructorStruct(VTypeCustom& vtypeCustom, DeclCallable* pDeclCallable, PropSlotOwner* pPropSlotOwner);
	public:
		VTypeCustom& GetVTypeCustom() const { return _vtypeCustom; }
		const PropSlotOwner& GetPropSlotOwner() const { return *_pPropSlotOwner; }
	public:
		// Virtual functions of Function
		virtual Value* DoEval(Processor& processor, Argument& argument) const override;
		virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
	};
private:
	RefPtr<ValueOwner> _pValuesPropInit;
	RefPtr<ValueOwner> _pValuesPropOfClass;
	RefPtr<Function> _pDestructor;
public:
	VTypeCustom();
public:
	void Inherit();
	void SetConstructor(Function* pConstructor) { _pConstructor.reset(pConstructor); }
	void SetDestructor(Function* pDestructor) { _pDestructor.reset(pDestructor); }
	const Function& GetDestructor() const { return *_pDestructor; }
	ValueOwner& GetValuesPropInit() { return *_pValuesPropInit; }
	const ValueOwner& GetValuesPropInit() const { return *_pValuesPropInit; }
	ValueOwner& GetValuesPropOfClass() { return *_pValuesPropOfClass; }
	const ValueOwner& GetValuesPropOfClass() const { return *_pValuesPropOfClass; }
	bool AssignPropSlot(Frame& frame, const Symbol* pSymbol, VType* pVType,
						   PropSlot::Flags flags, RefPtr<Value> pValueInit);
	bool AssignPropSlot(Frame& frame, const Symbol* pSymbol, const DottedSymbol& dottedSymbol,
						   PropSlot::Flags flags, RefPtr<Value> pValueInit);
	void SetCustomPropOfClass(size_t iProp, Value* pValue);
	Value* GetCustomPropOfClass(size_t iProp) { return GetValuesPropOfClass()[iProp]->Reference(); }
public:
	virtual bool IsCustom() const override { return true; }
	virtual void PrepareForAssignment(Processor& processor, const Symbol* pSymbol) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
	virtual bool DoAssignCustomMethod(RefPtr<Function> pFunction) override;
};

#if 0
//------------------------------------------------------------------------------
// ValueCustom
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueCustom : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueCustom);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ValueCustom");
public:
	// Constructor
	ValueCustom(VType& vtype) : Value_Object(vtype) {}
	// Copy constructor/operator
	ValueCustom(const ValueCustom& src) = delete;
	ValueCustom& operator=(const ValueCustom& src) = delete;
	// Move constructor/operator
	ValueCustom(ValueCustom&& src) = delete;
	ValueCustom& operator=(ValueCustom&& src) noexcept = delete;
protected:
	// Destructor
	~ValueCustom() = default;
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override { return IsSameType(value); }
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)? false : GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};
#endif

}

#endif
