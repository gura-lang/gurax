//==============================================================================
// TARFormat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

const int BLOCKSIZE			= 512;

const char *TMAGIC			= "ustar";	// ustar and a null
const int TMAGLEN			= 6;
const char *TVERSION		= "00";		// 00 and no null
const int TVERSLEN			= 2;

// Values used in typeflag field.
const char REGTYPE			= '0';		// regular file
const char AREGTYPE			= '\0';		// regular file
const char LNKTYPE			= '1';		// link
const char SYMTYPE			= '2';		// reserved
const char CHRTYPE			= '3';		// character special
const char BLKTYPE			= '4';		// block special
const char DIRTYPE			= '5';		// directory
const char FIFOTYPE			= '6';		// FIFO special
const char CONTTYPE			= '7';		// reserved
const char XHDTYPE			= 'x';		// Extended header referring to the next file in the archive
const char XGLTYPE			= 'g';		// Global extended header

// Bits used in the mode field, values in octal. 
const UInt32 TSUID			= 04000;	// set UID on execution
const UInt32 TSGID			= 02000;	// set GID on execution
const UInt32 TSVTX			= 01000;	// reserved
										// file permissions
const UInt32 TUREAD			= 00400;	// read by owner
const UInt32 TUWRITE		= 00200;	// write by owner
const UInt32 TUEXEC			= 00100;	// execute/search by owner
const UInt32 TGREAD			= 00040;	// read by group
const UInt32 TGWRITE		= 00020;	// write by group
const UInt32 TGEXEC			= 00010;	// execute/search by group
const UInt32 TOREAD			= 00004;	// read by other
const UInt32 TOWRITE		= 00002;	// write by other
const UInt32 TOEXEC			= 00001;	// execute/search by other

//-----------------------------------------------------------------------------
// Header
//-----------------------------------------------------------------------------
Header* Header::Read(Stream& stream)
{
	char buffBlock[BLOCKSIZE];
	int nTerminator = 0;
	for (;;) {
		size_t bytesRead = stream.Read(buffBlock, BLOCKSIZE);
		if (Error::IsIssued()) return nullptr;
		if (bytesRead < BLOCKSIZE) {
			Error::Issue(ErrorType::FormatError, "failed to read a block");
			return nullptr;
		}
		bool zeroBlockFlag = true;
		UInt32* p = reinterpret_cast<UInt32 *>(buffBlock);
		for (int i = 0; i < BLOCKSIZE / sizeof(UInt32); i++, p++) {
			if (*p != 0x00000000) {
				zeroBlockFlag = false;
				break;
			}
		}
		if (!zeroBlockFlag) break;
		nTerminator++;
		if (nTerminator == 2) return nullptr;
	}
	star_header &hdr = *reinterpret_cast<star_header *>(buffBlock);
	::printf("%s\n", hdr.name);
	std::unique_ptr<Header> pHdr(new Header());
	//pHdr->SetOffset(pStream->Tell());
	//if (!pHdr->SetRawHeader(sig, hdr)) return nullptr;
	return pHdr.release();
}

Gurax_EndModuleScope(tar)
