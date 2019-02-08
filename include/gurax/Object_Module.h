//==============================================================================
// Object_Module.h
//==============================================================================
#ifndef GURAX_OBJECT_MODULE_H
#define GURAX_OBJECT_MODULE_H
#include "Object_Object.h"
#include "Module.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Module
//------------------------------------------------------------------------------
class KlassT_Module : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Module Klass_Module;

//------------------------------------------------------------------------------
// Object_Module
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Module : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Module);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Module");
private:
	RefPtr<Module> _pModule;
public:
	// Constructor
	Object_Module() = delete;
	explicit Object_Module(Module* pModule, Klass& klass = Klass_Module) :
		Object_Object(klass), _pModule(pModule) {}
	// Copy constructor/operator
	Object_Module(const Object_Module& src) :
		Object_Object(src), _pModule(src._pModule->Reference()) {}
	Object_Module& operator=(const Object_Module& src) = delete;
	// Move constructor/operator
	Object_Module(Object_Module&& src) = delete;
	Object_Module& operator=(Object_Module&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Module() = default;
public:
	Module& GetModule() { return *_pModule; }
	const Module& GetModule() const { return *_pModule; }
public:
	// Virtual functions of Object
	virtual Frame* ProvideFrame() override { return &GetModule().GetFrame(); }
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetModule().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetModule().IsEqualTo(dynamic_cast<const Object_Module*>(pObject)->GetModule());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetModule().IsLessThan(dynamic_cast<const Object_Module*>(pObject)->GetModule()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetModule().ToString(ss);
	}
};

}

#endif
