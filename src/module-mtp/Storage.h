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

Gurax_EndModuleScope(mtp)

#endif
