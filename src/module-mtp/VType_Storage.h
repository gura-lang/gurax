//==============================================================================
// VType_Storage.h
//==============================================================================
#ifndef GURAX_MODULE_MTP_VTYPE_STORAGE_H
#define GURAX_MODULE_MTP_VTYPE_STORAGE_H
#include <gurax.h>
#include "Storage.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// VType_Storage
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Storage : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Storage VTYPE_Storage;

//------------------------------------------------------------------------------
// Value_Storage
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Storage : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Storage);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Storage");
protected:
	RefPtr<Storage> _pStorage;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Storage() = delete;
	explicit Value_Storage(Storage* pStorage, VType& vtype = VTYPE_Storage) :
		Value_Object(vtype), _pStorage(pStorage) {}
	// Copy constructor/operator
	Value_Storage(const Value_Storage& src) :
		Value_Object(src), _pStorage(src._pStorage->Reference()) {}
	Value_Storage& operator=(const Value_Storage& src) = delete;
	// Move constructor/operator
	Value_Storage(Value_Storage&& src) noexcept = delete;
	Value_Storage& operator=(Value_Storage&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Storage() = default;
public:
	Storage& GetStorage() { return *_pStorage; }
	const Storage& GetStorage() const { return *_pStorage; }
public:
	static Storage& GetStorage(Value& value) {
		return dynamic_cast<Value_Storage&>(value).GetStorage();
	}
	static const Storage& GetStorage(const Value& value) {
		return dynamic_cast<const Value_Storage&>(value).GetStorage();
	}
	static Storage* GetEntityPtr(Value& value) { return &GetStorage(value); }
	static const Storage* GetEntityPtr(const Value& value) { return &GetStorage(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetStorage().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetStorage().IsEqualTo(Value_Storage::GetStorage(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetStorage().IsLessThan(Value_Storage::GetStorage(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(mtp)

#endif
