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
	class ConstructorClass : public Constructor {
	protected:
		VTypeCustom& _vtypeCustom;
		RefPtr<Expr_Block> _pExprBody;
		const PUnit* _pPUnitBody;
	public:
		ConstructorClass(VTypeCustom& vtypeCustom, DeclCallable* pDeclCallable, Expr_Block* pExprBody);
	public:
		VTypeCustom& GetVTypeCustom() const { return _vtypeCustom; }
	public:
		// Virtual functions of Function
		virtual const Expr_Block& GetExprBody() const override { return *_pExprBody; }
		virtual const PUnit* GetPUnitBody() const override { return _pPUnitBody; }
		virtual Value* DoEval(Processor& processor, Argument& argument) const override;
		virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
	};
	class ConstructorClassDefault : public Constructor {
	protected:
		VTypeCustom& _vtypeCustom;
	public:
		ConstructorClassDefault(VTypeCustom& vtypeCustom, DeclCallable* pDeclCallable);
	public:
		VTypeCustom& GetVTypeCustom() const { return _vtypeCustom; }
	public:
		// Virtual functions of Function
		virtual Value* DoEval(Processor& processor, Argument& argument) const override;
		virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
	};
	class ConstructorStruct : public Constructor {
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
	RefPtr<ValueOwner> _pValuesPropOfInstInit;
	RefPtr<ValueOwner> _pValuesPropOfClass;
	RefPtr<Function> _pDestructor;
	RefPtr<Function> _pCastFunction;
public:
	VTypeCustom();
public:
	void Inherit();
	void SetConstructor(Constructor* pConstructor) { _pConstructor.reset(pConstructor); }
	void SetDestructor(Function* pDestructor) { _pDestructor.reset(pDestructor); }
	void SetCastFunction(Function* pCastFunction) { _pCastFunction.reset(pCastFunction); }
	const Function& GetDestructor() const { return *_pDestructor; }
	const Function& GetCastFunction() const { return *_pCastFunction; }
	ValueOwner& GetValuesPropOfInstInit() { return *_pValuesPropOfInstInit; }
	const ValueOwner& GetValuesPropOfInstInit() const { return *_pValuesPropOfInstInit; }
	ValueOwner& GetValuesPropOfClass() { return *_pValuesPropOfClass; }
	const ValueOwner& GetValuesPropOfClass() const { return *_pValuesPropOfClass; }
	bool AssignPropSlot(Processor& processor, const Symbol* pSymbol, VType* pVType,
						   PropSlot::Flags flags, RefPtr<Value> pValueInit);
	bool AssignPropSlot(Processor& processor, const Symbol* pSymbol, const DottedSymbol& dottedSymbol,
						   PropSlot::Flags flags, RefPtr<Value> pValueInit);
	void SetCustomPropOfClass(size_t iProp, Value* pValue);
	Value* GetCustomPropOfClass(size_t iProp) { return GetValuesPropOfClass()[iProp]->Reference(); }
public:
	virtual bool IsCustom() const override { return true; }
	virtual void PrepareForAssignment(Processor& processor, const Symbol* pSymbol) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
	virtual bool DoAssignCustomMethod(RefPtr<Function> pFunction) override;
};

}

#endif
