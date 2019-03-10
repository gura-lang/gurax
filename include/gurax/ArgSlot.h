//==============================================================================
// ArgSlot.h
//==============================================================================
#ifndef GURAX_ARGSLOT_H
#define GURAX_ARGSLOT_H
#include "Referable.h"
#include "Attribute.h"
#include "VType_List.h"
#include "DeclCallable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ArgSlot);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ArgSlot");
protected:
	RefPtr<DeclArg> _pDeclArg;
	RefPtr<ArgSlot> _pArgSlotNext;
public:
	// Constructor
	explicit ArgSlot(DeclArg* pDeclArg) : _pDeclArg(pDeclArg) {}
	// Copy constructor/operator
	ArgSlot(const ArgSlot& src) = delete;
	ArgSlot& operator=(const ArgSlot& src) = delete;
	// Move constructor/operator
	ArgSlot(ArgSlot&& src) = delete;
	ArgSlot& operator=(ArgSlot&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~ArgSlot() = default;
public:
	const DeclArg& GetDeclArg() const { return *_pDeclArg; }
	bool IsVType(const VType& vtype) const { return _pDeclArg->IsVType(vtype); }
	bool IsMatched(const Symbol* pSymbol) const {
		return GetDeclArg().GetSymbol()->IsIdentical(pSymbol);
	}
	ArgSlot* Find(const Symbol* pSymbol);
	void SetNext(ArgSlot* pArgSlotNext) { _pArgSlotNext.reset(pArgSlotNext); }
	ArgSlot* GetNext() { return _pArgSlotNext.get(); }
	const ArgSlot* GetNext() const { return _pArgSlotNext.get(); }
	const ArgSlot* GoNext() const { return const_cast<ArgSlot*>(this)->GoNext(); }
	void AssignToFrame(Frame& frame) const {
		if (!IsUndefined()) {
			frame.AssignValueOfArgument(GetDeclArg().GetSymbol(), GetValue()->Reference());;
		}
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ArgSlot& argSlot) const { return this == &argSlot; }
	bool IsEqualTo(const ArgSlot& argSlot) const { return IsIdentical(argSlot); }
	bool IsLessThan(const ArgSlot& argSlot) const { return this < &argSlot; }
public:
	// Virtual functions
	virtual void FeedValue(RefPtr<Value> pValue) = 0;
	virtual bool IsValid() const = 0;
	virtual ArgSlot* GoNext() { return _pArgSlotNext.get(); }
	virtual Value* GetValue() const = 0;
	virtual bool IsUndefined() const = 0;
	virtual bool IsVacant() const = 0;
	virtual String ToString(const StringStyle& ss) const = 0;
};

//------------------------------------------------------------------------------
// ArgSlotFactory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlotFactory {
public:
	virtual ArgSlot* Create(DeclArg* pDeclArg) const = 0;
};

//------------------------------------------------------------------------------
// ArgSlot_Single
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_Single : public ArgSlot {
protected:
	RefPtr<Value> _pValue;
public:
	ArgSlot_Single(DeclArg* pDeclArg) : ArgSlot(pDeclArg), _pValue(Value::undefined()) {}
public:
	// Virtual functions of ArgSlot
	virtual void FeedValue(RefPtr<Value> pValue) override;
	virtual Value* GetValue() const override { return _pValue.get(); }
	virtual bool IsUndefined() const override { return _pValue->IsUndefined(); }
	virtual bool IsVacant() const override { return _pValue->IsUndefined(); }
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// ArgSlot_Multiple
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_Multiple : public ArgSlot {
protected:
	RefPtr<Value_List> _pValue;
public:
	ArgSlot_Multiple(DeclArg* pDeclArg) : ArgSlot(pDeclArg), _pValue(new Value_List()) {}
public:
	// Virtual functions of ArgSlot
	virtual void FeedValue(RefPtr<Value> pValue) override;
	virtual ArgSlot* GoNext() override { return this; }
	virtual Value* GetValue() const override { return _pValue.get(); }
	virtual bool IsUndefined() const override { return false; }
	virtual bool IsVacant() const override { return true; }
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// ArgSlot_Once
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_Once : public ArgSlot_Single {
public:
	class GURAX_DLLDECLARE Factory : public ArgSlotFactory {
	public:
		virtual ArgSlot* Create(DeclArg* pDeclArg) const { return new ArgSlot_Once(pDeclArg); }
	};
public:
	static const Factory factory;
public:
	ArgSlot_Once(DeclArg* pDeclArg) : ArgSlot_Single(pDeclArg) {}
	virtual bool IsValid() const override { return !_pValue->IsUndefined(); }
};

//------------------------------------------------------------------------------
// ArgSlot_ZeroOrOnce
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_ZeroOrOnce : public ArgSlot_Single {
public:
	class GURAX_DLLDECLARE Factory : public ArgSlotFactory {
	public:
		virtual ArgSlot* Create(DeclArg* pDeclArg) const { return new ArgSlot_ZeroOrOnce(pDeclArg); }
	};
public:
	static const Factory factory;
public:
	ArgSlot_ZeroOrOnce(DeclArg* pDeclArg) : ArgSlot_Single(pDeclArg) {}
	virtual bool IsValid() const override { return true; }
};

//------------------------------------------------------------------------------
// ArgSlot_ZeroOrMore
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_ZeroOrMore : public ArgSlot_Multiple {
public:
	class GURAX_DLLDECLARE Factory : public ArgSlotFactory {
	public:
		virtual ArgSlot* Create(DeclArg* pDeclArg) const { return new ArgSlot_ZeroOrMore(pDeclArg); }
	};
public:
	static const Factory factory;
public:
	ArgSlot_ZeroOrMore(DeclArg* pDeclArg) : ArgSlot_Multiple(pDeclArg) {}
	virtual bool IsValid() const override { return true; }
};

//------------------------------------------------------------------------------
// ArgSlot_OnceOrMore
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_OnceOrMore : public ArgSlot_Multiple {
public:
	class GURAX_DLLDECLARE Factory : public ArgSlotFactory {
	public:
		virtual ArgSlot* Create(DeclArg* pDeclArg) const { return new ArgSlot_OnceOrMore(pDeclArg); }
	};
public:
	static const Factory factory;
public:
	ArgSlot_OnceOrMore(DeclArg* pDeclArg) : ArgSlot_Multiple(pDeclArg) {}
	virtual bool IsValid() const override { return !_pValue->GetValueTypedOwner().IsEmpty(); }
};

//------------------------------------------------------------------------------
// ArgSlot_Dict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_Dict : public ArgSlot {
protected:
	RefPtr<ValueDict> _pValueDict;
	const Symbol* _pSymbol;
public:
	ArgSlot_Dict(ValueDict* pValueDict, const Symbol* pSymbol) :
		ArgSlot(DeclArg::Empty->Reference()), _pValueDict(pValueDict), _pSymbol(pSymbol) {}
public:
	// Virtual functions of ArgSlot
	virtual void FeedValue(RefPtr<Value> pValue) override;
	virtual Value* GetValue() const override { return Value::nil(); }
	virtual bool IsUndefined() const override { return false; }
	virtual bool IsVacant() const override { return true; }
	virtual bool IsValid() const override { return true; }
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
