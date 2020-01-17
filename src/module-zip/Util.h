//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_UTIL_H
#define GURAX_MODULE_ZIP_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(zip)

class StatEx;

UInt16 SymbolToCompressionMethod(const Symbol* pSymbol);
UInt16 GetDosTime(const DateTime& dt);
UInt16 GetDosDate(const DateTime& dt);
DateTime* MakeDateTimeFromDos(UInt16 dosDate, UInt16 dosTime);

UInt32 SeekCentralDirectory(Stream& streamSrc);
Directory* CreateDirectory(Stream& streamSrc, Directory* pParent,
						   const char** pPathName, Directory::Type typeWouldBe);
Stream* CreateStream(Stream& streamSrc, const StatEx& statEx);

bool SkipStream(Stream& stream, size_t bytes);
bool ReadStream(Stream& stream, void* buff, size_t bytes, size_t offset = 0);
bool ReadStream(Stream& stream, UInt32* pSignature);
bool ReadStream(Stream& stream, Binary& binary, size_t bytes);
bool WriteStream(Stream& stream, void* buff, size_t bytes);
bool WriteStream(Stream& stream, Binary& binary);

Gurax_EndModuleScope(zip)

#endif
