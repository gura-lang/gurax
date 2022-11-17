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
	String _description;
public:
	// Constructor
	ImageMgr(String imgTypeName, String description) :
			_imgTypeName(imgTypeName), _description(description) {}
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
	const char* GetDescription() const { return _description.c_str(); }
public:
	virtual bool IsResponsible(Stream& stream) const = 0;
	virtual bool IsResponsibleExtName(const char* extName) const = 0;
	virtual bool Read(Stream& stream, Image& image) const = 0;
	virtual bool Write(Stream& stream, const Image& image) const = 0;
public:
	static void Assign(ImageMgr* pImageMgr);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ImageMgr& imageMgr) const { return this == &imageMgr; }
	bool IsEqualTo(const ImageMgr& imageMgr) const { return IsIdentical(imageMgr); }
	bool IsLessThan(const ImageMgr& imageMgr) const { return this < &imageMgr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ImageMgrList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgrList : public ListBase<ImageMgr*> {
public:
	const ImageMgr* FindResponsible(Stream& stream) const;
	const ImageMgr* FindByImgTypeName(const char* imgTypeName) const;
	const ImageMgr* FindByFileName(const char* fileName) const;
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
