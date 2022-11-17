//==============================================================================
// Info.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_INFO_H
#define GURAX_MODULE_CURL_INFO_H
#include <gurax.h>

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Info
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Info : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Info);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("curl.Info");
public:
	struct Pair {
		const char* name;
		CURLINFO info;
	};
	using Map = std::unordered_map<const Symbol*, CURLINFO, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
private:
	CURL* _curl;
private:
	static Map _map;
	static const Pair _pairTbl[];
public:
	// Constructor
	Info(CURL* curl) : _curl(curl) {}
	// Copy constructor/operator
	Info(const Info& src) = delete;
	Info& operator=(const Info& src) = delete;
	// Move constructor/operator
	Info(Info&& src) noexcept = delete;
	Info& operator=(Info&& src) noexcept = delete;
protected:
	~Info() = default;
public:
	static void Bootup();
	Value* GetProperty(const Symbol* pSymbol);
	Value* GetItem(CURLINFO info);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Info& other) const { return this == &other; }
	bool IsEqualTo(const Info& other) const { return IsIdentical(other); }
	bool IsLessThan(const Info& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(curl)

#endif
