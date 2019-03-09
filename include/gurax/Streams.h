//==============================================================================
// Streams.h
//==============================================================================
#ifndef GURAX_STREAMS_H
#define GURAX_STREAMS_H
#include "Stream.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream_File
//------------------------------------------------------------------------------
class Stream_File : public Stream {
private:
	FILE* _fp;
	bool _closeAtDeletionFlag;
	String _name;
	String _identifier;
public:
	Stream_File(FILE* fp, bool closeAtDeletionFlag, String name, String identifier) :
		_fp(fp), _closeAtDeletionFlag(closeAtDeletionFlag),
		_name(std::move(name)), _identifier(std::move(identifier)) {}
	Stream_File(FILE* fp, bool closeAtDeletionFlag, String name) :
		Stream_File(fp, closeAtDeletionFlag, name, name) {}
	virtual ~Stream_File() {
		if (_closeAtDeletionFlag) ::fclose(_fp);
	}
	static Stream* Open(const char* fileName, const char* mode);
	virtual void Close() { ::fclose(_fp); }
	virtual const char* GetName() const { return _name.c_str(); };
	virtual const char* GetIdentifier() const { return _identifier.c_str(); }
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
