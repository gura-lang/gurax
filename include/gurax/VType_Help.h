//==============================================================================
// VType_Help.h
//==============================================================================
#ifndef GURAX_VTYPE_HELP_H
#define GURAX_VTYPE_HELP_H
#include "VType_Object.h"
#include "Help.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Help
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Help : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Help VTYPE_Help;

//------------------------------------------------------------------------------
// Value_Help
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Help : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Help);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Help");
protected:
	RefPtr<Help> _pHelp;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Help() = delete;
	explicit Value_Help(Help* pHelp, VType& vtype = VTYPE_Help) :
		Value_Object(vtype), _pHelp(pHelp) {}
	// Copy constructor/operator
	Value_Help(const Value_Help& src) :
		Value_Object(src), _pHelp(src._pHelp->Reference()) {}
	Value_Help& operator=(const Value_Help& src) = delete;
	// Move constructor/operator
	Value_Help(Value_Help&& src) = delete;
	Value_Help& operator=(Value_Help&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Help() = default;
public:
	Help& GetHelp() { return *_pHelp; }
	const Help& GetHelp() const { return *_pHelp; }
public:
	static Help& GetHelp(Value& value) {
		return dynamic_cast<Value_Help&>(value).GetHelp();
	}
	static const Help& GetHelp(const Value& value) {
		return dynamic_cast<const Value_Help&>(value).GetHelp();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetHelp().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetHelp().IsEqualTo(Value_Help::GetHelp(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetHelp().IsLessThan(Value_Help::GetHelp(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	// Virtual functions for runtime process
	virtual void PresentHelp(Processor& processor, const Symbol* pLangCode) const override;
};

}

#endif
