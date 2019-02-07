//==============================================================================
// Object_Template.h
//==============================================================================
#ifndef GURAX_OBJECT_TEMPLATE_H
#define GURAX_OBJECT_TEMPLATE_H
#include "Object.h"
#include "Template.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Template
//------------------------------------------------------------------------------
class KlassT_Template : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Template Klass_Template;

//------------------------------------------------------------------------------
// Object_Template
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Template : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Template);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Template");
private:
	RefPtr<Template> _pTempl;
public:
	// Constructor
	Object_Template() = delete;
	explicit Object_Template(Template *pTempl) : Object(Klass_Template), _pTempl(pTempl) {}
	// Copy constructor/operator
	Object_Template(const Object_Template& src) : Object(Klass_Template), _pTempl(src._pTempl->Reference()) {}
	Object_Template& operator=(const Object_Template& src) { _pTempl.reset(src._pTempl->Reference()); return *this; }
	// Move constructor/operator
	Object_Template(Object_Template&& src) : Object(Klass_Template), _pTempl(src._pTempl.release()) {}
	Object_Template& operator=(Object_Template&& src) noexcept { _pTempl.reset(src._pTempl.release()); return *this; }
protected:
	// Destructor
	~Object_Template() = default;
public:
	Template& GetTemplate() { return *_pTempl; }
	const Template& GetTemplate() const { return *_pTempl; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetTemplate().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetTemplate().IsEqualTo(dynamic_cast<const Object_Template*>(pObject)->GetTemplate());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetTemplate().IsLessThan(dynamic_cast<const Object_Template*>(pObject)->GetTemplate()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetTemplate().ToString(ss);
	}
};

}

#endif
