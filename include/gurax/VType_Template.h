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
class VType_Template : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Template VTYPE_Template;

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
	// Constructor
	Value_Template(VType& vtype = VTYPE_Template) = delete;
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
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetTemplate().IsEqualTo(dynamic_cast<const Value_Template*>(pValue)->GetTemplate());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetTemplate().IsLessThan(dynamic_cast<const Value_Template*>(pValue)->GetTemplate()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetTemplate().ToString(ss);
	}
};

}

#endif
