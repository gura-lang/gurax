//==============================================================================
// Opt.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_OPT_H
#define GURAX_MODULE_CURL_OPT_H
#include <gurax.h>

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Opt
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Opt : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Opt);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("curl.Opt");
public:
	struct Pair {
		const char* name;
		CURLoption option;
	};
	using Map = std::unordered_map<const Symbol*, CURLoption, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
private:
	CURL* _curl;
private:
	static const Pair _pairTbl[];
	static Map _map;
public:
	RefPtr<Function> pFunc_WRITE;
	RefPtr<Function> pFunc_READ;
	RefPtr<Function> pFunc_HEADER;
	RefPtr<Function> pFunc_DEBUG;
	RefPtr<Function> pFunc_SSL_CTX;
	RefPtr<Function> pFunc_IOCTL;
	RefPtr<Function> pFunc_CONV_FROM_NETWORK;
	RefPtr<Function> pFunc_CONV_TO_NETWORK;
	RefPtr<Function> pFunc_CONV_FROM_UTF8;
	RefPtr<Function> pFunc_SOCKOPT;
	RefPtr<Function> pFunc_OPENSOCKET;
	RefPtr<Function> pFunc_SEEK;
	RefPtr<Function> pFunc_SSH_KEY;
	RefPtr<Function> pFunc_INTERLEAVE;
	RefPtr<Function> pFunc_CHUNK_BGN;
	RefPtr<Function> pFunc_CHUNK_END;
	RefPtr<Function> pFunc_FNMATCH;
	RefPtr<Function> pFunc_CLOSESOCKET;
	RefPtr<Function> pFunc_PROGRESS;
	RefPtr<Function> pFunc_XFERINFO;
	RefPtr<Function> pFunc_RESOLVER_START;
	RefPtr<Function> pFunc_TRAILER;
	RefPtr<Value> pValue_WRITE;
	RefPtr<Value> pValue_READ;
	RefPtr<Value> pValue_HEADER;
	RefPtr<Value> pValue_DEBUG;
	RefPtr<Value> pValue_SSL_CTX;
	RefPtr<Value> pValue_IOCTL;
	RefPtr<Value> pValue_CONV_FROM_NETWORK;
	RefPtr<Value> pValue_CONV_TO_NETWORK;
	RefPtr<Value> pValue_CONV_FROM_UTF8;
	RefPtr<Value> pValue_SOCKOPT;
	RefPtr<Value> pValue_OPENSOCKET;
	RefPtr<Value> pValue_SEEK;
	RefPtr<Value> pValue_SSH_KEY;
	RefPtr<Value> pValue_INTERLEAVE;
	RefPtr<Value> pValue_CHUNK_BGN;
	RefPtr<Value> pValue_CHUNK_END;
	RefPtr<Value> pValue_FNMATCH;
	RefPtr<Value> pValue_CLOSESOCKET;
	RefPtr<Value> pValue_PROGRESS;
	RefPtr<Value> pValue_XFERINFO;
	RefPtr<Value> pValue_RESOLVER_START;
	RefPtr<Value> pValue_TRAILER;
public:
	// Constructor
	Opt(CURL* curl);
	// Copy constructor/operator
	Opt(const Opt& src) = delete;
	Opt& operator=(const Opt& src) = delete;
	// Move constructor/operator
	Opt(Opt&& src) noexcept = delete;
	Opt& operator=(Opt&& src) noexcept = delete;
protected:
	~Opt() = default;
public:
	static void Bootup();
	bool SetProperty(const Symbol* pSymbol, const Value& value);
	bool SetItem(CURLoption option, const Value& value, CURLcode* pCode);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Opt& other) const { return this == &other; }
	bool IsEqualTo(const Opt& other) const { return IsIdentical(other); }
	bool IsLessThan(const Opt& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(curl)

#endif
