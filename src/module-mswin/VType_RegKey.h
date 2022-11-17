//==============================================================================
// VType_RegKey.h
//==============================================================================
#ifndef GURAX_MODULE_MSWIN_VTYPE_REGKEY_H
#define GURAX_MODULE_MSWIN_VTYPE_REGKEY_H
#include <gurax.h>
#include "RegKey.h"

Gurax_BeginModuleScope(mswin)

//------------------------------------------------------------------------------
// VType_RegKey
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_RegKey : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_RegKey VTYPE_RegKey;

//------------------------------------------------------------------------------
// Value_RegKey
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_RegKey : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_RegKey);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_RegKey");
protected:
	RefPtr<RegKey> _pRegKey;
public:
	static VType& vtype;
public:
	// Constructor
	Value_RegKey() = delete;
	explicit Value_RegKey(RegKey* pRegKey, VType& vtype = VTYPE_RegKey) :
		Value_Object(vtype), _pRegKey(pRegKey) {}
	// Copy constructor/operator
	Value_RegKey(const Value_RegKey& src) :
		Value_Object(src), _pRegKey(src._pRegKey->Reference()) {}
	Value_RegKey& operator=(const Value_RegKey& src) = delete;
	// Move constructor/operator
	Value_RegKey(Value_RegKey&& src) noexcept = delete;
	Value_RegKey& operator=(Value_RegKey&& src) noexcept = delete;
protected:
	// Destructor
	~Value_RegKey() = default;
public:
	RegKey& GetRegKey() { return *_pRegKey; }
	const RegKey& GetRegKey() const { return *_pRegKey; }
public:
	static RegKey& GetRegKey(Value& value) {
		return dynamic_cast<Value_RegKey&>(value).GetRegKey();
	}
	static const RegKey& GetRegKey(const Value& value) {
		return dynamic_cast<const Value_RegKey&>(value).GetRegKey();
	}
	static RegKey* GetEntityPtr(Value& value) { return &GetRegKey(value); }
	static const RegKey* GetEntityPtr(const Value& value) { return &GetRegKey(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetRegKey().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetRegKey().IsEqualTo(Value_RegKey::GetRegKey(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetRegKey().IsLessThan(Value_RegKey::GetRegKey(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_RegEnumKey
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_RegEnumKey : public Iterator {
private:
	RefPtr<RegKey> _pRegKey;
	REGSAM _samDesired;
	DWORD _dwIndex;
public:
	Iterator_RegEnumKey(RegKey* pRegKey, REGSAM samDesired) : _pRegKey(pRegKey), _samDesired(samDesired), _dwIndex(0) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//-----------------------------------------------------------------------------
// Iterator_RegEnumValue
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_RegEnumValue : public Iterator {
private:
	RefPtr<RegKey> _pRegKey;
	DWORD _dwIndex;
public:
	Iterator_RegEnumValue(RegKey* pRegKey) : _pRegKey(pRegKey), _dwIndex(0) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(mswin)

#endif
