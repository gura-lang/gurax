//==============================================================================
// Accumulator.h
//==============================================================================
#ifndef GURAX_MODULE_HASH_ACCUMULATOR_H
#define GURAX_MODULE_HASH_ACCUMULATOR_H
#include <gurax.h>
#include "md5.h"

Gurax_BeginModuleScope(hash)

//------------------------------------------------------------------------------
// Accumulator
//------------------------------------------------------------------------------
class Accumulator : public Stream {
protected:
	Binary _digest;
public:
	Accumulator() : Stream(Flag::Writable), _digest(true) {}
public:
	virtual const char* GetName() const override { return "accumulator"; };
	virtual const char* GetIdentifier() const override { return "accumulator"; }
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override { return 0; }
	virtual bool DoPutChar(char ch) override { return true; }
	virtual size_t DoRead(void* buff, size_t len) override { return 0; }
	virtual size_t DoWrite(const void* buff, size_t len) override { return len; }
	virtual bool DoFlush() override { return true; }
public:
	virtual void Initialize() = 0;
	virtual void Finish() = 0;
	virtual const Binary& GetDigest() = 0;
	//virtual const Value& GetValue();
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
	virtual size_t DoWrite(const void* buff, size_t len);
public:
	virtual void Initialize();
	virtual void Finish();
	virtual const Binary& GetDigest();
};

Gurax_EndModuleScope(hash)

#endif
