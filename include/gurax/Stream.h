//==============================================================================
// Stream.h
//==============================================================================
#ifndef GURAX_STREAM_H
#define GURAX_STREAM_H
#include "Codec.h"
#include "DateTime.h"
#include "Formatter.h"
#include "Binary.h"
#include "Pointer.h"
#include "StringPicker.h"
#include "StringStyle.h"
#include "Memory.h"

namespace Gurax {

class Stat;
class Value_Stat;
class Rational;

//------------------------------------------------------------------------------
// Stream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stream : public Referable, public CharSeq {
public:
	// Referable declaration
	Gurax_DeclareReferable(Stream);
public:
	class GURAX_DLLDECLARE FormatterEx : public Formatter {
	private:
		Stream& _stream;
	public:
		// Constructor
		FormatterEx(Stream& stream) : _stream(stream) {}
	public:
		// Virtual functions of Formatter
		virtual bool PutChar(char ch) override { return _stream.PutChar(ch); }
	};
	enum class SeekMode { Set, Cur, End };
	using Flags = UInt32;
	struct GURAX_DLLDECLARE Flag {
		static const Flags None				= 0;
		static const Flags Readable			= (1 << 0);
		static const Flags Writable			= (1 << 1);
		static const Flags BwdSeekable		= (1 << 2);
		static const Flags FwdSeekable		= (1 << 3);
		static const Flags Infinite			= (1 << 4);
	};
	using OpenFlags = UInt32;
	struct GURAX_DLLDECLARE OpenFlag {
		static const Flags None			= 0;
		static const Flags Read			= (1 << 0);
		static const Flags Write		= (1 << 1);
		static const Flags Append		= (1 << 2);
	};
public:
	static RefPtr<Stream> Dumb;
	static RefPtr<Stream> CIn;
	static RefPtr<Stream> COut;
	static RefPtr<Stream> CErr;
protected:
	Flags _flags;
	size_t _offset;
	RefPtr<Codec> _pCodec;
	struct {
		char buff[8];
		size_t cnt;
		size_t idx;
	} _decodeBuff;
public:
	static void Bootup();
public:
	// Constructor
	Stream(Flags flags, size_t offset = 0);
	Stream(Flags flags, Codec* pCodec, size_t offset = 0);
	// Copy constructor/operator
	Stream(const Stream& src) = delete;
	Stream& operator=(const Stream& src) = delete;
	// Move constructor/operator
	Stream(Stream&& src) = delete;
	Stream& operator=(Stream&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Stream() = default;
public:
	static Stream* Open(const char* pathName, OpenFlags openFlags);
	Flags GetFlags() const { return _flags; }
	size_t GetOffset() const { return _offset; }
	bool IsInfinite() const { return _flags & Flag::Infinite; }
	bool IsBwdSeekable() const { return _flags & Flag::BwdSeekable; }
	bool IsReadable() const { return _flags & Flag::Readable; }
	bool IsWritable() const { return _flags & Flag::Writable; }
	bool CheckReadable() const;
	bool CheckWritable() const;
	void SetCodec(Codec* pCodec) { _pCodec.reset(pCodec); }
	Codec& GetCodec() const { return *_pCodec; }
	virtual char GetChar() override;
	bool PutChar(char ch);
	Stream& Print(const char* str);
	Stream& Print(const String& str) { return Print(str.c_str()); }
	Stream& Print(StringPicker&& strPicker);
	Stream& Print(const StringList& strList) { return Print(StringPicker_StringList(strList)); }
	Stream& Print(const ValueList& valueList, const StringStyle& ss) {
		return Print(StringPicker_ValueList(valueList, ss));
	}
	Stream& Println(const char* str);
	Stream& Println(const String& str) { return Println(str.c_str()); }
	Stream& Println(StringPicker&& strPicker);
	Stream& Println(const StringList& strList) { return Println(StringPicker_StringList(strList)); }
	Stream& Println(const ValueList& valueList, const StringStyle& ss) {
		return Println(StringPicker_ValueList(valueList, ss));
	}
	Stream& Println() { PutChar('\n'); return *this; }
	Stream& PrintfV(const char* format, va_list ap);
	Stream& PrintfV(const String& format, va_list ap) { return PrintfV(format.c_str(), ap); }
	Stream& Printf(const char* format, ...);
	Stream& Printf(const String& format, ...);
	Stream& PrintValueList(const char* format, const ValueList& valueList);
	Stream& PrintValueList(const String& format, const ValueList& valueList) {
		return PrintValueList(format.c_str(), valueList);
	}
	bool ReadLine(String& str, bool includeEOLFlag);
	Iterator* ReadLines(size_t nLines, bool includeEOLFlag);
	Stream& SkipLines(size_t nLines);
	String ReadText();
	Binary Read(size_t len);
	BinaryReferable* ReadAsReferable(size_t len);
	static OpenFlags ModeToOpenFlags(const char* mode);
	Stream* CreateBwdSeekable();
	void Dump(const void* buff, size_t bytes, const DumpStyle& ds = DumpStyle::Empty);
	void Dump(const Binary& binary, const DumpStyle& ds = DumpStyle::Empty) {
		Dump(binary.data(), binary.size(), ds);
	}
	void Dump(const Memory& memory, const DumpStyle& ds = DumpStyle::Empty) {
		Dump(memory.GetPointerC<void>(), memory.GetBytes(), ds);
	}
public:
	size_t GetBytes() { return DoGetBytes(); }
	Stat* CreateStat() { return DoCreateStat(); }
	Value_Stat* CreateStatValue() { return DoCreateStatValue(); }
	bool Close() { return DoClose(); }
	size_t Read(void* buff, size_t len) { return DoRead(buff, len); }
	bool Write(const void* buff, size_t len) { return DoWrite(buff, len); }
	bool Write(const Binary& buff) { return Write(buff.data(), buff.size()); }
	bool Write(const Pointer& ptr) { return Write(ptr.GetPointerC<void>(), ptr.GetBytesAvailable()); }
	bool Flush() { return DoFlush(); }
	bool Seek(long offsetRel, SeekMode seekMode);
	bool SetOffset(size_t offset);
	bool ReadToBinary(Binary& buff, size_t bytesUnit = 65536);
	bool PipeToStream(Stream& streamDst, size_t bytesUnit = 65536);
	bool PipeToStreamCooked(Stream& streamDst);
	bool PipeFromStream(Stream& streamSrc, size_t bytesUnit = 65536) {
		return streamSrc.PipeToStream(*this, bytesUnit);
	}
	bool PipeFromStreamCooked(Stream& streamSrc) {
		return streamSrc.PipeToStreamCooked(*this);
	}
	bool HasIdentifier() const { return *GetIdentifier() != '\0'; }
public:
	virtual bool IsDumb() const { return false; }
	virtual const char* GetName() const = 0;
	virtual const char* GetIdentifier() const = 0;
	virtual size_t DoGetBytes() { return 0; }
	virtual Stat* DoCreateStat() { return nullptr; }
	virtual Value_Stat* DoCreateStatValue() { return nullptr; }
	virtual bool DoClose() = 0;
	virtual size_t DoRead(void* buff, size_t len) = 0;
	virtual bool DoWrite(const void* buff, size_t len) = 0;
	virtual bool DoFlush() = 0;
	virtual bool DoSeek(size_t offset, size_t offsetPrev);
protected:
	virtual int DoGetChar();
	virtual bool DoPutChar(char ch);
public:
	template<typename T_Num> bool SerializeNumber(T_Num num) { return Write(&num, sizeof(num)); }
	template<typename T_Num> bool DeserializeNumber(T_Num& num);
	template<typename T_Num> bool SerializePackedNumber(T_Num num);
	template<typename T_Num> bool DeserializePackedNumber(T_Num& num);
	template<typename T_Num> bool DeserializePackedNumber(T_Num& num, bool* pEndOfFileFlag);
	template<typename T_Num> bool SerializeNumList(const NumList<T_Num>& numList);
	template<typename T_Num> bool DeserializeNumList(NumList<T_Num>& numList);
	template<typename T_Num> bool SerializePackedNumList(const NumList<T_Num>& numList);
	template<typename T_Num> bool DeserializePackedNumList(NumList<T_Num>& numList);
	bool SerializeComplex(const Complex& num);
	bool DeserializeComplex(Complex& num);
	bool SerializeRational(const Rational& num);
	bool DeserializeRational(Rational& num);
	bool SerializeString(const char* str);
	bool DeserializeString(String& str);
	bool SerializeBinary(const Binary& binary);
	bool DeserializeBinary(Binary& binary);
	//bool SerializeMemory(const Memory& memory);
	//bool DeserializeMemory(RefPtr<Memory>& pMemory);
	bool SerializeSymbol(const Symbol* pSymbol);
	bool DeserializeSymbol(const Symbol*& pSymbol);
	bool SerializeSymbolSet(const SymbolSet& symbolSet);
	bool DeserializeSymbolSet(SymbolSet& symbolSet);
	bool SerializeSymbolList(const SymbolList& symbolList);
	bool DeserializeSymbolList(SymbolList& symbolList);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Stream& stream) const { return this == &stream; }
	bool IsEqualTo(const Stream& stream) const { return IsIdentical(stream); }
	bool IsLessThan(const Stream& stream) const { return this < &stream; }
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

template<typename T_Num> bool Stream::DeserializeNumber(T_Num& num)
{
	const char* errMsg = "invalid format of serialized number";
	if (Read(&num, sizeof(num)) == sizeof(num)) return true;
	Error::Issue(ErrorType::FormatError, errMsg);
	return false;
}

template<typename T_Num> bool Stream::SerializePackedNumber(T_Num num)
{
	UInt8 buff[sizeof(T_Num)];
	size_t bytesBuff = 0;
	if (num == 0) {
		buff[bytesBuff++] = 0x00;
	} else {
		while (num > 0) {
			UInt8 data = static_cast<UInt8>(num & 0x7f);
			num >>= 7;
			buff[bytesBuff++] = (num == 0)? data : (data | 0x80);
		}
	}
	return Write(buff, bytesBuff);
}

template<typename T_Num> bool Stream::DeserializePackedNumber(T_Num& num)
{
	const char* errMsg = "invalid format of serialized packed number";
	const size_t bytesBuffMax = (sizeof(T_Num) * 8 + 7) / 7;
	num = 0;
	UInt8 data = 0x00;
	size_t nShift = 0;
	for (size_t bytesBuff = 0; bytesBuff < bytesBuffMax; bytesBuff++, nShift += 7) {
		if (Read(&data, sizeof(data)) != sizeof(data)) {
			Error::Issue(ErrorType::FormatError, errMsg);
			return false;
		}
		num += static_cast<T_Num>(data & 0x7f) << nShift;
		if (!(data & 0x80)) return true;
	}
	Error::Issue(ErrorType::FormatError, errMsg);
	return false;
}

template<typename T_Num> bool Stream::DeserializePackedNumber(T_Num& num, bool* pEndOfFileFlag)
{
	const char* errMsg = "invalid format of serialized packed number";
	const size_t bytesBuffMax = (sizeof(T_Num) * 8 + 7) / 7;
	num = 0;
	UInt8 data = 0x00;
	size_t nShift = 0;
	*pEndOfFileFlag = false;
	for (size_t bytesBuff = 0; bytesBuff < bytesBuffMax; bytesBuff++, nShift += 7) {
		if (Read(&data, sizeof(data)) != sizeof(data)) {
			if (bytesBuff == 0) {
				*pEndOfFileFlag = true;
			} else {
				Error::Issue(ErrorType::FormatError, errMsg);
			}
			return false;
		}
		num += static_cast<T_Num>(data & 0x7f) << nShift;
		if (!(data & 0x80)) return true;
	}
	Error::Issue(ErrorType::FormatError, errMsg);
	return false;
}

template<typename T_Num> bool Stream::SerializeNumList(const NumList<T_Num>& numList)
{
	if (!SerializePackedNumber(static_cast<UInt64>(numList.size()))) return false;
	for (T_Num num : numList) {
		if (!SerializeNumber<T_Num>(num)) return false;
	}
	return true;
}

template<typename T_Num> bool Stream::DeserializeNumList(NumList<T_Num>& numList)
{
	UInt64 n = 0;
	if (!DeserializePackedNumber(static_cast<UInt64>(n))) return false;
	if (n == 0) return true;
	numList.reserve(n);
	for (size_t i = 0; i < n; i++) {
		T_Num num;
		if (!DeserializeNumber<T_Num>(num)) return false;
		numList.push_back(num);
	}
	return true;
}

template<typename T_Num> bool Stream::SerializePackedNumList(const NumList<T_Num>& numList)
{
	if (!SerializePackedNumber(static_cast<UInt64>(numList.size()))) return false;
	for (T_Num num : numList) {
		if (!SerializePackedNumber<T_Num>(num)) return false;
	}
	return true;
}

template<typename T_Num> bool Stream::DeserializePackedNumList(NumList<T_Num>& numList)
{
	UInt64 n = 0;
	if (!DeserializePackedNumber(static_cast<UInt64>(n))) return false;
	if (n == 0) return true;
	numList.reserve(n);
	for (size_t i = 0; i < n; i++) {
		T_Num num;
		if (!DeserializePackedNumber<T_Num>(num)) return false;
		numList.push_back(num);
	}
	return true;
}

//------------------------------------------------------------------------------
// Iterator_ReadLines
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_ReadLines : public Iterator {
private:
	RefPtr<Stream> _pStream;
	size_t _nLines;
	bool _includeEOLFlag;
	bool _doneFlag;
public:
	Iterator_ReadLines(Stream* pStream, size_t nLines, bool includeEOLFlag);
public:
	Stream& GetStream() { return *_pStream; }
	const Stream& GetStream() const { return *_pStream; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return (GetStream().IsInfinite()? Flag::Infinite : Flag::Finite) | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Deserialize
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Deserialize : public Iterator {
private:
	RefPtr<Stream> _pStream;
public:
	Iterator_Deserialize(Stream* pStream) : _pStream(pStream) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Infinite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
