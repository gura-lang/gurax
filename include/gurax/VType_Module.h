//==============================================================================
// VType_Module.h
//==============================================================================
#ifndef GURAX_VTYPE_MODULE_H
#define GURAX_VTYPE_MODULE_H
#include "VType_Object.h"
#include "Module.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Module
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Module : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Module VTYPE_Module;

//------------------------------------------------------------------------------
// Value_Module
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Module : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Module);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Module");
protected:
	RefPtr<Module> _pModule;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Module() = delete;
	explicit Value_Module(Module* pModule, VType& vtype = VTYPE_Module) :
		Value_Object(vtype), _pModule(pModule) {}
	// Copy constructor/operator
	Value_Module(const Value_Module& src) :
		Value_Object(src), _pModule(src._pModule->Reference()) {}
	Value_Module& operator=(const Value_Module& src) = delete;
	// Move constructor/operator
	Value_Module(Value_Module&& src) = delete;
	Value_Module& operator=(Value_Module&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Module() = default;
public:
	Module& GetModule() { return *_pModule; }
	const Module& GetModule() const { return *_pModule; }
public:
	static Module& GetModule(Value& value) {
		return dynamic_cast<Value_Module&>(value).GetModule();
	}
	static const Module& GetModule(const Value& value) {
		return dynamic_cast<const Value_Module&>(value).GetModule();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetModule().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetModule().IsEqualTo(dynamic_cast<const Value_Module*>(pValue)->GetModule());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetModule().IsLessThan(dynamic_cast<const Value_Module*>(pValue)->GetModule()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDigest(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
public:
	// Virtual functions for runtime process
	virtual void GatherMemberSymbol(SymbolList& symbolList) const override {
		GetModule().GatherMemberSymbol(symbolList);
	}
	virtual Value* DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag) override;
	virtual bool DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr) override;
};

}

#endif
