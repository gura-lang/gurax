//=============================================================================
// Codec
//=============================================================================
#ifndef GURAX_CODEC_H
#define GURAX_CODEC_H
#include "Binary.h"

namespace Gurax {

class Codec;
class CodecFactory;

//-----------------------------------------------------------------------------
// CodecFactoryList
//-----------------------------------------------------------------------------
using CodecFactoryList = std::vector<CodecFactory*>;

//-----------------------------------------------------------------------------
// CodecFactory
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE CodecFactory {
private:
	String _encoding;
	static CodecFactoryList _codecFactoryList;
public:
	static CodecFactory* Dumb;
public:
	CodecFactory(String encoding);
	const char* GetEncoding() const { return _encoding.c_str(); }
	virtual Codec* CreateCodec(bool delcrFlag, bool addcrFlag) = 0;
public:
	static CodecFactoryList& GetList() { return _codecFactoryList; }
	static void Register(CodecFactory* pFactory);
	static CodecFactory* Lookup(const char* name);
};

//-----------------------------------------------------------------------------
// Codec
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Codec : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Codec);
public:
	enum class Result { None, Complete, Error };
	enum class WidthProp { N, A, H, W, F, Na };
	struct BOM {
		// Byte Order Mark of Unicode
		static const char* const UTF8;
		static const char* const UTF16BE;
		static const char* const UTF16LE;
		static const char* const UTF32BE;
		static const char* const UTF32LE;
	};
	using Map = std::map<UInt16, UInt16>;
	struct CodeRow {
		int nCols;
		const UInt16* row;
	};
	struct WidthInfo {
		UInt32 codeUTF32Ceil;
		WidthProp widthProp;
	};
public:
	class GURAX_DLLDECLARE DecEncBase {
	protected:
		int _idxBuff;
		char _buffOut[8];
	public:
		DecEncBase() : _idxBuff(0) {}
		bool FollowChar(char& chConv);
		virtual Result FeedChar(char ch, char& chConv) = 0;
		virtual Result Flush(char& chConv);
	protected:
		void StoreChar(char ch) { _buffOut[_idxBuff++] = ch; }
	};
	class GURAX_DLLDECLARE Decoder : public DecEncBase {
	private:
		bool _delcrFlag;
	public:
		explicit Decoder(bool delcrFlag) : _delcrFlag(delcrFlag) {}
		void SetDelcrFlag(bool delcrFlag) { _delcrFlag = delcrFlag; }
		bool GetDelcrFlag() const { return _delcrFlag; }
		bool Decode(String& dst, const UInt8* src, size_t bytes);
		bool Decode(String& dst, const Binary& src) { return Decode(dst, src.data(), src.size()); }
	};
	class GURAX_DLLDECLARE Encoder : public DecEncBase {
	private:
		bool _addcrFlag;
	public:
		explicit Encoder(bool addcrFlag) : _addcrFlag(addcrFlag) {}
		void SetAddcrFlag(bool addcrFlag) { _addcrFlag = addcrFlag; }
		bool GetAddcrFlag() const { return _addcrFlag; }
		bool Encode(Binary& dst, const char* src);
		bool Encode(Binary& dst, const String& src) { return Encode(dst, src.c_str()); }
	};
private:
	CodecFactory* _pCodecFactory;
	std::unique_ptr<Decoder> _pDecoder;
	std::unique_ptr<Encoder> _pEncoder;
	static const WidthInfo _widthInfoTbl[];
public:
	static RefPtr<Codec> Dumb;
