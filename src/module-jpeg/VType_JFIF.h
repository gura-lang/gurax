//==============================================================================
// VType_JFIF.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_VTYPE_JFIF_H
#define GURAX_MODULE_JPEG_VTYPE_JFIF_H
#include <gurax.h>
#include "JFIF.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// VType_JFIF
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_JFIF : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_JFIF VTYPE_JFIF;

//------------------------------------------------------------------------------
// Value_JFIF
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_JFIF : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_JFIF);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_JFIF");
protected:
	RefPtr<JFIF> _pJFIF;
public:
	static VType& vtype;
public:
	// Constructor
	Value_JFIF() = delete;
	explicit Value_JFIF(JFIF* pJFIF, VType& vtype = VTYPE_JFIF) :
		Value_Object(vtype), _pJFIF(pJFIF) {}
	// Copy constructor/operator
	Value_JFIF(const Value_JFIF& src) :
		Value_Object(src), _pJFIF(src._pJFIF->Reference()) {}
	Value_JFIF& operator=(const Value_JFIF& src) = delete;
	// Move constructor/operator
	Value_JFIF(Value_JFIF&& src) noexcept = delete;
	Value_JFIF& operator=(Value_JFIF&& src) noexcept = delete;
protected:
	// Destructor
	~Value_JFIF() = default;
public:
	JFIF& GetJFIF() { return *_pJFIF; }
	const JFIF& GetJFIF() const { return *_pJFIF; }
public:
	static JFIF& GetJFIF(Value& value) {
		return dynamic_cast<Value_JFIF&>(value).GetJFIF();
	}
	static const JFIF& GetJFIF(const Value& value) {
		return dynamic_cast<const Value_JFIF&>(value).GetJFIF();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetJFIF().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetJFIF().IsEqualTo(Value_JFIF::GetJFIF(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetJFIF().IsLessThan(Value_JFIF::GetJFIF(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(jpeg)

#endif
