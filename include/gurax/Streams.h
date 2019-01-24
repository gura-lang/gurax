//==============================================================================
// Streams.h
//==============================================================================
#ifndef GURAX_STREAMS_H
#define GURAX_STREAMS_H
#include "Stream.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream_Console
//------------------------------------------------------------------------------
class Stream_Console : public Stream {
private:
	String _name;
	FILE* _fp;
public:
	Stream_Console(String name, FILE* fp) : _name(std::move(name)), _fp(fp) {}
	virtual const char* GetName() const { return _name.c_str(); };
	virtual const char* GetIdentifier() const { return _name.c_str(); }
	virtual int GetChar() { return ::fgetc(_fp); }
	virtual bool PutChar(char ch) { ::fputc(ch, _fp); return true; }
	virtual size_t Read(void* buff, size_t len) {
		return ::fread(buff, 1, len, _fp);
	}
	virtual size_t Write(const void* buff, size_t len) {
		return ::fwrite(buff, 1, len, _fp);
	}
};

}

#endif
