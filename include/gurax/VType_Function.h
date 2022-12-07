//==============================================================================
// VType_Function.h
//==============================================================================
#ifndef GURAX_VTYPE_FUNCTION_H
#define GURAX_VTYPE_FUNCTION_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Function
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Function : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Function VTYPE_Function;

//------------------------------------------------------------------------------
// Value_Function
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Function : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Function);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Function");
public:
	class GURAX_DLLDECLARE GatherCriteria_Statement : public Frame::GatherCriteria {
	public:
		virtual bool IsEligible(const Value& value) const override {
			return value.IsType(VTYPE_Function) && dynamic_cast<const Value_Function&>(value).GetFunction().IsTypeStatement();
		}
	};
	class GURAX_DLLDECLARE GatherCriteria_Function : public Frame::GatherCriteria {
	public:
		virtual bool IsEligible(const Value& value) const override {
			return value.IsType(VTYPE_Function) && dynamic_cast<const Value_Function&>(value).GetFunction().IsTypeFunction();
		}
	};
	class GURAX_DLLDECLARE GatherCriteria_Method : public Frame::GatherCriteria {
	public:
		virtual bool IsEligible(const Value& value) const override {
			return value.IsType(VTYPE_Function) && dynamic_cast<const Value_Function&>(value).GetFunction().IsTypeMethod();
		}
	};
	class GURAX_DLLDECLARE GatherCriteria_ClassMethod : public Frame::GatherCriteria {
	public:
		virtual bool IsEligible(const Value& value) const override {
			return value.IsType(VTYPE_Function) && dynamic_cast<const Value_Function&>(value).GetFunction().IsClassMethod();
		}
	};
	class GURAX_DLLDECLARE GatherCriteria_HybridMethod : public Frame::GatherCriteria {
	public:
		virtual bool IsEligible(const Value& value) const override {
			return value.IsType(VTYPE_Function) && dynamic_cast<const Value_Function&>(value).GetFunction().IsHybridMethod();
		}
	};
	class GURAX_DLLDECLARE GatherCriteria_InstanceMethod : public Frame::GatherCriteria {
	public:
		virtual bool IsEligible(const Value& value) const override {
			return value.IsType(VTYPE_Function) && dynamic_cast<const Value_Function&>(value).GetFunction().IsInstanceMethod();
		}
	};
protected:
	RefPtr<Function> _pFunction;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Function() = delete;
	explicit Value_Function(Function* pFunction, VType& vtype = VTYPE_Function) :
		Value_Object(vtype), _pFunction(pFunction) {}
	// Copy constructor/operator
	Value_Function(const Value_Function& src) :
		Value_Object(src), _pFunction(src._pFunction->Reference()) {}
	Value_Function& operator=(const Value_Function& src) = delete;
	// Move constructor/operator
	Value_Function(Value_Function&& src) = delete;
	Value_Function& operator=(Value_Function&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Function() = default;
public:
	Function& GetFunction() { return *_pFunction; }
	const Function& GetFunction() const { return *_pFunction; }
public:
	static Function& GetFunction(Value& value) {
		return dynamic_cast<Value_Function&>(value).GetFunction();
	}
	static const Function& GetFunction(const Value& value) {
		return dynamic_cast<const Value_Function&>(value).GetFunction();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetFunction().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetFunction().IsEqualTo(dynamic_cast<const Value_Function&>(value).GetFunction());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetFunction().IsLessThan(dynamic_cast<const Value_Function&>(value).GetFunction()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	// Virtual functions for runtime process
	virtual HelpHolder* GetHelpHolder(bool classFlag) const override { return &_pFunction->GetHelpHolder(); }
	virtual void PresentHelp(Processor& processor, const Symbol* pLangCode) const override;
	virtual bool CanBeCallableMember() const override { return _pFunction->IsTypeMethod(); }
	virtual const DeclCallable* GetDeclCallable() override;
	virtual Frame* GetFrameForVType(Processor& processor) override;
	virtual void DoCall(Processor& processor, Argument& argument) override;
	virtual Value* DoEval(Processor& processor, Argument& argument) const override;
};

}

#endif
