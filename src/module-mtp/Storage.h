//==============================================================================
// Storage.h
//==============================================================================
#ifndef GURAX_MODULE_MTP_STORAGE_H
#define GURAX_MODULE_MTP_STORAGE_H
#include <gurax.h>
#include "Device.h"

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
private:
	RefPtr<Device> _pDevice;
	StringW _objectID;
	const Symbol* _pStorageType;		// Storage type
	const Symbol* _pFilesystemType;		// Filesystem type
	const Symbol* _pAccessCapability;	// Access capability
	UInt64 _maxCapacity;				// Maximum capability
	UInt64 _freeSpaceInBytes;			// Free space in bytes
	UInt64 _freeSpaceInObjects;			// Free space in objects
	String _storageDescription;			// A brief description of this storage 
	String _volumeIdentifier;			// A volume identifier
public:
	// Constructor
	Storage(Device* pDevice, LPCWSTR objectID);
	// Copy constructor/operator
	Storage(const Storage& src) = delete;
	Storage& operator=(const Storage& src) = delete;
	// Move constructor/operator
	Storage(Storage&& src) noexcept = delete;
	Storage& operator=(Storage&& src) noexcept = delete;
protected:
	~Storage() = default;
public:
	static Storage* OpenStorage(size_t iDevice, size_t iStorage);
public:
	Device& GetDevice() { return *_pDevice; }
	LPCWSTR GetObjectID() const { return _objectID.c_str(); }
	const Symbol* GetStorageType() const { return _pStorageType; }
	const Symbol* GetFilesystemType() const { return _pFilesystemType; }
	const Symbol* GetAccessCapability() const { return _pAccessCapability; }
	UInt64 GetMaxCapacity() const { return _maxCapacity; }
	UInt64 GetFreeSpaceInBytes() const { return _freeSpaceInBytes; }
	UInt64 GetFreeSpaceInObjects() const { return _freeSpaceInObjects; }
	const char* GetStorageDescription() const { return _storageDescription.c_str(); }
	const char* GetVolumeIdentifier() const { return _volumeIdentifier.c_str(); }
	void SetStorageType(const Symbol* pStorageType) { _pStorageType = pStorageType; }
	void SetFilesystemType(const Symbol* pFilesystemType) { _pFilesystemType = pFilesystemType; }
	void SetAccessCapability(const Symbol* pAccessCapability) { _pAccessCapability = pAccessCapability; }
	void SetMaxCapacity(UInt64 maxCapacity) { _maxCapacity = maxCapacity; }
	void SetFreeSpaceInBytes(UInt64 freeSpaceInBytes) { _freeSpaceInBytes = freeSpaceInBytes; }
	void SetFreeSpaceInObjects(UInt64 freeSpaceInObjects) { _freeSpaceInObjects = freeSpaceInObjects; }
	void SetStorageDescription(const char* storageDescription) { _storageDescription = storageDescription; }
	void SetVolumeIdentifier(const char* volumeIdentifier) { _volumeIdentifier = volumeIdentifier; }
public:
	DirectoryEx* OpenDirectory(const char* pathName, bool errorIfNotFoundFlag);
	bool RecvFile(Processor& processor, const char* pathName, Stream& stream, const Function* pFuncBlock);
	bool SendFile(Processor& processor, const char* pathName, Stream& stream, const Function* pFuncBlock);
	bool DeleteFile(const char* pathName);
	bool MoveFile(const char* pathNameOld, const char* pathNameNew, bool overwriteFlag);
	bool CopyFile(const char* pathNameSrc, const char* pathNameDst, bool overwriteFlag);
public:
	static bool IsFileSeparator(char ch) { return ch == '/'; }
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
public:
	StorageOwner() {}
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

//-----------------------------------------------------------------------------
// Iterator_DirectoryGlobEx
//-----------------------------------------------------------------------------
class Iterator_DirectoryGlobEx : public Iterator_DirectoryGlob {
protected:
	RefPtr<Storage> _pStorage;
public:
	Iterator_DirectoryGlobEx(Storage* pStorage) : _pStorage(pStorage) {}
	virtual Directory* OpenDirectory(const char* pathName) override;
};

Gurax_EndModuleScope(mtp)

#endif
