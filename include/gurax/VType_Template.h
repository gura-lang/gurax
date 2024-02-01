//==============================================================================
// VType_Template.h
//==============================================================================
#ifndef GURAX_VTYPE_TEMPLATE_H
#define GURAX_VTYPE_TEMPLATE_H
#include "VType_Object.h"
#include "Template.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Template
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Template : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	Value* DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Template VTYPE_Template;

//------------------------------------------------------------------------------
// Value_Template
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Template : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Template);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Template");
protected:
	RefPtr<Template> _pTempl;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Template(Template* pTempl, VType& vtype = VTYPE_Template) :
		Value_Object(vtype), _pTempl(pTempl) {}
	// Copy constructor/operator
	Value_Template(const Value_Template& src) :
		Value_Object(src), _pTempl(src._pTempl->Reference()) {}
	Value_Template& operator=(const Value_Template& src) = delete;
	// Move constructor/operator
	Value_Template(Value_Template&& src) = delete;
	Value_Template& operator=(Value_Template&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Template() = default;
public:
	Template& GetTemplate() { return *_pTempl; }
	const Template& GetTemplate() const { return *_pTempl; }
public:
	static Template& GetTemplate(Value& value) {
		return dynamic_cast<Value_Template&>(value).GetTemplate();
	}
	static const Template& GetTemplate(const Value& value) {
		return dynamic_cast<const Value_Template&>(value).GetTemplate();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetTemplate().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetTemplate().IsEqualTo(dynamic_cast<const Value_Template&>(value).GetTemplate());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetTemplate().IsLessThan(dynamic_cast<const Value_Template&>(value).GetTemplate()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
