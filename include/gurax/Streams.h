//==============================================================================
// Streams.h
//==============================================================================
#ifndef GURAX_STREAMS_H
#define GURAX_STREAMS_H
#include "Stream.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Stream_Dumb
//------------------------------------------------------------------------------
class Stream_Dumb : public Stream {
public:
	Stream_Dumb() {}
	virtual bool IsDumb() const override { return true; }
	virtual const char* GetName() const override { return "dumb"; };
	virtual const char* GetIdentifier() const override { return "dumb"; }
	virtual void Close() override {}
	virtual int GetChar() override { return 0; }
	virtual bool PutChar(char ch) override { return true; }
	virtual size_t Read(void* buff, size_t len) override { ::memset(buff, 0x00, len); return len; }
	virtual size_t Write(const void* buff, size_t len) override { return len; }
};

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
	virtual const char* GetName() const override { return _name.c_str(); };
	virtual const char* GetIdentifier() const override { return _identifier.c_str(); }
	virtual void Close() override { ::fclose(_fp); }
	virtual int GetChar() override { return ::fgetc(_fp); }
	virtual bool PutChar(char ch) override { ::fputc(ch, _fp); return true; }
	virtual size_t Read(void* buff, size_t len) override {
		return ::fread(buff, 1, len, _fp);
	}
	virtual size_t Write(const void* buff, size_t len) override {
		return ::fwrite(buff, 1, len, _fp);
	}
};

//------------------------------------------------------------------------------
// Stream_Binary
//------------------------------------------------------------------------------
class Stream_Binary : public Stream {
private:
	RefPtr<BinaryReferable> _pBuff;
	size_t _offset;
public:
	Stream_Binary(BinaryReferable* pBuff, size_t offset);
	Stream_Binary();
	virtual bool IsDumb() const override { return false; }
	virtual const char* GetName() const override { return "binary"; };
	virtual const char* GetIdentifier() const override { return "binary"; }
	virtual void Close() override {}
	virtual int GetChar() override;
	virtual bool PutChar(char ch) override;
	virtual size_t Read(void* buff, size_t len) override;
	virtual size_t Write(const void* buff, size_t len) override;
};

}

#endif
