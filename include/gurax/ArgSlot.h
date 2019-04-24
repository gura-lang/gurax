//==============================================================================
// ArgSlot.h
//==============================================================================
#ifndef GURAX_ARGSLOT_H
#define GURAX_ARGSLOT_H
#include "Referable.h"
#include "Attribute.h"
#include "VType_Dict.h"
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
	RefPtr<Value> _pValue;
	DeclCallable::Flags _flags;
	RefPtr<ArgSlot> _pArgSlotNext;
public:
	// Constructor
	ArgSlot(DeclArg* pDeclArg, Value* pValue, DeclCallable::Flags flags) : _pDeclArg(pDeclArg), _pValue(pValue), _flags(flags) {}
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
	DeclArg& GetDeclArg() { return *_pDeclArg; }
	const DeclArg& GetDeclArg() const { return *_pDeclArg; }
	Value& GetValue() { return *_pValue; }
	const Value& GetValue() const { return *_pValue; }
	DeclCallable::Flags GetFlags() const { return _flags; }
	bool IsVType(const VType& vtype) const { return _pDeclArg->IsVType(vtype); }
	bool IsMatched(const Symbol* pSymbol) const {
		return GetDeclArg().GetSymbol()->IsIdentical(pSymbol);
	}
	ArgSlot* Find(const Symbol* pSymbol);
	void SetNext(ArgSlot* pArgSlotNext) { _pArgSlotNext.reset(pArgSlotNext); }
	ArgSlot* GetNext() { return _pArgSlotNext.get(); }
	const ArgSlot* GetNext() const { return _pArgSlotNext.get(); }
	const ArgSlot* Advance() const { return const_cast<ArgSlot*>(this)->Advance(); }
	bool ReadyToPickValue() const { return _pValue->ReadyToPickValue(); }
	Value* PickValue() const { return _pValue->PickValue(); }
	void AssignToFrame(Frame& frame) const {
		if (IsDefined()) frame.AssignFromArgument(GetDeclArg().GetSymbol(), PickValue());;
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ArgSlot& argSlot) const { return this == &argSlot; }
	bool IsEqualTo(const ArgSlot& argSlot) const { return IsIdentical(argSlot); }
	bool IsLessThan(const ArgSlot& argSlot) const { return this < &argSlot; }
public:
	// Virtual functions
	virtual void ResetValue() = 0;
	virtual void FeedValue(Argument& argument, Frame& frame, RefPtr<Value> pValue) = 0;
	virtual bool HasValidValue() const = 0;
	virtual ArgSlot* Advance() { return _pArgSlotNext.get(); }
	virtual bool IsDefined() const = 0;
	virtual bool IsVacant() const = 0;
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const = 0;
};

//------------------------------------------------------------------------------
// ArgSlotFactory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlotFactory {
public:
	virtual ArgSlot* Create(DeclArg* pDeclArg, DeclCallable::Flags flags) const = 0;
};

