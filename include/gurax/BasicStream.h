//==============================================================================
// BasicStream.h
//==============================================================================
#ifndef GURAX_BASICSTREAM_H
#define GURAX_BASICSTREAM_H
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
	virtual const char* GetIdentifier() const override { return ""; }
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override { return 0; }
	virtual bool DoPutChar(char ch) override { return true; }
	virtual size_t DoRead(void* buff, size_t len) override { ::memset(buff, 0x00, len); return len; }
	virtual bool DoWrite(const void* buff, size_t len) override { return true; }
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
	virtual const char* GetIdentifier() const override { return ""; }
	virtual bool DoClose() override { return ::fclose(_fp) == 0; }
	virtual int DoGetChar() override { return ::fgetc(_fp); }
	virtual bool DoPutChar(char ch) override { ::fputc(ch, _fp); return true; }
	virtual size_t DoRead(void* buff, size_t len) override {
		return ::fread(buff, 1, len, _fp);
	}
	virtual bool DoWrite(const void* buff, size_t len) override {
		return ::fwrite(buff, 1, len, _fp) == len;
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
	Stream_Binary(Flags flags, Codec* pCodec, BinaryReferable* pBuff, size_t offset = 0);
	Stream_Binary(Flags flags);
	Stream_Binary(Flags flags, Codec* pCodec);
public:
	Binary& GetBuff() { return _pBuff->GetBinary(); }
	BinaryReferable& GetBuffReferable() { return *_pBuff; }
	void ClearBuff() { GetBuff().clear(); _offset = 0; }
public:
	virtual const char* GetName() const override { return "binary"; };
	virtual const char* GetIdentifier() const override { return ""; }
	virtual size_t DoGetBytes() override;
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override;
	virtual bool DoPutChar(char ch) override;
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoWrite(const void* buff, size_t len) override;
	virtual bool DoFlush() override { return true; }
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

//------------------------------------------------------------------------------
// Stream_StringReader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stream_StringReader : public Stream {
private:
	RefPtr<StringReferable> _pStr;
public:
	Stream_StringReader(StringReferable* pStr);
public:
	virtual const char* GetName() const override { return "String"; };
	virtual const char* GetIdentifier() const override { return ""; }
	virtual size_t DoGetBytes() override;
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override;
	virtual bool DoPutChar(char ch) override { return false; }
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoWrite(const void* buff, size_t len) override { return false; }
	virtual bool DoFlush() override { return false; }
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

#if 0
//------------------------------------------------------------------------------
// Stream_Pointer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stream_Pointer : public Stream {
private:
	RefPtr<Pointer> _pPointer;
public:
	Stream_Pointer(Flags flags, Pointer* pPointer);
public:
	Pointer& GetPointer() { return *_pPointer; }
public:
	virtual const char* GetName() const override { return "pointer"; };
	virtual const char* GetIdentifier() const override { return ""; }
	virtual size_t DoGetBytes() override { return GetPointer().GetBytesEntire(); }
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override;
	virtual bool DoPutChar(char ch) override;
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoWrite(const void* buff, size_t len) override;
	virtual bool DoFlush() override { return true; }
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};
#endif

//------------------------------------------------------------------------------
// Stream_FIFO
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Stream_FIFO : public Stream {
private:
	RefPtr<Memory> _pMemory;
	size_t _offsetWrite;
	size_t _offsetRead;
	size_t _bytesAvail;
	bool _brokenFlag;
	OAL::Semaphore _semaphore;
public:
	Stream_FIFO(size_t bytesBuff);
public:
	virtual const char* GetName() const override { return "FIFO"; };
	virtual const char* GetIdentifier() const override { return ""; }
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override { return 0; }
	virtual bool DoPutChar(char ch) override { return true; }
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoWrite(const void* buff, size_t len) override;
	virtual bool DoFlush() override { return true; }
};

}

#endif
