//==============================================================================
// Stream.h
//==============================================================================
#ifndef GURAX_STREAM_H
#define GURAX_STREAM_H
#include "Codec.h"
#include "DateTime.h"
#include "Formatter.h"
#include "StringPicker.h"

namespace Gurax {

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
	//enum class ErrorType { None, Codec };
	using Flags = UInt32;
	struct Flag {
		static const Flags None			= 0;
		static const Flags Infinite		= (1 << 0);
		static const Flags BwdSeekable	= (1 << 1);
		static const Flags Readable		= (1 << 2);
		static const Flags Writable		= (1 << 3);
	};
	using OpenFlags = UInt32;
	struct OpenFlag {
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
	RefPtr<Codec> _pCodec;
public:
	static void Bootup();
public:
	// Constructor
	Stream(Flags flags);
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
	bool IsInfinite() const { return _flags & Flag::Infinite; }
	bool IsBwdSeekable() const { return _flags & Flag::BwdSeekable; }
	bool IsReadable() const { return _flags & Flag::Readable; }
	bool IsWritable() const { return _flags & Flag::Writable; }
	void SetCodec(Codec* pCodec) { _pCodec.reset(pCodec); }
	Codec& GetCodec() const { return *_pCodec; }
	virtual char GetChar() override;
	String ReadChar();
	bool PutChar(char ch);
	Stream& Print(const char* str);
	Stream& Print(StringPicker&& strPicker);
	Stream& Print(const StringList& strList) { return Print(StringPicker_StringList(strList)); }
	Stream& Print(const ValueList& valueList) { return Print(StringPicker_ValueList(valueList)); }
	Stream& Println(const char* str);
	Stream& Println(StringPicker&& strPicker);
	Stream& Println(const StringList& strList) { return Println(StringPicker_StringList(strList)); }
	Stream& Println(const ValueList& valueList) { return Println(StringPicker_ValueList(valueList)); }
	Stream& Println() { PutChar('\n'); return *this; }
	Stream& PrintfV(const char* format, va_list ap);
	Stream& Printf(const char* format, ...);
	Stream& PrintFmt(const char* format, const ValueList& valueList);
	bool ReadLine(String& str, bool includeEOLFlag);
	Iterator* ReadLines(bool includeEOLFlag);
	static OpenFlags ModeToOpenFlags(const char* mode);
	void Dump(const void* buff, size_t bytes, const StringStyle& ss = StringStyle::Empty);
	virtual bool IsDumb() const { return false; }
	virtual const char* GetName() const = 0;
	virtual const char* GetIdentifier() const = 0;
	virtual void Close() = 0;
	virtual size_t Read(void* buff, size_t len) = 0;
	virtual size_t Write(const void* buff, size_t len) = 0;
	virtual void Flush() = 0;
protected:
	virtual int DoGetChar() = 0;
	virtual bool DoPutChar(char ch) = 0;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Stream& stream) const { return this == &stream; }
	bool IsEqualTo(const Stream& stream) const { return IsIdentical(stream); }
	bool IsLessThan(const Stream& stream) const { return this < &stream; }
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Iterator_ReadLines
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_ReadLines : public Iterator {
private:
	RefPtr<Stream> _pStream;
	bool _includeEOLFlag;
	bool _doneFlag;
public:
	Iterator_ReadLines(Stream* pStream, bool includeEOLFlag);
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

}

#endif
