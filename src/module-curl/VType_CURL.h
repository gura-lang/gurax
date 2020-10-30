//==============================================================================
// VType_CURL.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_VTYPE_CURL_H
#define GURAX_MODULE_CURL_VTYPE_CURL_H
#include <gurax.h>
#include <curl/curl.h>

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// VType_CURL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_CURL : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_CURL VTYPE_CURL;

//------------------------------------------------------------------------------
// Value_CURL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_CURL : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_CURL);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_CURL");
protected:
	RefPtr<Processor> _pProcessor;
	CURL* _pCURL;
	RefPtr<Stream> _pStreamWrite;
	RefPtr<Stream> _pStreamRead;
public:
	RefPtr<Function> pFunc_WRITE;
	RefPtr<Function> pFunc_READ;
	RefPtr<Function> pFunc_PROGRESS;
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
	RefPtr<Function> pFunc_XFERINFO;
	RefPtr<Function> pFunc_RESOLVER_START;
	RefPtr<Function> pFunc_TRAILER;
	RefPtr<Value> pValue_WRITE;
	RefPtr<Value> pValue_READ;
	RefPtr<Value> pValue_PROGRESS;
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
	RefPtr<Value> pValue_XFERINFO;
	RefPtr<Value> pValue_RESOLVER_START;
	RefPtr<Value> pValue_TRAILER;
public:
	static VType& vtype;
public:
	// Constructor
	Value_CURL() = delete;
	explicit Value_CURL(Processor* pProcessor, CURL* pCURL, VType& vtype = VTYPE_CURL);
	// Copy constructor/operator
	Value_CURL(const Value_CURL& src) = delete;
	Value_CURL& operator=(const Value_CURL& src) = delete;
	// Move constructor/operator
	Value_CURL(Value_CURL&& src) noexcept = delete;
	Value_CURL& operator=(Value_CURL&& src) noexcept = delete;
protected:
	// Destructor
	~Value_CURL() = default;
public:
	CURL* GetEntityPtr() { return _pCURL; }
	const CURL* GetEntityPtr() const { return _pCURL; }
public:
	static CURL* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_CURL&>(value).GetEntityPtr();
	}
	static const CURL* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_CURL&>(value).GetEntityPtr();
	}
public:
	void SetStreamWrite(Stream* pStream) { _pStreamWrite.reset(pStream); }
	void SetStreamRead(Stream* pStream) { _pStreamRead.reset(pStream); }
	Stream& GetStreamWrite() { return *_pStreamWrite; }
	Stream& GetStreamRead() { return *_pStreamRead; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_CURL::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_CURL::GetEntityPtr(value) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	void SetupCallback();
	static size_t Callback_WRITE(char* ptr, size_t size, size_t nmemb, void* userdata);
	static size_t Callback_READ(char* ptr, size_t size, size_t nmemb, void* userdata);
	static void Callback_PROGRESS();
	static void Callback_HEADER();
	static void Callback_DEBUG();
	static void Callback_SSL_CTX();
	static void Callback_IOCTL();
	static void Callback_CONV_FROM_NETWORK();
	static void Callback_CONV_TO_NETWORK();
	static void Callback_CONV_FROM_UTF8();
	static void Callback_SOCKOPT();
	static void Callback_OPENSOCKET();
	static void Callback_SEEK();
	static void Callback_SSH_KEY();
	static void Callback_INTERLEAVE();
	static void Callback_CHUNK_BGN();
	static void Callback_CHUNK_END();
	static void Callback_FNMATCH();
	static void Callback_CLOSESOCKET();
	static void Callback_XFERINFO();
	static void Callback_RESOLVER_START();
	static void Callback_TRAILER();
};

Gurax_EndModuleScope(curl)

#endif
