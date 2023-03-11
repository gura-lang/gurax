//==============================================================================
// VType_Usemap.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_USEMAP_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_USEMAP_H
#include <gurax.h>
#include "Usemap.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Usemap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Usemap : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Usemap VTYPE_Usemap;

//------------------------------------------------------------------------------
// Value_Usemap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Usemap : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Usemap);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Usemap");
protected:
	RefPtr<Usemap> _pUsemap;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Usemap() = delete;
	explicit Value_Usemap(Usemap* pUsemap, VType& vtype = VTYPE_Usemap) :
		Value_Object(vtype), _pUsemap(pUsemap) {}
	// Copy constructor/operator
	Value_Usemap(const Value_Usemap& src) :
		Value_Object(src), _pUsemap(src._pUsemap->Reference()) {}
	Value_Usemap& operator=(const Value_Usemap& src) = delete;
	// Move constructor/operator
	Value_Usemap(Value_Usemap&& src) noexcept = delete;
	Value_Usemap& operator=(Value_Usemap&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Usemap() = default;
public:
	Usemap& GetUsemap() { return *_pUsemap; }
	const Usemap& GetUsemap() const { return *_pUsemap; }
public:
	static Usemap& GetUsemap(Value& value) {
		return dynamic_cast<Value_Usemap&>(value).GetUsemap();
	}
	static const Usemap& GetUsemap(const Value& value) {
		return dynamic_cast<const Value_Usemap&>(value).GetUsemap();
	}
	static Usemap* GetEntityPtr(Value& value) { return &GetUsemap(value); }
	static const Usemap* GetEntityPtr(const Value& value) { return &GetUsemap(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetUsemap().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetUsemap().IsEqualTo(Value_Usemap::GetUsemap(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetUsemap().IsLessThan(Value_Usemap::GetUsemap(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
