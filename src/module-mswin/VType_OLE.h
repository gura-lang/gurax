//==============================================================================
// VType_OLE.h
//==============================================================================
#ifndef GURAX_MODULE_MSWIN_VTYPE_OLE_H
#define GURAX_MODULE_MSWIN_VTYPE_OLE_H
#include <gurax.h>
#include "OLE.h"

Gurax_BeginModuleScope(mswin)

//------------------------------------------------------------------------------
// VType_OLE
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_OLE : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_OLE VTYPE_OLE;

//------------------------------------------------------------------------------
// Value_OLE
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_OLE : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_OLE);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_OLE");
protected:
	RefPtr<OLE> _pOLE;
public:
	static VType& vtype;
public:
	// Constructor
	Value_OLE() = delete;
	explicit Value_OLE(OLE* pOLE, VType& vtype = VTYPE_OLE) :
		Value_Object(vtype), _pOLE(pOLE) {}
	// Copy constructor/operator
	Value_OLE(const Value_OLE& src) :
		Value_Object(src), _pOLE(src._pOLE->Reference()) {}
	Value_OLE& operator=(const Value_OLE& src) = delete;
	// Move constructor/operator
	Value_OLE(Value_OLE&& src) noexcept = delete;
	Value_OLE& operator=(Value_OLE&& src) noexcept = delete;
protected:
	// Destructor
	~Value_OLE() = default;
public:
	OLE& GetOLE() { return *_pOLE; }
	const OLE& GetOLE() const { return *_pOLE; }
public:
	static OLE& GetOLE(Value& value) {
		return dynamic_cast<Value_OLE&>(value).GetOLE();
	}
	static const OLE& GetOLE(const Value& value) {
		return dynamic_cast<const Value_OLE&>(value).GetOLE();
	}
	static OLE* GetEntityPtr(Value& value) { return &GetOLE(value); }
	static const OLE* GetEntityPtr(const Value& value) { return &GetOLE(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual const DeclCallable* GetDeclCallableWithError();
	virtual const DeclCallable* GetDeclCallable();
	//virtual void DoCall(Processor& processor, Argument& argument);
	virtual Value* DoEval(Processor& processor, Argument& argument) const;
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag);
	virtual bool DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr);
	virtual size_t DoCalcHash() const override {
		return GetOLE().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetOLE().IsEqualTo(Value_OLE::GetOLE(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetOLE().IsLessThan(Value_OLE::GetOLE(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(mswin)

#endif
