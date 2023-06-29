//==============================================================================
// Value.h
//==============================================================================
#ifndef GURAX_VALUE_H
#define GURAX_VALUE_H
#include "Number.h"
#include "VType.h"
#include "DeclCallable.h"
#include "Error.h"
#include "Iterator.h"

namespace Gurax {

class Argument;
class Formatter;
class FormatterFlags;
class Index;
class Processor;
class VTypeCustom;

//------------------------------------------------------------------------------
// Value
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value);
public:
	// Algorithm operators
	struct GURAX_DLLDECLARE EqualTo {
		bool operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue1->IsEqualTo(*pValue2);
		}
	};
	struct GURAX_DLLDECLARE LessThan {
		bool operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue1->IsLessThan(*pValue2);
		}
	};
	struct GURAX_DLLDECLARE LessThanOrEqualTo {
		bool operator()(const Value* pValue1, const Value* pValue2) const {
			return !pValue2->IsLessThan(*pValue1);
		}
	};
	struct GURAX_DLLDECLARE GreaterThan {
		bool operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue2->IsLessThan(*pValue1);
		}
	};
	struct GURAX_DLLDECLARE GreaterThanOrEqualTo {
		bool operator()(const Value* pValue1, const Value* pValue2) const {
			return !pValue1->IsLessThan(*pValue2);
		}
	};
	struct GURAX_DLLDECLARE CustomCompare {
	private:
		Processor& _processor;
		const Function& _function;
		Argument& _argument;
	public:
		CustomCompare(Processor& processor, const Function& function, Argument& argument) :
			_processor(processor), _function(function), _argument(argument) {}
		bool operator()(const Value* pValue1, const Value* pValue2) const;
	};
	struct GURAX_DLLDECLARE KeyEqualTo {
		bool operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue1->GetValueKey().IsEqualTo(pValue2->GetValueKey());
		}
	};
	struct GURAX_DLLDECLARE KeyLessThan {
		bool operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue1->GetValueKey().IsLessThan(pValue2->GetValueKey());
		}
	};
	struct GURAX_DLLDECLARE KeyLessThanOrEqualTo {
		bool operator()(const Value* pValue1, const Value* pValue2) const {
			return !pValue2->GetValueKey().IsLessThan(pValue1->GetValueKey());
		}
	};
	struct GURAX_DLLDECLARE KeyGreaterThan {
		bool operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue2->GetValueKey().IsLessThan(pValue1->GetValueKey());
		}
	};
	struct GURAX_DLLDECLARE KeyGreaterThanOrEqualTo {
		bool operator()(const Value* pValue1, const Value* pValue2) const {
			return !pValue1->GetValueKey().IsLessThan(pValue2->GetValueKey());
		}
	};
	struct GURAX_DLLDECLARE KeyCustomCompare {
	private:
		Processor& _processor;
		const Function& _function;
		Argument& _argument;
	public:
		KeyCustomCompare(Processor& processor, const Function& function, Argument& argument) :
			_processor(processor), _function(function), _argument(argument) {}
		bool operator()(const Value* pValue1, const Value* pValue2) const;
	};
	struct GURAX_DLLDECLARE Hash {
		size_t operator()(const Value* pValue) const {
			return pValue->CalcHash();
		}
	};
public:
	class CustomPack {
	private:
		VTypeCustom* _pVTypeCustom;
		RefPtr<Processor> _pProcessor;
		Value* _pValueThis;
		RefPtr<ValueOwner> _pValuesProp;
	public:
		CustomPack(VTypeCustom& vtypeCustom, Processor* pProcessor, Value* pValueThis);
		void SetVType(VTypeCustom& vtypeCustom) { _pVTypeCustom = &vtypeCustom; }
		VTypeCustom& GetVType() const { return *_pVTypeCustom; }
		virtual ~CustomPack();
		bool InitCustomProp();
		void SetCustomProp(size_t iProp, Value* pValue);
		Value* GetCustomProp(size_t iProp);
		const ValueOwner& GetCustomProps() { return *_pValuesProp; }
	};
private:
	// These values are initialized by Value::CreateConstant().
	static const Value* _pValue_undefined;
	static const Value* _pValue_nil;
	static const Value* _pValue_false_;
	static const Value* _pValue_true_;
	static const Value* _pValue_Zero;
	static const Value* _pValue_EmptyStr;
protected:
	VType* _pVType;
protected:
	std::unique_ptr<CustomPack> _pCustomPack;
