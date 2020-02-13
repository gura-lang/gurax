//==============================================================================
// ImageMgr.h
//==============================================================================
#ifndef GURAX_IMAGEMGR_H
#define GURAX_IMAGEMGR_H
#include "Image.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ImageMgr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgr : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ImageMgr);
protected:
	String _typeName;
public:
	// Constructor
	ImageMgr(String typeName) : _typeName(typeName) {}
	// Copy constructor/operator
	ImageMgr(const ImageMgr& src) = delete;
	ImageMgr& operator=(const ImageMgr& src) = delete;
	// Move constructor/operator
	ImageMgr(ImageMgr&& src) = delete;
	ImageMgr& operator=(ImageMgr&& src) noexcept = delete;
protected:
	virtual ~ImageMgr() = default;
public:
	const char* GetTypeName() const { return _typeName.c_str(); }
public:
	virtual bool IsResponsible(Stream& stream) const = 0;
	virtual Image* Read(Stream& stream) const = 0;
	virtual bool Write(Stream& stream, const Image& image) const = 0;
	
public:
	static void Assign(ImageMgr* pImageMgr);
	static const ImageMgr* FindResponsible(Stream& stream);
	static const ImageMgr* FindByTypeName(const char* typeName);
};

//------------------------------------------------------------------------------
// ImageMgrList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgrList : public std::vector<ImageMgr*> {
public:
	const ImageMgr* FindResponsible(Stream& stream) const;
	const ImageMgr* FindByTypeName(const char* typeName) const;
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
