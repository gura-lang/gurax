//==============================================================================
// Value.h
//==============================================================================
#ifndef GURAX_VALUE_H
#define GURAX_VALUE_H
#include "VType.h"
#include "Iterator.h"
#include "DeclCallable.h"

namespace Gurax {

class Argument;
class Formatter;
class FormatterFlags;
class Index;
class Processor;

//------------------------------------------------------------------------------
// Value
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value);
public:
	// Algorithm operators
	struct EqualTo {
		size_t operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue1->IsEqualTo(pValue2);
		}
	};
	struct LessThan {
		size_t operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue1->IsLessThan(pValue2);
		}
	};
	struct GreaterThan {
		size_t operator()(const Value* pValue1, const Value* pValue2) const {
			return pValue2->IsLessThan(pValue1);
		}
	};
	struct Hash {
		size_t operator()(const Value* pValue) const {
			return pValue->CalcHash();
		}
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
public:
	// Constructor
	Value() = delete;
	explicit Value(VType& vtype) : _pVType(&vtype) {}
	// Copy constructor/operator
	Value(const Value& src) : _pVType(src._pVType) {}
	Value& operator=(const Value& src) = delete;
	// Move constructor/operator
	Value(Value&& src) : _pVType(src._pVType) {}
	Value& operator=(Value&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Value() = default;
public:
	VType& GetVType() { return *_pVType; }
	const VType& GetVType() const { return *_pVType; }
	size_t CalcHash() const { return DoCalcHash(); }
	bool IsIdentical(const Value* pValue) const { return this == pValue; }
	static bool IsIdentical(const Value* pValue1, const Value* pValue2) {
		return pValue1? pValue1->IsIdentical(pValue2) : (!pValue1 && !pValue2);
	}
	bool IsSameType(const Value* pValue) const { return GetVType().IsIdentical(pValue->GetVType()); }
	static bool IsSameType(const Value* pValue1, const Value* pValue2) {
		return pValue1 && pValue1->IsSameType(pValue2);
	}
	bool IsType(const VType& vtype) const { return GetVType().IsIdentical(vtype); }
	static bool IsType(const Value* pValue, const VType& vtype) { return pValue && pValue->IsType(vtype); }
	bool IsInstanceOf(const VType& vtype) const;
	static bool IsInstanceOf(const Value* pValue, const VType& vtype) { return pValue && pValue->IsInstanceOf(vtype); }
	String ToString() const { return ToString(StringStyle::Empty); }
	String ToString(const StringStyle& ss) const {
		return ss.IsDigest()? ToStringDigest(ss) : ToStringDetail(ss);
	}
public:
	bool IsMutable() const { return GetVType().IsMutable(); }
	bool IsImmutable() const { return GetVType().IsImmutable(); }
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
	// Virtual functions
	virtual Value* Clone() const = 0;
	virtual size_t DoCalcHash() const = 0;
	virtual bool IsEqualTo(const Value* pValue) const = 0;
	virtual bool IsLessThan(const Value* pValue) const = 0;
	virtual String ToStringDigest(const StringStyle& ss) const;
	virtual String ToStringDetail(const StringStyle& ss) const { return String::Empty; }
public:
	// Virtual functions for runtime process
	virtual bool IsValid() const { return true; }
	virtual bool IsUndefined() const { return false; }
	virtual bool IsNil() const { return false; }
	virtual bool IsIterable() const { return false; }
	virtual bool IsIterator() const { return false; }
	virtual bool IsList() const { return false; }
	virtual bool IsVType() const { return false; }
	virtual bool IsMappable(const DeclArg& declArg, DeclCallable::Flags flags) const { return false; }
	virtual bool IsAsDictKey() const { return false; }
	virtual void UpdateMapMode(Argument& argument) const {}
	virtual bool ReadyToPickValue() { return true; }
	virtual Value* PickValue() { return Reference(); }
	virtual void UpdateIteratorInfo(Iterator::Flags& flags, size_t& len) const {}
	virtual bool GetBool() const { return true; }
	virtual bool IsCallable() const { return false; }
	virtual const DeclCallable* GetDeclCallable() const;
	virtual void DoCall(Processor& processor, Argument& argument) {}
	virtual Value* DoIndexGet(const Index& index) const;
	virtual void DoIndexSet(const Index& index, Value* pValue);
	virtual Value* DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFounderrorFlag);
	virtual bool DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr);
	virtual Iterator* DoGenIterator() const;
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
protected:
	void _ToStringDigest(String& str, const StringStyle& ss) const;
};

}

#endif