public:
	// Constructor
	Value() = delete;
	explicit Value(VType& vtype) : _pVType(&vtype) {}
	// Copy constructor/operator
	Value(const Value& src) : _pVType(src._pVType) {}
	Value& operator=(const Value& src) = delete;
	// Move constructor/operator
	Value(Value&& src) noexcept : _pVType(src._pVType) {}
	Value& operator=(Value&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Value() = default;
public:
	template<typename T_Value>
	T_Value* Cast(DeclArg::Flags flags = DeclArg::Flag::None) const {
		return dynamic_cast<T_Value*>(T_Value::vtype.Cast(*this, nullptr, flags));
	}
	VType& GetVTypeOfEntity() const { return *_pVType; }
	VType& GetVTypeCustom() const;
	size_t CalcHash() const { return DoCalcHash(); }
	bool IsIdentical(const Value* pValue) const { return this == pValue; }
	static bool IsIdentical(const Value* pValue1, const Value* pValue2) {
		return pValue1? pValue1->IsIdentical(pValue2) : (!pValue1 && !pValue2);
	}
	bool IsSameType(const Value& value) const { return GetVTypeCustom().IsIdentical(value.GetVTypeCustom()); }
	static bool IsSameType(const Value* pValue1, const Value* pValue2) {
		return pValue1 && pValue1->IsSameType(*pValue2);
	}
	bool IsType(const VType& vtype) const { return GetVTypeCustom().IsIdentical(vtype); }
	static bool IsType(const Value* pValue, const VType& vtype) { return pValue && pValue->IsType(vtype); }
	bool IsInstanceOf(const VType& vtype) const;
	Value* AsMember(const Value& valueTarget) const;
	static bool IsInstanceOf(const Value* pValue, const VType& vtype) { return pValue && pValue->IsInstanceOf(vtype); }
	static const Symbol* GetSymbol(const Value& value);
	String ToString() const { return ToString(StringStyle::Empty); }
	String ToStringGeneric(const StringStyle& ss, const char* strEntity) const;
	String ToStringGeneric(const StringStyle& ss, const String& strEntity) const {
		return ToStringGeneric(ss, strEntity.c_str());
	}
public:
	bool IsInvalid() const { return !IsValid(); }
	bool IsMutable() const { return GetVTypeCustom().IsMutable(); }
	bool IsImmutable() const { return GetVTypeCustom().IsImmutable(); }
public:
	static void CreateConstant();
public:
	static const Value& C_undefined()			{ return *_pValue_undefined; }
	static const Value& C_nil()					{ return *_pValue_nil; }
	static const Value& C_false()				{ return *_pValue_false_; }
	static const Value& C_true()				{ return *_pValue_true_; }
	static Value* undefined()					{ return _pValue_undefined->Reference(); }
	static Value* nil()							{ return _pValue_nil->Reference(); }
	static Value* false_()						{ return _pValue_false_->Reference(); }
	static Value* true_()						{ return _pValue_true_->Reference(); }
	static Value* Bool(bool f)					{ return f? true_() : false_(); }
	static Value* Zero()						{ return _pValue_Zero->Reference(); }
	static Value* EmptyStr()					{ return _pValue_EmptyStr->Reference(); }
	static Value* undefined(size_t nRefs)		{ return _pValue_undefined->Reference(nRefs); }
	static Value* nil(size_t nRefs)				{ return _pValue_nil->Reference(nRefs); }
	static Value* false_(size_t nRefs)			{ return _pValue_false_->Reference(nRefs); }
	static Value* true_(size_t nRefs)			{ return _pValue_true_->Reference(nRefs); }
	static Value* Bool(bool f, size_t nRefs)	{ return f? true_(nRefs) : false_(nRefs); }
	static Value* Zero(size_t nRefs)			{ return _pValue_Zero->Reference(nRefs); }
	static Value* EmptyStr(size_t nRefs)		{ return _pValue_EmptyStr->Reference(nRefs); }
public:
	void Call(Processor& processor, Argument& argument) { DoCall(processor, argument); }
	Value* Eval(Processor& processor, Argument& argument) const { return DoEval(processor, argument); }
	Value* EvalEasy(Processor& processor, RefPtr<Value> pValueArg, DeclCallable::Flags flags = DeclCallable::Flag::None);
	Value* EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2,
						DeclCallable::Flags flags = DeclCallable::Flag::None);
	Value* EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2,
						RefPtr<Value> pValueArg3, DeclCallable::Flags flags = DeclCallable::Flag::None);
	Value* EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2,
						RefPtr<Value> pValueArg3, RefPtr<Value> pValueArg4, DeclCallable::Flags flags = DeclCallable::Flag::None);
	Value* IndexGet(const Index& index) const { return DoIndexGet(index); }
	void IndexSet(const Index& index, Value* pValue) { return DoIndexSet(index, pValue); }
	Value* GetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag) {
		return DoGetProperty(pSymbol, attr, notFoundErrorFlag);
	}
	bool SetProperty(const Symbol* pSymbol, Value* pValue, const Attribute& attr) {
		return DoSetProperty(pSymbol, pValue, attr);
	}
	bool AssignCustomMethod(Function* pFunction) { return DoAssignCustomMethod(pFunction); }
	Iterator* GenIterator() const { return DoGenIterator(); }
	Function& LookupMethod(const Symbol* pSymbol) const;
