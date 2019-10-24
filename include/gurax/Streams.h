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
	Stream_Dumb() : Stream(Flag::Readable | Flag::Writable) {}
	virtual bool IsDumb() const override { return true; }
	virtual const char* GetName() const override { return "dumb"; };
	virtual const char* GetIdentifier() const override { return "dumb"; }
	virtual void Close() override {}
	virtual int DoGetChar() override { return 0; }
	virtual bool DoPutChar(char ch) override { return true; }
	virtual size_t Read(void* buff, size_t len) override { ::memset(buff, 0x00, len); return len; }
	virtual size_t Write(const void* buff, size_t len) override { return len; }
};

//------------------------------------------------------------------------------
// Stream_Console
//------------------------------------------------------------------------------
class Stream_Console : public Stream {
private:
	FILE* _fp;
	String _name;
public:
	Stream_Console(Flags flags, FILE* fp, String name) : Stream(flags),  _fp(fp), _name(name) {}
	virtual const char* GetName() const override { return _name.c_str(); };
	virtual const char* GetIdentifier() const override { return _name.c_str(); }
	virtual void Close() override { ::fclose(_fp); }
	virtual int DoGetChar() override { return ::fgetc(_fp); }
	virtual bool DoPutChar(char ch) override { ::fputc(ch, _fp); return true; }
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
public:
	Binary& GetBuff() { return _pBuff->GetBinary(); }
	BinaryReferable& GetBuffReferable() { return *_pBuff; }
public:
	virtual bool IsDumb() const override { return false; }
	virtual const char* GetName() const override { return "binary"; };
	virtual const char* GetIdentifier() const override { return "binary"; }
	virtual void Close() override {}
	virtual int DoGetChar() override;
	virtual bool DoPutChar(char ch) override;
	virtual size_t Read(void* buff, size_t len) override;
	virtual size_t Write(const void* buff, size_t len) override;
};

}

#endif
