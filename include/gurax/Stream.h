//==============================================================================
// Stream.h
//==============================================================================
#ifndef GURAX_STREAM_H
#define GURAX_STREAM_H
#include "DateTime.h"
#include "Formatter.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stream : public Referable {
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
	enum class ErrorType { None, Codec };
	using Flags = UInt32;
	struct Flag {
		static const Flags None			= 0;
		static const Flags Infinite		= (1 << 0);
		static const Flags BwdSeekable	= (1 << 1);
		static const Flags Readable		= (1 << 2);
		static const Flags Writable		= (1 << 3);
		static const Flags Append		= (1 << 4);
	};
	struct Info {
	public:
		//DateTime atime;
		//DateTime mtime;
		//DateTime ctime;
		Int32 uid;
		Int32 gid;
		Flags flags;
		Flags flagsMask;
	public:
		inline Info() : uid(0), gid(0), flags(Flag::None), flagsMask(Flag::None) {}
	};
public:
	static RefPtr<Stream> CIn;
	static RefPtr<Stream> COut;
	static RefPtr<Stream> CErr;
public:
	// Constructor
	Stream() {}
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
	static void Bootup();
	Stream& Print(const char* str);
	Stream& Print(const StringList& strList);
	Stream& Print(const ValueList& valueList);
	Stream& Println(const char* str);
	Stream& Println(const StringList& strList);
	Stream& Println(const ValueList& valueList);
	Stream& Println() { PutChar('\n'); return *this; }
	Stream& PrintfV(const char* format, va_list ap);
	Stream& Printf(const char* format, ...);
	Stream& PrintFmt(const char* format, const ValueList& valueList);
	bool ReadLine(String& str, bool includeEOLFlag);
	bool ReadLines(StringList& strList, bool includeEOLFlag);
	void Dump(const void* buff, size_t bytes, const StringStyle& ss = StringStyle::Empty);
	virtual const char* GetName() const = 0;
	virtual const char* GetIdentifier() const = 0;
	virtual void Close() = 0;
	virtual int GetChar() = 0;
	virtual bool PutChar(char ch) = 0;
	virtual size_t Read(void* buff, size_t len) = 0;
	virtual size_t Write(const void* buff, size_t len) = 0;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Stream& stream) const { return this == &stream; }
	bool IsEqualTo(const Stream& stream) const { return IsIdentical(stream); }
	bool IsLessThan(const Stream& stream) const { return this < &stream; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(stream)"; }
};

}

#endif
