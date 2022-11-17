//==============================================================================
// Accumulator.h
//==============================================================================
#ifndef GURAX_MODULE_HASH_ACCUMULATOR_H
#define GURAX_MODULE_HASH_ACCUMULATOR_H
#include <gurax.h>
extern "C" {
#include "md5.h"
#include "sha1.h"
}

Gurax_BeginModuleScope(hash)

//------------------------------------------------------------------------------
// Accumulator
//------------------------------------------------------------------------------
class Accumulator : public Stream {
protected:
	Binary _digest;
public:
	Accumulator() : Stream(Flag::Writable) {}
public:
	virtual const char* GetName() const override { return "accumulator"; };
	virtual const char* GetIdentifier() const override { return ""; }
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override { return 0; }
	virtual bool DoPutChar(char ch) override { return true; }
	virtual size_t DoRead(void* buff, size_t len) override { return 0; }
	virtual bool DoWrite(const void* buff, size_t len) override { return true; }
	virtual bool DoFlush() override { return true; }
public:
	const Binary& GetDigest();
	String GetDigestHex(bool upperFlag);
public:
	virtual void Initialize() = 0;
	virtual void Finish() = 0;
	virtual Value* GetValue() { return Value::nil(); }
};

//-----------------------------------------------------------------------------
// Accumulator_CRC32
//-----------------------------------------------------------------------------
class Accumulator_CRC32 : public Accumulator {
private:
	CRC32 _crc32;
public:
	Accumulator_CRC32();
public:
	virtual const char *GetName() const;
	virtual bool DoWrite(const void* buff, size_t len);
public:
	virtual void Initialize();
	virtual void Finish();
	virtual Value* GetValue();
};

//-----------------------------------------------------------------------------
// Accumulator_MD5
//-----------------------------------------------------------------------------
class Accumulator_MD5 : public Accumulator {
private:
	md5_state_t _state;
public:
	Accumulator_MD5();
public:
	virtual const char *GetName() const;
	virtual bool DoWrite(const void* buff, size_t len);
public:
	virtual void Initialize();
	virtual void Finish();
};

//-----------------------------------------------------------------------------
// Accumulator_SHA1
//-----------------------------------------------------------------------------
class Accumulator_SHA1 : public Accumulator {
private:
	sha1_context _ctx;
public:
	Accumulator_SHA1();
public:
	virtual const char *GetName() const;
	virtual bool DoWrite(const void* buff, size_t len);
public:
	virtual void Initialize();
	virtual void Finish();
};

Gurax_EndModuleScope(hash)

#endif
