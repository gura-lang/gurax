//==============================================================================
// ImageMgr.h
//==============================================================================
#ifndef GURAX_IMAGEMGR_H
#define GURAX_IMAGEMGR_H
#include "Referable.h"

namespace Gurax {

class Image;
class Stream;

//------------------------------------------------------------------------------
// ImageMgr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgr : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ImageMgr);
protected:
	String _imgTypeName;
public:
	// Constructor
	ImageMgr(String imgTypeName) : _imgTypeName(imgTypeName) {}
	// Copy constructor/operator
	ImageMgr(const ImageMgr& src) = delete;
	ImageMgr& operator=(const ImageMgr& src) = delete;
	// Move constructor/operator
	ImageMgr(ImageMgr&& src) = delete;
	ImageMgr& operator=(ImageMgr&& src) noexcept = delete;
protected:
	virtual ~ImageMgr() = default;
public:
	const char* GetImgTypeName() const { return _imgTypeName.c_str(); }
public:
	virtual bool IsResponsible(Stream& stream) const = 0;
	virtual bool Read(Stream& stream, Image& image) const = 0;
	virtual bool Write(Stream& stream, const Image& image) const = 0;
public:
	static void Assign(ImageMgr* pImageMgr);
	static const ImageMgr* Find(Stream& stream, const char* imgTypeName);
};

//------------------------------------------------------------------------------
// ImageMgrList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgrList : public std::vector<ImageMgr*> {
public:
	const ImageMgr* FindResponsible(Stream& stream) const;
	const ImageMgr* FindByImgTypeName(const char* imgTypeName) const;
};

//------------------------------------------------------------------------------
// ImageMgrOner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgrOwner : public ImageMgrList {
public:
	~ImageMgrOwner() { Clear(); }
	void Clear();
};

}

#endif
