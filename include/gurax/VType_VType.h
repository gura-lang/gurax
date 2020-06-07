//==============================================================================
// VType_VType.h
//==============================================================================
#ifndef GURAX_VTYPE_VTYPE_H
#define GURAX_VTYPE_VTYPE_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_VType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_VType : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_VType VTYPE_VType;

//------------------------------------------------------------------------------
// Value_VType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_VType : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_VType);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_VType");
protected:
	VType* _pVTypeThis;
public:
	static VType& vtype;
public:
	// Constructor
	Value_VType() = delete;
	explicit Value_VType(VType& vtypeThis, VType& vtype = VTYPE_VType) :
		Value_Object(vtype), _pVTypeThis(&vtypeThis) {}
	// Copy constructor/operator
	Value_VType(const Value_VType& src) :
		Value_Object(src), _pVTypeThis(src._pVTypeThis) {}
	Value_VType& operator=(const Value_VType& src) = delete;
	// Move constructor/operator
	Value_VType(Value_VType&& src) = delete;
	Value_VType& operator=(Value_VType&& src) noexcept = delete;
protected:
	// Destructor
	~Value_VType() = default;
public:
	VType& GetVTypeThis() { return *_pVTypeThis; }
	const VType& GetVTypeThis() const { return *_pVTypeThis; }
public:
	static VType& GetVTypeThis(Value& value) {
		return dynamic_cast<Value_VType&>(value).GetVTypeThis();
	}
	static const VType& GetVTypeThis(const Value& value) {
		return dynamic_cast<const Value_VType&>(value).GetVTypeThis();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetVTypeThis().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetVTypeThis().IsEqualTo(dynamic_cast<const Value_VType*>(pValue)->GetVTypeThis());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetVTypeThis().IsLessThan(dynamic_cast<const Value_VType*>(pValue)->GetVTypeThis()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringFormatter(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
public:
	// Virtual functions for runtime process
	virtual HelpHolder* GetHelpHolder() const override { return &_pVTypeThis->GetHelpHolder(); }
	virtual void PresentHelp(Processor& processor, const Symbol* pLangCode) const override;
	virtual bool IsVType() const override { return true; }
	virtual bool CanBeCallableMember() const override { return !GetVTypeThis().GetConstructor().IsEmpty(); }
	virtual bool CanEvalAsMethod(const Function& function) const override;
	virtual void GatherMemberSymbol(SymbolList& symbolList) const override {
		GetVTypeThis().GatherMemberSymbol(symbolList);
	}
	virtual const DeclCallable* GetDeclCallableWithError() override;
	virtual const DeclCallable* GetDeclCallable() override;
	virtual void DoCall(Processor& processor, Argument& argument) override;
	virtual Value* DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag) override;
	virtual bool DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr) override;
	virtual bool DoAssignCustomMethod(RefPtr<Function> pFunction) override;
};

}

#endif
