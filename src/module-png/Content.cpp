//==============================================================================
// Content.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(png)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
Content::~Content()
{
	::png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
}

bool Content::Read(Stream& stream)
{
	Handler handler(stream);
	png_ptr = ::png_create_read_struct(
			PNG_LIBPNG_VER_STRING, nullptr, Handler::Error, Handler::Warning);
	info_ptr = ::png_create_info_struct(png_ptr);
	if (::setjmp(png_jmpbuf(png_ptr))) {
		::png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		return false;
	}
	::png_set_read_fn(png_ptr, &handler, Handler::ReadData);
	::png_read_info(png_ptr, info_ptr);
	return !Error::IsIssued();
}

String Content::ToString(const StringStyle& ss) const
{
	return "png.Content";
}

Gurax_EndModuleScope(png)
