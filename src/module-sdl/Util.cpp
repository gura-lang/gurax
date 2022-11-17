//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

Sint64 RWsize_Stream(SDL_RWops* context)
{
	Stream* pStream = reinterpret_cast<Stream*>(context->hidden.unknown.data1);
	if (pStream->IsInfinite()) return -1;
	return static_cast<Sint64>(pStream->GetBytes());
}

Sint64 RWseek_Stream(SDL_RWops* context, Sint64 offset, int whence)
{
	Stream* pStream = reinterpret_cast<Stream*>(context->hidden.unknown.data1);
	Stream::SeekMode seekMode =
		(whence == RW_SEEK_SET)? Stream::SeekMode::Set :
		(whence == RW_SEEK_CUR)? Stream::SeekMode::Cur :
		(whence == RW_SEEK_END)? Stream::SeekMode::End : Stream::SeekMode::Set;
	return pStream->Seek(offset, seekMode)? 0 : -1;
}

size_t RWread_Stream(SDL_RWops* context, void* ptr, size_t size, size_t maxnum)
{
	Stream* pStream = reinterpret_cast<Stream*>(context->hidden.unknown.data1);
	size_t bytes = size * maxnum;
	if (bytes == 0) return 0;
	return pStream->Read(ptr, size * maxnum) / size;
}

size_t RWwrite_Stream(SDL_RWops* context, const void* ptr, size_t size, size_t num)
{
	Stream* pStream = reinterpret_cast<Stream*>(context->hidden.unknown.data1);
	size_t bytes = size * num;
	if (bytes == 0) return 0;
	return pStream->Write(ptr, bytes)? size : 0;
}

int RWclose_Stream(SDL_RWops* context)
{
	Stream* pStream = reinterpret_cast<Stream*>(context->hidden.unknown.data1);
	SDL_FreeRW(context);
	return pStream->Close()? 0 : -1;
}

SDL_RWops* RWFromStream(Stream* pStream)
{
	SDL_RWops* context = SDL_AllocRW();
	context->size = RWsize_Stream;
	context->seek = RWseek_Stream;
	context->read = RWread_Stream;
	context->write = RWwrite_Stream;
	context->close = RWclose_Stream;
	context->type = SDL_RWOPS_UNKNOWN;
	context->hidden.unknown.data1 = pStream;
	return context;
}

Gurax_EndModuleScope(sdl)
