//==============================================================================
// VType_Opt.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_VTYPE_OPT_H
#define GURAX_MODULE_CURL_VTYPE_OPT_H
#include <gurax.h>
#include "Opt.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// VType_Opt
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Opt : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Opt VTYPE_Opt;

//------------------------------------------------------------------------------
// Value_Opt
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Opt : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Opt);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Opt");
protected:
	RefPtr<Opt> _pOpt;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Opt() = delete;
	explicit Value_Opt(Opt* pOpt, VType& vtype = VTYPE_Opt) :
		Value_Object(vtype), _pOpt(pOpt) {}
	// Copy constructor/operator
	Value_Opt(const Value_Opt& src) :
		Value_Object(src), _pOpt(src._pOpt->Reference()) {}
	Value_Opt& operator=(const Value_Opt& src) = delete;
	// Move constructor/operator
	Value_Opt(Value_Opt&& src) noexcept = delete;
	Value_Opt& operator=(Value_Opt&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Opt() = default;
public:
	Opt& GetOpt() { return *_pOpt; }
	const Opt& GetOpt() const { return *_pOpt; }
public:
	static Opt& GetOpt(Value& value) {
		return dynamic_cast<Value_Opt&>(value).GetOpt();
	}
	static const Opt& GetOpt(const Value& value) {
		return dynamic_cast<const Value_Opt&>(value).GetOpt();
	}
	static Opt* GetEntityPtr(Value& value) { return &GetOpt(value); }
	static const Opt* GetEntityPtr(const Value& value) { return &GetOpt(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetOpt().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetOpt().IsEqualTo(Value_Opt::GetOpt(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetOpt().IsLessThan(Value_Opt::GetOpt(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	virtual bool DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr);
};

Gurax_EndModuleScope(curl)

#endif
