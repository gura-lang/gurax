//==============================================================================
// Object_template.h
//==============================================================================
#ifndef GURAX_OBJECT_TEMPLATE_H
#define GURAX_OBJECT_TEMPLATE_H
#include "Object.h"
#include "Template.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_template
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_template : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_template);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_template");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	RefPtr<Template> _pTempl;
public:
	// Constructor
	Object_template() = delete;
	explicit Object_template(Template *pTempl) : Object(klass), _pTempl(pTempl) {}
	// Copy constructor/operator
	Object_template(const Object_template& src) : Object(klass), _pTempl(src._pTempl->Reference()) {}
	Object_template& operator=(const Object_template& src) { _pTempl.reset(src._pTempl->Reference()); return *this; }
	// Move constructor/operator
	Object_template(Object_template&& src) : Object(klass), _pTempl(src._pTempl.release()) {}
	Object_template& operator=(Object_template&& src) noexcept { _pTempl.reset(src._pTempl.release()); return *this; }
protected:
	// Destructor
	~Object_template() = default;
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
			GetTemplate().IsEqualTo(dynamic_cast<const Object_template*>(pObject)->GetTemplate());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetTemplate().IsLessThan(dynamic_cast<const Object_template*>(pObject)->GetTemplate()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override {
		return GetTemplate().ToString(ss);
	}
};

}

#endif
