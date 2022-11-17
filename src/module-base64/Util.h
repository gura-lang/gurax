//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_BASE64_UTIL_H
#define GURAX_MODULE_BASE64_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(base64)

//------------------------------------------------------------------------------
// Info
//------------------------------------------------------------------------------
struct Info {
	const char* name;
	const char* charTbl;
	const size_t bytesOutTbl[16];
	const int nPaddingsTbl[16];
	size_t bytesPerGroup;
	size_t nCharsPerGroup;
	size_t bitsPerChar;
	size_t nCharsPerLineDefault;
public:
	static const Info Base16;
	static const Info Base32;
	static const Info Base32hex;
	static const Info Base64;
};

//------------------------------------------------------------------------------
// Decoder
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Decoder : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Decoder);
public:
	struct Code {
		static const int Space = -1;
		static const int Padding = -2;
		static const int Error = -3;
	};
private:
	RefPtr<Stream> _pStreamDst;
	int _nCharsAccum;
	int _nPaddings;
	UInt64 _accum;
	size_t _iBuffWork;
	int _numTbl[256];
	const Info& _info;
public:
	// Constructor
	Decoder(Stream* pStreamDst, const Info& info);
	// Copy constructor/operator
	Decoder(const Decoder& src) = delete;
	Decoder& operator=(const Decoder& src) = delete;
	// Move constructor/operator
	Decoder(Decoder&& src) noexcept = delete;
	Decoder& operator=(Decoder&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Decoder() = default;
public:
	bool Decode(const void* buff, size_t bytes);
	bool DecodeStream(Stream& streamSrc, size_t bytesUnit = 65536);
public:
	static bool Decode(BinaryReferable& buffDst,
						const void* buff, size_t bytes, const Info& info);
	static bool Decode(BinaryReferable& buffDst,
						const Binary& buffSrc, const Info& info) {
		return Decode(buffDst, buffSrc.data(), buffSrc.size(), info);
	}
};

//------------------------------------------------------------------------------
// Encoder
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Encoder : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Encoder);
private:
	RefPtr<Stream> _pStreamDst;
	size_t _nCharsPerLine;
	size_t _iCol;
	size_t _bytesAccum;
	UInt64 _accum;
	const Info& _info;
public:
	// Constructor
	Encoder(Stream* pStreamDst, int nCharsPerLine, const Info& info);
	// Copy constructor/operator
	Encoder(const Encoder& src)	= delete;
	Encoder& operator=(const Encoder& src) = delete;
	// Move constructor/operator
	Encoder(Encoder&& src) noexcept = delete;
	Encoder& operator=(Encoder&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Encoder() = default;
public:
	bool Encode(const void* buff, size_t bytes);
	bool EncodeStream(Stream& streamSrc, size_t bytesUnit = 65536);
	bool Finish();
public:
	static size_t CalcAlign(size_t n, size_t align) {
		return (align <= 1)? n : (n + align - 1) / align * align;
	}
};

//------------------------------------------------------------------------------
// Stream_Reader
//------------------------------------------------------------------------------
class Stream_Reader : public Stream {
protected:
	RefPtr<Stream> _pStreamSrc;
	RefPtr<Stream_Binary> _pStreamMid;
	RefPtr<Decoder> _pDecoder;
	size_t _offsetMid;
public:
	Stream_Reader(Stream* pStreamSrc, const Info& info);
	~Stream_Reader() { Close(); }
public:
	virtual const char* GetName() const override { return "base64.Reader"; };
	virtual const char* GetIdentifier() const override { return ""; }
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override { return 0; }
	virtual bool DoPutChar(char ch) override { return _pDecoder->Decode(&ch, 1); }
	virtual size_t DoRead(void* buff, size_t bytes) override;
	virtual bool DoWrite(const void* buff, size_t bytes) override { return false; }
	virtual bool DoFlush() override { return true; }
};

//------------------------------------------------------------------------------
// Stream_Writer
//------------------------------------------------------------------------------
class Stream_Writer : public Stream {
protected:
	RefPtr<Encoder> _pEncoder;
public:
	Stream_Writer(Stream* pStreamDst, size_t nCharsPerLine, const Info& info);
	~Stream_Writer() { Close(); }
public:
	virtual const char* GetName() const override { return "base64.Writer"; };
	virtual const char* GetIdentifier() const override { return ""; }
	virtual bool DoClose() override { return _pEncoder->Finish(); }
	virtual int DoGetChar() override { return 0; }
	virtual bool DoPutChar(char ch) override { return _pEncoder->Encode(&ch, 1); }
	virtual size_t DoRead(void* buff, size_t bytes) override { return 0; }
	virtual bool DoWrite(const void* buff, size_t bytes) override {
		return _pEncoder->Encode(buff, bytes);
	}
	virtual bool DoFlush() override { return true; }
};

Gurax_EndModuleScope(base64)

#endif
