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
	class ConstructorDefault : public Function {
	protected:
		VTypeCustom& _vtypeCustom;
	public:
		ConstructorDefault(VTypeCustom& vtypeCustom, const Symbol* pSymbol);
	public:
		VTypeCustom& GetVTypeCustom() const { return _vtypeCustom; }
	public:
		// Virtual functions of Function
		virtual Value* DoEval(Processor& processor, Argument& argument) const override;
		virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override;
	};
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
	RefPtr<ValueOwner> _pValuesPropInit;
	RefPtr<Function> _pDestructor;
public:
	VTypeCustom();
public:
	void SetDestructor(Function* pDestructor) { _pDestructor.reset(pDestructor); }
	const Function& GetDestructor() const { return *_pDestructor; }
	ValueOwner& GetValuesPropInit() { return *_pValuesPropInit; }
	const ValueOwner& GetValuesPropInit() const { return *_pValuesPropInit; }
	bool AssignFunction(Function* pFunction);
	bool AssignPropHandler(Frame& frame, const Symbol* pSymbol, const DottedSymbol& dottedSymbol,
						   PropHandler::Flags flags, RefPtr<Value> pValueInit);
public:
	virtual void PrepareForAssignment(const Symbol* pSymbol) override;
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
		Value_Object(vtypeCustom), _pValuesProp(new ValueOwner()) {}
	// Copy constructor/operator
	ValueCustom(const ValueCustom& src) = delete;
	ValueCustom& operator=(const ValueCustom& src) = delete;
	// Move constructor/operator
	ValueCustom(ValueCustom&& src) = delete;
	ValueCustom& operator=(ValueCustom&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~ValueCustom();
public:
	VTypeCustom& GetVType() { return dynamic_cast<VTypeCustom&>(Value_Object::GetVType()); }
	const VTypeCustom& GetVType() const { return dynamic_cast<const VTypeCustom&>(Value_Object::GetVType()); }
	bool InitCustomProp();
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
