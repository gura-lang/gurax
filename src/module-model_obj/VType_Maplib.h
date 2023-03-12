//==============================================================================
// VType_Maplib.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_MAPLIB_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_MAPLIB_H
#include <gurax.h>
#include "Data.h"
#include "Maplib.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Maplib
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Maplib : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Maplib VTYPE_Maplib;

//------------------------------------------------------------------------------
// Value_Maplib
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Maplib : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Maplib);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Maplib");
protected:
	RefPtr<Maplib> _pMaplib;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Maplib() = delete;
	explicit Value_Maplib(Maplib* pMaplib, VType& vtype = VTYPE_Maplib) :
		Value_Object(vtype), _pMaplib(pMaplib) {}
	// Copy constructor/operator
	Value_Maplib(const Value_Maplib& src) :
		Value_Object(src), _pMaplib(src._pMaplib->Reference()) {}
	Value_Maplib& operator=(const Value_Maplib& src) = delete;
	// Move constructor/operator
	Value_Maplib(Value_Maplib&& src) noexcept = delete;
	Value_Maplib& operator=(Value_Maplib&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Maplib() = default;
public:
	Maplib& GetMaplib() { return *_pMaplib; }
	const Maplib& GetMaplib() const { return *_pMaplib; }
public:
	static Maplib& GetMaplib(Value& value) {
		return dynamic_cast<Value_Maplib&>(value).GetMaplib();
	}
	static const Maplib& GetMaplib(const Value& value) {
		return dynamic_cast<const Value_Maplib&>(value).GetMaplib();
	}
	static Maplib* GetEntityPtr(Value& value) { return &GetMaplib(value); }
	static const Maplib* GetEntityPtr(const Value& value) { return &GetMaplib(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetMaplib().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetMaplib().IsEqualTo(Value_Maplib::GetMaplib(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetMaplib().IsLessThan(Value_Maplib::GetMaplib(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
