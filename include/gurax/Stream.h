//==============================================================================
// Stream.h
//==============================================================================
#ifndef GURAX_STREAM_H
#define GURAX_STREAM_H
#include "Formatter.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stream : public Referable {
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
public:
	// Referable declaration
	Gurax_DeclareReferable(Stream);
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
	void Print(const char* str);
	void Println(const char* str);
	void Printf(const char* format, ...);
	void PrintFmt(const char* format, const ObjectList& objectList);
	bool ReadLine(String& str, bool includeEOLFlag);
	bool ReadLines(StringList& strList, bool includeEOLFlag);
	void Dump(const void* buff, size_t bytes, bool upperFlag = false);
	virtual const char* GetName() const = 0;
	virtual const char* GetIdentifier() const = 0;
	virtual int GetChar() = 0;
	virtual bool PutChar(char ch) = 0;
	virtual size_t Read(void* buff, size_t len) = 0;
	virtual size_t Write(const void* buff, size_t len) = 0;
};

}

#endif