public:
	bool InitCustomProp(VTypeCustom& vtypeCustom, Processor* pProcessor);
	bool HasCustomProp() const { return !!_pCustomPack; }
	void SetCustomProp(size_t iProp, Value* pValue) {
		if (_pCustomPack) _pCustomPack->SetCustomProp(iProp, pValue);
	}
	Value* GetCustomProp(size_t iProp) {
		if (_pCustomPack) return _pCustomPack->GetCustomProp(iProp);
		return Value::nil();
	}
	const ValueOwner& GetCustomProps() const { return _pCustomPack->GetCustomProps(); }
public:
	// Virtual functions
	virtual Value* Clone() const = 0;
	virtual size_t DoCalcHash() const = 0;
	virtual bool IsEqualTo(const Value& value) const = 0;
	virtual bool IsLessThan(const Value& value) const = 0;
	virtual String ToString(const StringStyle& ss) const = 0;
public:
	// Virtual functions for runtime process
	virtual HelpHolder* GetHelpHolder(bool classFlag) const { return nullptr; }
	virtual void PresentHelp(Processor& processor, const Symbol* pLangCode) const;
	virtual const Value& GetValueKey() const { return *this; }
	virtual const Value& GetValue() const { return *this; }
	virtual bool IsValid() const { return true; }
	virtual bool IsUndefined() const { return false; }
	virtual bool IsNil() const { return false; }
	virtual bool IsZero() const { return false; }
	virtual bool IsIterable() const { return false; }
	virtual bool IsIterableOrTuple() const { return false; }
	virtual bool IsIterator() const { return false; }
	virtual bool IsList() const { return false; }
	virtual bool IsTuple() const { return false; }
	virtual bool IsVType() const { return false; }
	virtual bool IsMappable(const DeclArg& declArg, DeclCallable::Flags flags) const { return false; }
	virtual bool IsAsDictKey() const { return false; }
	virtual void UpdateMapMode(Argument& argument) const {}
	virtual bool FeedExpandToArgument(Frame& frame, Argument& argument);
	virtual bool ReadyToPickValue(Frame& frame, DeclArg& declArg) { return true; }
	virtual bool ReadyToPickValueWithoutCast() { return true; }
	virtual Value* PickValue() { return Reference(); }
	virtual void UpdateIteratorInfo(Iterator::Flags& flags, size_t& len) const {}
	virtual bool GetBool() const { return true; }
	virtual bool CanBeCallableMember() const { return false; }
	virtual bool CanEvalAsMethod(const Function& function) const;
	virtual void GatherMemberSymbol(SymbolList& symbolList) const {
		GetVTypeCustom().GatherMemberSymbol(symbolList, true);
	}
	virtual const DeclCallable* GetDeclCallableWithError();
	virtual const DeclCallable* GetDeclCallable();
	virtual Frame* GetFrameForVType(Processor& processor);
	virtual void DoCall(Processor& processor, Argument& argument);
	virtual Value* DoEval(Processor& processor, Argument& argument) const { return Value::nil(); }
	virtual Value* DoIndexGet(const Index& index) const;
	virtual void DoIndexSet(const Index& index, RefPtr<Value> pValue);
	virtual bool DoEmptyIndexGet(Value** ppValue) const;
	virtual bool DoEmptyIndexSet(RefPtr<Value> pValue);
	virtual bool DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const;
	virtual bool DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue);
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag);
	virtual bool DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr);
	virtual bool DoAssignCustomMethod(RefPtr<Function> pFunction);
	virtual Iterator* DoGenIterator() const;
public:
	bool Serialize(Stream& stream) const;
	static Value* Deserialize(Stream& stream);
	virtual bool DoSerialize(Stream& stream) const;
public:
	// Virtual functions for Formatter
	virtual bool Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const;
	virtual bool Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const;
};

}

#endif
