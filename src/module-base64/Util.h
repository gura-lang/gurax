//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_BASE64_UTIL_H
#define GURAX_MODULE_BASE64_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(base64)

//------------------------------------------------------------------------------
// Decoder
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Decoder : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Decoder);
public:
	struct Info {
		const char* name;
		const int numTbl[256];
		const size_t bytesOutTbl[16];
		size_t bytesPerGroup;
		size_t nCharsPerGroup;
		size_t bitsPerChar;
	};
private:
	RefPtr<Stream> _pStreamOut;
	int _nCharsAccum;
	int _nPaddings;
	UInt64 _accum;
	size_t _iBuffWork;
	const Info& _info;
public:
	static const int SPC = -1;
	static const int PAD = -2;
	static const int ERR = -3;
	static const Info info_Base16;
	static const Info info_Base32;
	static const Info info_Base32hex;
	static const Info info_Base64;
public:
	// Constructor
	Decoder(Stream* pStreamOut, const Info& info);
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
};

//------------------------------------------------------------------------------
// Encoder
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Encoder : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Encoder);
private:
	RefPtr<Stream> _pStreamOut;
	size_t _nCharsPerLine;
	size_t _column;
	size_t _bytesAccum;
	UInt64 _accum;
private:
	static const char _charTbl[];
public:
	// Constructor
	Encoder(Stream* pStreamOut, int nCharsPerLine);
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
};

Gurax_EndModuleScope(base64)

#endif
