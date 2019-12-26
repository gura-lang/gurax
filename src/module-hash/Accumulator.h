//==============================================================================
// Accumulator.h
//==============================================================================
#ifndef GURAX_MODULE_HASH_ACCUMULATOR_H
#define GURAX_MODULE_HASH_ACCUMULATOR_H
#include <gurax.h>

Gurax_BeginModuleScope(hash)

//------------------------------------------------------------------------------
// Accumulator
//------------------------------------------------------------------------------
class Accumulator : public Stream {
public:
	Accumulator() : Stream(Flag::Writable) {}
public:
	virtual const char* GetName() const override { return "accumulator"; };
	virtual const char* GetIdentifier() const override { return "accumulator"; }
	virtual bool DoClose() override { return true; }
	virtual int DoGetChar() override { return 0; }
	virtual bool DoPutChar(char ch) override { return true; }
	virtual size_t DoRead(void* buff, size_t len) override { return 0; }
	virtual size_t DoWrite(const void* buff, size_t len) override { return len; }
	virtual bool DoFlush() override { return true; }
};

Gurax_EndModuleScope(hash)

#endif