public:
	// Constructor
	Codec(CodecFactory* pCodecFactory, Decoder* pDecoder, Encoder* pEncoder);
	// Copy constructor/operator
	Codec(const Codec& src) = delete;
	Codec& operator=(const Codec& src) = delete;
	// Move constructor/operator
	Codec(Codec&& src) = delete;
	Codec& operator=(Codec&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Codec() = default;
public:
	CodecFactory& GetCodecFactory() { return *_pCodecFactory; }
	const CodecFactory& GetCodecFactory() const { return *_pCodecFactory; }
	const char* GetEncoding() const { return GetCodecFactory().GetEncoding(); }
	Decoder& GetDecoder() { return *_pDecoder; }
	Encoder& GetEncoder() { return *_pEncoder; }
	const Decoder& GetDecoder() const { return *_pDecoder; }
	const Encoder& GetEncoder() const { return *_pEncoder; }
	bool GetDelcrFlag() const { return GetDecoder().GetDelcrFlag(); }
	bool GetAddcrFlag() const { return GetEncoder().GetAddcrFlag(); }
	void SetDelcrFlag(bool delcrFlag) { GetDecoder().SetDelcrFlag(delcrFlag); }
	void SetAddcrFlag(bool addcrFlag) { GetEncoder().SetAddcrFlag(addcrFlag); }
	Codec* Duplicate() const;
	static Codec* Create(const char* encoding, bool delcrFlag, bool addcrFlag);
	static void Bootup();
	static UInt16 DBCSToUTF16(const CodeRow codeRows[], int nCodeRows, UInt16 codeDBCS);
	static UInt16 UTF16ToDBCS(const CodeRow codeRows[], int nCodeRows, UInt16 codeUTF16, Map** ppMap);
	static WidthProp GetWidthProp(UInt32 codeUTF32);
public:
	static const char* EncodingFromLANG();
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Codec& codec) const { return this == &codec; }
	bool IsEqualTo(const Codec& codec) const { return IsIdentical(codec); }
	bool IsLessThan(const Codec& codec) const { return this < &codec; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//-----------------------------------------------------------------------------
// CodecFactory_Generic
//-----------------------------------------------------------------------------
template<typename T>
class CodecFactory_Generic : public CodecFactory {
public:
	explicit CodecFactory_Generic(const char* encoding) : CodecFactory(encoding) {}
	virtual Codec* CreateCodec(bool delcrFlag, bool addcrFlag) override {
		return new Codec(this, new typename T::Decoder(delcrFlag), new typename T::Encoder(addcrFlag));
	}
};

//-----------------------------------------------------------------------------
// Codec_Dumb
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Codec_Dumb : public Codec {
public:
	using Codec::Codec;
public:
	class GURAX_DLLDECLARE Decoder : public Codec::Decoder {
	public:
		explicit Decoder(bool delcrFlag) : Codec::Decoder(delcrFlag) {}
		virtual Result FeedChar(char ch, char& chConv) override;
	};
	class GURAX_DLLDECLARE Encoder : public Codec::Encoder {
	public:
		explicit Encoder(bool addcrFlag) : Codec::Encoder(addcrFlag) {}
		virtual Result FeedChar(char ch, char& chConv) override;
	};
};

//-----------------------------------------------------------------------------
// Codec_UTF
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Codec_UTF : public Codec {
public:
	using Codec::Codec;
public:
	class GURAX_DLLDECLARE Decoder : public Codec::Decoder {
	public:
		explicit Decoder(bool delcrFlag) : Codec::Decoder(delcrFlag) {}
		Result FeedUTF32(UInt32 codeUTF32, char& chConv);
	};
	class GURAX_DLLDECLARE Encoder : public Codec::Encoder {
	protected:
		int _cntChars;
		UInt32 _codeUTF32;
	public:
		explicit Encoder(bool addcrFlag) :
			Codec::Encoder(addcrFlag), _cntChars(0), _codeUTF32(0x00000000) {}
		UInt32 GetUTF32() const { return _codeUTF32; }
		virtual Result FeedChar(char ch, char& chConv) override;
		virtual Result FeedUTF32(UInt32 codeUTF32, char& chConv) = 0;
	};
};

//-----------------------------------------------------------------------------
// Codec_SBCS
//-----------------------------------------------------------------------------
class Codec_SBCS : public Codec_UTF {
public:
	using Codec_UTF::Codec_UTF;
public:
	class Decoder : public Codec_UTF::Decoder {
	private:
		const UInt16* _tblToUTF16;
	public:
		Decoder(bool delcrFlag, const UInt16* tblToUTF16) :
			Codec_UTF::Decoder(delcrFlag), _tblToUTF16(tblToUTF16) {}
		virtual Result FeedChar(char ch, char& chConv) override;
	};
	class Encoder : public Codec_UTF::Encoder {
	private:
		const Map& _mapToSBCS;
	public:
		Encoder(bool addcrFlag, const Map& mapToSBCS) :
			Codec_UTF::Encoder(addcrFlag), _mapToSBCS(mapToSBCS) {}
		virtual Result FeedUTF32(UInt32 codeUTF32, char& chConv) override;
	};
};

//-----------------------------------------------------------------------------
// CodecFactory_SBCS
//-----------------------------------------------------------------------------
class CodecFactory_SBCS : public CodecFactory {
public:
	const UInt16* _tblToUTF16;
	Codec::Map _mapToSBCS;
public:
	CodecFactory_SBCS(String encoding, const UInt16* tblToUTF16);
	virtual Codec* CreateCodec(bool delcrFlag, bool addcrFlag) override;
};

//-----------------------------------------------------------------------------
// Codec_DBCS
//-----------------------------------------------------------------------------
class Codec_DBCS : public Codec_UTF {
public:
	using Codec_UTF::Codec_UTF;
public:
	class Decoder : public Codec_UTF::Decoder {
	private:
		UInt16 _codeDBCS;
	public:
		explicit Decoder(bool delcrFlag) : Codec_UTF::Decoder(delcrFlag), _codeDBCS(0x0000) {}
		virtual Result FeedChar(char ch, char& chConv) override;
		virtual bool IsLeadByte(UChar ch) { return ch >= 0x80; }
		virtual UInt16 DBCSToUTF16(UInt16 codeDBCS) = 0;
	};
	class Encoder : public Codec_UTF::Encoder {
	public:
		explicit Encoder(bool addcrFlag) : Codec_UTF::Encoder(addcrFlag) {}
		virtual Result FeedUTF32(UInt32 codeUTF32, char& chConv) override;
		virtual UInt16 UTF16ToDBCS(UInt16 codeUTF16) = 0;
	};
};

}

#endif
