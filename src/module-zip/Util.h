//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_UTIL_H
#define GURAX_MODULE_ZIP_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(zip)

class StatEx;
class EndOfCentralDirectoryRecord;

UInt16 SymbolToCompressionMethod(const Symbol* pSymbol);
const Symbol* CompressionMethodToSymbol(UInt16 compressionMethod);
UInt16 GetDosTime(const DateTime& dt);
UInt16 GetDosDate(const DateTime& dt);
DateTime* MakeDateTimeFromDos(UInt16 dosDate, UInt16 dosTime);

UInt32 SeekCentralDirectory(Stream& streamSrc, EndOfCentralDirectoryRecord* pRecord = nullptr);
bool InspectDescriptor(Stream& streamCon, Stream& streamSrc);

bool SkipStream(Stream& stream, size_t bytes);
bool ReadStream(Stream& stream, void* buff, size_t bytes, size_t offset = 0);
bool ReadStream(Stream& stream, UInt32* pSignature);
bool ReadStream(Stream& stream, Binary& binary, size_t bytes);
bool WriteStream(Stream& stream, const void* buff, size_t bytes);
bool WriteStream(Stream& stream, const Binary& binary);

Gurax_EndModuleScope(zip)

#endif
