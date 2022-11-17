//==============================================================================
// ImageMgrCustom.h
//==============================================================================
#ifndef GURAX_IMAGEMGRCUSTOM_H
#define GURAX_IMAGEMGRCUSTOM_H
#include "ImageMgr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ImageMgrCustom
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ImageMgrCustom : public ImageMgr {
private:
	StringList _extNameTbl;
	RefPtr<Processor> _pProcessor;
	RefPtr<Function> _pFuncRead;
	RefPtr<Function> _pFuncWrite;
public:
	ImageMgrCustom(String imgTypeName, String description, StringList extNameTbl,
				Processor* pProcessor, Function* pFuncRead, Function* pFuncWrite);
public:
	virtual bool IsResponsible(Stream& stream) const override;
	virtual bool IsResponsibleExtName(const char* extName) const override;
	virtual bool Read(Stream& stream, Image& image) const override;
	virtual bool Write(Stream& stream, const Image& image) const override;
};

}

#endif
