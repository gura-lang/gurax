//==============================================================================
// RegKey.h
//==============================================================================
#ifndef GURAX_MODULE_MSWIN_REGKEY_H
#define GURAX_MODULE_MSWIN_REGKEY_H
#include <gurax.h>

Gurax_BeginModuleScope(mswin)

//------------------------------------------------------------------------------
// RegKey
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE RegKey : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(RegKey);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("mswin.RegKey");
private:
	HKEY _hKey;
	String _name;
	bool _ownerFlag;
public:
	// Constructor
	RegKey(HKEY hKey, String name, bool ownerFlag = true);
	// Copy constructor/operator
	RegKey(const RegKey& src) = delete;
	RegKey& operator=(const RegKey& src) = delete;
	// Move constructor/operator
	RegKey(RegKey&& src) noexcept = delete;
	RegKey& operator=(RegKey&& src) noexcept = delete;
protected:
	~RegKey();
public:
	HKEY GetHKEY() { return _hKey; }
	const char* GetName() const { return _name.c_str(); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const RegKey& other) const { return this == &other; }
	bool IsEqualTo(const RegKey& other) const { return IsIdentical(other); }
	bool IsLessThan(const RegKey& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(mswin)

#endif
