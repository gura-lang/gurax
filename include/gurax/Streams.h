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
class GURAX_DLLDECLARE Stream_Dumb : public Stream {
public:
	Stream_Dumb() : Stream(Flag::Readable | Flag::Writable) {}
public:
	virtual bool IsDumb() const override { return true; }
	virtual const char* GetName() const override { return "dumb"; };
	virtual const char* GetIdentifier() const override { return "dumb"; }
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override { return 0; }
	virtual bool DoPutChar(char ch) override { return true; }
	virtual size_t DoRead(void* buff, size_t len) override { ::memset(buff, 0x00, len); return len; }
	virtual size_t DoWrite(const void* buff, size_t len) override { return len; }
	virtual bool DoFlush() override { return true; }
};

//------------------------------------------------------------------------------
// Stream_Console
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stream_Console : public Stream {
private:
	FILE* _fp;
	String _name;
public:
	Stream_Console(Flags flags, FILE* fp, String name) : Stream(flags),  _fp(fp), _name(name) {}
public:
	virtual const char* GetName() const override { return _name.c_str(); };
	virtual const char* GetIdentifier() const override { return _name.c_str(); }
	virtual bool DoClose() override { return ::fclose(_fp) == 0; }
	virtual int DoGetChar() override { return ::fgetc(_fp); }
	virtual bool DoPutChar(char ch) override { ::fputc(ch, _fp); return true; }
	virtual size_t DoRead(void* buff, size_t len) override {
		return ::fread(buff, 1, len, _fp);
	}
	virtual size_t DoWrite(const void* buff, size_t len) override {
		return ::fwrite(buff, 1, len, _fp);
	}
	virtual bool DoFlush() override { return ::fflush(_fp) == 0; }
};

//------------------------------------------------------------------------------
// Stream_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stream_Binary : public Stream {
private:
	RefPtr<BinaryReferable> _pBuff;
public:
	Stream_Binary(Flags flags, BinaryReferable* pBuff, size_t offset = 0);
	Stream_Binary(Flags flags);
public:
	Binary& GetBuff() { return _pBuff->GetBinary(); }
	BinaryReferable& GetBuffReferable() { return *_pBuff; }
public:
	virtual bool IsDumb() const override { return false; }
	virtual const char* GetName() const override { return "binary"; };
	virtual const char* GetIdentifier() const override { return "binary"; }
	virtual size_t DoGetBytes() override;
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override;
	virtual bool DoPutChar(char ch) override;
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual size_t DoWrite(const void* buff, size_t len) override;
	virtual bool DoFlush() override { return true; }
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

}

#endif
