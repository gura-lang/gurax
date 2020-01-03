//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_UTIL_H
#define GURAX_MODULE_ZIP_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(zip)
#if 0
UInt16 SymbolToCompressionMethod(const Symbol *pSymbol);
UInt16 GetDosTime(const DateTime &dt);
UInt16 GetDosDate(const DateTime &dt);
DateTime MakeDateTimeFromDos(UInt16 dosDate, UInt16 dosTime);
bool IsMatchedName(const char *name1, const char *name2);

UInt32 SeekCentralDirectory(Signal &sig, Stream *pStream);
Directory *CreateDirectory(Environment &env, Stream *pStreamSrc,
	Directory *pParent, const char **pPathName, PathMgr::NotFoundMode notFoundMode);
Stream *CreateStream(Environment &env, Stream *pStreamSrc, const CentralFileHeader *pHdr);

bool SkipStream(Signal &sig, Stream &stream, size_t bytes);
bool ReadStream(Signal &sig, Stream &stream, void *buff, size_t bytes, size_t offset = 0);
bool ReadStream(Signal &sig, Stream &stream, UInt32 *pSignature);
bool ReadStream(Signal &sig, Stream &stream, Binary &binary, size_t bytes);
bool WriteStream(Signal &sig, Stream &stream, void *buff, size_t bytes);
bool WriteStream(Signal &sig, Stream &stream, Binary &binary);
#endif

Gurax_EndModuleScope(zip)

#endif
