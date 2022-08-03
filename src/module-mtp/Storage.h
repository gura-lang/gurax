//==============================================================================
// Storage.h
//==============================================================================
#ifndef GURAX_MODULE_MTP_STORAGE_H
#define GURAX_MODULE_MTP_STORAGE_H
#include <gurax.h>

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// Storage
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Storage : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Storage);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("mtp.Storage");
public:
	// Constructor
	Storage() {}
	// Copy constructor/operator
	Storage(const Storage& src) = delete;
	Storage& operator=(const Storage& src) = delete;
	// Move constructor/operator
	Storage(Storage&& src) noexcept = delete;
	Storage& operator=(Storage&& src) noexcept = delete;
protected:
	~Storage() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Storage& other) const { return this == &other; }
	bool IsEqualTo(const Storage& other) const { return IsIdentical(other); }
	bool IsLessThan(const Storage& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// StorageList
//------------------------------------------------------------------------------
class StorageList : public ListBase<Storage*> {
};

//------------------------------------------------------------------------------
// StorageOwner
//------------------------------------------------------------------------------
class StorageOwner : public StorageList, Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(StorageOwner);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("mtp.StorageOwner");
private:
	~StorageOwner() { Clear(); }
public:
	void Clear() {
		for (auto pStorage : *this) Storage::Delete(pStorage);
		clear();
	}
	bool Enumerate();
};

//------------------------------------------------------------------------------
// Iterator_Storage
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Storage : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Storage");
private:
	RefPtr<StorageOwner> _pStorageOwner;
	size_t _idx;
	size_t _idxBegin;
	size_t _idxEnd;
public:
	Iterator_Storage(StorageOwner* pStorageOwner) :
		_pStorageOwner(pStorageOwner), _idx(0), _idxBegin(0), _idxEnd(pStorageOwner->size()) {}
	Iterator_Storage(StorageOwner* pStorageOwner, size_t idxBegin) :
		_pStorageOwner(pStorageOwner), _idx(idxBegin), _idxBegin(idxBegin), _idxEnd(pStorageOwner->size()) {}
	Iterator_Storage(StorageOwner* pStorageOwner, size_t idxBegin, size_t idxEnd) :
		_pStorageOwner(pStorageOwner), _idx(idxBegin), _idxBegin(idxBegin), _idxEnd(idxEnd) {}
public:
	StorageOwner& GetStorageOwner() { return *_pStorageOwner; }
	const StorageOwner& GetStorageOwner() const { return *_pStorageOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetStorageOwner().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(mtp)

#endif
