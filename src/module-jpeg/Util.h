//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_UTIL_H
#define GURAX_MODULE_JPEG_UTIL_H
#include <gurax.h>
#define HAVE_BOOLEAN
using boolean = bool;
extern "C" {
#include <jpeglib.h>
#include <jerror.h>
#include <setjmp.h>
}

Gurax_BeginModuleScope(jpeg)

//-----------------------------------------------------------------------------
// ErrorMgr
//-----------------------------------------------------------------------------
struct ErrorMgr {
	jpeg_error_mgr pub;
	jmp_buf jmpenv;
public:
	bool Initialize(jpeg_compress_struct& cinfo);
	bool Initialize(jpeg_decompress_struct& cinfo);
public:
	static void error_exit(j_common_ptr cinfo);
};

//-----------------------------------------------------------------------------
// SourceMgr
//-----------------------------------------------------------------------------
struct SourceMgr {
	jpeg_source_mgr pub;
	Stream* pStream;
	JOCTET* buff;
	bool firstFlag;
public:
	static const size_t BuffSize = 4096;
	static void Setup(j_decompress_ptr cinfo, Stream& stream);
	static void init_source(j_decompress_ptr cinfo);
	static boolean fill_input_buffer(j_decompress_ptr cinfo);
	static void skip_input_data(j_decompress_ptr cinfo, long num_bytes);
	static void term_source(j_decompress_ptr cinfo);
};

//-----------------------------------------------------------------------------
// DestinationMgr
//-----------------------------------------------------------------------------
struct DestinationMgr {
	jpeg_destination_mgr pub;
	Stream* pStream;
	JOCTET* buffer;
public:
	static const size_t BuffSize = 4096;
	static void Setup(j_compress_ptr cinfo, Stream& stream);
	static void init_destination(j_compress_ptr cinfo);
	static boolean empty_output_buffer(j_compress_ptr cinfo);
	static void term_destination(j_compress_ptr cinfo);
};

Gurax_EndModuleScope(jpeg)

#endif
