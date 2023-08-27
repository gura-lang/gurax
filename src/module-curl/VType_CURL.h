//==============================================================================
// VType_CURL.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_VTYPE_CURL_H
#define GURAX_MODULE_CURL_VTYPE_CURL_H
#include <gurax.h>
#include <curl/curl.h>
#include "Info.h"
#include "Opt.h"

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
	CURL* _curl;
	RefPtr<Info> _pInfo;
	RefPtr<Opt> _pOpt;
	RefPtr<Stream> _pStreamWrite;
	RefPtr<Stream> _pStreamRead;
	RefPtr<Stream> _pStreamHeader;
public:
	static VType& vtype;
public:
	// Constructor
	Value_CURL() = delete;
	explicit Value_CURL(Processor* pProcessor, CURL* curl, VType& vtype = VTYPE_CURL);
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
	CURL* GetEntityPtr() { return _curl; }
	const CURL* GetEntityPtr() const { return _curl; }
public:
	static CURL* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_CURL&>(value).GetEntityPtr();
	}
	static const CURL* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_CURL&>(value).GetEntityPtr();
	}
public:
	Processor& GetProcessor() { return *_pProcessor; }
	void SetStreamWrite(Stream* pStream) { _pStreamWrite.reset(pStream); }
	void SetStreamRead(Stream* pStream) { _pStreamRead.reset(pStream); }
	void SetStreamHeader(Stream* pStream) { _pStreamHeader.reset(pStream); }
	bool IsValidStreamWrite() { return !!_pStreamWrite; }
	bool IsValidStreamRead() { return !!_pStreamRead; }
	bool IsValidStreamHeader() { return !!_pStreamHeader; }
	Stream& GetStreamWrite() { return *_pStreamWrite; }
	Stream& GetStreamRead() { return *_pStreamRead; }
	Stream& GetStreamHeader() { return *_pStreamHeader; }
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
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	void SetupCallback();
	Info& GetInfo() { return *_pInfo; }
	Opt& GetOpt() { return *_pOpt; }
public:
	static size_t Callback_WRITE(char* ptr, size_t size, size_t nitems, void* userdata);
	static size_t Callback_READ(char* ptr, size_t size, size_t nitems, void* userdata);
	static size_t Callback_HEADER(char* ptr, size_t size,   size_t nitems, void* userdata);
	static int Callback_DEBUG(CURL* curl, curl_infotype type, char* data, size_t size, void* userdata);
	static CURLcode Callback_SSL_CTX(CURL* curl, void* ssl_ctx, void* userdata);
	static curlioerr Callback_IOCTL(CURL* curl, int cmd, void* userdata);
	static CURLcode Callback_CONV_FROM_NETWORK(char* ptr, size_t length);
	static CURLcode Callback_CONV_TO_NETWORK(char* ptr, size_t length);
	static CURLcode Callback_CONV_FROM_UTF8(char* ptr, size_t length);
	static int Callback_SOCKOPT(void* userdata, curl_socket_t curlfd, curlsocktype purpose);
	static curl_socket_t Callback_OPENSOCKET(void* userdata, curlsocktype purpose, curl_sockaddr* address);
	static int Callback_SEEK(void* userdata, curl_off_t offset, int origin);
	static int Callback_SSH_KEY(CURL* curl, const curl_khkey* knownkey, const curl_khkey* foundkey, curl_khmatch match, void* userdata);
	static size_t Callback_INTERLEAVE(void* ptr, size_t size, size_t nitems, void* userdata);
	static long Callback_CHUNK_BGN(const void* transfer_info, void* userdata, int remains);
	static long Callback_CHUNK_END(void* userdata);
	static int Callback_FNMATCH(void* userdata, const char* pattern, const char* string);
	static int Callback_CLOSESOCKET(void* userdata, curl_socket_t item);
	static int Callback_PROGRESS(void* userdata, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
	static int Callback_XFERINFO(void* userdata, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
	static int Callback_RESOLVER_START(void* resover_state, void* reserved, void* userdata);
	static int Callback_TRAILER(struct curl_slist** list, void* userdata);
};

Gurax_EndModuleScope(curl)

#endif
