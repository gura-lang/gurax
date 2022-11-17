//==============================================================================
// ImageMgrCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ImageMgrCustom
//------------------------------------------------------------------------------
ImageMgrCustom::ImageMgrCustom(String imgTypeName, String description, StringList extNameTbl,
			Processor* pProcessor, Function* pFuncRead, Function* pFuncWrite) :
	ImageMgr(imgTypeName, description), _extNameTbl(extNameTbl),
	_pProcessor(pProcessor), _pFuncRead(pFuncRead), _pFuncWrite(pFuncWrite)
{
}

bool ImageMgrCustom::IsResponsible(Stream& stream) const
{
	::printf("check\n");
	return false;
}

bool ImageMgrCustom::IsResponsibleExtName(const char* extName) const
{
	for (const String& extNameReg : _extNameTbl) {
		if (::strcasecmp(extName, extNameReg.c_str()) == 0) return true;
	}
	return false;
}

bool ImageMgrCustom::Read(Stream& stream, Image& image) const
{
	if (!_pFuncRead) {
		Error::Issue(ErrorType::InvalidOperation, "can't read image data of %s", GetImgTypeName());
		return false;
	}
	Value::Delete(_pFuncRead->EvalEasy(*_pProcessor, new Value_Stream(stream.Reference()), new Value_Image(image.Reference())));
	return !Error::IsIssued();
}

bool ImageMgrCustom::Write(Stream& stream, const Image& image) const
{
	if (!_pFuncWrite) {
		Error::Issue(ErrorType::InvalidOperation, "can't write image data of %s", GetImgTypeName());
		return false;
	}
	Value::Delete(_pFuncWrite->EvalEasy(*_pProcessor, new Value_Stream(stream.Reference()), new Value_Image(image.Reference())));
	return !Error::IsIssued();
}

}
