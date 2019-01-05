//==============================================================================
// Object_module.h
//==============================================================================
#ifndef GURAX_OBJECT_MODULE_H
#define GURAX_OBJECT_MODULE_H
#include "Object.h"
#include "Module.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_module
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_module : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_module);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("module");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	RefPtr<Module> _pModule;
public:
	// Constructor
	Object_module() = delete;
	explicit Object_module(Module *pModule) : Object(klass), _pModule(pModule) {}
	// Copy constructor/operator
	Object_module(const Object_module& src) : Object(klass), _pModule(src._pModule->Reference()) {}
	Object_module& operator=(const Object_module& src) { _pModule.reset(src._pModule->Reference()); return *this; }
	// Move constructor/operator
	Object_module(Object_module&& src) : Object(klass), _pModule(src._pModule.release()) {}
	Object_module& operator=(Object_module&& src) noexcept { _pModule.reset(src._pModule.release()); return *this; }
protected:
	// Destructor
	~Object_module() = default;
public:
	const Module* GetModule() const { return _pModule.get(); }
public:
	// Virtual modules of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return reinterpret_cast<size_t>(this); }
	virtual bool IsEqualTo(const Object* pObject) const override { return IsIdentical(pObject); }
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetModule()->IsLessThan(dynamic_cast<const Object_module*>(pObject)->GetModule()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle&) const override { return _pModule->ToString(); }
};

}

#endif