//------------------------------------------------------------------------------
// ArgSlot_Single
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_Single : public ArgSlot {
public:
	explicit ArgSlot_Single(DeclArg* pDeclArg, DeclCallable::Flags flags) :
		ArgSlot(pDeclArg, Value::undefined(), flags) {}
public:
	// Virtual functions of ArgSlot
	virtual void ResetValue() override;
	virtual void FeedValue(Argument& argument, Frame& frame, RefPtr<Value> pValue) override;
	virtual bool IsDefined() const override { return !_pValue->IsUndefined(); }
	virtual bool IsVacant() const override { return _pValue->IsUndefined(); }
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// ArgSlot_Multiple
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_Multiple : public ArgSlot {
public:
	explicit ArgSlot_Multiple(DeclArg* pDeclArg, DeclCallable::Flags flags) :
		ArgSlot(pDeclArg, new Value_List(), flags) {}
protected:
	Value_List& GetValue() { return dynamic_cast<Value_List&>(*_pValue); }
	const Value_List& GetValue() const { return dynamic_cast<const Value_List&>(*_pValue); }
public:
	// Virtual functions of ArgSlot
	virtual void ResetValue() override;
	virtual void FeedValue(Argument& argument, Frame& frame, RefPtr<Value> pValue) override;
	virtual ArgSlot* Advance() override { return this; }
	virtual bool IsDefined() const override { return true; }
	virtual bool IsVacant() const override { return true; }
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// ArgSlot_Dict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_Dict : public ArgSlot {
protected:
	const Symbol* _pSymbol;
public:
	ArgSlot_Dict(Value_Dict* pValueOfDict, const Symbol* pSymbol) :
		ArgSlot(DeclArg::Empty->Reference(), pValueOfDict, DeclCallable::Flag::None), _pSymbol(pSymbol) {}
protected:
	Value_Dict& GetValue() { return dynamic_cast<Value_Dict&>(*_pValue); }
	const Value_Dict& GetValue() const { return dynamic_cast<const Value_Dict&>(*_pValue); }
public:
	// Virtual functions of ArgSlot
	virtual void ResetValue() override;
	virtual void FeedValue(Argument& argument, Frame& frame, RefPtr<Value> pValue) override;
	virtual bool IsDefined() const override { return true; }
	virtual bool IsVacant() const override { return true; }
	virtual bool HasValidValue() const override { return true; }
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// ArgSlot_Once
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_Once : public ArgSlot_Single {
public:
	class GURAX_DLLDECLARE Factory : public ArgSlotFactory {
	public:
		virtual ArgSlot* Create(DeclArg* pDeclArg, DeclCallable::Flags flags) const {
			return new ArgSlot_Once(pDeclArg, flags);
		}
	};
public:
	static const Factory factory;
public:
	ArgSlot_Once(DeclArg* pDeclArg, DeclCallable::Flags flags) : ArgSlot_Single(pDeclArg, flags) {}
	virtual bool HasValidValue() const override { return !_pValue->IsUndefined(); }
};

//------------------------------------------------------------------------------
// ArgSlot_ZeroOrOnce
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_ZeroOrOnce : public ArgSlot_Single {
public:
	class GURAX_DLLDECLARE Factory : public ArgSlotFactory {
	public:
		virtual ArgSlot* Create(DeclArg* pDeclArg, DeclCallable::Flags flags) const {
			return new ArgSlot_ZeroOrOnce(pDeclArg, flags);
		}
	};
public:
	static const Factory factory;
public:
	ArgSlot_ZeroOrOnce(DeclArg* pDeclArg, DeclCallable::Flags flags) : ArgSlot_Single(pDeclArg, flags) {}
	virtual bool HasValidValue() const override { return true; }
};

//------------------------------------------------------------------------------
// ArgSlot_ZeroOrMore
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_ZeroOrMore : public ArgSlot_Multiple {
public:
	class GURAX_DLLDECLARE Factory : public ArgSlotFactory {
	public:
		virtual ArgSlot* Create(DeclArg* pDeclArg, DeclCallable::Flags flags) const {
			return new ArgSlot_ZeroOrMore(pDeclArg, flags);
		}
	};
public:
	static const Factory factory;
public:
	ArgSlot_ZeroOrMore(DeclArg* pDeclArg, DeclCallable::Flags flags) : ArgSlot_Multiple(pDeclArg, flags) {}
	virtual bool HasValidValue() const override { return true; }
};

//------------------------------------------------------------------------------
// ArgSlot_OnceOrMore
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_OnceOrMore : public ArgSlot_Multiple {
public:
	class GURAX_DLLDECLARE Factory : public ArgSlotFactory {
	public:
		virtual ArgSlot* Create(DeclArg* pDeclArg, DeclCallable::Flags flags) const {
			return new ArgSlot_OnceOrMore(pDeclArg, flags);
		}
	};
public:
	static const Factory factory;
public:
	ArgSlot_OnceOrMore(DeclArg* pDeclArg, DeclCallable::Flags flags) : ArgSlot_Multiple(pDeclArg, flags) {}
	virtual bool HasValidValue() const override { return !GetValue().GetValueTypedOwner().IsEmpty(); }
};

}

#endif
