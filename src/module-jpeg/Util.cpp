//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//-----------------------------------------------------------------------------
// ErrorMgr
//-----------------------------------------------------------------------------
void ErrorMgr::error_exit(j_common_ptr cinfo)
{
	ErrorMgr* pErrMgr = reinterpret_cast<ErrorMgr*>(cinfo->err);
	char buff[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message)(cinfo, buff);
	Error::Issue(ErrorType::FormatError, "%s", buff);
	::longjmp(pErrMgr->jmpenv, 1);
}

//-----------------------------------------------------------------------------
// SourceMgr
//-----------------------------------------------------------------------------
void SourceMgr::Setup(j_decompress_ptr cinfo, Stream& stream)
{
	if (!cinfo->src) {
		cinfo->src = reinterpret_cast<jpeg_source_mgr*>((*cinfo->mem->alloc_small)(
			reinterpret_cast<j_common_ptr>(cinfo), JPOOL_PERMANENT, sizeof(SourceMgr)));
		SourceMgr* pSrcMgr = reinterpret_cast<SourceMgr*>(cinfo->src);
		pSrcMgr->buff = reinterpret_cast<JOCTET *>((*cinfo->mem->alloc_small)(
			reinterpret_cast<j_common_ptr>(cinfo), JPOOL_PERMANENT, BuffSize));
	}
	SourceMgr* pSrcMgr = reinterpret_cast<SourceMgr*>(cinfo->src);
	pSrcMgr->pub.init_source		= init_source;
	pSrcMgr->pub.fill_input_buffer	= fill_input_buffer;
	pSrcMgr->pub.skip_input_data	= skip_input_data;
	pSrcMgr->pub.resync_to_restart	= jpeg_resync_to_restart; // use default method
	pSrcMgr->pub.term_source		= term_source;
	pSrcMgr->pub.bytes_in_buffer	= 0;		// forces fill_input_buffer on first read
	pSrcMgr->pub.next_input_byte	= nullptr;	// until buffer loaded
	pSrcMgr->pStream = &stream;
}

void SourceMgr::init_source(j_decompress_ptr cinfo)
{
	SourceMgr* pSrcMgr = reinterpret_cast<SourceMgr*>(cinfo->src);
	pSrcMgr->firstFlag = true;
}

boolean SourceMgr::fill_input_buffer(j_decompress_ptr cinfo)
{
	SourceMgr& srcMgr = *reinterpret_cast<SourceMgr*>(cinfo->src);
	size_t nbytes = srcMgr.pStream->Read(srcMgr.buff, BuffSize);
	if (nbytes == 0) {
		if (srcMgr.firstFlag) {
			ERREXIT(cinfo, JERR_INPUT_EMPTY);
		}
		WARNMS(cinfo, JWRN_JPEG_EOF);
		srcMgr.buff[0] = 0xff;
		srcMgr.buff[1] = JPEG_EOI;
		nbytes = 2;
	}
	srcMgr.pub.next_input_byte = srcMgr.buff;
	srcMgr.pub.bytes_in_buffer = nbytes;
	srcMgr.firstFlag = false;
	return TRUE;
}

void SourceMgr::skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{
	jpeg_source_mgr* src = cinfo->src;
	if (num_bytes > 0) {
		while (num_bytes > static_cast<long>(src->bytes_in_buffer)) {
			num_bytes -= static_cast<long>(src->bytes_in_buffer);
			(*src->fill_input_buffer)(cinfo);
		}
		src->next_input_byte += num_bytes;
		src->bytes_in_buffer -= num_bytes;
	}
}

void SourceMgr::term_source(j_decompress_ptr cinfo)
{
}

//-----------------------------------------------------------------------------
// DestinationMgr
//-----------------------------------------------------------------------------
void DestinationMgr::Setup(j_compress_ptr cinfo, Stream& stream)
{
	DestinationMgr *pDstMgr = reinterpret_cast<DestinationMgr *>(cinfo->dest);
	if (!cinfo->dest) {
		cinfo->dest = reinterpret_cast<jpeg_destination_mgr *>((*cinfo->mem->alloc_small)(
			reinterpret_cast<j_common_ptr>(cinfo), JPOOL_PERMANENT, sizeof(DestinationMgr)));
		pDstMgr = reinterpret_cast<DestinationMgr *>(cinfo->dest);
	}
	pDstMgr->pub.init_destination		= init_destination;
	pDstMgr->pub.empty_output_buffer	= empty_output_buffer;
	pDstMgr->pub.term_destination		= term_destination;
	pDstMgr->pStream = &stream;
}

void DestinationMgr::init_destination(j_compress_ptr cinfo)
{
	DestinationMgr& dstMgr = *reinterpret_cast<DestinationMgr*>(cinfo->dest);
	dstMgr.buffer = reinterpret_cast<JOCTET *>((*cinfo->mem->alloc_small)(
		reinterpret_cast<j_common_ptr>(cinfo), JPOOL_IMAGE, BuffSize));
	dstMgr.pub.next_output_byte = dstMgr.buffer;
	dstMgr.pub.free_in_buffer = BuffSize;
}

boolean DestinationMgr::empty_output_buffer(j_compress_ptr cinfo)
{
	DestinationMgr& dstMgr = *reinterpret_cast<DestinationMgr*>(cinfo->dest);
	if (!dstMgr.pStream->Write(dstMgr.buffer, BuffSize)) {
		ERREXIT(cinfo, JERR_FILE_WRITE);
	}
	dstMgr.pub.next_output_byte = dstMgr.buffer;
	dstMgr.pub.free_in_buffer = BuffSize;
	return TRUE;
}

void DestinationMgr::term_destination(j_compress_ptr cinfo)
{
	DestinationMgr& dstMgr = *reinterpret_cast<DestinationMgr*>(cinfo->dest);
	size_t nbytes = BuffSize - dstMgr.pub.free_in_buffer;
	if (nbytes > 0) {
		if (!dstMgr.pStream->Write(dstMgr.buffer, nbytes)) {
			ERREXIT(cinfo, JERR_FILE_WRITE);
		}
	}
}

//-----------------------------------------------------------------------------
// utility functions
//-----------------------------------------------------------------------------
void IssueError_InvalidFormat()
{
	Error::Issue(ErrorType::FormatError, "invalid format of jpeg file");
}

Gurax_EndModuleScope(jpeg)
